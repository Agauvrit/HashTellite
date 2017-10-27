#pragma once

/* Fichier d'en-tête de la classe Location */

// Librairies
#include "Coordinates.h"

class Location
{
public:

	// Constructeur
	Location(int idCol=0,Coordinates* coordinate=0);
	
	// Destructeur
	~Location();

	// Getteurs
	bool getPhotoTaken() const;
	Coordinates* getCoord() const;
	int getIdCol() const;

	// Setteurs
	void setPhotoTaken(bool photo_taken);	
	void setCoordinates(Coordinates*);
	void setIdCol(int);


private:

	int idCol; // Identifiant de la collection auquel elle est relié
	bool photo_taken;	// Savoir si la photo a été prise ou non
	Coordinates* coordinate;	// Coordonées de la location
};