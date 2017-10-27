#pragma once

/* Fichier d'en-t�te de la classe ComplexException */

//Librairies
#include <exception>
#include <string.h>

// Importation de l'objet std
using namespace std;

// D�claration de la classe h�ritant de "exception"
class OpenFileException : public exception
{

public:

	// Constructeur
	OpenFileException() throw();
	// Obtention d'information sur le type d'erreur
	virtual const char* what() const throw();
	// Destructeur
	virtual ~OpenFileException() throw();


private:
	// D�claration des attributs
	char* e_phrase;		//Description de l'erreur
};
