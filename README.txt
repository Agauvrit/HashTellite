***********************************	
*********   HashTellite   *********
***********************************

Authors : - Jimmy Dor�
	  - Quentin Billaud	
	  - Aur�lien Gauvrit
	  - Yumiao Fu

Version 1.0 : fonctionnel

Les deux formats disponibles en sortie sont ".txt" ou ".csv". 
Si le format indiqu� est un csv ou un xls, le fichier de sortie contiendra les donn�es ordonn�es dans un tableur pour de futures analyses.
Sinon, une sortie texte "classique" appara�t dans le fichier.

Concernant le choix de fichiers d'entr�es, par d�faut les 4 seront lanc�s, cependant ce choix est modifiable dans le fichier "Abritre.h",
modifi�s les valeurs des lignes 19 a 22.


Ex�cution du programme : 

--> Sous visual studio :
Pr�ciser le r�pertoire des ex�cutables ainsi que le nom du fichier de sortie sous format .txt ou .csv dans les propri�t�s du projet.
Onglet Projet / Propri�t�s du projet / D�bogage / Arguments de la commande.

Exemple : C:\Users\Game\Source\Repos\HashTellite\HashTellite\Rep\ Resultats.txt

ATTENTION : Pensez mettre un "\" apr�s le nom du r�pertoire d'�xecutables

La liste des ex�cutables se trouvent dans le r�pertoire "Rep" et les informations propres au programme seront affich�s dans le fichier
"Resultats.txt".  


--> En ligne de commande :
Apr�s avoir g�n�r� les �xecutables sous visual studio, d�placer l'�x�cutable "HashTellite_Arbitre.exe" se trouvant dans
le r�pertoire "Release" dans le r�pertoire "HashTellite_Arbitre" ou se trouvent les dossiers "in" et "out".

Ex�cuter le programme sous un invit� de commande et placer vous au niveau de l'ex�cutable, dans le dossier "HashTellite_arbitre", � l'aide des commandes dir et cd.

Exemple : start HashTellite_Arbitre.exe C:\Users\Game\Source\Repos\HashTellite\HashTellite\Rep\ Resultats.txt


Tous les r�sultats propres a chaque ex�cutable (temps et score) ainsi que les temps moyens et scores moyens sont disponibles dans le
fichier de sortie sp�cifier en second argument. Ici "Resultats.txt"

PS : Si le programme ne fonctionne pas, v�rifiez que le dossier "out" dans hashtellite_arbitre existe bien. Dans le cas �ch�ant, cr�ez le.
PS2 : Plus d'informations sur le programme sont contenues dans le rapport final du projet