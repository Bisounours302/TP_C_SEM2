# include "biblio.h"
#include <ctype.h>


char joursemaines[7][10] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
char moisdelannees[12][15] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};



void init (T_Bibliotheque *ptrB)
{

ptrB->nbLivres=0;
// ou (*ptrB).nbLivres=0;
}

int ajouterLivre(T_Bibliotheque  *ptrB, int *liste_code)
{
	if (ptrB->nbLivres<CAPACITE_BIBLIO)// reste t il de la place?
	{
	saisirLivre(&(ptrB->etagere[ptrB->nbLivres]));
	creationCode(&(ptrB->etagere[ptrB->nbLivres]), liste_code);
	ptrB->etagere[ptrB->nbLivres].emprunt = 0;
	ptrB->nbLivres++;
	return 1;
	}
return 0;
}


int  afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
int i;
if(ptrB->nbLivres==0)
	return 0;
	else
		{
		for(i=0;i<ptrB->nbLivres;i++)
			{
			afficherLivre(&(ptrB->etagere[i])  );
			
			}
		return 1;
		}
}



int AfficherLivresTitre(const T_Bibliotheque *ptrB, T_Titre t)
{
	int o = 1 + ptrB->nbLivres;
	int indices[o];
	int flag = 0;
	int i = 0;
	int j = 1;

	if(ptrB->nbLivres == 0)
		return -1;
	for(i; i < ptrB->nbLivres; i++)
	{
		if (strcmp((ptrB->etagere[i]).titre, t) == 0)
		{
			flag++;
			indices[flag] = i;
		}
	}
	if (flag == 0)
		return 0;
	for (j; j<= flag; j++)
		afficherLivre(&(ptrB->etagere[indices[j]]));
	return 1;
	}	


int AfficherLivresAuteur(const T_Bibliotheque *ptrB, T_Aut aut)
{
	int o = 1 + ptrB->nbLivres;
	int indices[o];
	int flag = 0;
	int i = 0;
	int j = 1;

	if(ptrB->nbLivres == 0)
		return -1;
	for(i; i < ptrB->nbLivres; i++)
	{
		if (strcmp((ptrB->etagere[i]).auteur, aut) == 0)
		{
			flag++;
			indices[flag] = i;
		}
	}
	if (flag == 0)
		return 0;
	for (j; j < flag + 1; j++)
		afficherLivre(&(ptrB->etagere[indices[j]]));

	return 1;
}	



int SupprimerLivre(T_Bibliotheque *ptrB, T_Titre t)
{
	if(ptrB->nbLivres == 0)
		return -1;
	int i = 0;
	while(i != (ptrB->nbLivres) && strcmp((ptrB->etagere[i]).titre, t) != 0)
		i++;
	if (i == ptrB->nbLivres)
		return 0;
	if  (i == ptrB->nbLivres - 1)
	{
		ptrB->nbLivres--;
		return 1;
	}
	for (i; i < ptrB->nbLivres - 1; i ++)
	{
		strcpy((ptrB->etagere[i]).titre, (ptrB->etagere[i + 1]).titre);
		strcpy((ptrB->etagere[i]).auteur, (ptrB->etagere[i + 1]).auteur);
	}
	ptrB->nbLivres--;
	return 1;
}

void TrierLivresTitre(T_Bibliotheque *ptrB){
    int i,j;
    T_livre tmp;
    for(i=0; i< ptrB->nbLivres -1;i++){
        for(j=i+1; j<ptrB->nbLivres; j++){
			char text1[200];
			char text2[200];
			majuscule(ptrB->etagere[i].titre, text1);
			majuscule(ptrB->etagere[j].titre, text2);
            if(strcmp(text1, text2) >0 )
            {
            tmp = ptrB->etagere[i];
            ptrB->etagere[i]= ptrB->etagere[j];
            ptrB->etagere[j]= tmp;
            }
        }
    }
}

