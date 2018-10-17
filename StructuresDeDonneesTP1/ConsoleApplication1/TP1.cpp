/****************************************************************
*	Noms : Timothée Drouot & Hans Darmstadt-Belanger			*
*	Date :		10-10-2018										*
*	But	 :	Créer un programme qui construit une liste de		*
*			professeurs à partir d'un fichier d'infrmation		*
*			et qui execute des manipulations sur cette liste	*
*			à partir des commandes retrouvées dans un autre		*
*			fichier de commandes								*
*****************************************************************/

#pragma region Includes
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#pragma endregion Includes

using namespace std;

#pragma region Structures
struct cours
{
	string sigle;
	cours *suivant;
	int nbOccurence;
};

struct etudiant
{
	string nom;
	etudiant *suivant;
};

struct Professeur
{
	string nom;
	int ancien;
	int nombreEtudiants;
	cours *teteListeDeCours;
	etudiant *teteListeEtudiants;
	Professeur *suivant;

};
#pragma endregion Structures

class DossierProfesseur {
private:

#pragma region ProprietesPrivees
	void LireFichierDeDonnees(string fichierAOuvrir, Professeur *ptrTeteListeProfesseurs);
	void LireFichierParametres(string fichierAOuvrir, Professeur *ptrTeteListeProfesseurs);
	void typeDeDonneeAEnregistrer(string ligne, Professeur *ptrTeteListeProfesseurs);
	void typeDeParametre(string ligne, Professeur *ptrTeteListeProfesseurs);
	void enregistrerNomProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs);
	void enregistrerAcienneteProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs);
	void enregistrerCoursProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs);
	void enregistrerEtudiantProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs);
	cours *ajouterCoursListeCoursCommun(cours *queueListe, string sigleCours);
	Professeur* trouverQueueDeListe(Professeur *ptrTeteListeProfesseurs);
	cours* trouverQueueDeListe(cours *ptrTeteListeProfesseurs);
	etudiant* trouverQueueDeListe(etudiant *ptrTeteListeProfesseurs);
	void initialiserPointerProfesseurNullPtr(Professeur *ptrTeteListeProfesseurs);
#pragma endregion ProprietesPrivees

public:
	#pragma region ProprieteesPubliques
bool listeAUneTete = false;
	DossierProfesseur();
	~DossierProfesseur();
	void suppressionProfesseurParAncienneté(int ancien, Professeur *ptrTeteListeProfesseurs);
	void afficherCoursCommun(string profA, string profB, Professeur *ptrTeteListeProfesseurs);
	void afficherCoursLePlusDemander(Professeur *ptrTeteListeProfesseurs);
	void afficherSiUnEtudiantEstSuperviseParPlusDUnProfesseur(Professeur *ptrTeteListeProfesseurs, string nomEtu);
	void afficherProfesseurQuiSuperviseLePlusDEtudiant(Professeur *ptrTeteListeProfesseurs);
	void recopierSorties(string filename);
	Professeur *tete;
	Professeur *queue;
	int typeDonnee = 0;
	string sorties;
#pragma endregion ProprieteesPubliques
};




/// <summary>
/// Lis le contenu du fichier de données et appelle les fonctions d'enregistrement pour les données lues
/// </summary>
/// <param name="fichierAOuvrir">Le  fichier à lire.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::LireFichierDeDonnees(string fichierAOuvrir, Professeur *ptrTeteListeProfesseurs)
{
	fstream entree;
	string ligne;

	entree.open(fichierAOuvrir, ios::in);
	if (entree) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			cout << ligne;
			typeDeDonneeAEnregistrer(ligne, ptrTeteListeProfesseurs);
		}
	}
	entree.close();
}

/// <summary>
/// Lis le fichier de paramètres et appelle les fonctions de traitement des données
/// </summary>
/// <param name="fichierAOuvrir">Le fichier à ouvrir contenant les paramètres.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::LireFichierParametres(string fichierAOuvrir, Professeur *ptrTeteListeProfesseurs)
{
	fstream entree;
	string ligne;

	entree.open(fichierAOuvrir, ios::in);
	if (entree) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			cout << ligne;
			typeDeParametre(ligne, ptrTeteListeProfesseurs);
		}
	}
	entree.close();
}

