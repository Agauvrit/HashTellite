// Librairies
#include "Satellite.h"
#include "System.h"
#include <iostream>

/**
*	Constructeur de la classe Satellite
*	@param v
*			Velocité du satellite
*	@param id
*			Identifiant du satellite
*	@param coord
*			Coordonnées du satellite
*	@param camera
*			Coordonnées de la caméra du satellite
*	@param mv
*			Déplacement maximum de la caméra en un tour
*	@param rad
*			Angle maximum de vision du satellite
*/
Satellite::Satellite(long v, int id, Coordinates *coord, Coordinates *camera, long mv, long rad)
{
	this->velocity = v;
	this->id = id;
	this->cam = camera;
	this->coord = coord;
	this->move_step = mv;
	this->radius = rad;
	this->deltaAbs = 0;
	this->deltaOrd = 0;
	this->tourLastShot = 0;
}

/**
*	Destructeur de la classe Satellite
*/
Satellite::~Satellite()
{
}

/**
*	Getteur de la vélocité
*	@return vélocité du satellite
*/
long Satellite::getVelocity() const
{
	return this->velocity;
}

/**
*	Getteur de l'identifiant du satellite
*	@return identifiant du satellite
*/
int Satellite::getId() const
{
	return this->id;
}

/**
*	Getteur du déplacement maximum de la caméra
*	@return déplacement max de la caméra
*/
long Satellite::getMoveStep() const
{
	return this->move_step;
}

/**
*	Getteur de l'angle maximum de vision du satellite
*	@return angle maximum du satellite
*/
long Satellite::getRadius() const
{
	return this->radius;
}

/**
*	Getteur des coordonées de la caméra
*	@return coordonées de la caméra
*/
Coordinates * Satellite::getCamera() const
{
	return this->cam;
}

/**
*	Getteur des coordonées du satellite
*	@return coordonnées du satellite
*/
Coordinates* Satellite::getCoordinates() const
{
	return this->coord;
}

/**
*	Getteur de l'écart horizontale de la caméra
*	@return écart de la caméra au satellite
*/
long Satellite::getDeltaAbs() const
{
	return this->deltaAbs;
}

/**
*	Getteur de l'écart vertical de la caméra
*	@return écart de la caméra au satellite
*/
long Satellite::getDeltaOrd() const
{
	return this->deltaOrd;
}

/**
*	Getteur du dernier tour de prise de photo
*	@return tour de la dernière prise de photo
*/
long Satellite::getTourLastShot() const
{
	return this->tourLastShot;
}

/**
*	Setteur de la vélocité
*	@param v
*			nouvelle vélocité
*/
void Satellite::setVelocity(long v)
{
	this->velocity = v;
}

/**
*	Setteur de l'identifiant
*	@param id
*			nouvelle identifiant
*/
void Satellite::setId(int id) {
	this->id = id;
}

/**
*	Setteur du pas de la caméra
*	@param mv
*			nouveau pas
*/
void Satellite::setMoveStep(long mv)
{
	this->move_step = mv;
}

/**
*	Setteur de l'angle maximum du satellite
*	@param rad
*			nouvel angle maximum
*/
void Satellite::setRadius(long rad)
{
	this->radius = rad;
}

/**
*	Setteur des coordonnées de la caméra
*	@param c
*			nouvelles coordonnées
*/
void Satellite::setCamera(Coordinates * c)
{
	this->cam = c;
	}

/**
*	Setteur des coordonnées du satellite
*	@param c
*			nouvelle coordonnées
*/
void Satellite::setCoordinates(Coordinates* c) {
	this->coord = c;
}

/**
*	Setteur du décalage horizontal
*	@param i
*			nouveau décalage
*/
void Satellite::setDeltaAbs(long i)
{
	this->deltaAbs = i;
}

/**
*	Setteur du décalage vertical
*	@param i
*			nouveau décalage
*/
void Satellite::setDeltaOrd(long i)
{
	this->deltaOrd = i;
}

/**
*	Setteur deu dernier tour de prise de photo
*	@param l
*			tour de prise de photo
*/
void Satellite::setTourLastShot(long l)
{
	this->tourLastShot = l;
}
/**
*	Fonction qui calcul les nouvelles coordonées et la vélocité du satellite au tour suivant
*/
void Satellite::move()
{
	if (this->coord->getLatitude() + this->velocity > 90 * 3600) {
		this->coord->setLatitude(180 * 3600 - (this->coord->getLatitude() + this->velocity));
		this->coord->setLongitude(-180 * 3600 + (this->coord->getLongitude() - 15));
		this->velocity = this->velocity * (-1);
	}
	else if (this->coord->getLatitude() + this->velocity < -90 * 3600) {
		this->coord->setLatitude(-180 * 3600 - (this->coord->getLatitude() + this->velocity));
		this->coord->setLongitude(-180 * 3600 + (this->coord->getLongitude() - 15));
		this->velocity = this->velocity * (-1);
	}
	else {
		this->coord->setLatitude(this->coord->getLatitude() + this->velocity);
		this->coord->setLongitude(this->coord->getLongitude() - 15);
	}

	//Pour que la longitude reste dans les bornes [-648000,647999]
	if (this->coord->getLongitude() < System::MINLONGITUDE) {
		this->coord->setLongitude((System::MINLONGITUDE*(-1)) + (this->coord->getLongitude() + (System::MINLONGITUDE*(-1))));
	}

	if (this->coord->getLongitude() > System::MAXLONGITUDE) {
		this->coord->setLongitude(System::MAXLONGITUDE + (this->coord->getLongitude() - System::MAXLONGITUDE));
	}

	// Recalcul des coordonnées de la caméra
	this->cam->setLatitude(this->coord->getLatitude() + this->deltaAbs);
	this->cam->setLongitude(this->coord->getLongitude() + this->deltaOrd);

}
