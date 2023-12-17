#ifndef TABLE_HACHAGE_H
#define TABLE_HACHAGE_H

typedef enum dico_mode
{
    CLASSIC,   // Represents a classic dictionary with word definitions.
    TRANSLATE, // Represents a translation dictionary between two languages.
} DICO_MODE;

typedef struct mot
{
    char *cle;
    char *signification;
    char *traduction;
} Mot;

typedef struct element
{
    Mot *mot;
    struct element *suivant;
} Element;

typedef struct table_hachage
{
    Element **table;
    int taille;
} Table_hachage;

Table_hachage init_table_hachage(int taille);
void inserer_mot(Table_hachage *table, char *cle, char *signification, char *traduction);
Element *chercher_mot(Table_hachage *table, char *cle);
void supprimer_mot(Table_hachage *table, char *cle, DICO_MODE mode);
int hash(char *cle);
void detruire_table_hachage(Table_hachage *table);

#endif