/// <summary>
/// Reçois la ligne lue et appelle la fonction nécessaire selon le type de donnée à enregistrer
/// </summary>
/// <param name="ligne">La ligne qui vient d'être lue par la fonction de lecture.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::typeDeDonneeAEnregistrer(string ligne, Professeur *ptrTeteListeProfesseurs)
{
	switch (typeDonnee)
	{
	case 0:
		enregistrerNomProfesseur(ligne, ptrTeteListeProfesseurs);
		break;
	case 1:
		enregistrerAcienneteProfesseur(ligne, ptrTeteListeProfesseurs);
		break;
	case 2:
		enregistrerCoursProfesseur(ligne, ptrTeteListeProfesseurs);
		break;
	case 3:
		enregistrerEtudiantProfesseur(ligne, ptrTeteListeProfesseurs);
		break;
	default:
		cout << "Erreur : int inconnu" << endl;
		sorties += "Erreur : int inconnu\n";
		system("pause");
		break;
	}
}

/// <summary>
/// Reçois la ligne lue par la fonction de lecture des paramêtres et appelle la fonction pertinente pour effectuer les traitements
/// </summary>
/// <param name="ligne">La ligne lue et à interpréter</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::typeDeParametre(string ligne, Professeur * ptrTeteListeProfesseurs)
{
	string parametreDAction = ligne.substr(0, 1);

	if (parametreDAction == "%")
	{
		int longueurLigne = ligne.length();
		string argument = ligne.substr(2, longueurLigne - 2);
		int argumentLigne = std::stoi(argument);
		suppressionProfesseurParAncienneté(argumentLigne, ptrTeteListeProfesseurs);
	}
	else if (parametreDAction == "&")
	{
		int longueurLigne = ligne.length();
		string argument = ligne.substr(2, longueurLigne - 2);
		std::size_t pos = argument.find(" ");
		string nomProfB = argument.substr(pos + 1);
		int longueurNomProfB = nomProfB.length();
		std::size_t pos2 = ligne.find(" ");
		string nomProfA = ligne.substr(pos2 + 1, longueurNomProfB);
		afficherCoursCommun(nomProfA, nomProfB, ptrTeteListeProfesseurs);
	}
	else if (parametreDAction == "+")
	{
		afficherCoursLePlusDemander(ptrTeteListeProfesseurs);
	}
	else if (parametreDAction == "*")
	{
		int longueurLigne = ligne.length();
		string argument = ligne.substr(2, longueurLigne - 2);
		std::size_t pos = argument.find(" ");
		string nomEtu = argument.substr(pos + 1);
		afficherSiUnEtudiantEstSuperviseParPlusDUnProfesseur(ptrTeteListeProfesseurs, nomEtu);
	}
	else if (parametreDAction == "@")
	{
		afficherProfesseurQuiSuperviseLePlusDEtudiant(ptrTeteListeProfesseurs);
	}
	else if (parametreDAction == "$")
	{
		recopierSorties("nouveau.txt");
	}
	else
	{
		cout << "Erreur de parametre." << endl;
		sorties += "Erreur de parametre.\n";
		system("pause");
	}
}

/// <summary>
/// Enregistre le nom d'un nouveau professeur à la fin de la liste.
/// </summary>
/// <param name="ligne">La ligne venant d'être lue et qui contient le nom du professseur à enregistrer</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::enregistrerNomProfesseur(string ligneLue, Professeur *ptrTeteListeProfesseurs)
{
	Professeur *queueListeProfesseurs = trouverQueueDeListe(ptrTeteListeProfesseurs);
	queueListeProfesseurs->nom = ligneLue;
	typeDonnee = 1;
}

