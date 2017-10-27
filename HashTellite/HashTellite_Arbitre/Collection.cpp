
// Librairies
#include "Collection.h"
#include "Location.h"

using namespace std;

/**
*	Constructeur de la classe Collection
*	@param nb_points
*			Le nombre de points lié a la collection
*	@param id
*			Identifiant de la collection
*/
Collection::Collection(unsigned int nb_points,unsigned int id):nb_points(nb_points),id(id)
{
}

/**
*	Constructeur de la classe Collection
*	@param nb
*			Le nombre de points lié a la collection
*	@param id
*			Identifiant de la collection
*	@param loc
*			Liste des locations de la collection
*	@param tim
*			Liste des intervalles de temps de la collection
*/
Collection::Collection(std::vector<Location*> loc, std::vector<TimeInterval*> tim, unsigned int nb,unsigned int id):nb_points(nb), liste_pictures(loc), liste_time_interval(tim),id(id)
{
}

/**
*	Destructeur de la classe Collection
*/
Collection::~Collection()
{
}

/**
*	Getteur du nombre de points
*	@return nombre de points
*/
unsigned int Collection::getNbPoints() const
{
	return this->nb_points;
}

/*
*	Setteurdu nombre de points
*	@param nb_points
*			nombre de points
*/
void Collection::setNbPoints(unsigned int nb_points)
{
	this->nb_points = nb_points;
}

/*
*	Getteur de la liste de location
*	@return liste de location
*/
std::vector<Location*> Collection::getListePictures() const
{
	return this->liste_pictures;
}

/*
*	Getteur de la liste d'interval
*	@return liste d'intervals
*/
std::vector<TimeInterval*> Collection::getListeTimeInterval() const
{
	return this->liste_time_interval;
}

/*
*	Getteur de l'identifiant
*	@return identifiant de la collection
*/
unsigned int Collection::getId() const
{
	return this->id;
}

/*
*	Setteur de l'identifiant de la collection
*	@param i
*			identifiant de la collection
*/
void Collection::setId(unsigned int i)
{
	this->id = i;
}

/*
*	Setteur de la liste de location
*	@param p
*			liste de location
*/
void Collection::setListePictures(std::vector<Location*> p)
{
	this->liste_pictures = p;
}

/*
*	Setteur de la liste d'intervals
*	@param t
*			liste d'intervals
*/
void Collection::setListeTimeInterval(std::vector<TimeInterval*> t)
{
	this->liste_time_interval = t;
}
