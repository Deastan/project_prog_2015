#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
<<<<<<< HEAD
#include <algorithm>
=======
#include <sstream>
>>>>>>> 8f1bb274db5190fc4e4153490661966d4a17e526

using namespace std;

//Permet d'afficher les erreurs 
int usage(string message) 
{
    cerr << "ERREUR : ";
    cerr << message << endl;
    exit(1);
}

//Structure pour récupérer les points sous forme de coordonnée (x, y)
//x est l'abcisse du graphe
//f est l'ordonnée du graphe
//couleur permet de savoir qu'elle est la couleur du point
struct coord
{
	int x;
	int f;
	int couleur;
};

//Deux typedef pour faciliter la compréhension du code
typedef vector <int> TabCouleur;
typedef vector<coord> TabPixel;

/***********************************************************************
 * 	Prototype des fonctions
 ***********************************************************************/
void affiche(string fichierEntreeNom, int largeurImage, int hauteurImage,
	int nbrCouleur, TabCouleur const& tabC1, TabPixel const& tabP1);

void afficheTabPixel(TabPixel const& tabP1);
void afficheTabCouleur(TabCouleur const& tabC1);
bool lireTexte(string const& fichierEntreeNom, int& largeurImage, int& hauteurImage, 
				int& nbrCouleur, TabCouleur& tabC1, TabPixel& tabP1);
bool ecrireCourbe(string fichierSortieNom, TabCouleur const& tabC1, TabPixel const& tabP1);
bool plusPetit(const coord &a, const coord &b);

/***********************************************************************
 * 	Main
 ***********************************************************************/
int main(int argc, const char * argv[])
{	
	//initialisation des variables
	string fichierEntreeNom("Pixmap.txt"), fichierSortieNom("courbes.m");
	int largeurImage, hauteurImage, nbrCouleur;
	TabCouleur tabC1;
	TabPixel tabP1;
<<<<<<< HEAD
=======
	coord temp;
	int JR(0);
>>>>>>> 8f1bb274db5190fc4e4153490661966d4a17e526
	
	if(!lireTexte(fichierEntreeNom, largeurImage, hauteurImage, 
				nbrCouleur, tabC1, tabP1))//lis le fichier texte donné par labview
	{
		usage("Le fichier n'a pas pu être lu !");			
	}
	sort(tabP1.begin(), tabP1.end(), plusPetit);//Trier le tableau 
	if(!ecrireCourbe(fichierSortieNom, tabC1, tabP1))//Ecrit le fichier courbes
	{
		usage("Le fichier n'a pas pu être écrit ! ");
	}
	
	return 0;
	
}//Fin de la main

/***********************************************************************
 * 	Definitions des fonctions
 ***********************************************************************/

//Afficher le tableau de pixel
void affiche(string const& fichierEntreeNom, int const& largeurImage, int const& hauteurImage,
	int const& nbrCouleur, TabCouleur const& tabC1, TabPixel const& tabP1)
{
	cout << "Le nom du fichier image est " << fichierEntreeNom << endl;
	cout << "La largeur de l'image est " << largeurImage << " et la hauteur est " << hauteurImage << endl;
	cout << "Il y a " << nbrCouleur << " couleurs." << endl;
	afficheTabCouleur(tabC1);
	//afficheTabPixel(tabP1);
}