/// <summary>
/// Enregistre l'ancienneté d'un aciennete professeur.
/// </summary>
/// <param name="ligne">La ligne lue contenant l'ancienneté du professeur.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::enregistrerAcienneteProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs)
{
	Professeur *queueListeProfesseurs = trouverQueueDeListe(ptrTeteListeProfesseurs);
	queueListeProfesseurs->ancien = std::stoi(ligne);
	typeDonnee = 2;
}

/// <summary>
/// Ajoute un cours à la liste de cours du dernier professeur dans la liste
/// </summary>
/// <param name="ligne">La ligne lue du fichier contenant le cours à ajouter.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::enregistrerCoursProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs)
{
	if (ligne == "&") {
		typeDonnee = 3;
	}
	else
	{
		cours* membreDeLaListeDeCours = new cours;
		membreDeLaListeDeCours->suivant = nullptr;
		membreDeLaListeDeCours->sigle = ligne;

		Professeur *queueListeProfesseurs = trouverQueueDeListe(ptrTeteListeProfesseurs);

		if (queueListeProfesseurs->teteListeDeCours->sigle.empty())
		{
			queueListeProfesseurs->teteListeDeCours->sigle = ligne;
		}

		else
		{
			cours *queueListeCours = trouverQueueDeListe(queueListeProfesseurs->teteListeDeCours);

			queueListeCours->suivant = membreDeLaListeDeCours;
			membreDeLaListeDeCours->sigle = ligne;

		}
	}
}

/// <summary>
/// Ajoute un cours à la liste de cours du dernier professeur dans la liste 
/// </summary>
/// <param name="ligne">La ligne lue du fichier contenant l'étudiant à ajouter.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de la liste des professeurs.</param>
void DossierProfesseur::enregistrerEtudiantProfesseur(string ligne, Professeur *ptrTeteListeProfesseurs)
{
	if (ligne == "$") {
		Professeur *nouveauProfesseur = new Professeur;
		Professeur *queueListe = trouverQueueDeListe(ptrTeteListeProfesseurs);
		initialiserPointerProfesseurNullPtr(nouveauProfesseur);
		queueListe->suivant = nouveauProfesseur;

		typeDonnee = 0;
	}
	else
	{
		etudiant* membreDeLaListeEtudiants = new etudiant;
		membreDeLaListeEtudiants->suivant = nullptr;
		membreDeLaListeEtudiants->nom = ligne;

		Professeur *queueListeProfesseurs = trouverQueueDeListe(ptrTeteListeProfesseurs);

		if (queueListeProfesseurs->teteListeEtudiants->nom.empty())
		{
			queueListeProfesseurs->teteListeEtudiants->nom = ligne;
		}
		else
		{
			etudiant *queueListeEtudiant = trouverQueueDeListe(queueListeProfesseurs->teteListeEtudiants);
			queueListeEtudiant->suivant = membreDeLaListeEtudiants;
		}
	}
}

/// <summary>
/// Ajoute un cours à la liste de cours que deux professeurs ont en commun
/// </summary>
/// <param name="queueListe">Un pointeur vers la queue de la liste de cours que les professeurs ont en commun</param>
/// <param name="sigleCours">Le sigle du cours à ajouter à la liste.</param>
/// <returns></returns>
cours * DossierProfesseur::ajouterCoursListeCoursCommun(cours * queueListe, string sigleCours)
{
	cours *nouvelElement = new cours;
	nouvelElement->sigle = sigleCours;
	nouvelElement->suivant = nullptr;
	if (queueListe == nullptr) {
		queueListe = nouvelElement;
	}
	else {
		queueListe->suivant = nouvelElement;
	}
	return nouvelElement;
}

/// <summary>
/// Trouve la queue de la liste à partir du poiteur de tête de liste fourni en paramêtre
/// </summary>
/// <param name="ptrListeProfesseur">Le pointeur de tête de liste</param>
/// <returns>La queue de la liste de professeurs</returns>
Professeur* DossierProfesseur::trouverQueueDeListe(Professeur *ptrListeProfesseur)
{
	while (ptrListeProfesseur->suivant != nullptr)
	{
		ptrListeProfesseur = ptrListeProfesseur->suivant;
	}
	return ptrListeProfesseur;
}

