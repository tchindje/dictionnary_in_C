#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_hachage.h"

int main()
{
    // Initialise la table de hachage avec une taille de 26.
    Table_hachage table = init_table_hachage(26);

    // Insère des mots dans la table de hachage.
    inserer_mot(&table, "chat", "animal domestique\nle chat est beaucoup de texte\n", "cat");

    inserer_mot(&table, "chien", "animal de compagnie1", "");
    inserer_mot(&table, "chien", "animal domestique", "dog");
    inserer_mot(&table, "chien", "animal de compagnie2", "");
    inserer_mot(&table, "arbre", "végétaux", "Vegeetables");

    // Recherche un mot dans la table de hachage.
    char cle[10] = "chien";

    Element *result = chercher_mot(&table, cle);
    if (result == NULL)
    {
        printf("main >> le dico ne contient pas le mot %s\n", cle);
    }

    while (result && strcmp(result->mot->cle, cle) == 0)
    {
        printf("main >> %s : %s\n", result->mot->cle, result->mot->signification);
        result = result->suivant;
    }

    // Supprime un mot de la table de hachage.
    supprimer_mot(&table, cle, CLASSIC);

    result = chercher_mot(&table, cle);
    if (result == NULL)
    {
        printf("main >> le dico ne contient pas le mot %s\n", cle);
    }

    while (result && strcmp(result->mot->cle, cle) == 0)
    {
        printf("main >> %s : %s\n", result->mot->cle, result->mot->signification);
        result = result->suivant;
    }

    return 0;
}
