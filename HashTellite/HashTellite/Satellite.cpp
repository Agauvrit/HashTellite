// Librairies
#include "Satellite.h"
#include "System.h"
#include <iostream>

/**
*	Constructeur de la classe Satellite
*	@param v
*			Velocit� du satellite
*	@param id
*			Identifiant du satellite
*	@param coord
*			Coordonn�es du satellite
*	@param camera
*			Coordonn�es de la cam�ra du satellite
*	@param mv
*			D�placement maximum de la cam�ra en un tour
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
*	Getteur de la v�locit�
*	@return v�locit� du satellite
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
*	Getteur du d�placement maximum de la cam�ra
*	@return d�placement max de la cam�ra
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
*	Getteur des coordon�es de la cam�ra
*	@return coordon�es de la cam�ra
*/
Coordinates * Satellite::getCamera() const
{
	return this->cam;
}

/**
*	Getteur des coordon�es du satellite
*	@return coordonn�es du satellite
*/
Coordinates* Satellite::getCoordinates() const
{
	return this->coord;
}

/**
*	Getteur de l'�cart horizontale de la cam�ra
*	@return �cart de la cam�ra au satellite
*/
long Satellite::getDeltaAbs() const
{
	return this->deltaAbs;
}

/**
*	Getteur de l'�cart vertical de la cam�ra
*	@return �cart de la cam�ra au satellite
*/
long Satellite::getDeltaOrd() const
{
	return this->deltaOrd;
}

/**
*	Getteur du dernier tour de prise de photo
*	@return tour de la derni�re prise de photo
*/
long Satellite::getTourLastShot() const
{
	return this->tourLastShot;
}

/**
*	Setteur de la v�locit�
*	@param v
*			nouvelle v�locit�
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
*	Setteur du pas de la cam�ra
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
*	Setteur des coordonn�es de la cam�ra
*	@param c
*			nouvelles coordonn�es
*/
void Satellite::setCamera(Coordinates * c)
{
	this->cam = c;
	}

/**
*	Setteur des coordonn�es du satellite
*	@param c
*			nouvelle coordonn�es
*/
void Satellite::setCoordinates(Coordinates* c) {
	this->coord = c;
}

/**
*	Setteur du d�calage horizontal
*	@param i
*			nouveau d�calage
*/
void Satellite::setDeltaAbs(long i)
{
	this->deltaAbs = i;
}

/**
*	Setteur du d�calage vertical
*	@param i
*			nouveau d�calage
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
*	Fonction qui calcul les nouvelles coordon�es et la v�locit� du satellite au tour suivant
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

	// Recalcul des coordonn�es de la cam�ra
	this->cam->setLatitude(this->coord->getLatitude() + this->deltaAbs);
	this->cam->setLongitude(this->coord->getLongitude() + this->deltaOrd);

}