/// <summary>
/// Trouve la queue de la liste à partir du poiteur de tête de liste fourni en paramêtre
/// </summary>
/// <param name="ptrTeteListeCours">Le pointeur de tête de liste</param>
/// <returns>La queue de la liste de cours</returns>
cours* DossierProfesseur::trouverQueueDeListe(cours *ptrTeteListeCours)
{
	while (ptrTeteListeCours->suivant != nullptr)
	{
		ptrTeteListeCours = ptrTeteListeCours->suivant;
	}
	return ptrTeteListeCours;
}

/// <summary>
/// Trouve la queue de la liste à partir du poiteur de tête de liste fourni en paramêtre
/// </summary>
/// <param name="ptrTeteListeEtudiants">Le pointeur de tête de liste.</param>
/// <returns>la queue de la liste d'etudiants</returns>
etudiant* DossierProfesseur::trouverQueueDeListe(etudiant *ptrTeteListeEtudiants)
{
	while (ptrTeteListeEtudiants->suivant != nullptr)
	{
		ptrTeteListeEtudiants = ptrTeteListeEtudiants->suivant;
	}
	return ptrTeteListeEtudiants;
}

/// <summary>
/// Initialise toutes les propriétées de l'instance à NULLPTR
/// </summary>
/// <param name="ptrTeteListeProfesseurs">Un pointeur vers le profasseur à initialiser.</param>
void DossierProfesseur::initialiserPointerProfesseurNullPtr(Professeur * ptrTeteListeProfesseurs)
{
	ptrTeteListeProfesseurs->suivant = nullptr;
	cours* cours1 = new cours;
	ptrTeteListeProfesseurs->teteListeDeCours = cours1;
	cours1->suivant = nullptr;
	etudiant* etudiant1 = new etudiant;
	ptrTeteListeProfesseurs->teteListeEtudiants = etudiant1;
	etudiant1->suivant = nullptr;
}

/// <summary>
/// Initializes a new instance of the <see cref="DossierProfesseur"/> class.
/// </summary>
DossierProfesseur::DossierProfesseur()
{
	Professeur *teteListeProfesseur = new Professeur;
	initialiserPointerProfesseurNullPtr(teteListeProfesseur);

	LireFichierDeDonnees("FP.txt", teteListeProfesseur);

	LireFichierParametres("FT.txt", teteListeProfesseur);

}

DossierProfesseur::~DossierProfesseur()
{
}

/// <summary>
/// Supprime un ou des professeur(s) selon l'ancienneté
/// </summary>
/// <param name="ancien">L'ancienneté selon laquelle les professeurs sont supprimée.</param>
/// <param name="ptrTeteListeProfesseurs">The PTR tete liste professeurs.</param>
void DossierProfesseur::suppressionProfesseurParAncienneté(int ancien, Professeur *ptrTeteListeProfesseurs)
{
	Professeur *elementActuel = ptrTeteListeProfesseurs;
	Professeur *elementPrecedent = new Professeur;
	initialiserPointerProfesseurNullPtr(elementPrecedent);

	do
	{
		if (elementActuel->ancien == ancien)
		{
			elementPrecedent->suivant = elementActuel->suivant;
			delete elementActuel;
			break;
		}
		else
		{
			elementPrecedent = elementActuel;
			elementActuel = elementActuel->suivant;
		}
	} while (elementActuel != nullptr);
}

