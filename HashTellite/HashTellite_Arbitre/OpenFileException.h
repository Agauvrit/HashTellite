#pragma once

/* Fichier d'en-tête de la classe ComplexException */

//Librairies
#include <exception>
#include <string.h>

// Importation de l'objet std
using namespace std;

// Déclaration de la classe héritant de "exception"
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
	// Déclaration des attributs
	char* e_phrase;		//Description de l'erreur
};
