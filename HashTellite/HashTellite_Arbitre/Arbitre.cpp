#include "Arbitre.h"
#include "System.h"


using namespace std;
using namespace std::chrono;

/**
*	Constructeur de la classe Arbitre
*	@param repo
*			Chemin indiquant le répertoire où se trouvent les exécutables
*	@param fileOut
*			nom du fichier de sortie (txt ou csv)
*/
Arbitre::Arbitre(char* repo, char* fileOut)
{
	this->repoExe = repo;
	this->name_file_out = fileOut;
	if(FOREVER_ALONE) this->liste_filesin.push_back(".\\in\\forever_alone.in");
	if (CONSTELLATION) this->liste_filesin.push_back(".\\in\\constellation.in");
	if (WEEKEND) this->liste_filesin.push_back(".\\in\\weekend.in");
	if (OVERLAP) this->liste_filesin.push_back(".\\in\\overlap.in");
	score_global["forever_alone"] = 139376;
	score_global["constellation"] = 2992745;
	score_global["weekend"] = 6711964;
	score_global["overlap"] = 1161996;
}

/**
*	Destructeur de la classe Arbitre
*/
Arbitre::~Arbitre()
{
}

/**
*	Fonction permettant de spliter une string selon un caractère et qui met les différentes partie du split dans un tableau
*	@param s
*			string à couper
*	@param delim
*			char de delimitation (si on veut couper aux '\' ou aux '.'...)
*	@param elems
*			tableau qui va contenir les différentes parties du split
*/
void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

/**
*	Fonction permettant de spliter une string selon un caractère et qui renvoie les différentes partie du split dans un tableau
*	@param s
*			string à couper
*	@param delim
*			char de delimitation (si on veut couper aux '\' ou aux '.'...)
*	@return vector<string>
*			tableau qui va contenir les différentes parties du split
*/
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}


/**
*	Fonction permettant de récupérer le nom d'un fichier via un chemin spécifié
*  
*	@param file
*			le chemin du fichier (truc/machin/toto.txt)
*	@return string
*			le nom du fichier (toto)
*/
string Arbitre::getFileName(string file) {
	std::vector<std::string> x = split(file, '\\');
	std::vector<std::string> x2 = split(x[x.size() - 1], '.');

	return x2[x2.size()-2];
}


/**
*	Fonction permettant de récupérer une partie du nom d'un fichier via un chemin spécifié
*
*	@param file
*			le chemin du fichier (truc/machin/Hashtellite-forever_alone.txt)
*	@return string
*			la partie du fichier qui nous intéresse(forever_alone)
*/
string Arbitre::getFileNameOut(string file) {
	std::vector<std::string> x = split(file, '\\');
	std::vector<std::string> x2 = split(x[x.size() - 1], '.');
	std::vector<std::string> x3 = split(x2[x2.size() - 2], '-');

	return x3[1];
}


/**
*	Fonction permettant de déterminer si le fichier est un .exe
*
*	@param file
*			Le chemin du fichier à déterminer (titi\toto\repExe\app.exe)
*	@return bool
*			renvoie true si le fichier est un exe, faux sinon
*/
bool Arbitre::isExe(const char * file) {
	std::vector<std::string> x = split(file, '\\');
	std::vector<std::string> x2 = split(x[x.size() - 1], '.');

	return x2[1] == "exe";
}

/**
*	Fonction permettant de déterminer si le fichier est un .out
*
*	@param file
*			Le chemin du fichier à déterminer (titi\toto\repOut\example.out)
*	@return bool
*			renvoie true si le fichier est un out, faux sinon
*/
bool Arbitre::isOut(const char * file) {
	std::vector<std::string> x = split(file, '\\');
	std::vector<std::string> x2 = split(x[x.size() - 1], '.');

	return x2[1] == "out";
}

/**
*	Fonction permettant de déterminer si le fichier est un .csv ou un .xls
*
*	@param file
*			Le chemin du fichier à déterminer (titi\toto\repExe\tableur.csv)
*	@return bool
*			renvoie true si le fichier est un .csv ou un.xls, faux sinon
*/
bool Arbitre::isCsv(const char * file) {
	std::vector<std::string> x = split(file, '\\');
	std::vector<std::string> x2 = split(x[x.size() - 1], '.');

	return x2[1] == "csv" || x2[1] == "xls";
}

/**
*	Fonction qui est appelée sur chaque fichier quand on parcourt un dossier
*
*	@param file
*			Le chemin du fichier que l'on parcourt
*/
void Arbitre::operator()(const char* file) {
	//On ajoute le chemin de l'executable dans une liste
	if (this->isExe(file)) {
		this->liste_exe.push_back(file);
	}
	else if (this->isOut(file)) {
		//Pour filtrer les .out inutile pouvant se trouver dans le dossier
		for (size_t i = 0; i < this->liste_filesin.size(); i++)
		{
			if (this->getFileNameOut(file) == this->getFileName(this->liste_filesin.at(i))) {
				this->liste_out.push_back(file);
			}
		}
	}
}

