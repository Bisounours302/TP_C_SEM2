// TP GESTION D'UNE BIBLIOTHEQUE
#include "biblio.h"

void lectureFichierTXT();
void sauvegarde(T_Bibliotheque *ptrB);
void chargement(T_Bibliotheque *ptrB);

int menu()
{
	int choix;
	// au programme du TP7 :
	printf("\n\n 1 - ajouter un nouveau livre dans la bibliotheque ");
	printf("\n 2 - afficher tous les livres de la bibliotheque ");
	printf("\n 3 - rechercher un livre (par son titre)"); // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
	printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
	printf("\n 5 - supprimer un livre de la bibliotheque");
	// si les 5 choix ci dessus sont bien codés, modifiez votre structure T_Livre et passez à 5 champs (avec code,editeur et annee)

	// au programme du TP8 :
	// ajouter le champ emprunteur à votre structure T_Livre
	printf("\n 6 - emprunter un livre de la bibliotheque");
	/*
	printf("\n 7 - restituer/rendre un livre de la bibliotheque");
	*/
	printf("\n 8 - trier les livres (par titre)");
	printf("\n 9 - trier les livres (par auteur)");
	printf("\n 10 - trier les livres (par annee)");

	// si les 5 choix (6-10) sont bien codés, changez le type T_Emp et remplacez-le par la structure T_Emp visible dans livre.h
	// vous pourrez alors faire les menus 11,12,etc...
	// printf("\n 11- lister les livres disponibles ");
	// printf("\n 12 - lister les emprunts en retard "); //on suppose qu'un emprunt dure 7 jours.
	// printf("\n 13 - ... imaginez vous même vos propres fonctionnalités ")

	printf("\n 0 - QUITTER");
	printf("\n Votre choix : ");
	scanf("%d[^\n]", &choix);
	getchar();
	return choix;
}

int main()
{
	lectureFichierTXT();
	int reponse, chx;
	int liste_code[MAX_CODE + 1] = {0};
	T_Bibliotheque B;
	init(&B);
	T_Titre t;
	T_Aut aut;

	chargement(&B); // chargement d'un fichier de structure(s) T_livre

	do
	{
		chx = menu();
		switch (chx)
		{
		case 1:
			reponse = ajouterLivre(&B, liste_code);
			if (reponse == 1)
				printf(" ajout reussi !!");
			else
				printf("impossible d ajouter (bibliotheque pleine)");
			break;
		case 2:
			reponse = afficherBibliotheque(&B);
			if (reponse == 0)
				printf("La bibliotheque est vide");

			break;

		case 3:
			lireChaine("TITRE :", t, MAX_TITRE);
			reponse = AfficherLivresTitre(&B, t);
			if (reponse == -1)
				printf("\nLa bibliotheque est vide\n");
			if (reponse == 0)
				printf("\nLivre non trouvé\n");
			break;

		case 4:
			lireChaine("AUTEUR :", aut, K_MaxAut);
			reponse = AfficherLivresAuteur(&B, aut);
			if (reponse == -1)
				printf("\nLa bibliotheque est vide\n");
			if (reponse == 0)
				printf("\nLivre non trouvé\n");
			break;

		case 5:
			lireChaine("TITRE :", t, MAX_TITRE);
			reponse = SupprimerLivre(&B, t);
			if (reponse == -1)
				printf("\nLa bibliotheque est vide\n");
			if (reponse == 0)
				printf("\nLivre non trouvé\n");
			break;

		case 6:
			char jourfr[200];
			char moisfr[200];
			int variable = choixLivre(&B);
			if (variable == -1)
			{
				printf("\nLivre non trouvé");
				break;
			}
			T_livre livre = B.etagere[variable];
			if (livre.emprunt)
			{
				printf("\nLivre déjà emprunté");
				break;
			}
			Emprunt(&livre, jourfr, moisfr);
			printf("%s %s %d %s %d", livre.emprunteur.nomemprunteur, livre.emprunteur.lejour, livre.emprunteur.ledate,livre.emprunteur.lemois,livre.emprunteur.lannee);
			break;

		case 8:
			TrierLivresTitre(&B);
			printf("\nTri par Titre réussi !!\n");
			break;

		case 9:
			TrierLivresAuteur(&B);
			printf("\nTri par Auteur réussi !!\n");
			break;

		case 10:
			TrierLivresAnnee(&B);
			printf("\nTri par Annee réussi !! \n");
			break;
		}

	} while (chx != 0);
	sauvegarde(&B);

	return 0;
}

void sauvegarde(T_Bibliotheque *ptrB)
{
	FILE *fic = NULL; // le type FILE
	int i;
	fic = fopen("baseLivres", "w"); // w = le mode = write avec ECRASEMENT
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		for (i = 0; i < ptrB->nbLivres; i++)
		{
			// fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
			fwrite(&(ptrB->etagere[i]), sizeof(T_livre), 1, fic);
		}
		fclose(fic);
		puts("SAUVEGARDE REUSSIE ..............");
	}
	else
		puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}

void chargement(T_Bibliotheque *ptrB)
{
	FILE *fic = NULL; // le type FILE
	int i = 0;
	fic = fopen("baseLivres", "r"); // r = le mode read
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		do
		{

			fread(&(ptrB->etagere[i]), sizeof(T_livre), 1, fic);
			i++;
		} while (!feof(fic));
		fclose(fic);
		ptrB->nbLivres = i - 1;
		puts("CHARGEMENT  REUSSI ..............");
	}
	else
		puts("ECHEC DE CHARGEMENT  !!!!!  ");
}

void lectureFichierTXT()
{
	int M = 100;
	FILE *fic = NULL; // le type FILE
	char chaine[M];
	char chaine2[M];
	char c;
	fic = fopen("fic.txt", "rt"); // r = le mode read   w = mode write (avec ecrasement)
	// fopen renvoie NULL si probleme (fichier effac� , disque non accessible ...
	if (fic != NULL)
	{
		do
		{
			fgets(chaine, M, fic);	   // fputs pour �crire dans un fichier txt
			fscanf(fic, "%s", chaine); // fprintf pour �crire dans un fichier txt
			fscanf(fic, "%s %s", chaine, chaine2);
			fscanf(fic, "%c", &c);
			fscanf(fic, "%c", &chaine[0]);
			if (!feof(fic))
				printf("\n\t >%s--%s<", chaine, chaine2);
			printf(">%c<", c);
		} while (!feof(fic));
		fclose(fic);
		puts("\nLECTURE REUSSIE ..............");
	}
	else
		puts("ECHEC DE LECTURE DU FICHIER TXT !!!!!  ");
}


