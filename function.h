#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include "table_hachage.h"

void lire_mots_fichier(FILE *fichier, Table_hachage *table);
void ecrire_mots_fichier(FILE *fichier, Table_hachage *table);
#endif