#pragma once

/* Fichier d'en-t�te de la classe TimeInterval */

class TimeInterval
{
public:
	// Constructeur
	TimeInterval(long start=0, long end=0);

	// Destructeur
	~TimeInterval();

	// Getteurs
	long getStart() const;
	long getEnd() const;
	
	// Setteurs
	void setStart(long start);
	void setEnd(long end);


private:
	long start;	// D�but de l'intervalle de temps pour la prise de photo
	long end;	// Fin de l'intervalle de temps pour la prise de photo
};

