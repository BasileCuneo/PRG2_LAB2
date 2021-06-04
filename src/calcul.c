/*
 -----------------------------------------------------------------------------------
 Nom du fichier : calcul.c
 Auteur(s)      : Clément Dieperink, Basile Cuneo, Joris Schaller
 Date creation  : 28.05.2021

 Description    : Implémentation de la librairie pour les calcules de taxe.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <math.h>

#include "calcul.h"

// ------------------------------------------------------------------------------
// la fonction calcule la taxe annuelle du bateau et la retourne
// ------------------------------------------------------------------------------
Price taxe(const Boat* boat) {
   Price taxe = 0;

   switch (boat->propulsionType) {
      case SAIL:
         taxe += BASE_SAIL; // Taxe de base pour un bateau à voile
         if (boat->properties.sailing->sailSurface >= TAXED_SAIL) {
            taxe += BIG_SAIL; // Taxe pour grande surface de voile
         }
         break;
      case MOTOR:
         taxe += BASE_MOTOR; // Taxe de base pour un bateau à moteur
         switch (boat->properties.motor->type) {
            case FISHING:
               if (boat->properties.motor->properties.fishing->fishMaxWeight >=
                   TAXED_WEIGHT) {
                  taxe += BIG_FISH_WEIGHT; // Taxe additionnelle fixe pour grosse pèche
               }
               break;
            case PLEASURE:
               if (boat->properties.motor->power < TAXED_POWER) {
                  taxe += SMALL_PLEASURE_MOTOR; // Taxe additionnelle fixe pour petit moteur
               } else {
                  // Taxe additionnelle dépendant de la longueur du bateau
                  taxe += boat->properties.motor->properties.pleasure->length *
                          LENGTH_MULT;
               }
               break;
         }
         break;
   }
   return taxe;
}

// ------------------------------------------------------------------------------
// Calcule la somme des taxes annuelles des bateaux du port qui
// correspondent à la condition passée en paramètre, retourne la somme
// ------------------------------------------------------------------------------
Price sumAnnualTaxes(const Boat* port[], size_t nbBoats,
                     bool (* condition)(const Boat*)) {
   Price sum = 0;

   // Calcul la somme des taxes de tous les bateaux respectant la condition.
   for (size_t i = 0; i < nbBoats; ++i) {
      if (condition(port[i])) {
         sum += taxe(port[i]);
      }
   }

   return sum;
}

// ------------------------------------------------------------------------------
// Calcule la moyenne des taxes annuelles des bateaux du port qui
// correspondent à la condition passée en paramètre, retourne la moyenne
// ------------------------------------------------------------------------------
Price meanAnnualTaxes(const Boat* port[], size_t nbBoats,
                      bool (* condition)(const Boat*)) {
   size_t taxedBoat = 0;
   Price sum = 0;

   // Calcul la somme des taxes de tous les bateaux respectant la condition.
   // Et récupère le nombre de bateau respectant la condition.
   for (size_t i = 0; i < nbBoats; ++i) {
      if (condition(port[i])) {
         ++taxedBoat;
         sum += taxe(port[i]);
      }
   }

   return sum / (Price) taxedBoat;
}

// ------------------------------------------------------------------------------
// Retourne la valeur de comparaison de deux prix (p.ex. l'utilisation de qsort).
// ------------------------------------------------------------------------------
int cmpfunc_price(const void* a, const void* b) {
   if (*(Price*) a > *(Price*) b) {
      return 1;
   } else if (*(Price*) a < *(Price*) b) {
      return -1;
   } else {
      return 0;
   }
}

// ------------------------------------------------------------------------------
// Calcule la médiane des taxes annuelles des bateaux du port
// qui correspondent à la condition passée en paramètre, retourne la médiane
// ------------------------------------------------------------------------------
Price medianAnnualTaxes(const Boat* port[], size_t nbBoats,
                        bool (* condition)(const Boat*)) {
   Price txs[nbBoats];
   size_t nEffectiveBoat = 0;

   // Calcul la taxe de tous les bateaux respectant la condition.
   // Et récupère le nombre de bateau respectant la condition.
   for (size_t i = 0; i < nbBoats; ++i) {
      if (condition(port[i])) {
         txs[nEffectiveBoat] = taxe(port[i]);
         ++nEffectiveBoat;
      }
   }

   if (nEffectiveBoat == 0) {
      return 0;
   }

   // Trie les prix pour récupérer la médiane.
   qsort(txs, nEffectiveBoat, sizeof(txs[0]), cmpfunc_price);

   if (nEffectiveBoat % 2 == 0) {
      // Si il y a un nombre paire d'élément, la médiane est la moyenne des deux
      // élément au milieu.
      return (txs[nEffectiveBoat / 2 - 1] + txs[nEffectiveBoat / 2]) / 2;
   } else {
      return txs[nEffectiveBoat / 2];
   }
}

// ------------------------------------------------------------------------------
// Calcule la déviation standard des taxes annuelles des bateaux
// du port qui correspondent à la condition passée en paramètre, retourne la médiane
// ------------------------------------------------------------------------------
Price stddevAnnualTaxes(const Boat* port[], size_t nbBoats,
                        bool (* condition)(const Boat*)) {
   Price mean = meanAnnualTaxes(port, nbBoats, condition);
   Price sum = 0;
   size_t effectiveNumberOfBoat = 0;

   // Calcule la somme des carrés des écarts avec la moyenne des bateaux
   // correspondant à la condition.
   for (size_t i = 0; i < nbBoats; ++i) {
      if (condition(port[i])) {
         sum += (taxe(port[i]) - mean) * (taxe(port[i]) - mean);
         ++effectiveNumberOfBoat;
      }
   }

   return sqrt(sum / (double) effectiveNumberOfBoat);
}

// ------------------------------------------------------------------------------
// Affiche les taxes perçus du port
// ------------------------------------------------------------------------------
void showTaxesPerCat(const Boat** port, size_t nbBoat) {
   bool (* conditions[])(const Boat*) = {isSailing, isPleasure, isFishing};
   const Name BOAT_NAME_TYPE[] = {PROPULSION_NAMES[0], MOTOR_BOAT_NAMES[1],
                                  MOTOR_BOAT_NAMES[0]};
   const size_t NB_TYPE = sizeof(conditions) / sizeof(conditions[0]);

   // Titre du tableau.
   printf("Statistiques des taxes par type de bateau [CHF]:\n");

   // En-tête du tableau.
   printf("%*s | %*s | %*s | %*s | %*s\n", TITLE_L, "Type des bateaux",
          SUM_L, "Somme", MEAN_L, "Moyenne", MEDIAN_L, "Mediane",
          STDDEV_L, "Ecart-type");

   // Affiche chaque ligne.
   for (size_t i = 0; i < NB_TYPE; ++i) {
      printf("%*s | %*.*f | %*.*f | %*.*f | %*.*f \n",
             TITLE_L, BOAT_NAME_TYPE[i],
             SUM_L, NB_DECIMAL, sumAnnualTaxes(port, nbBoat, conditions[i]),
             MEAN_L, NB_DECIMAL, meanAnnualTaxes(port, nbBoat, conditions[i]),
             MEDIAN_L, NB_DECIMAL, medianAnnualTaxes(port, nbBoat, conditions[i]),
             STDDEV_L, NB_DECIMAL, stddevAnnualTaxes(port, nbBoat, conditions[i]));
   }
}
