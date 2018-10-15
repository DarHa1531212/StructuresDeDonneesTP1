// Noms : Timothée Drouot & Hans Darmstadt-Belanger
// Date : 10-10-2018
// ConsoleApplication1.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

class DossierProfesseur {
private:

	void ouvrirEtLireLeContenuDUnFichierAEnregistrer(string fichierAOuvrir, Professeur *test);
	void ouvrirEtLireLeContenuDuFichierDeParametres(string fichierAOuvrir, Professeur *test);
	void typeDeDonneeAEnregistrer(string ligne, Professeur *test);
	void typeDeParametre(string ligne, Professeur *test);
	void enregistrerNomProfesseur(string ligne, Professeur *test);
	void enregistrerAcienneteProfesseur(string ligne, Professeur *test);
	void enregistrerCoursProfesseur(string ligne, Professeur *test);
	void enregistrerEtudiantProfesseur(string ligne, Professeur *test);
	cours *ajouterCoursListeCoursCommun(cours *queueListe, string sigleCours);

	Professeur* trouverQueueDeListe(Professeur *test);
	cours* trouverQueueDeListe(cours *test);
	etudiant* trouverQueueDeListe(etudiant *test);
	void initialiserPointerProfesseurNullPtr(Professeur *test);
	

public:
	bool listeAUneTete = false;
	DossierProfesseur();
	~DossierProfesseur();
	void suppressionProfesseur(int ancien, Professeur *test);
	void afficherCoursCommun(string profA, string profB, Professeur *test);
	void afficherCoursLePlusDemander(Professeur *test);
	void afficherEtudiantSuperviserParPlusDUnProfesseur(Professeur *test, string nomEtu);
	void afficherProfesseurQuiSuperviseLePlusDEtudiant(Professeur *test) ;
	void recopieListeChainee(string filename, Professeur *test);
	Professeur *tete;
	Professeur *queue;
	int typeDonnee = 0;
	string sorties;

};



void DossierProfesseur::ouvrirEtLireLeContenuDUnFichierAEnregistrer(string fichierAOuvrir, Professeur *test)
{
	fstream entree;
	string ligne;


	entree.open(fichierAOuvrir, ios::in);
	if (entree) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			cout << ligne;
			typeDeDonneeAEnregistrer(ligne, test);
		}
	}
	entree.close();
}

void DossierProfesseur::ouvrirEtLireLeContenuDuFichierDeParametres(string fichierAOuvrir, Professeur *test)
{
	fstream entree;
	string ligne;


	entree.open(fichierAOuvrir, ios::in);
	if (entree) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			cout << ligne;
			typeDeParametre(ligne, test);
		}
	}
	entree.close();
}

void DossierProfesseur::typeDeDonneeAEnregistrer(string ligne, Professeur *test)
{
	switch (typeDonnee)
	{
	case 0:
		enregistrerNomProfesseur(ligne, test);
		break;
	case 1:
		enregistrerAcienneteProfesseur(ligne, test);
		break;
	case 2:
		enregistrerCoursProfesseur(ligne, test);
		break;
	case 3:
		enregistrerEtudiantProfesseur(ligne, test);
		break;
	default:
		cout << "Erreur : int inconnu" << endl;
		sorties += "Erreur : int inconnu\n";
		system("pause");
		break;
	}
}

void DossierProfesseur::typeDeParametre(string ligne, Professeur * test)
{
	string parametreDAction = ligne.substr(0, 1);
	

	if (parametreDAction == "%")
	{
		int longueurLigne = ligne.length();
		string argument = ligne.substr(2, longueurLigne - 2);
		int argumentLigne = std::stoi(argument);
		suppressionProfesseur(argumentLigne, test);
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
		afficherCoursCommun(nomProfA, nomProfB, test);
	}
	else if (parametreDAction == "+")
	{
		afficherCoursLePlusDemander(test);
	}
	else if (parametreDAction == "*")
	{
		int longueurLigne = ligne.length();
		string argument = ligne.substr(2, longueurLigne - 2);
		std::size_t pos = argument.find(" ");
		string nomEtu = argument.substr(pos + 1);
		afficherEtudiantSuperviserParPlusDUnProfesseur(test,nomEtu);
	}
	else if (parametreDAction == "@")
	{
		afficherProfesseurQuiSuperviseLePlusDEtudiant(test);
	}
	else if (parametreDAction == "$")
	{
		recopieListeChainee("nouveau.txt", test);
	}
	else
	{
		cout << "Erreur de parametre." << endl;
		sorties += "Erreur de parametre.\n";
		system("pause");
	}
}

void DossierProfesseur::enregistrerNomProfesseur(string ligne, Professeur *test)
{
	Professeur *queueListeProfesseurs = trouverQueueDeListe(test);
	queueListeProfesseurs->nom = ligne;
	typeDonnee = 1;
}

