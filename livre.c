#include "livre.h"

void saisirLivre(T_livre * ptrL)
{
lireChaine("TITRE :", (ptrL->titre), MAX_TITRE );
lireChaine("AUTEUR :", (ptrL->auteur ), MAX);
lireChaine("EDITEUR :", (ptrL->editeur ), MAX);
printf("ANNEE :");
scanf("%d", &ptrL->annee);
}

void afficherLivre(const T_livre *ptrL)
{
afficherChaine("TITRE :", (ptrL->titre));
printf(" - ");
afficherChaine("AUTEUR :", (ptrL->auteur ));
printf(" - ");
afficherChaine("EDITEUR :", (ptrL->editeur));
printf(" - ");
printf("ANNEE :%d - ", (ptrL->annee));
printf("CODE :%d\n", (ptrL->code));
}

void creationCode(T_livre *ptrL, int *liste_code)
{
    int code= (rand() % 500) + 1;
    while (code_existant(code, liste_code))
    {
        code= rand() % 500 + 1;
    }
    liste_code[0] = liste_code[0] + 1;
    liste_code[liste_code[0]] = code;
    ptrL->code = code;
}

int code_existant(int code, int* liste)
{
    int i;
    if (liste[0] == 0) return 0;
    for (i = 1; i <= liste[0]; i++)
        if (liste[i] == code) return 1;
    return 0;    
}
