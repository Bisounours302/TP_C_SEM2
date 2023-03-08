# include "biblio.h"


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

