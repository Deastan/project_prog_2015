#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <typeinfo>

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

//Deux typedef pour faciliter la compréhension et la lecture du code
typedef vector <int> TabCouleur;
typedef vector<coord> TabPixel;

/***********************************************************************
 * 	Prototype des fonctions
 ***********************************************************************/
void affiche(string fichierEntreeNom, int largeurImage, int hauteurImage,
	int nbrCouleur, TabCouleur const& tabC1, TabPixel const& tabP1);
bool controlLargeur(int largeur);
bool controlHauteur(int hauteur);
bool controlCouleur(int nbrCouleur);
bool controlCouleurFond(TabCouleur tab);
void controlFonction(TabPixel const& tab);
void afficheTabPixel(TabPixel const& tabP1);
void afficheTabCouleur(TabCouleur const& tabC1);
bool lireTexte(string const& fichierEntreeNom, int& largeurImage, int& hauteurImage, 
				int& nbrCouleur, TabCouleur& tabC1, TabPixel& tabP1, string operating);				
bool ecrireCourbe(string fichierSortieNom, TabCouleur const& tabC1, TabPixel const& tabP1);
bool plusPetit(const coord &a, const coord &b);

/***********************************************************************
 * 	Main
 ***********************************************************************/
int main(int argc, const char* argv[])
{	
	//initialisation des variables
	string fichierEntreeNom("Pixmap.txt"), fichierSortieNom("courbes.m"), operating(argv[1]);
	int largeurImage, hauteurImage, nbrCouleur;
	TabCouleur tabC1;
	TabPixel tabP1;
	
	//lis le fichier texte donné par labview
	lireTexte(fichierEntreeNom, largeurImage, hauteurImage, 
				nbrCouleur, tabC1, tabP1, operating) and !controlCouleurFond(tabC1);
	
	//Trier le tableau 			
	sort(tabP1.begin(), tabP1.end(), plusPetit);
	
	//Contrôle qu'il y ait pas de valeur de x pour la même valeur
	controlFonction(tabP1);
	
	//Ecris le fichier courbe
	ecrireCourbe(fichierSortieNom, tabC1, tabP1);
	
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
	afficheTabPixel(tabP1);
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
				int& nbrCouleur, TabCouleur& tabC1, TabPixel& tabP1, string operating)
{
	//Déclaration des variables
	coord temp;
	string stringTemporaire;
	int nbrPixel;
	int nbrPixelMin(1000);
	int temporaireInt;
	char separation;
	ifstream fichierEntree(fichierEntreeNom.c_str());//fichier de lecture
	bool cond(false), condCouleur(false), condLargeur(false), condHauteur(false);
	
	//partie pour utiliser le programme sous mac, linux, windows car pas le même os dans le groupe !
	if(operating.compare("Mac OS"))
	{
		separation = '\r';
	}else if(operating.compare("Windows"))
	{
		separation = '\n';
	}else if(operating.compare("Linux"))
	{
		separation = '\n';
	}
	
	//Contrôle si le fichier existe et si on peut l'ouvrir, gestion d'une erreur
	if(fichierEntree.fail())
	{
		usage("Impossible d'ouverture le fichier : " + fichierEntreeNom);
	}else //Si on a réussi à ouvrir le fichier sans erreur, on va à l'étape suivante.
	{
		//déclaration de la variable d'indice en localité spaciale
		int i(0);
		
		//Boucle de ligne sur le fichier d'entrée
		while(!fichierEntree.eof())//!fichierEntree.eof()
		{
			
			getline(fichierEntree, stringTemporaire, separation); // '\n'
			
			// note: les ligne de "   " seront des 0 seules les lignes "" seront signalées
			if(stringTemporaire == "" and i != (largeurImage*hauteurImage+3+nbrCouleur))
			{
					usage("Il y a une ligne vide dans le fichier");
			}else if(i != (largeurImage*hauteurImage+3+nbrCouleur))
			{
				//récupère l'entier avec ou sans caractère après
				stringstream ss(stringTemporaire);
				if((ss >>  temporaireInt).fail())
				{
					for(unsigned int k(0);((k<stringTemporaire.size() and (ss >> temporaireInt).fail()==1) or (stringTemporaire.size()) == 1);k++)
					{
						if(stringTemporaire.size() > 1)
						{
							if(stringTemporaire != "")
							{
								//On réussi à enlever les caractaires avant et récupérer l'entier
								stringTemporaire.erase(0,1);
								stringstream ss(stringTemporaire);
							}else
							{
								usage("La ligne contient des caractères qui ne peuvent pas être convertit en entier !");
							}
						}else
						{
							if(stringTemporaire[0] >= '0' and stringTemporaire[0] <= '9')
							{
								stringstream ss(stringTemporaire);
							}else
							{
								usage("La ligne contient des caractères qui ne peuvent pas être convertit en entier !");
							}
						}
					}
				
				}
				
				
				
				
				// si il arrive à convertire et que ce n'est pas vide mais qu'on veut être sûre qu'il n'y a pas 2 entiers sur la même ligne (tous les autres cas déjà checkés)
				else if (stringTemporaire.find(" ")!=string::npos and stringTemporaire.find(" ")>0) //trouve un " " plus loin que position 0 de la string -> peut etre un cas interessant
				{
					// enlève le 1er entier et le " "
					stringTemporaire.erase(0,stringTemporaire.find(" ")+1);
					stringstream ss(stringTemporaire);
					//reteste si il y a possibilité de convertir la fin de la string en entier (auquel cas on en aurait 2 au moins)
					if((!((ss >>  temporaireInt).fail()))and (stringTemporaire[0]!=' '))
					{
						usage("Il y a deux entiers sur la même ligne ou des espaces inutiles");
					}
				}
				
				
				
				//début des enregistrements après les contrôles et une partie des gestions des erreurs.
				if(i == 0)
				{
					//Enregistrement de la première ligne dans largeur
					largeurImage=temporaireInt;
					condLargeur = controlLargeur(largeurImage);
				}else if(i == 1 and condLargeur)
				{
					//Enregistrement de la deuxième dans hauteur
					hauteurImage=temporaireInt;
					condHauteur = controlHauteur(hauteurImage);
				}else if(i == 2 and condLargeur and condHauteur)
				{
					//Enregistrement du nombre de couleur
					nbrCouleur=temporaireInt;
					condCouleur = controlCouleur(nbrCouleur);
				}else if(2<i and i<=(2+nbrCouleur) and condLargeur and condHauteur and condCouleur)
				{		
					//ajoute une ligne au tableau des couleurs contenant #couleur
					temporaireInt=temporaireInt;
					tabC1.push_back(temporaireInt);
				}else
				{
					if(condLargeur and condHauteur and condCouleur)
					{	
						if(i==3+nbrCouleur)
						{
							if(temporaireInt !=0)
							{
								usage("Le premier pixel n'a pas la couleur de fond !");
							}
						}else if(i==(largeurImage*hauteurImage+3+nbrCouleur+1))
						{
							if(temporaireInt !=0)
							{
								usage("Le dernier pixel n'a pas la couleur de fond !");
							}
						}
						if(!fichierEntree.eof() and temporaireInt !=0 )
						{
							//enregistre les points par rapport à la hauteur et largeur de l'image
							//(i+3+nbrCouleur) représente la ligne a partir de la liste de pixel
							//-1 pour avoir 0 quand hauteur de l'image =1
							temp = {(i-3-nbrCouleur)%largeurImage, hauteurImage-1-((i-3-nbrCouleur)/largeurImage), temporaireInt};
							tabP1.push_back(temp);
						}
					}
				}
			}
			//Incérmentation pour connaitre le numéro de la ligne
			i++;
			//Nombre de pixel dans l'image
			nbrPixel = i-3-nbrCouleur;
		}//fin de la boucle while
		//fermeture du fichier
		fichierEntree.close();
		
		//contrôle du nombre de pixel est au dessus de nbrPixelMax
		if(nbrPixel < nbrPixelMin)
		{
			usage("Le nombre de pixel est trop petit ! Il doit y en avoir plus que");
			cond = false;
		}else
		{
			cond = true;
		}
	}
	return cond;
}//fin de la fonction lire

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
	return true;//N'est pas utilisé !
}

