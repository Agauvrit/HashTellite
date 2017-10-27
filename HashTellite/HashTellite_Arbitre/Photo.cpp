// Librairies
#include "Photo.h"

/**
*	Constructeur de la classe Photo
*/
Photo::Photo()
{
}

/**
*	Constructeur de la classe Photo
*	@param idSat
*			Identifiant du satellite
*	@param idT
*			Numero du tour de prise de la photo
*	@param c
*			Coordonnées de la location prise en photo
*/
Photo::Photo(int idSat, unsigned int idT, Coordinates* c):idSatellite(idSat),idTour(idT),coord(c)
{
}

/**
*	Constructeur de la classe Photo
*	@param idSat
*			Identifiant du satellite
*	@param idT
*			Numero du tour de prise de la photo
*	@param l
*			Location prise en photo
*/
Photo::Photo(int idSat, unsigned int idT, Location* l): idSatellite(idSat), idTour(idT)
{
	this->coord = new Coordinates(l->getCoord()->getLatitude(), l->getCoord()->getLongitude());
}

/**
*	Destructeur de la classe Photo
*/
Photo::~Photo()
{
}

/**
*	Getteur des coordonnées
*	@return coordonnées de la photo
*/
Coordinates * Photo::getCoordinates() const
{
	return this->coord;
}

/**
*	Getteur de l'identfiant du satellite
*	@return identifiant du satellite
*/
int Photo::getIdSatellite() const
{
	return this->idSatellite;
}

/**
*	Getteur de l'identifiant du tour
*	@return identifiant du tour
*/
unsigned int Photo::getIdTour() const
{
	return this->idTour;
}

/**
*	Setteur des coordonnées de la photo
*	@param c
*			nouvelles coordonnées
*/
void Photo::setCoordinates(Coordinates * c)
{
	this->coord;
}

/**
*	Setteur de l'identifiant du tour
*	@param i
*			identifiant du tour
*/
void Photo::setIdTour(unsigned int i)
{
	this->idTour = i;
}

/**
*	Setteur de l'identifiant du satellite
*	@return identifiant du satellite
*/
void Photo::setIdSatellite(int i)
{
	this->idSatellite = i;
}