void TrierLivresAuteur(T_Bibliotheque *ptrB){
    int i,j;
    T_livre tmp;
    for(i=0; i< ptrB->nbLivres -1;i++){
        for(j=i+1; j<ptrB->nbLivres; j++){
			char text1[200];
			char text2[200];
			majuscule(ptrB->etagere[i].auteur, text1);
			majuscule(ptrB->etagere[j].auteur, text2);
            if(strcmp(text1, text2) >0 )
            {
            tmp = ptrB->etagere[i];
            ptrB->etagere[i]= ptrB->etagere[j];
            ptrB->etagere[j]= tmp;
            }
        }
    }
}

void TrierLivresAnnee(T_Bibliotheque *ptrB){
    int i,j;
    T_livre tmp;
    for(i=0; i< ptrB->nbLivres -1;i++){
        for(j=i+1; j<ptrB->nbLivres; j++){
            if(ptrB->etagere[i].annee > ptrB->etagere[j].annee)
            {
            tmp = ptrB->etagere[i];
            ptrB->etagere[i]= ptrB->etagere[j];
            ptrB->etagere[j]= tmp;
            }
        }
    }
}

void majuscule(char *chaine, char *chaine2)
{
    int i = 0;
	chaine2[0] = toupper(chaine[0]);
    for (i = 1 ; chaine[i - 1] != '\0' ; i++)
    {
        chaine2[i] = toupper(chaine[i]);
    }
}



void Emprunt(T_livre *ptrL,char *jourfr,char *moisfr)
{
	recupererDate(1, jourfr, moisfr);
	recupererDate(3, jourfr, moisfr);
	printf("Nom de l'emprunteur : ");
    scanf("%s", ptrL->emprunteur.nomemprunteur);
	strcpy(ptrL->emprunteur.lejour, jourfr);
	ptrL->emprunteur.ledate = recupererDate(2, jourfr, moisfr);
	strcpy(ptrL->emprunteur.lemois, moisfr);
	ptrL->emprunteur.lannee = recupererDate(4, jourfr, moisfr);

	ptrL->emprunt = 1;
}

void Rendre(T_livre *ptrL)
{
	ptrL->emprunt = 0;
}

int recupererDate(int mescouilles, char *jourfr, char *moisfr)
{
	char jour[256];
	char date[256];
	char mois[256];
	char annee[256];
	time_t timestamp = time(NULL);

	strftime(jour, sizeof(jour), "%A", localtime(&timestamp));
	strftime(date, sizeof(date), "%d", localtime(&timestamp));
	strftime(mois, sizeof(mois), "%m", localtime(&timestamp));
	strftime(annee, sizeof(annee), "%Y", localtime(&timestamp));

	if (mescouilles == 1)
	{
		strcpy(jourfr, joursemaines[chx_jour(jour)]);
		return -1;
	}

	if (mescouilles == 2)
		return atoi(date);

	if (mescouilles == 3)
	{
		strcpy(moisfr, moisdelannees[atoi(mois)]);
		return -1;
	}
	return atoi(annee);
		
}

int chx_jour(char *jour)
{
	if (strcmp(jour, "Monday") == 0)
		return 0;
	if (strcmp(jour, "Tuesday") == 0)
		return 1;
	if (strcmp(jour, "Wednesday") == 0)
		return 2;
	if (strcmp(jour, "Thursday") == 0)
		return 3;
	if (strcmp(jour, "Friday") == 0)
		return 4;
	if (strcmp(jour, "Saturday") == 0)
		return 5;
	if (strcmp(jour, "Sunday") == 0)
		return 6;
	return -1;
}


int choixLivre(T_Bibliotheque *ptrB)
{
	int codecherche;
	printf("\nDonnez le code du livre que vous voulez : ");
	scanf("%d", &codecherche);
	for(int i = 0; i < ptrB->nbLivres; i++)
	{
		if (ptrB->etagere[i].code == codecherche)
			return i;
	}
	return -1;
}