/**
*	Fonction permettant de calculer le temps d'exécution pour les fichiers d'entrée spécifiés, ainsi que les exe
*
*	@return map < string, map<string, double>>
*			sous la forme de :		{ 
*									   exe1 -> {fileIn1->4,fileIn2->8}
*									   exe2 -> {fileIn1->9,fileIn2->5}
*									}
*/
map < string, map<string, double>> Arbitre::CalculTemps(){

	map < string, map<string, double>> tab_recap_global;
	map<string, double> tab_recap_pour_exe;

	//On parcourt tous les exécutables
	for (int i = 0; i < this->liste_exe.size(); i++){
		string nameExe = this->getFileName(this->liste_exe.at(i)); //On récupère le nom de l'exe
		//On parcourt tous les fichiers d'entrée
		for (int j = 0; j < this->liste_filesin.size(); j++)
		{
			string filename = this->getFileName(this->liste_filesin.at(j));
			string command = this->liste_exe.at(i) + ' ' + this->liste_filesin.at(j) + " ./out/" + nameExe + '-' + filename + ".out"; // machin.exe truc.in truc.out				
			high_resolution_clock::time_point t1 = high_resolution_clock::now(); //On démarre le chrono
			system((char*)command.c_str()); //On appelle l'exe avec les paramètres préparés auparavant
			high_resolution_clock::time_point t2 = high_resolution_clock::now(); // On stoppe le chrono
			auto duration = duration_cast<milliseconds>(t2 - t1).count();
			tab_recap_pour_exe[filename] = duration; 
		}
		tab_recap_global[nameExe] = tab_recap_pour_exe;
	}

	return tab_recap_global;
}

/**
*	Fonction permettant de calculer le score pour les fichiers d'entrée spécifiés, ainsi que les exe
*
*	@return map < string, map<string, int>>
*			sous la forme de :		{
*									   exe1 -> {fileIn1->48000,fileIn2->8536}
*									   exe2 -> {fileIn1->12000,fileIn2->5432}
*									}
*/
map < string, map<string, int>> Arbitre::calculScore() {
	map < string, map<string, int>> tab_recap_global;
	map<string, int> tab_recap_pour_out;

	for (int i = 0; i < this->liste_exe.size(); i++) {//On parcourt tous les exe
		string nameExe = this->getFileName(this->liste_exe.at(i));
		for (int j = 0; j < this->liste_out.size(); j++) //On parcourt tous les fichiers de sortie
		{
			string filename = this->getFileNameOut(this->liste_out.at(j)); 
			string fileIn = ".\\in\\" + filename + ".in";
			Input* i = new Input(fileIn, ""); //On crée un nouveau système avec un fichier d'entrée
			i->createSystem();
			int score = i->getSystem().comptePoint(this->liste_out.at(j)); //On calcule le score de la solution en fonction du fichier de sortie
			tab_recap_pour_out[filename] = score;
		}
		tab_recap_global[nameExe] = tab_recap_pour_out;
	}
	return tab_recap_global;

}

/**
*	Fonction prenant les différentes matrices de temps et de score, les parsant pour les afficher dans un fichier (affichage différent si fichier.csv ou fichier.txt
*
*	@param matriceTemps la matrice correspondant à la fonction calculTemps
*/
void Arbitre::outputTableau(map < string, map<string, double>> matriceTemps) {

	map < string, map<string, int>> matriceScore = this->calculScore();
	map<string, double> tempsMoyenMs;
	map<string, double> scoreMoyen;
	bool csv = isCsv(this->name_file_out);
	ofstream fichier(this->name_file_out, ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

	if (fichier)
	{	
		//On parcourt la matrice Temps
		for (map < string, map<string, double>>::iterator it = matriceTemps.begin(); it != matriceTemps.end(); ++it)
		{
			if (csv) { fichier << it->first << endl << "File In ;" << "Temps (ms) ;" << "Temps (s) ;" << "Score ; " << "Pourcentage %" << endl; }
			else { fichier << "Nom Exe : " << it->first << endl << "---------------------" << endl; }
			for (map<string, double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)//On parcourt la deuxième map
			{
				//On récupère le temps et le score, on les manipule et on les met dans le fichier de sortie
				double tempsSec = it2->second / 1000;
				int score = matriceScore[it->first][it2->first];
				double percentage = (static_cast<double>(score) / this->score_global[it2->first]) * 100;
				if (csv) { fichier << it2->first << ";" << it2->second << ";" << tempsSec << ";" << score << ";" << percentage << endl; }
				else { fichier << "FileIn : " << it2->first << ", Temps : " << it2->second << "ms (" << tempsSec << "s)" << ", Score : " << score << " , Pourcentage : " << percentage << "%" << endl; }
				tempsMoyenMs[it2->first] += it2->second;
				scoreMoyen[it2->first] += score;
			}
			if (csv) { fichier << endl; }
			else { fichier << endl << endl; }
		}

		//Partie pour écrire sur le fichier, en rapport avec la moyenne des temps et des scores
		if (csv) { fichier << endl << "Moyenne globale " << endl << "File In;" << "Temps Moyen (ms);" << "Temps Moyen (s);" << "Score Moyen" << endl; }
		else {fichier << endl << "Moyenne globale " << endl << "---------------------" << endl;}
		for (map<string, double>::iterator it3 = tempsMoyenMs.begin(); it3 != tempsMoyenMs.end(); ++it3) {
			double tempsMoyenSec = it3->second / this->liste_exe.size() / 1000;
			scoreMoyen[it3->first] /= this->liste_exe.size();
			if (csv) {fichier << it3->first << ";" << it3->second / this->liste_exe.size() << ";" << tempsMoyenSec << ";" << scoreMoyen[it3->first] << endl; }
			else { fichier << "FileIn : " << it3->first << ", Temps : " << it3->second / this->liste_exe.size() << "ms (" << tempsMoyenSec << "s)" << ", Score Moyen :" << scoreMoyen[it3->first] << endl; };
		}
	}
	else
		cerr << "Le fichier est ouvert, il faut le fermer si tu veux mettre tes données dedans" << endl;
}