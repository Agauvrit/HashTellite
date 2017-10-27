#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include "FileHandling.hpp"
#include "Input.h"
#include <stdio.h>
#include <fstream>
#include <direct.h>
#include <stdlib.h>

//ICI, ON DETERMINE SUR QUELS FICHIERS D'ENTREE ON VEUT LANCER L'ARBITRE
//true --> ON VEUT UTILISER CE FICHIER
//false --> ON NE VEUT PAS UTILISER CE FICHIER
const bool FOREVER_ALONE = true;
const bool CONSTELLATION = true;
const bool WEEKEND = true;
const bool OVERLAP = true;


using namespace std;

class Arbitre
{
public:
	//Constructeur
	Arbitre(char* repo, char* fileOut);
	
	//Destructeur
	~Arbitre();

	//Itérateur sur les fichiers d'un dossier
	void operator()(const char *);

	//Extraction du nom d'un fichier dans un chemin
	string getFileName(string file);
	string getFileNameOut(string file);

	//Reconnaissance du format des fichiers
	bool isExe(const char * file);
	bool isOut(const char * file);
	bool isCsv(const char * file);

	//Getteur pour accéder au répertoire contenant les .exe
	char* getRepoExe() {return this->repoExe; }

	//Calcul de la matrice en rapport avec le temps d'exécution
	map < string, map<string, double>> CalculTemps();
	//Calcul de la matrice en rapport avec le score des fichiers de sortie
	map<string, map<string, int>> calculScore();
	//Sortie des résultats dans un fichier
	void outputTableau(map < string, map<string, double>> matriceTemps);

private:
	char* repoExe; //chemin du répertoire contenant les .exe
	char* name_file_out; //nom du fichier de sortie
	vector<string> liste_exe; //Liste des chemins vers tous les .exe
	vector<string> liste_out; //Liste des chemins vers tous les .out
	vector<string> liste_filesin; //Liste des chemins vers tous les .in
	map<string, int> score_global; //Matrice associant à un fichier le score maximum (utile pour calculer le pourcentage d'efficacité d'une solution")
};