//Retourne un booleen pour dire si la largeur est comprise dans les bornes.
bool controlLargeur(int largeur)
{
	bool cond(false);
	if(largeur <= 1000 and largeur >= 10)
	{
		cond = true;
	}else
	{
		usage("La largeur de l'image est invalide !");
	}
	
	return cond;
}
//Retourne un booleen pour dire si la hauteur est comprise dans les bornes.
bool controlHauteur(int hauteur)
{
	bool cond(false);
	
	if(hauteur <= 1000 and hauteur >= 10)
	{
		cond = true;
	}else
	{
		usage("La hauteur de l'image est invalide !");
	}
	
	return cond;
}
//Retourne un booleen pour dire si le nombre de couleur est comprise dans les bornes.
bool controlCouleur(int nbrCouleur)
{
	bool cond(false);
	
	if(nbrCouleur < 1 and nbrCouleur > 20)
	{
		usage("Le nombre de couleur de l'image doit être en 1 et 20 !");
		
	}else
	{
		cond = true;
	}
	
	return cond;
}
//Retourne un booleen pour dire si le tableau de couleur contient un 0 qui est la couleur de fond
//Ce qui n'est pas possible car on enregistre tout les nombres différents de zéro dans notre tableau
//Mais le contrôle est demandé donc on le met
bool controlCouleurFond(TabCouleur tab)
{	
	for(unsigned int i(0);i<tab.size();i++)
	{
		if(tab[i]==0)
		{
			usage("Il y a une courbe avec la couleur blanche (0) qui est la couleur de fond !");
			return false;
		}
	}
	return true;
}

//contrôle du nombre que ça soit bien une fonction (test de la droite verticale)
void controlFonction(TabPixel const& tab)
{
	for(unsigned int i(0);i<tab.size();i++)
	{
		for(unsigned int j(0);j<tab.size();j++)
		{
			if(tab[i].x == tab[j].x and i!=j and tab[i].couleur == tab[j].couleur)
			{
				usage("Il y a deux valeurs de f(x) pour un même x pour une même courbe !");
			}
		}
	}
}
