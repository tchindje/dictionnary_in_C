
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "table_hachage.h"

// global variable to manipulate stream file

void lire_mots_fichier(FILE *fichier, Table_hachage *table)
{

    // Boucle de lecture
    while (!feof(fichier))
    {
        // Lecture de la ligne
        char ligne[200];
        fgets(ligne, 200, fichier);

        // Allocation de mémoire pour la copie temporaire
        char *ligne_copie = malloc(sizeof(char) * 200);

        // Copie de la ligne dans la variable temporaire
        strcpy(ligne_copie, ligne);

        // Séparation des parties de la ligne
        char *cle = strsep(&ligne_copie, "|");
        char *signification = strsep(&ligne_copie, "|");
        char *traduction = strsep(&ligne_copie, "|");

        inserer_mot(table, cle, signification, traduction);

        // Libération de la mémoire de la copie temporaire
        free(ligne_copie);
    }
}

void ecrire_mots_fichier(FILE *fichier, Table_hachage *table)
{
    // Boucle sur les mots du dictionnaire
    Element *element = malloc(sizeof(Element));

    for (int i = 0; i < table->taille; i++)
    {
        // Récupération de element
        element = table->table[i];

        while (element != NULL)
        {

            // Écriture du mot dans le fichier
            fprintf(fichier, "%s| %s| %s\n", element->mot->cle, element->mot->signification, element->mot->traduction);
            element = element->suivant;
        }
        fprintf(fichier, "\n");
    }

    free(element);
    printf("ecriture reussi\n");
}
