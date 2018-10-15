/****************************************************************************************************************************************************
*	Noms: Hans Darmstadt-Bélanger et Timothée Drouot																								*
*	Date: 15 Octobre 2018																															*
*	But: Faire un programme qui crée une liste de professeurs à partir d'un fichier texte et qui effectue différentes manipulation sur cette liste	*
*****************************************************************************************************************************************************/

#include "pch.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct cours
{
	string sigle;
	cours *suivant;
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
	cours *teteListeDeCours;
	//TODO: delete theses lines before publishing
	//cours *queueListeDeCours; 
	etudiant *teteListeEtudiants;
	//etudiant *queueListeEtudiants;
	Professeur *suivant;

};

class DossierProfesseur {
private:

	void ouvrirEtLireLeContenuDUnFichierAEnregistrer(string fichierAOuvrir, Professeur *prtTeteListeProfesseurs);
	void ouvrirEtLireLeContenuDuFichierDeParametres(string fichierAOuvrir, Professeur *prtTeteListeProfesseurs);
	void typeDeDonneeAEnregistrer(string ligne, Professeur *prtTeteListeProfesseurs);
	void typeDeParametre(string ligne, Professeur *prtTeteListeProfesseurs);
	void enregistrerNomProfesseur(string ligne, Professeur *prtTeteListeProfesseurs);
	void enregistrerAcienneteProfesseur(string ligne, Professeur *prtTeteListeProfesseurs);
	void enregistrerCoursProfesseur(string ligne, Professeur *prtTeteListeProfesseurs);
	void enregistrerEtudiantProfesseur(string ligne, Professeur *prtTeteListeProfesseurs);
	cours *ajouterCoursListeCoursCommun(cours *queueListe, string sigleCours);

	Professeur* trouverQueueDeListe(Professeur *prtTeteListeProfesseurs);
	cours* trouverQueueDeListe(cours *prtTeteListeProfesseurs);
	etudiant* trouverQueueDeListe(etudiant *prtTeteListeProfesseurs);
	void initialiserPointerProfesseurNullPtr(Professeur *prtTeteListeProfesseurs);

public:
	bool listeAUneTete = false;
	DossierProfesseur();
	~DossierProfesseur();
	void suppressionProfesseur(int ancien, Professeur *prtTeteListeProfesseurs);
	void afficherCoursCommun(string profA, string profB, Professeur *prtTeteListeProfesseurs);
	void *afficherCoursLePlusDemander(Professeur *prtTeteListeProfesseurs) const;
	void recopieListeChainee(string nouveau, Professeur *prtTeteListeProfesseurs);
	Professeur *tete;
	Professeur *queue;
	int typeDonnee = 0;

};



void DossierProfesseur::ouvrirEtLireLeContenuDUnFichierAEnregistrer(string fichierAOuvrir, Professeur *prtTeteListeProfesseurs)
{
	fstream entree;
	string ligne;


	entree.open(fichierAOuvrir, ios::in);
	if (entree) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			cout << ligne;
			typeDeDonneeAEnregistrer(ligne, prtTeteListeProfesseurs);
		}
	}
	entree.close();
}

void DossierProfesseur::ouvrirEtLireLeContenuDuFichierDeParametres(string fichierAOuvrir, Professeur *prtTeteListeProfesseurs)
{
	fstream entree;
	string ligne;


	entree.open(fichierAOuvrir, ios::in);
	if (entree) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			cout << ligne;
			typeDeParametre(ligne, prtTeteListeProfesseurs);
		}
	}
	entree.close();
}