//Afficher le tableau de couleur
void afficheTabCouleur(TabCouleur const& tabC1)
{
	for(unsigned int i(0);i<tabC1.size();i++)
	{
		cout << "La couleur " << i+1 << " est " << tabC1[i] << endl;
	}
}
//Afficher le tableau de pixel
void afficheTabPixel(TabPixel const& tabP1)
{
	for(unsigned int i(0);i < tabP1.size();i++)
	{
		cout << tabP1[i].x << " " << tabP1[i].f << " " << tabP1[i].couleur << endl;
	}
}
//Fonction pour "l'objet" structure qui retourne un bool 
//Si x1 < x2 => true et sinon false
bool plusPetit(const coord &a, const coord &b)
{
    return a.x < b.x;
}
//Fonction qui va lire le fichier donnée en paramètre et l'enregistrer dans les différents tableaux
//string const& fichierEntreeNom Donne le nom du fichier nécessaire à l'ouverture du fichier
//int& largeurImage Enregistre la largeur du fichier lecture dans cette variable de référence largeurImage
//int& hauteurImage Enregistre la hauteur du fichier lecture dans cette variable de référence hauteurImage
//int& nbrCouleur Enregistre le nombre de couleur contenu dans le fichier dans la variable référencée
//TabCouleur& tabC1 Tableau qui contiendra les valeurs de couleur dans le fichier
//TabPixel& tabP1 Tableau qui contiendra les coordonnées et couleurs de chacun des points
bool lireTexte(string const& fichierEntreeNom, int& largeurImage, int& hauteurImage, 
				int& nbrCouleur, TabCouleur& tabC1, TabPixel& tabP1)
{
	//Déclaration des variables
	coord temp;
	string stringTemporaire;
	ifstream fichierEntree(fichierEntreeNom.c_str());//fichier de lecture

	if(fichierEntree.fail())//test si on a ouvert ou pas le fichier
	{
		usage("Impossible d'ouverture le fichier : " + fichierEntreeNom);
		
	}else //Si on a réussi à ouvrir le fichier sans erreur, on va à l'étape suivante.
	{
		int i(0);//déclaration de la variable d'indice en localité spaciale
		
		//Boucle de ligne sur le fichier d'entrée
		while(!fichierEntree.eof())//!fichierEntree.eof()
		{
			getline(fichierEntree, stringTemporaire,'\r'); // '\n'
			
			if(i == 0)
			{
<<<<<<< HEAD
				largeurImage = stoi(stringTemporaire);//Enregistrement de la première ligne dans largeur
				
			}else if(i == 1)
			{
				hauteurImage = stoi(stringTemporaire);//Enregistrement de la deuxième dans hauteur
				
			}else if(i == 2)
			{
				nbrCouleur = stoi(stringTemporaire);//Enregistrement du nombre de couleur
				
			}else if(2<i and i<=(2+nbrCouleur))
			{		//ajoute une ligne au tableau des couleurs contenant #couleur
					tabC1.push_back(stoi(stringTemporaire));
			}else
			{
				if(!fichierEntree.eof() and stoi(stringTemporaire) !=0 )
=======
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
>>>>>>> 8f1bb274db5190fc4e4153490661966d4a17e526
				{
					//enregistre les points par rapport à la hauteur et largeur de l'image
					temp = {i%largeurImage, hauteurImage-(i/largeurImage), stoi(stringTemporaire)};
					tabP1.push_back(temp);
				}
			}
			i++;//Incérmentation pour connaitre le numéro de la ligne
		}//fin de la boucle
		fichierEntree.close();//fermeture du fichier
	}//fin du else
	return true;//Ne marche pas encore
}//fin de la fonction

//Fonction qui va créer et écrire les données commes demandé dans le cahier des charges du projet
//string fichierSortieNom Prend le nom donné pour créer le fichier 
//TabCouleur const& tabC1 récupération des données du tableaux couleur pour les mettre dans le fichier courbes.m
//TabPixel const& tabP1 récupération des données du tableaux pixel pour les mettre dans le fichier courbes.m
bool ecrireCourbe(string fichierSortieNom, TabCouleur const& tabC1, TabPixel const& tabP1)
{
	//Déclaration et création du fichier
	ofstream fichierSortie(fichierSortieNom);
	
	if(fichierSortie.fail())//Gestion de l'erreur
	{
		usage("Impossible d'écrire sur le fichier : " + fichierSortieNom);
	}else //Ecriture du fichier de sortie
	{
		for(unsigned int j(0);j<tabC1.size();j++)
		{
			fichierSortie << "C" << j << " = [" << endl;
			
			for(unsigned int i(0);i<tabP1.size();i++)
			{
				if(tabC1[j]==tabP1[i].couleur)
				{
					fichierSortie << tabP1[i].x << " " << tabP1[i].f << endl;
				}
			}
			fichierSortie << "];" << endl;
		}
		fichierSortie.close();
	}
	return true;//Ne marche pas encore
}

