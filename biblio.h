#ifndef BIBLIO_H   //compilation conditionnelle
#define BIBLIO_H


#include "livre.h"

#define CAPACITE_BIBLIO 20// nb maximum de livres ds la bibliotheque

typedef  T_livre 	T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres;  //nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;




//prototypes
void init (T_Bibliotheque *ptrB);
/// @brief 
/// @param ptrB 
/// @param liste 
/// @return 
int ajouterLivre(T_Bibliotheque  *ptrB, int *liste_code);
int  afficherBibliotheque(const T_Bibliotheque  *ptrB);
int AfficherLivresTitre(const T_Bibliotheque *ptrB, T_Titre t);
int SupprimerLivre(T_Bibliotheque *ptrB, T_Titre t);
int AfficherLivresAuteur(const T_Bibliotheque *ptrB, T_Aut aut);

#endif