#pragma once
/* Fichier source de la classe ComplexException */

// Librairies
#include "OpenFileException.h"
#include <cmath>
#include <math.h>
#include <iostream>

// Importation de l'objet std
using namespace std;

/**
*	Constructeur de la classe OpenFileException
*/
OpenFileException::OpenFileException() throw()
{
		e_phrase = "Erreur lors de l'ouverture du fichier";
}

/**
*	Récupération du message d'erreur
*	@preturn message d'erreur
*/const char * OpenFileException::what() const throw()
{
	return e_phrase;
}

/**
*	Destructeur de la classe Location
*/
OpenFileException::~OpenFileException() throw()
{
}