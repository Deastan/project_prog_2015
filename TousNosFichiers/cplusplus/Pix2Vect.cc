#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

struct coord
{
	int x;
	int f;
};

typedef vector <int> TabCouleur;
typedef vector<coord> TabPixel;

/***********************************************************************
 * 	Prototype des fonctions
 ***********************************************************************/
void affiche(string fichierEntreeNom, int largeurImage, int hauteurImage,
	int nbrCouleur, TabCouleur tabC1, TabPixel tabP1);

/***********************************************************************
 * 	Main
 ***********************************************************************/
int main()
{
//Début du programme "Afficher un message pour du debug"
	cout << "Le programme est lancé " << endl;
	
//initialisation des champs
	string fichierEntreeNom("Pixmap"),stringTemporaire(" ");
	//int temporaire;
	int largeurImage;
	int hauteurImage;
	int nbrCouleur;
	TabCouleur tabC1;
	TabPixel tabP1;
	coord temp;
	int JR(0);
	
//Demande à l'utilisateur le nom du fichier à lire
	/*cout << "Quel est le nom de l'image ? " << flush;
	cin >> ws;
	getline(cin,fichierEntreeNom);*/
	
//Pour ne pas avoir besoin de mettre l'extension
	fichierEntreeNom = fichierEntreeNom + ".txt"; 
	cout << "Le nom est : " << fichierEntreeNom << endl;
	
//Déclaration et ouverture du fichier
	ifstream fichierEntree(fichierEntreeNom.c_str());

//test si on a ouvert ou pas le fichier
	int i(0);
	if(fichierEntree.fail())
	{
		cerr << "Erreur lors de l'ouverture de " << fichierEntreeNom << endl;
	}else //Si on a réussi à ouvrir le fichier sans erreur, on va à l'étape suivante.
	{
		//Barrière d'affichage pour une partition
		cout << endl << "**************************************************" << endl << endl;
		cout << "Ouverture du fichier " << endl;
		
		//Boucle de ligne sur le fichier
		while(!fichierEntree.eof())//!fichierEntree.eof()
		{
			getline(fichierEntree, stringTemporaire,'\r'); // '\n'
			//Enregistrement de la première ligne dans largeur
			if(i == 0)
			{
				//largeurImage = stoi(stringTemporaire);
				
				stringstream ss(stringTemporaire);
				ss >> largeurImage;
					
			}else if(i == 1)//Enregistrement de la deuxième dans hauteur
			{
				//hauteurImage = stoi(stringTemporaire);
				
				
				stringstream ss(stringTemporaire);
				ss >> hauteurImage;
				
			}else if(i == 2)//Enregistrement du nombre de couleur
			{
				//nbrCouleur = stoi(stringTemporaire);
				
				stringstream ss(stringTemporaire);
				ss >> nbrCouleur;
				
			}else if(i == 3) // Faire le modulo
			{
				
				stringstream ss(stringTemporaire);
				ss >> JR;
				
				tabC1.push_back(JR);
				
			
				
			}else if(!fichierEntree.eof())
			{
				
				stringstream ss(stringTemporaire);
				ss >> JR;
				
				if(JR !=0 )
				{
					temp = {i%largeurImage, hauteurImage-(i/largeurImage)};
					tabP1.push_back(temp);
				}
			}
			//Incérmentation pour connaitre le numéro de la ligne
			i++;
		}//fin de la boucle
		
		fichierEntree.close();
		cout << "le fichier est fermée " << endl;
		
	}//fin du else
	
	
	
	

	//Barrière d'affichage pour une partition
	cout << endl << "**************************************************" << endl << endl;
	//Afficher dans la console les valeurs récupérées
	affiche(fichierEntreeNom, largeurImage, hauteurImage, nbrCouleur, tabC1, tabP1);
	
	//Barrière d'affichage pour une partition
	cout << endl << "**************************************************" << endl << endl;
	cout << "Fin du programme" << endl;
	return 0;
}//Fin de la main

/***********************************************************************
 * 	Definitions des fonctions
 ***********************************************************************/

void affiche(string fichierEntreeNom, int largeurImage, int hauteurImage,
	int nbrCouleur, TabCouleur tabC1, TabPixel tabP1)
{
	cout << "Le nom du fichier image est " << fichierEntreeNom << endl;
	cout << "La largeur de l'image est " << largeurImage << " et la hauteur est " << hauteurImage << endl;
	cout << "Il y a " << nbrCouleur << " couleurs." << endl;
	for(unsigned int i(0);i < tabC1.size();i++)
	{
		cout << "La couleur " << i+1 << " est " << tabC1[i] << endl;
	}
	
	for(unsigned int i(0);i < tabP1.size();i++)
	{
		cout << tabP1[i].x << " " << tabP1[i].f << endl;
	}
}