void DossierProfesseur::enregistrerAcienneteProfesseur(string ligne, Professeur *test)
{
	Professeur *queueListeProfesseurs = trouverQueueDeListe(test);
	queueListeProfesseurs->ancien = std::stoi(ligne);
	typeDonnee = 2;
}

void DossierProfesseur::enregistrerCoursProfesseur(string ligne, Professeur *test)
{
	if (ligne == "&") {
		typeDonnee = 3;
	}
	else
	{
		cours* membreDeLaListeDeCours = new cours;
		membreDeLaListeDeCours->suivant = nullptr;
		membreDeLaListeDeCours->sigle = ligne;

		Professeur *queueListeProfesseurs = trouverQueueDeListe(test);

		if (queueListeProfesseurs->teteListeDeCours->sigle == "")
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

void DossierProfesseur::enregistrerEtudiantProfesseur(string ligne, Professeur *test)
{
	if (ligne == "$") {
		Professeur *nouveauProfesseur = new Professeur;
		Professeur *queueListe = trouverQueueDeListe(test);
		initialiserPointerProfesseurNullPtr(nouveauProfesseur);
		queueListe->suivant = nouveauProfesseur;


		typeDonnee = 0;
	}
	else
	{
		etudiant* membreDeLaListeEtudiants = new etudiant;
		membreDeLaListeEtudiants->suivant = nullptr;
		membreDeLaListeEtudiants->nom = ligne;

		Professeur *queueListeProfesseurs = trouverQueueDeListe(test);

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

Professeur* DossierProfesseur::trouverQueueDeListe(Professeur *test)
{
	while (test->suivant != nullptr)
	{
		test = test->suivant;
	}
	return test;
}

cours* DossierProfesseur::trouverQueueDeListe(cours *test)
{
	while (test->suivant != nullptr)
	{
		test = test->suivant;
	}
	return test;
}

etudiant* DossierProfesseur::trouverQueueDeListe(etudiant *test)
{
	while (test->suivant != nullptr)
	{
		test = test->suivant;
	}
	return test;
}

void DossierProfesseur::initialiserPointerProfesseurNullPtr(Professeur * test)
{
	test->suivant = nullptr;
	cours* cours1 = new cours;
	test->teteListeDeCours = cours1;
	cours1->suivant = nullptr;
	etudiant* etudiant1 = new etudiant;
	test->teteListeEtudiants = etudiant1;
	etudiant1->suivant = nullptr;
}

DossierProfesseur::DossierProfesseur()
{
	Professeur *teteListeProfesseur = new Professeur;
	initialiserPointerProfesseurNullPtr(teteListeProfesseur);

	ouvrirEtLireLeContenuDUnFichierAEnregistrer("FP.txt", teteListeProfesseur);

	ouvrirEtLireLeContenuDuFichierDeParametres("FT.txt", teteListeProfesseur);

}

DossierProfesseur::~DossierProfesseur()
{
}

void DossierProfesseur::suppressionProfesseur(int ancien, Professeur *test)
{
	Professeur *elementActuel = test;
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

void DossierProfesseur::afficherCoursCommun(string profA, string profB, Professeur * test)
{
	int trouve = 0;
	Professeur *profActuel = test;
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

void DossierProfesseur::afficherCoursLePlusDemander(Professeur * test)
{
	bool trouve = false;
	Professeur *profActuel = test;
	
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
	sorties += "cours le plus demande : " +  coursLePlusDemande->sigle + " avec " + to_string( coursLePlusDemande->nbOccurence )+ " occurences.\n";
}

void DossierProfesseur::afficherEtudiantSuperviserParPlusDUnProfesseur(Professeur * test, string nomEtu)
{
	int trouve = 0;
	Professeur *profActuel = test;
	

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

void DossierProfesseur::afficherProfesseurQuiSuperviseLePlusDEtudiant(Professeur * test)
{
	Professeur *professeurAyantLePlusDEtudiants = test;
	Professeur *professeurActuel = test;

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
		if(nombreEtuProfActuel > professeurAyantLePlusDEtudiants->nombreEtudiants)
		{
			professeurAyantLePlusDEtudiants = professeurActuel;
		}
		professeurActuel = professeurActuel->suivant;
	}

	cout << "Le professeur avec le plus d'etudiants supervise est " << professeurAyantLePlusDEtudiants->nom << " avec " << professeurAyantLePlusDEtudiants->nombreEtudiants << " etudiants." << endl;
	sorties += "Le professeur avec le plus d'etudiants supervise est " + professeurAyantLePlusDEtudiants->nom + " avec " + to_string(professeurAyantLePlusDEtudiants->nombreEtudiants) + " etudiants.\n";
}

void DossierProfesseur::recopieListeChainee(string filename, Professeur * test)
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


int main()
{
	DossierProfesseur dossier;
	system("PAUSE");
	return 0;
}