void DossierProfesseur::typeDeDonneeAEnregistrer(string ligne, Professeur *prtTeteListeProfesseurs)
{
	switch (typeDonnee)
	{
	case 0:
		enregistrerNomProfesseur(ligne, prtTeteListeProfesseurs);
		break;
	case 1:
		enregistrerAcienneteProfesseur(ligne, prtTeteListeProfesseurs);
		break;
	case 2:	//enregistrer les cours du professeur
		enregistrerCoursProfesseur(ligne, prtTeteListeProfesseurs);
		break;
	case 3: //enregistrer les eleves du professeur
		enregistrerEtudiantProfesseur(ligne, prtTeteListeProfesseurs);
		break;
	default:
		cout << "Erreur : int inconnu" << endl;
		system("pause");
		break;
	}
}

void DossierProfesseur::typeDeParametre(string ligne, Professeur * prtTeteListeProfesseurs)
{
	string parametreDAction = ligne.substr(0, 1);
	int longueurLigne = ligne.length();
	string argument = ligne.substr(2, longueurLigne - 2);

	if (parametreDAction == "%")
	{
		int argumentLigne = std::stoi(argument);
		suppressionProfesseur(argumentLigne, prtTeteListeProfesseurs);
	}
	else if (parametreDAction == "&")
	{
		std::size_t pos = argument.find(" ");
		string nomProfB = argument.substr(pos + 1);
		int longueurNomProfB = nomProfB.length();
		std::size_t pos2 = ligne.find(" ");
		string nomProfA = ligne.substr(pos2 + 1, longueurNomProfB);
		afficherCoursCommun(nomProfA, nomProfB, prtTeteListeProfesseurs);
	}
	else if (parametreDAction == "+")
	{
		//TODO : afficherCoursLePlusDemander(test);
	}
	else if (parametreDAction == "*")
	{
		//TODO : afficherEtudiantSuperviserParPlusDUnProfesseur(test);
	}
	else if (parametreDAction == "@")
	{
		//TODO : afficherProfesseurQuiSuperviseLePlusDEtudiant(test);
	}
	else if (parametreDAction == "$")
	{
		//TODO : recopieListeChainee();
	}
	else
	{
		cout << "Erreur de parametre." << endl;
		system("pause");
	}
}

void DossierProfesseur::enregistrerNomProfesseur(string ligne, Professeur *prtTeteListeProfesseurs)
{
	Professeur *queueListeProfesseurs = trouverQueueDeListe(prtTeteListeProfesseurs);
	queueListeProfesseurs->nom = ligne;
	typeDonnee = 1;
}

void DossierProfesseur::enregistrerAcienneteProfesseur(string ligne, Professeur *prtTeteListeProfesseurs)
{
	Professeur *queueListeProfesseurs = trouverQueueDeListe(prtTeteListeProfesseurs);
	queueListeProfesseurs->ancien = std::stoi(ligne);
	typeDonnee = 2;
}

void DossierProfesseur::enregistrerCoursProfesseur(string ligne, Professeur *prtTeteListeProfesseurs)
{
	if (ligne == "&") {
		typeDonnee = 3;
	}
	else
	{
		cours* membreDeLaListeDeCours = new cours;
		membreDeLaListeDeCours->suivant = nullptr;
		membreDeLaListeDeCours->sigle = ligne;

		Professeur *queueListeProfesseurs = trouverQueueDeListe(prtTeteListeProfesseurs);

		if (queueListeProfesseurs->teteListeDeCours->sigle == "")//première itération
		{
			queueListeProfesseurs->teteListeDeCours->sigle = ligne;
		}

		else
		{
			cours *queueListeCours = trouverQueueDeListe(queueListeProfesseurs->teteListeDeCours);

			queueListeCours->suivant = membreDeLaListeDeCours;
			membreDeLaListeDeCours->sigle = ligne;

		}



		//if ((*queueListe).teteListeDeCours == nullptr)
		//{
		//	*(*queueListe).teteListeDeCours = membreDeLaListeDeCours;
		//	//*(*queueListe).queueListeDeCours = membreDeLaListeDeCours;
		//}
		//else
		//{
		//	*(*queueListe).queueListeDeCours -> suivant = membreDeLaListeDeCours;
		//	*(*queueListe).queueListeDeCours = membreDeLaListeDeCours;
		//}


	}
}

