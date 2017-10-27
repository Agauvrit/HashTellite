#pragma once

// Librairies
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <set>
#include <sstream>

#include "Input.h"
#include "OpenFileException.h"
#include "Collection.h"
#include "Coordinates.h"
#include "Location.h"
#include "Photo.h"
#include "Satellite.h"
#include "TimeInterval.h"
#include "System.h"

//#define DEBUG

using namespace std;

/**
*	Constructeur de la classe Input
*	@param nameI
*			Nom du fichier d'entrée
*	@param nameO
*			Nom du fichier de sortie
*/
Input::Input(std::string nameI,std::string nameO):nomFichierInput(nameI),nomFichierOutput(nameO)
{
}

/**
*	Constructeur de la classe Input par recopie
*	@param i
*			objet a copier
*/
Input::Input(const Input &i)
{
}

/**
*	Destructeur de la classe Input
*/
Input::~Input()
{
}

/**
*	Création du système en lisant le fichier d'entrée
*/
void Input::createSystem()
{
	// Déclaration de variable tampon pour créer les objets
	unsigned int nbTours;	
	unsigned int nbSatellites;
	unsigned int nbImageCollections;
	long timeStart;
	long timeEnd;
	unsigned int score;
	unsigned int nbLocations;
	unsigned int nbIntervals;
	
	// Stockage de la ligne courante en lecture
	std::string ligne;

	// Déclaration des structures qui vont receuillir les satellites, collections, locations et intervals
	std::vector<Satellite*> satellites;
	std::vector<Collection*> collections;
	std::vector<Location*> locations;
	std::vector<TimeInterval*> timeIntervals;

	// Concernant la création d'un satellite
	long latitude;
	long longitude;
	long moveStep;
	long radius;
	int velocity;

	// Déclaration du pattern utilisé
	std::regex pat(R"#([\wÙÛÜŸÀÂÆÇÉÈÊËÏÎÔŒùûüÿàâæçéèêëïîôœ][\wÙÛÜŸÀÂÆÇÉÈÊËÏÎÔŒùûüÿàâæçéèêëïîôœ\-]*)#");

	// Ouverture du fichier d'entrée
	std::ifstream file(this->nomFichierInput,ios::in);
	if (!file)
	{
		std::cerr << "Erreur a l'ouverture du fichier d'input";
		throw OpenFileException();
	}
	
	// Lecture du nombre de tours de simulation
	std::getline(file, ligne);
	stringstream ss(ligne);
	ss >> nbTours;
	
	// Lecture du nombre de satellites
	std::getline(file, ligne);
	stringstream ss2(ligne);
	ss2 >> nbSatellites;

	// Parcours des satellites
	for (unsigned int i = 0; i < nbSatellites; i++) {

		std::getline(file, ligne);
		stringstream ss3(ligne);
		// Affectation des valeurs lues
		ss3 >> latitude >> longitude >> velocity >> moveStep >> radius;

		// Ajout des satellites
		satellites.push_back(new Satellite(velocity,i, new Coordinates(latitude, longitude), new Coordinates(latitude, longitude),moveStep,radius));
	}
	
	// récupération nombre de collection
	std::getline(file, ligne);
	stringstream ss4(ligne);
	ss4 >> nbImageCollections;
	
	// Parcours des collections
	for (unsigned int j = 0; j < nbImageCollections; j++) {
		// Récupération des informations relative à une collection
		std::getline(file, ligne);
		stringstream ss5(ligne);
		ss5 >> score >> nbLocations >> nbIntervals;
		
		// Pour chaque locations contenues dans la collection
		for (unsigned int k = 0; k < nbLocations; k++) {
			// Récupération des informations de la location
			std::getline(file, ligne);
			stringstream ss6(ligne);
			ss6 >> latitude >> longitude;

			// Ajout des locations
			locations.push_back(new Location(j,new Coordinates(latitude,longitude)));
		}

		// Pour chaque interval liés a la collection
		for (unsigned int k = 0; k < nbIntervals; k++) {
			// Récupération d'informations sur les intervals
			std::getline(file, ligne);
			stringstream ss7(ligne);
			ss7 >> timeStart >> timeEnd;
			
			// Ajout de l'interval
			timeIntervals.push_back(new TimeInterval(timeStart,timeEnd));
		}
		
		// Ajout de la collection
		collections.push_back(new Collection(locations,timeIntervals,score,j));

		// Refresh pour la prochaine collection
		score = 0;
		locations.clear();
		timeIntervals.clear();
	}

	// Fermeture du fichier
	file.close();

	// Création du système
	System s(nbTours);
	s.setCollections(collections);
	s.setSatellites(satellites);

	// Affectation du système créé
	this->system = s;
}

/**
*	Génération du fichier de sortie
*/
void Input::getOutput()
{

	ofstream file(this->nomFichierOutput, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

	// Vérification de l'ouverture ou création du fichier de sortie
	if (!file){
		std::cerr << "Erreur a l'ouverture du fichier d'output";
		throw OpenFileException();
	}

	// Ajout du nombre de photos
	file << this->system.getNombrePhotos() << endl;

	// récupération des photos
	std::vector<Photo*> myvector = this->system.getListePhotos();

	// Pour chaque photo ajout des coordonnées, l'identifiant du tour pris et du satellite
	for (std::vector<Photo*>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
		file << (**it).getCoordinates()->getLatitude() << " ";
		file << (**it).getCoordinates()->getLongitude() << " ";
		file << (**it).getIdTour() << " ";
		file << (**it).getIdSatellite() << endl;
	}

	file.close();  // on referme le fichier
}

/**
*	Getteur du nom de fichier d'entrée
*	@return nom de fichier de d'entrée
*/
std::string Input::getNomFichierInput() const
{
	return this->nomFichierInput;
}

/**
*	Getteur du nom de fichier de sortie
*	@return nom de fichier de sortie
*/
std::string Input::getNomFichierOutput() const
{
	return this->nomFichierOutput;
}

/**
*	Fonction globale qui crée, simule le système et crée le fichier de sortie
*/
void Input::turn() {
	this->createSystem();
	this->system.turn();
	this->getOutput();
}