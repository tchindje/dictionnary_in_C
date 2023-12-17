#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_hachage.h"

Table_hachage init_table_hachage(int taille)
{
    Table_hachage table_h;
    table_h.taille = taille;
    table_h.table = malloc(taille * sizeof(Element *));

    for (int i = 0; i < taille; i++)
    {
        table_h.table[i] = NULL;
    }

    return table_h;
}

void inserer_mot(Table_hachage *table_h, char *cle, char *signification, char *traduction)
{
    int indice = hash(cle) % table_h->taille; // hasher le mot

    Element *element = malloc(sizeof(Element));
    element->mot = malloc(sizeof(Mot));
    element->mot->cle = cle;
    element->mot->signification = signification;
    element->mot->traduction = traduction;
    element->suivant = NULL;

    // verifie si le mot n'existait pas encore dans le dico
    if (table_h->table[indice] == NULL)
    {
        table_h->table[indice] = element;
    }
    else
    {
        Element *element_cur = table_h->table[indice]; // insert element at the end of list
        while (element_cur->suivant != NULL)
        {
            element_cur = element_cur->suivant;
        }
        element_cur->suivant = element;
    }
}

///////////////////////////////////////////////////////////////

Element *chercher_mot(Table_hachage *table_h, char *cle)
{
    int indice = hash(cle) % table_h->taille;

    Element *element = table_h->table[indice];

    while (element != NULL)
    {
        if (strcmp(element->mot->cle, cle) == 0)
        {
            return element;
        }
        element = element->suivant;
    }
    return NULL;
}

//////////////////////////////////////////////////////////
void supprimer_mot(Table_hachage *table_h, char *cle, DICO_MODE mode)
{
    int indice = hash(cle) % table_h->taille;

    if (table_h->table[indice] == NULL)
    {
        printf("tabhah >> le dico ne contient pas le mot %s. Suppresion impossible!\n", cle);
        return;
    }

    Element *cur = table_h->table[indice];
    Element *prev_cur = cur;

    if (strcmp(cur->mot->cle, cle) == 0)
    {
        if (mode == CLASSIC)
        {
            //     // supprime uniquement  le champs signification du mot
            cur->mot->signification = "";

            if (strcmp(cur->mot->traduction, "") == 0)
            {
                // eviter les mots unitiles : mot sans signification et sans traduction
                table_h->table[indice] = cur->suivant;
                free(cur->mot);
                free(cur);
            }

            printf("tabhah >> suppression du mot '%s' en mode %s reussi.\n", cle, mode == CLASSIC ? "classic" : "tranduction");
            return;
        }

        if (mode == TRANSLATE)
        {
            // supprime uniquement  le champs signification du mot
            cur->mot->traduction = "";

            if (strcmp(cur->mot->signification, "") == 0)
            {
                table_h->table[indice] = cur->suivant;
                free(cur->mot);
                free(cur);
            }

            printf("tabhah >> suppression du mot '%s' en mode %s reussi.\n", cle, mode == CLASSIC ? "classic" : "tranduction");
            return;
        }
    }

    cur = cur->suivant;
    while (cur != NULL)
    {
        if (strcmp(cur->mot->cle, cle) == 0)
        {

            if (mode == CLASSIC)
            {
                // supprime uniquement le champs signification du mot
                // strcpy(cur->mot->signification, "");
                cur->mot->signification = "";

                if (strcmp(cur->mot->traduction, "") == 0)
                {
                    if (cur->suivant == NULL)
                    {
                        prev_cur->suivant = NULL;
                    }
                    else
                    {
                        prev_cur->suivant = cur->suivant;
                    }

                    free(cur->mot);
                    free(cur);
                }
                printf("tabhah >> suppression du mot '%s' en mode %s reussi.\n", cle, mode == CLASSIC ? "classic" : "tranduction");
                return;
            }

            if (mode == TRANSLATE)
            {
                // supprime uniquement le champs signification du mot
                // strcpy(cur->mot->signification, "");
                cur->mot->traduction = "";

                if (strcmp(cur->mot->signification, "") == 0)
                {
                    if (cur->suivant == NULL)
                    {
                        prev_cur->suivant = NULL;
                    }
                    else
                    {
                        prev_cur->suivant = cur->suivant;
                    }
                    free(cur->mot);
                    free(cur);
                }
                printf("tabhah >> suppression du mot '%s' en mode %s reussi.\n", cle, mode == CLASSIC ? "classic" : "tranduction");
                return;
            }
        }

        prev_cur = cur;
        if (cur->suivant != NULL)
        {
            cur = cur->suivant;
        }
        else
        {
            printf("tabhach >> le dico ne contient pas le mot %s.\n", cle);
            return;
        }
    }
}

/////////////////////////////////////////////////////////

int hash(char *cle)
{
    int somme = 0;
    for (int i = 0; cle[i] != '\0'; i++)
    {
        somme += cle[i];
    }
    return somme;
}

/////////////////////////////////////////////////////////
void detruire_table_hachage(Table_hachage *table)
{
    for (int i = 0; i < table->taille; i++)
    {
        // Récupération de la première liste chaînée
        Element *element = table->table[i];

        // Parcours de la liste chaînée et libération de la mémoire
        while (element != NULL)
        {
            // Libération de la mémoire du mot actuel
            free(element->mot);

            element = element->suivant;
        }
    }

    table->table = NULL;
    table = NULL;

    // Libération de la mémoire de la table de hachage

    printf("destruction de la table de hachage en memoire\n");
}
