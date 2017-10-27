#pragma once

/* Fichier d'en-tête de la classe Collection*/

/* Classe permettant de regrouper certaines photos et de spécifier un score associe */

// Librairies
#include "Location.h"
#include "TimeInterval.h"
#include <vector>

using namespace std;


class Collection
{
public:
	
	// Constructeur
	Collection(unsigned int = 0,unsigned int = 0);
	Collection(std::vector<Location*> , std::vector<TimeInterval*>, unsigned int = 0, unsigned int  = 0);

	// Destructeur
	~Collection();

	// Getteurs
	unsigned int getNbPoints() const;
	std::vector<Location*> getListePictures() const;
	std::vector<TimeInterval*> getListeTimeInterval() const;
	unsigned int getId() const;

	// Setteurs
	void setNbPoints(unsigned int nb_points);
	void setId(unsigned int);
	void setListePictures(std::vector<Location*>);
	void setListeTimeInterval(std::vector<TimeInterval*>);

private:

	unsigned int id;	// Identifiant de la collection
	unsigned int nb_points;		// Nombre de points correspondant a la collection
	std::vector<Location*> liste_pictures;		// Liste des locations a prendre en photo
	std::vector<TimeInterval*> liste_time_interval;		// Liste des intervalles de temps pour prendre les photos
};