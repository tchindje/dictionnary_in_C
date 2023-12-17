#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_hachage.h"
#include "function.h"

int main()
{
    // Initialise la table de hachage avec une taille de 26.
    Table_hachage table = init_table_hachage(26);

    // ouverture du fichier en mode lecure
    FILE *fichier = fopen("dictionnaire.txt", "r");

    // chargement du fichier dans la table de hachage
    lire_mots_fichier(fichier, &table);

    // Rechercher un mot dans la table de hachage.
    char cle[10];

    int create_del = 0;

    DICO_MODE mode;
    int choix;

    do
    {
        printf("\n\n------------------------------------\n\n");
        printf("Menu principal\n");
        printf("1. Rechercher un mot\n");
        printf("2. Traduire un mot\n");
        printf("3. Connaitre la signification d'un mot\n");
        printf("4. Insérer un mot **(SEULEMENT LES ADMIN)**\n");
        printf("5. Supprimer un mot **(SEULEMENT LES ADMIN)**\n");
        printf("6. Quitter\n");

        printf("\n------------------------------------\n\n");

        printf("Choisissez votre choix : ");
        scanf("%d", &choix);

        Element *result = NULL;
        char password[10];

        switch (choix)
        {
        case 1:
            // Recherche d'un mot
            printf("enter le mot a rechercher : ");
            scanf("%s", cle);
            result = chercher_mot(&table, cle);
            if (result == NULL)
            {
                printf("main >> le dico ne contient pas le mot %s\n", cle);
            }

            while (result && strcmp(result->mot->cle, cle) == 0)
            {
                char trad[300];
                if (strcmp(result->mot->traduction, "") != 0)
                {
                    strcpy(trad, result->mot->traduction);
                }
                else
                {
                    strcpy(trad, "(traduction not found ) ");
                }

                char sign[300];
                if (strcmp(result->mot->signification, "") != 0)
                {
                    strcpy(sign, result->mot->signification);
                }
                else
                {
                    strcpy(sign, "( signification not found ) ");
                }

                printf("main >> %s : %s \n", result->mot->cle, sign);
                printf("main >> %s en anglais est : %s \n", result->mot->cle, trad);
                result = result->suivant;
            }
            break;

        case 2:
            // Traduire le mot
            printf("enter le mot a rechercher : ");
            scanf("%s", cle);
            result = chercher_mot(&table, cle);
            if (result == NULL)
            {
                printf("main >> le dico ne contient pas le mot %s\n", cle);
            }

            while (result && strcmp(result->mot->cle, cle) == 0)
            {
                char mo[300];
                if (strcmp(result->mot->traduction, "") != 0)
                {
                    strcpy(mo, result->mot->traduction);
                }
                else
                {
                    strcpy(mo, "(traduction not found ) ");
                }

                printf("main >> %s : %s \n", cle, mo);

                result = result->suivant;
            }
            break;
        case 3:
            // Signification
            printf("enter le mot a rechercher : ");
            scanf("%s", cle);

            printf("--------------------------------------------------\n");
            result = chercher_mot(&table, cle);
            if (result == NULL)
            {
                printf("main >> le dico ne contient pas le mot %s.\n", cle);
            }
            while (result && strcmp(result->mot->cle, cle) == 0)
            {
                char mot[300];
                if (strcmp(result->mot->signification, "") != 0)
                {
                    strcpy(mot, result->mot->signification);
                }
                else
                {
                    strcpy(mot, "( signification not found ) ");
                }

                printf("main >> %s : %s \n", cle, mot);
                result = result->suivant;
            }
            printf("--------------------------------------------------\n\n");
            break;

        case 4:
            // insertion
            printf("enter votre mot de passe : ");
            scanf("%s", password);
            if (strcmp(password, "pass123") != 0)
            {
                printf("\nVous n'avez pas le droit!");
            }
            else
            {
                create_del = 1;
                char signification[200], traduction[200];
                printf("enter le mot a inserrer : ");
                scanf("%s", cle);

                printf("choisir le mode : (1 - classique  2 - traduction 3 - mixte)");
                printf("---------------------------------------------\n");

                int m;
                scanf("%d", &m);
                if (m != 1 && m != 2 && m != 3)
                {
                    printf("option invalide.\n");
                    break;
                }

                if (m == 1)
                {
                    printf("enter la signification du mot\n");
                    scanf("%s", signification);

                    strcpy(traduction, "");
                }

                if (m == 2)
                {
                    printf("enter la traduction du mot\n");
                    scanf("%s", traduction);
                    printf("\n");

                    strcpy(signification, "");
                }

                if (m == 3)
                {
                    printf("enter la signification du mot :");
                    scanf("%s", signification);

                    printf("enter la traduction du mot: ");
                    scanf("%s", traduction);
                }

                inserer_mot(&table, cle, signification, traduction);
                printf("main>> insertion reussi.\n");
            }
            break;

        case 5:
            // Suppression d'un mot
            printf("enter votre mot de passe : ");
            scanf("%s", password);
            if (strcmp(password, "pass123") != 0)
            {
                printf("\nVous n'avez pas le droit!");
            }
            else
            {
                create_del = 1;
                printf("enter le mot a supprimer : ");
                scanf("%s", cle);

                printf("enter le mode (0 - supression  1 - supprimer en mode classic  2 - supprimer traduction) : ");

                int m;
                scanf("%d", &m);
                if (m != 0 && m != 1 && m != 2)
                {
                    printf("mode  invalide.\n");
                    break;
                }
                if (m == 0)
                {
                    supprimer_mot(&table, cle, MIXTE);
                    printf("main>> suppression reussi.\n");
                }
                if (m == 1)
                {
                    supprimer_mot(&table, cle, CLASSIC);
                    printf("main>> suppression reussi.\n");
                }

                if (m == 2)
                {
                    supprimer_mot(&table, cle, TRANSLATE);
                    printf("main>> suppression reussi.\n");
                }
            }

            break;
        case 6:
            // Quitter
            // save table data in the file

            if (create_del == 1)
            {
                FILE *fichier1 = fopen("dictionnaire.txt", "w");
                ecrire_mots_fichier(fichier1, &table);
                fclose(fichier1);
            }

            // liberer la memoire
            detruire_table_hachage(&table);
            printf("Bye ...\n");

            return 0;
        default:
            // Option invalide
            printf("Option invalide. Veuillez recommencer!\n");
            break;
        }
    } while (mode != 6);

    fclose(fichier);

    return 0;
}
