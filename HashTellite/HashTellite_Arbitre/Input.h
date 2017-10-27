#pragma once

/* Fichier d'en-tête de la classe Input */

/* CLasse qui fais le lien entre le système et les fichiers exterieurs */

// Librairies
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>

#include "System.h"

class Input
{
public:

	// Constructeurs
	Input(std::string nameI="test.in", std::string nameO="test.out"); // Constructeur par défaut
	Input(const Input&); // Constructeur de recopie
	
	// Destructeur
	~Input(); // Destructeur éventuellement virtuel

	// Getteurs
	std::string getNomFichierInput() const;
	std::string getNomFichierOutput() const;
	System getSystem() const;

	// Fonction principales
	void createSystem();
	void getOutput();
	void turn();

private:

	System system;	// Système qui va contenir l'ensemble
	std::string nomFichierInput;	// Nom du fichier d'input
	std::string nomFichierOutput;	// Nom du fichier d'output
};
