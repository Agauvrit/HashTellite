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
*			Nom du fichier d'entr�e
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
*	Cr�ation du syst�me en lisant le fichier d'entr�e
*/
void Input::createSystem()
{
	// D�claration de variable tampon pour cr�er les objets
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

	// D�claration des structures qui vont receuillir les satellites, collections, locations et intervals
	std::vector<Satellite*> satellites;
	std::vector<Collection*> collections;
	std::vector<Location*> locations;
	std::vector<TimeInterval*> timeIntervals;

	// Concernant la cr�ation d'un satellite
	long latitude;
	long longitude;
	long moveStep;
	long radius;
	int velocity;

	// D�claration du pattern utilis�
	std::regex pat(R"#([\w��ܟ����������Ԍ����������������][\w��ܟ����������Ԍ����������������\-]*)#");

	// Ouverture du fichier d'entr�e
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
	
	// r�cup�ration nombre de collection
	std::getline(file, ligne);
	stringstream ss4(ligne);
	ss4 >> nbImageCollections;
	
	// Parcours des collections
	for (unsigned int j = 0; j < nbImageCollections; j++) {
		// R�cup�ration des informations relative � une collection
		std::getline(file, ligne);
		stringstream ss5(ligne);
		ss5 >> score >> nbLocations >> nbIntervals;
		
		// Pour chaque locations contenues dans la collection
		for (unsigned int k = 0; k < nbLocations; k++) {
			// R�cup�ration des informations de la location
			std::getline(file, ligne);
			stringstream ss6(ligne);
			ss6 >> latitude >> longitude;

			// Ajout des locations
			locations.push_back(new Location(j,new Coordinates(latitude,longitude)));
		}

		// Pour chaque interval li�s a la collection
		for (unsigned int k = 0; k < nbIntervals; k++) {
			// R�cup�ration d'informations sur les intervals
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

	// Cr�ation du syst�me
	System s(nbTours);
	s.setCollections(collections);
	s.setSatellites(satellites);

	// Affectation du syst�me cr��
	this->system = s;
}

/**
*	G�n�ration du fichier de sortie
*/
void Input::getOutput()
{

	ofstream file(this->nomFichierOutput, ios::out | ios::trunc);  //d�claration du flux et ouverture du fichier

	// V�rification de l'ouverture ou cr�ation du fichier de sortie
	if (!file){
		std::cerr << "Erreur a l'ouverture du fichier d'output";
		throw OpenFileException();
	}

	// Ajout du nombre de photos
	file << this->system.getNombrePhotos() << endl;

	// r�cup�ration des photos
	std::vector<Photo*> myvector = this->system.getListePhotos();

	// Pour chaque photo ajout des coordonn�es, l'identifiant du tour pris et du satellite
	for (std::vector<Photo*>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
		file << (**it).getCoordinates()->getLatitude() << " ";
		file << (**it).getCoordinates()->getLongitude() << " ";
		file << (**it).getIdTour() << " ";
		file << (**it).getIdSatellite() << endl;
	}

	file.close();  // on referme le fichier
}

/**
*	Getteur du nom de fichier d'entr�e
*	@return nom de fichier de d'entr�e
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
*	Fonction globale qui cr�e, simule le syst�me et cr�e le fichier de sortie
*/
void Input::turn() {
	this->createSystem();
	this->system.turn();
	this->getOutput();
}