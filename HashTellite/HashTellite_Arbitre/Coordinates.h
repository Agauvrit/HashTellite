#pragma once

/* Fichier d'en-tête de la classe Coordinates */

/* Classe permettant de positionner les différents éléments du système */

class Coordinates
{
public:
	// Constructeur
	Coordinates(long longitude=0, long latitude=0);

	// Destructeur
	~Coordinates();

	// Getteurs
	long getLongitude() const;
	long getLatitude() const;

	// Récupération des latitudes et longitudes décomposés
	long* getLati();
	long* getLongi();


	// Setteurs
	void setLongitude(long);
	void setLatitude(long);

	// Mise a jour des coordonnées
	void upCoord();
	

private:
	long lati[3];	// Décomposition de la latitude
	long longi[3];	// Décomposition de la longitude
	long latitude; // Latitude en format long
	long longitude;	// Longitude en format long
};