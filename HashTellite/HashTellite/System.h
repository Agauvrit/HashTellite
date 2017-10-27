#pragma once

/* Fichier d'en-tête de la classe System */

#include <vector>
#include "Collection.h"
#include "Satellite.h"
#include "Photo.h"


using namespace std;

class System
{

public:

	// Definition de constantes globales au systeme
	static const long MINLATITUDE = -324000;
	static const long MAXLATITIUDE = 324000;
	static const long MINLONGITUDE = -648000;
	static const long MAXLONGITUDE = 647999;

	// Constructeurs
	System(unsigned long nb_turns=0);
	System(std::vector<Collection*>, std::vector<Photo*>, std::vector<Satellite*>, unsigned long nb_turns = 0);
	
	// Destructeur
	~System();

	// Getteurs
	unsigned long getNbTurns() const;
	std::vector<Collection*> getListeCollections() const;
	std::vector<Photo*> getListePhotos() const;
	std::vector<Satellite*> getListeSatellites() const;
	unsigned int getNombrePhotos() const;

	// Setteurs
	void setNbTurns(unsigned int nb_points);
	void setCollections(std::vector<Collection*>);
	void setSatellites(std::vector<Satellite*>);

	// Fonction de simulation du systeme
	void turn();

	// Vérification d'une location atteignable via la caméra a un tour donnée
	bool System::locationReachable(int nbTour, Satellite* s, Location* loc);
	// Verification de la visibilité par le satellite d'une location
	bool System::locationViewable(Satellite* s, Location* l);
	// Savoir si il reste des photos a prendre 
	bool areLocationsTaken(std::vector<Collection*> cols);
	// Savoir si les locations de la collection sont un intervalle prenable ou non
	bool iscollectionTakeable(Collection* c, long turn);
	// Obtenir les coordonées d'un satellite a un tour donnée
	static Coordinates* getFuturPos(int v, Coordinates* c, unsigned int nb);
	// Savoir si le satellite est hors des bornes de prise de photos
	static bool System::isOutOfBorder(Satellite* s);



private :
	unsigned long nb_turns;	// Nombre de tours total de la simulation
	std::vector<Collection*> liste_collections;	// Stockage des collections
	std::vector<Satellite*> liste_Satellites;	// Stockage des satellites
	std::vector<Photo*> liste_photos;	// Stockage des locations a prendre en photo
};