void DossierProfesseur::enregistrerEtudiantProfesseur(string ligne, Professeur *prtTeteListeProfesseurs)
{
	if (ligne == "$") {
		Professeur *nouveauProfesseur = new Professeur;
		Professeur *queueListe = trouverQueueDeListe(prtTeteListeProfesseurs);
		initialiserPointerProfesseurNullPtr(nouveauProfesseur);
		queueListe->suivant = nouveauProfesseur;


		typeDonnee = 0;
	}
	else
	{
		etudiant* membreDeLaListeEtudiants = new etudiant;
		membreDeLaListeEtudiants->suivant = nullptr;
		membreDeLaListeEtudiants->nom = ligne;

		Professeur *queueListeProfesseurs = trouverQueueDeListe(prtTeteListeProfesseurs);

		if (queueListeProfesseurs->teteListeEtudiants->nom == "")
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

/*cours DossierProfesseur::ajouterCoursListeCoursCommun(cours *queueListe, string sigle)
{
	cours *nouvelElement = new cours;
	nouvelElement->sigle = sigle;
	nouvelElement->suivant = nullptr;
	queueListe->suivant = nouvelElement;

	return *nouvelElement;
}*/

Professeur* DossierProfesseur::trouverQueueDeListe(Professeur *prtTeteListeProfesseurs)
{
	while (prtTeteListeProfesseurs->suivant != nullptr)
	{
		prtTeteListeProfesseurs = prtTeteListeProfesseurs->suivant;
	}
	return prtTeteListeProfesseurs;
}

cours* DossierProfesseur::trouverQueueDeListe(cours *prtQueueListeCours)
{
	while (prtQueueListeCours->suivant != nullptr)
	{
		prtQueueListeCours = prtQueueListeCours->suivant;
	}
	return prtQueueListeCours;
}

etudiant* DossierProfesseur::trouverQueueDeListe(etudiant *ptrQueueListeEtutiants)
{
	while (ptrQueueListeEtutiants->suivant != nullptr)
	{
		ptrQueueListeEtutiants = ptrQueueListeEtutiants->suivant;
	}
	return ptrQueueListeEtutiants;
}

void DossierProfesseur::initialiserPointerProfesseurNullPtr(Professeur * prtTeteListeProfesseurs)
{
	prtTeteListeProfesseurs->suivant = nullptr;
	cours* cours1 = new cours;
	prtTeteListeProfesseurs->teteListeDeCours = cours1;
	cours1->suivant = nullptr;
	etudiant* etudiant1 = new etudiant;
	prtTeteListeProfesseurs->teteListeEtudiants = etudiant1;
	etudiant1->suivant = nullptr;
}

DossierProfesseur::DossierProfesseur()
{
	//Professeur nouveauMembreListeProfesseur;
	Professeur *teteListeProfesseur = new Professeur;
	initialiserPointerProfesseurNullPtr(teteListeProfesseur);

	//*tete = *teteListeProfesseur;
	//Professeur *queue = nullptr;

	ouvrirEtLireLeContenuDUnFichierAEnregistrer("FP.txt", teteListeProfesseur);

	ouvrirEtLireLeContenuDuFichierDeParametres("FT.txt", teteListeProfesseur);

}

DossierProfesseur::~DossierProfesseur()
{
}

void DossierProfesseur::suppressionProfesseur(int ancien, Professeur *prtTeteListeProfesseurs)
{
	Professeur *elementActuel = prtTeteListeProfesseurs;
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

void DossierProfesseur::afficherCoursCommun(string profA, string profB, Professeur * prtTeteListeProfesseurs)
{
	int trouve = 0;
	Professeur *profActuel = prtTeteListeProfesseurs;
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
	//TODO: écrir le contenu de la liste de cours en commun dans le fichier text
}


int main()
{
	DossierProfesseur dossier;
	system("PAUSE");
	return 0;
}
