// Librairies
#include "Coordinates.h"

/**
*	Constructeur de la classe Coordinates
*	@param latitude
*			Latitude 
*	@param longitude
*			Longitude
*/
Coordinates::Coordinates(long latitude, long longitude)
{
	this->latitude = latitude;
	this->longitude = longitude;
	this->upCoord();
}

/**
*	Destructeur de la classe Coordinates
*/
Coordinates::~Coordinates()
{
}

/**
*	Getteur de la longitude
*	@return longitude
*/
long Coordinates::getLongitude() const
{
	return this->longitude;
}

/**
*	Getteur de la latitude
*	@return latitude
*/
long Coordinates::getLatitude() const
{
	return this->latitude;
}

/**
*	Setteur de la longitude
*	@param longitude
*			Nouvelle longitude
*/
void Coordinates::setLongitude(long longitude)
{
	this->longitude = longitude;
	this->upCoord();
}

/**
*	Setteur de la latitude
*	@param latitude
*			Nouvelle latitude
*/
void Coordinates::setLatitude(long latitude)
{
	this->latitude = latitude;
	this->upCoord();
}

/**
*	Mise a jour de la décomposition de la latitude et longitude
*/
void Coordinates::upCoord()
{	
	long residu;

	residu = this->latitude % 3600;
	lati[0] = this->latitude / 3600;
	lati[1] = residu / 60;
	lati[2] = residu % 60;

	residu = this->longitude % 3600;
	longi[0] = this->longitude / 3600;
	longi[1] = residu / 60;
	longi[2] = residu % 60;
}

/**
*	Getteur de la latitude décomposé
*	@return latitude décomposé
*/
long * Coordinates::getLati()
{
	return this->lati;
}

/**
*	Getteur de la longitude décomposé
*	@return longitude décomposé
*/
long * Coordinates::getLongi()
{
	return this->longi;
}
