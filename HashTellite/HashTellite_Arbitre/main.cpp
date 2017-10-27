#include "Arbitre.h"

template <typename Func>
class Extract {
private:
	Func &func; 
public:
	Extract(Func &func) : func(func) {}; 
	void operator()(const char *filename) {
		func(filename);
	}
};

int main(int argc, char* argv[]) {
	Arbitre a(argv[1], argv[2]); // Indiquer le chemin du répertoire des fichiers à tester en relatif
	Extract<Arbitre> Extract(a);
	IterateOnFileDir<>(a.getRepoExe(), Extract);
	map < string, map<string, double>> matriceTemps = a.CalculTemps();
	IterateOnFileDir<>(".\\out\\", Extract);
	a.outputTableau(matriceTemps);
}