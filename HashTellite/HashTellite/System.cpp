// Librairies
#include "System.h"
#include <map>
#include <set>
#include <iostream>
#include <algorithm>


/**
*	Constructeur de la classe System
*	@param nb_turns
*			Nombre de tours de simulation
*/
System::System(unsigned long nb_turns)
{
	this->nb_turns = nb_turns;
}

/**
*	Constructeur de la classe System
*	@param nb_turns
*			Nombre de tours de simulation
*	@param c
*			Liste de collections
*	@param p 
*			Liste de photo a prendre
*	@param s
*			Liste de satellites
*/
System::System(std::vector<Collection*> c, std::vector<Photo*> p, std::vector<Satellite*> s, unsigned long nb_turns) :liste_collections(c), liste_photos(p), liste_Satellites(s), nb_turns(nb_turns)
{
}

/**
*	Destructeur de la classe System
*/
System::~System()
{
}

/**
*	Getteur du nombre de tours de simulation
*	@return nombre de tours de simulation
*/
unsigned long System::getNbTurns() const
{
	return this->nb_turns;
}

/**
*	Setteur du nombre de tours
*	@param nb_turns
*			Mise a jour du nombre de tours
*/
void System::setNbTurns(unsigned int nb_turns)
{
	this->nb_turns = nb_turns;
}

/**
*	Getteur des collections
*	@return Liste de collections
*/
std::vector<Collection*> System::getListeCollections() const
{
	return this->liste_collections;
}

/**
*	Getteur des photos prises
*	@return Liste des photos prises
*/
std::vector<Photo*> System::getListePhotos() const
{
	return this->liste_photos;
}

/**
*	Getteur des satellites
*	@return Liste de satellites
*/
std::vector<Satellite*> System::getListeSatellites() const
{
	return this->liste_Satellites;
}

/**
*	Obtention du nombre de photos prises
*	@return nombres de photos
*/
unsigned int System::getNombrePhotos() const
{
	return this->liste_photos.size();
}

/**
*	Setteur des collections
*	@param c
*			Liste de collections
*/
void System::setCollections(std::vector<Collection*> c)
{
	this->liste_collections = c;
}

/**
*	Setteur des satellites
*	@param s
*			Liste de satellites
*/
void System::setSatellites(std::vector<Satellite*> s)
{
	this->liste_Satellites = s;
}

/**
*	Verification de la possiblité d'atteindre une location suivant le satellite et le tour en cours
*	@param nbTour
*			Le tour en cours
*	@param s
*			Le satellite
*	@param loc
*			La location a prendre en photo
*	@return prise de photo ou non
*/
bool System::locationReachable(int nbTour, Satellite* s, Location* loc) {
	
	// Vérification des distances entre la caméra du satellite et la location suivant le nombre de tour disponible entre deux prises de vue
	if( (loc->getCoord()->getLatitude() >= (s->getCamera()->getLatitude() - (s->getMoveStep()*(nbTour - s->getTourLastShot())))) && \
		(loc->getCoord()->getLatitude() <= (s->getCamera()->getLatitude() + (s->getMoveStep()*(nbTour - s->getTourLastShot())))) && \
			(loc->getCoord()->getLongitude() >= (s->getCamera()->getLongitude() - (s->getMoveStep()*(nbTour - s->getTourLastShot())))) && \
				(loc->getCoord()->getLongitude() <= (s->getCamera()->getLongitude() + (s->getMoveStep()*(nbTour - s->getTourLastShot()))))) {
		return true;
	}
	else {
		return false;
	}
}

/**
*	Verification si la location est présente dans l'angle de vue du satellite
*	@param s
*			Le satellite
*	@param l
*			La location
*	@return La location est visible ou non
*/
bool System::locationViewable(Satellite* s, Location* l) {

	// Récupération des intervals
	long minAbs = s->getCoordinates()->getLatitude() - s->getRadius(), maxAbs = s->getCoordinates()->getLatitude() + s->getRadius(), \
		minOrd = s->getCoordinates()->getLongitude() - s->getRadius(), maxOrd = s->getCoordinates()->getLongitude() + s->getRadius();

	// vérification suivant les coordonées de la location
	if (l->getCoord()->getLatitude() >= minAbs && l->getCoord()->getLatitude() <= maxAbs && (l->getCoord()->getLongitude() >= minOrd\
		&& l->getCoord()->getLongitude() <= maxOrd))
		return true;
	return false;
}

/**
*	Savoir si il reste des photos a prendre
*	@param cols
*			Liste de collections
*	@return il reste ou non des photos a prendre
*/
bool System::areLocationsTaken(std::vector<Collection*> cols) {

	bool b = true;
	// Parcours des collections
	for (auto c : cols) {
		// Parcours des locations
		for (auto l : c->getListePictures()) {
			if (!l->getPhotoTaken()) {
				b = false;
			}
		}
	}
	return b;
}

/**
*	Les locations de cette collections sont-elles prenables a ce tour
*	@param c
*			La collection
*	@param turn
*			Le tour
*	@return Photo prenables ou non
*/
bool System::iscollectionTakeable(Collection* c, long turn) {

	// Parcours des intervals
	for (auto a : c->getListeTimeInterval()) {
		if ((turn >= a->getStart()) && (turn <= a->getEnd()))
			return true;
	}
	return false;
}

