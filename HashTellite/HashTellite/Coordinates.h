#pragma once

/* Fichier d'en-t�te de la classe Coordinates */

/* Classe permettant de positionner les diff�rents �l�ments du syst�me */

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

	// R�cup�ration des latitudes et longitudes d�compos�s
	long* getLati();
	long* getLongi();


	// Setteurs
	void setLongitude(long);
	void setLatitude(long);

	// Mise a jour des coordonn�es
	void upCoord();
	

private:
	long lati[3];	// D�composition de la latitude
	long longi[3];	// D�composition de la longitude
	long latitude; // Latitude en format long
	long longitude;	// Longitude en format long
};