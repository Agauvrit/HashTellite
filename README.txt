***********************************	
*********   HashTellite   *********
***********************************

Authors : - Jimmy Doré
	  - Quentin Billaud	
	  - Aurélien Gauvrit
	  - Yumiao Fu

Version 1.0 : fonctionnel

Les deux formats disponibles en sortie sont ".txt" ou ".csv". 
Si le format indiqué est un csv ou un xls, le fichier de sortie contiendra les données ordonnées dans un tableur pour de futures analyses.
Sinon, une sortie texte "classique" apparaît dans le fichier.

Concernant le choix de fichiers d'entrées, par défaut les 4 seront lancés, cependant ce choix est modifiable dans le fichier "Abritre.h",
modifiés les valeurs des lignes 19 a 22.


Exécution du programme : 

--> Sous visual studio :
Préciser le répertoire des exécutables ainsi que le nom du fichier de sortie sous format .txt ou .csv dans les propriétés du projet.
Onglet Projet / Propriétés du projet / Débogage / Arguments de la commande.

Exemple : C:\Users\Game\Source\Repos\HashTellite\HashTellite\Rep\ Resultats.txt

ATTENTION : Pensez mettre un "\" après le nom du répertoire d'éxecutables

La liste des exécutables se trouvent dans le répertoire "Rep" et les informations propres au programme seront affichés dans le fichier
"Resultats.txt".  


--> En ligne de commande :
Après avoir généré les éxecutables sous visual studio, déplacer l'éxécutable "HashTellite_Arbitre.exe" se trouvant dans
le répertoire "Release" dans le répertoire "HashTellite_Arbitre" ou se trouvent les dossiers "in" et "out".

Exécuter le programme sous un invité de commande et placer vous au niveau de l'exécutable, dans le dossier "HashTellite_arbitre", à l'aide des commandes dir et cd.

Exemple : start HashTellite_Arbitre.exe C:\Users\Game\Source\Repos\HashTellite\HashTellite\Rep\ Resultats.txt


Tous les résultats propres a chaque exécutable (temps et score) ainsi que les temps moyens et scores moyens sont disponibles dans le
fichier de sortie spécifier en second argument. Ici "Resultats.txt"

PS : Si le programme ne fonctionne pas, vérifiez que le dossier "out" dans hashtellite_arbitre existe bien. Dans le cas échéant, créez le.
PS2 : Plus d'informations sur le programme sont contenues dans le rapport final du projet