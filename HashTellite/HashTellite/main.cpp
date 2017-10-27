#pragma once

/* Fichier principal d'éxecution créant et simulant le systeme */

// Librairies
#include <iostream>
#include <locale>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#include "Input.h"
#include "OpenFileException.h"


//#define DEBUG

using namespace std;

int main(int argc, char* argv[]) {

	try {
		Input in(argv[1],argv[2]);	// Création du système via le fichier d'entré
		in.turn();	// Simulation du système
	}
	// Gestion des erreurs pouvant survenir
	catch (std::exception e) {
		cout << "erreur : " << e.what() << endl;
	}
	return 0;
}