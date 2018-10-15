#pragma once
class CDossierProfesseur
{
public:
	CDossierProfesseur();
	~CDossierProfesseur();
	void Supprimer(int ancien);
	int Commun(char* X, char* Y);
	char* LeCoursLePlusDemande() const;
	char* ProfesseurLePlusAncien() const;
	bool Supervision() const;
	void Recopier(char *Nouveau);
};

struct Professeur
{
	char* nom;
	int ancien;
	cours* listedecours;
	Professeur* suivant;
	etudiant* listeetudiants;
};

struct cours
{
	char *sigle;
	cours *suivant;
};

struct etudiant
{
	char *nom;
	etudiant *suivant;
};
