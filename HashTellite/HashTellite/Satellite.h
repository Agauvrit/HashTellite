#pragma once

/* Fichier d'en-tête de la classe Satellite */

// Librairies
#include "Coordinates.h"

class Satellite
{
public:

	// Constructeur
	Satellite(long=0, int id =0, Coordinates* = 0, Coordinates* = 0, long = 0, long = 0);
	
	// Destructeur
	~Satellite();

	// Getteurs
	long getVelocity() const;
	int getId() const;
	long getMoveStep() const;
	long getRadius() const;
	Coordinates* getCamera() const;
	Coordinates* getCoordinates() const;
	long getDeltaAbs() const;
	long getDeltaOrd() const;
	long getTourLastShot() const;

	// Setteurs
	void setVelocity(long);
	void setId(int id);
	void setMoveStep(long);
	void setRadius(long);
	void setCamera(Coordinates*);
	void setCoordinates(Coordinates*);
	void setDeltaAbs(long);
	void setDeltaOrd(long);
	void setTourLastShot(long);

	// Fonction qui fait tourner d'un tour le satellite
	void move();

private:

	long velocity;	// Velocite relative au satellite
	int id;	// Numero d'identifiant du satellite
	long move_step;	// Pas de la caméra entre deux tour
	long radius;	// Angle maximum de vision du satellite
	long tourLastShot;	// Identifiant du dernier tour ou une photo a été prise
	long deltaAbs;	// Decalage horizontale de la caméra par rapport au satellite
	long deltaOrd;	// Decalage verticale de la caméra par rapport au satellite
	Coordinates* cam;	// Coordonnees de la caméra du satellite
	Coordinates* coord;	// Coordonnees du satellite
};

