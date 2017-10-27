#pragma once

/* Fichier d'en-t�te de la classe Location */

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

	int idCol; // Identifiant de la collection auquel elle est reli�
	bool photo_taken;	// Savoir si la photo a �t� prise ou non
	Coordinates* coordinate;	// Coordon�es de la location
};