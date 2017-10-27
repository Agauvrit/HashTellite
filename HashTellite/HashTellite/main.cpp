#pragma once

/* Fichier principal d'�xecution cr�ant et simulant le systeme */

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
		Input in(argv[1],argv[2]);	// Cr�ation du syst�me via le fichier d'entr�
		in.turn();	// Simulation du syst�me
	}
	// Gestion des erreurs pouvant survenir
	catch (std::exception e) {
		cout << "erreur : " << e.what() << endl;
	}
	return 0;
}