/**
*	Verification si le satellite est dans les bornes de prises de photo
*	@param s
*			Le satellite
*	@return le satellite peut prendre ou non des photos
*/
bool System::isOutOfBorder(Satellite* s) {
	if ((s->getCoordinates()->getLongitude() < ((-1)*(85 * 3600))) || (s->getCoordinates()->getLongitude() > ((85 * 3600))))
		return true;
	else
		return false;
}

/**
*	Fonction principale de simulation du système
*/
void System::turn() {

	// Stockage classé des latitudes et longitude
	std::map<long,std::map<long,Location*>> mapLocs;
	long lati, longi;

	// Pour chaque collection
	for (size_t i = 0; i < this->getListeCollections().size(); i++)
	{
		// Pour chaque location
		for (unsigned j = 0; j < this->getListeCollections().at(i)->getListePictures().size(); j++) {
			// Récupération latitude et longitude puis ajout dans la map
			lati = this->getListeCollections().at(i)->getListePictures().at(j)->getCoord()->getLatitude();
			longi = this->getListeCollections().at(i)->getListePictures().at(j)->getCoord()->getLongitude();
			mapLocs[lati][longi] = this->getListeCollections().at(i)->getListePictures().at(j);
		}
	}

	bool pictTak = false;	// Photo prise ou non dans le tour en cours
	long minAbs,maxAbs,minOrd,maxOrd;	// Bornes du satellite

	// Pour chaque tour de simulation
	for (unsigned long turn = 0; turn < this->getNbTurns() -1 ; turn++) {

		long nbSat = this->liste_Satellites.size();

		// Pour chaque satellite
		for (long i = 0; i < nbSat; i++) {

			// Choix du satellite
			Satellite* s = this->liste_Satellites.at(i);

				// Calcul des bornes de vision du satellite
				minAbs = s->getCoordinates()->getLatitude() - s->getRadius();
				maxAbs = s->getCoordinates()->getLatitude() + s->getRadius();
				minOrd = s->getCoordinates()->getLongitude() - s->getRadius();
				maxOrd = s->getCoordinates()->getLongitude() + s->getRadius();

				// Parcours de la map en latitude puis longitude parmis ceux qui correspondent au critères des bornes
				for (std::map<long, std::map<long,Location*>>::iterator it1 = mapLocs.lower_bound(minAbs); it1 != mapLocs.upper_bound(maxAbs); ++it1) {
					for (std::map<long, Location*>::iterator it = it1->second.lower_bound(minOrd); it != it1->second.upper_bound(maxOrd); ++it) {
						
						// Pour les locations se trouvant dans l'angle maximum du satellite
						if (!it->second->getPhotoTaken()) {	// Vérification si la location est déja prise en photo
							if(iscollectionTakeable(liste_collections.at(it->second->getIdCol()),turn)) {	//	Le tour courant permet-il de prendre la photo 
								if (locationReachable(turn, s, it->second)) {	// Suivant la dernière prise de vue, est-il possible de prendre la photo
									this->liste_photos.push_back(new Photo(s->getId(), turn, it->second));	// Ajout d'une nouvelle photo
									s->setDeltaAbs(s->getDeltaAbs() + (it->second->getCoord()->getLatitude() - s->getCamera()->getLatitude()));	// Mise a jour du décalage horizontal
									s->setDeltaOrd(s->getDeltaOrd() + (it->second->getCoord()->getLongitude() - s->getCamera()->getLongitude()));	// Mise a jour du décalage vertical
									s->setCamera(new Coordinates(it->second->getCoord()->getLatitude(), it->second->getCoord()->getLongitude()));	// Modification coordonnées de la caméra
									it->second->setPhotoTaken(true);	// Préciser que la location a été prise en photo
									s->setTourLastShot(turn);	// Indication du tour de prise de vue
									pictTak = true;
								}
								if (pictTak)
									break;
							}
						}
					}
					if (pictTak)
						break;
				}
			pictTak = false;
			s->move();
		}
	}
}

/**
*	Obtention des coordonnées d'un satellite a un tour donné
*	@param v
*			Velocité du satellite
*	@param c
*			Coordonées du satellite
*	@param nb
*			Tour souhaité
*	@return coordonées du satellite au tour souhaité
*/
Coordinates * System::getFuturPos(int v, Coordinates * c, unsigned int nb)
{
	// Reprise de la fonction move
	if (nb > 0) {
		if (c->getLatitude() + v > 90 * 3600) {
			c->setLatitude(180 * 3600 - (c->getLatitude() + v));
			c->setLongitude(-180 * 3600 + (c->getLongitude() - 15));
			v = v * (-1);
		}
		else if (c->getLatitude() + v < -90 * 3600) {
			c->setLatitude(-180 * 3600 - (c->getLatitude() + v));
			c->setLongitude(-180 * 3600 + (c->getLongitude() - 15));
			v = v * (-1);
		}
		else {
			c->setLatitude(c->getLatitude() + v);
			c->setLongitude(c->getLongitude() - 15);
		}

		//Pour que la longitude reste dans les bornes [-648000,647999]
		if (c->getLongitude() < System::MINLONGITUDE) {
			c->setLongitude((System::MINLONGITUDE*(-1)) + (c->getLongitude() + (System::MINLONGITUDE*(-1))));
		}

		if (c->getLongitude() > System::MAXLONGITUDE) {
			c->setLongitude(System::MAXLONGITUDE + (c->getLongitude() - System::MAXLONGITUDE));
		}
		// Fonction récursive
		return System::getFuturPos(v, c, nb - 1);
	}
	else {
		return c;
	}
}