/// <summary>
/// Boucle au travers de la lite de professeurs pour trouver les Professeurs A et B
/// et Boucle au travers des cours des deux professeurs afin de trouver des cours en communs.
/// Les cours en commun trouvés sont ajoutés à une liste de cours en commun.
/// </summary>
/// <param name="profA">Le nom du professeur A.</param>
/// <param name="profB">Le nom du professeur B.</param>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de liste de professeurs.</param>
void DossierProfesseur::afficherCoursCommun(string profA, string profB, Professeur * ptrTeteListeProfesseurs)
{
	int trouve = 0;
	Professeur *profActuel = ptrTeteListeProfesseurs;
	Professeur *ptrProfA = nullptr;
	Professeur *ptrProfB = nullptr;
	cours *coursActuelProfA = nullptr;
	cours *coursActuelProfB = nullptr;
	cours *teteListeCoursCommun = nullptr;
	cours *queueListeCoursCommun = nullptr;

	while (trouve != 2)
	{
		if (profActuel->nom == profA)
		{
			trouve++;
			ptrProfA = profActuel;
		}
		else if (profActuel->nom == profB)
		{
			trouve++;
			ptrProfB = profActuel;
		}
		profActuel = profActuel->suivant;
		if (profActuel == nullptr)
		{
			return;
		}
	}

	coursActuelProfA = ptrProfA->teteListeDeCours;
	coursActuelProfB = ptrProfB->teteListeDeCours;

	while (coursActuelProfA != nullptr)
	{
		while (coursActuelProfB != nullptr)
		{
			if (coursActuelProfB->sigle == coursActuelProfA->sigle)
			{
				queueListeCoursCommun = ajouterCoursListeCoursCommun(queueListeCoursCommun, coursActuelProfA->sigle);
				if (teteListeCoursCommun == nullptr) {
					teteListeCoursCommun = queueListeCoursCommun;
				}
				break;
			}
			coursActuelProfB = coursActuelProfB->suivant;
		}
		coursActuelProfB = ptrProfB->teteListeDeCours;
		coursActuelProfA = coursActuelProfA->suivant;
	}
}

/// <summary>
/// Crée une liste exhaustive de tous les cours de tous les professeurs avec le nombre de professeurs qui 
/// donnent chaque cours et trouve le cours le plus populaire à partir de la liste précédemment créée.
/// </summary>
/// <param name="ptrTeteListeProfesseurs">Pointeur vers la tête de liste de professeurs.</param>
void DossierProfesseur::afficherCoursLePlusDemander(Professeur * ptrTeteListeProfesseurs)
{
	bool trouve = false;
	Professeur *profActuel = ptrTeteListeProfesseurs;

	cours *teteListeExhaustiveCours = nullptr;
	cours *listeExhaustiveActuelle = nullptr;

	cours *coursLePlusDemande = nullptr;

	while (profActuel != nullptr)
	{
		cours *coursActuel = profActuel->teteListeDeCours;
		while (coursActuel != nullptr)
		{
			while (listeExhaustiveActuelle != nullptr)
			{
				if (listeExhaustiveActuelle->sigle == coursActuel->sigle)
				{
					trouve = true;
					listeExhaustiveActuelle->nbOccurence++;
					break;
				}
				listeExhaustiveActuelle = listeExhaustiveActuelle->suivant;
			}
			if (trouve == false)
			{
				cours *nouveauCoursListeExhaustive = new cours;
				nouveauCoursListeExhaustive->sigle = coursActuel->sigle;
				nouveauCoursListeExhaustive->nbOccurence = 1;
				nouveauCoursListeExhaustive->suivant = teteListeExhaustiveCours;
				teteListeExhaustiveCours = nouveauCoursListeExhaustive;
			}
			coursActuel = coursActuel->suivant;
			trouve = false;
			listeExhaustiveActuelle = teteListeExhaustiveCours;
		}
		profActuel = profActuel->suivant;
	}

	coursLePlusDemande = teteListeExhaustiveCours;
	while (listeExhaustiveActuelle != nullptr)
	{
		if (coursLePlusDemande->nbOccurence < listeExhaustiveActuelle->nbOccurence)
		{
			coursLePlusDemande = listeExhaustiveActuelle;
		}
		listeExhaustiveActuelle = listeExhaustiveActuelle->suivant;
	}
	cout << "cours le plus demande : " << coursLePlusDemande->sigle << " avec " << coursLePlusDemande->nbOccurence << " occurences." << endl;
	sorties += "cours le plus demande : " + coursLePlusDemande->sigle + " avec " + to_string(coursLePlusDemande->nbOccurence) + " occurences.\n";
}
/// <summary>
/// Détermine si un étudiant est supervisé par plus d'un professeur en bouclant au travers des listes d'étudiants des
/// professeurs et compte le nombre de correspondances trouvéess. Le résultat est affiché dans la console.
/// </summary>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de liste de professeurs.</param>
/// <param name="nomEtu">Le nom de l'etudiant.</param>
void DossierProfesseur::afficherSiUnEtudiantEstSuperviseParPlusDUnProfesseur(Professeur * ptrTeteListeProfesseurs, string nomEtu)
{
	int trouve = 0;
	Professeur *profActuel = ptrTeteListeProfesseurs;

	while (profActuel != nullptr)
	{
		etudiant *etudiantActuel = profActuel->teteListeEtudiants;
		while (etudiantActuel != nullptr)
		{
			if (etudiantActuel->nom == nomEtu)
			{
				trouve++;
			}
			etudiantActuel = etudiantActuel->suivant;
		}
		profActuel = profActuel->suivant;
	}
	if (trouve >= 2) {
		cout << nomEtu << " est supervise par " << trouve << " professeurs." << endl;
		sorties += nomEtu + " est supervise par " + to_string(trouve) + " professeurs.\n";
	}
	else
	{
		cout << nomEtu << " est supervise par un seul professeur ou n'existe pas." << endl;
		sorties += nomEtu + " est supervise par un seul professeur ou n'existe pas.\n";
	}
}

