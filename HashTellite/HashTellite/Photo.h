#pragma once

/* Fichier d'en-tête de la classe Photo */

// Librairies
#include "Coordinates.h"
#include "Location.h"


class Photo
{
public:

	// Constructeurs
	Photo();
	Photo(int, unsigned int, Coordinates*);
	Photo(int, unsigned int, Location*);

	// Destructeur
	~Photo();

	// Getteurs
	Coordinates* getCoordinates() const;
	int getIdSatellite() const;
	unsigned int getIdTour() const;

	// Setteurs
	void setCoordinates(Coordinates*);
	void setIdTour(unsigned int);
	void setIdSatellite(int);

private:
	int idSatellite;	// Numéro d'identifiant du satellite
	unsigned int idTour;	// Numero du tour pour la prise de photo 
	Coordinates* coord;		// Coordonées de la location prise en photo
};

