// Librairies
#include "Location.h"

/**
*	Constructeur de la classe Location
*	@param id
*			Identifiant 
*	@param longitude
*			Longitude
*/
Location::Location(int id,Coordinates* coord): photo_taken(false),coordinate(coord),idCol(id)
{
}

/**
*	Destructeur de la classe Location
*/
Location::~Location()
{
}

/**
*	Getteur de photo_taken
*	@return bool�en permettant de savoir si la photo a �t� prise
*/
bool Location::getPhotoTaken() const
{
	return this->photo_taken;
}

/**
*	Setteur de photo_taken
*	@param photo_taken
*			photo prise ou non
*/
void Location::setPhotoTaken(bool photo_taken)
{
	this->photo_taken = photo_taken;
}

/**
*	Getteur des coodon�es de la location
*	@return coordonn�es
*/
Coordinates* Location::getCoord() const
{
	return this->coordinate;
}

/**
*	Getteur de l'identifiant de la collection associ�
*	@return identifiant
*/
int Location::getIdCol() const
{
	return this->idCol;
}

/**
*	Setteur des coordon�es de la location
*	@param c
*			Nouvelles coordonn�es
*/
void Location::setCoordinates(Coordinates* c)
{
	this->coordinate = c;
}

/**
*	Setteur de l'identifiant de la collection
*	@param n
*			identifiant collection
*/
void Location::setIdCol(int n)
{
	this->idCol = n;
}