/// <summary>
/// Boucle au travers de la liste de professeurs et compte le nombre d'étudians supervisés par chaque professeur.
/// Le professeur supervisant le plus grand nombre d'étudiants est affiché dans la console.
/// </summary>
/// <param name="ptrTeteListeProfesseurs">Le pointeur de tête de liste de professeurs.</param>
void DossierProfesseur::afficherProfesseurQuiSuperviseLePlusDEtudiant(Professeur * ptrTeteListeProfesseurs)
{
	Professeur *professeurAyantLePlusDEtudiants = ptrTeteListeProfesseurs;
	Professeur *professeurActuel = ptrTeteListeProfesseurs;

	while (professeurActuel != nullptr)
	{
		int nombreEtuProfActuel = 0;
		etudiant *etudiantActuel = professeurActuel->teteListeEtudiants;
		while (etudiantActuel != nullptr)
		{
			nombreEtuProfActuel++;
			etudiantActuel = etudiantActuel->suivant;
		}
		professeurActuel->nombreEtudiants = nombreEtuProfActuel;
		if (nombreEtuProfActuel > professeurAyantLePlusDEtudiants->nombreEtudiants)
		{
			professeurAyantLePlusDEtudiants = professeurActuel;
		}
		professeurActuel = professeurActuel->suivant;
	}

	cout << "Le professeur avec le plus d'etudiants supervise est " << professeurAyantLePlusDEtudiants->nom << " avec " << professeurAyantLePlusDEtudiants->nombreEtudiants << " etudiants." << endl;
	sorties += "Le professeur avec le plus d'etudiants supervise est " + professeurAyantLePlusDEtudiants->nom + " avec " + to_string(professeurAyantLePlusDEtudiants->nombreEtudiants) + " etudiants.\n";
}

/// <summary>
/// Recopie toutes les sorties affichées dans la console dans un fichier texte
/// </summary>
/// <param name="filename">Le nom du fichier dans lequel les sorties seront recopiées.</param>
void DossierProfesseur::recopierSorties(string filename)
{
	ofstream fichier(filename, ios::out);

	if (fichier)
	{
		fichier << sorties;
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}


/// <summary>
/// Point d'entrée du programme
/// </summary>
/// <returns>Retourne 0 afin d'indiquer que le programme s'est bien déroulé.</returns>
int main()
{
	DossierProfesseur dossier;
	system("PAUSE");
	return 0;
}
