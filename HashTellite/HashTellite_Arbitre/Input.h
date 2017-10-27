#pragma once

/* Fichier d'en-t�te de la classe Input */

/* CLasse qui fais le lien entre le syst�me et les fichiers exterieurs */

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
	Input(std::string nameI="test.in", std::string nameO="test.out"); // Constructeur par d�faut
	Input(const Input&); // Constructeur de recopie
	
	// Destructeur
	~Input(); // Destructeur �ventuellement virtuel

	// Getteurs
	std::string getNomFichierInput() const;
	std::string getNomFichierOutput() const;
	System getSystem() const;

	// Fonction principales
	void createSystem();
	void getOutput();
	void turn();

private:

	System system;	// Syst�me qui va contenir l'ensemble
	std::string nomFichierInput;	// Nom du fichier d'input
	std::string nomFichierOutput;	// Nom du fichier d'output
};
