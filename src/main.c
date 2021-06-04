/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Clément Dieperink, Basile Cuneo, Joris Schaller
 Date creation  : 28.05.2021

 Description    : Fichier permettant de démontrer la fonctionnalités de
 nos différentes fonctions

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <inttypes.h>

#include "boat.h"
#include "calcul.h"

int main(void) {
   Boat* port[] = {
      sailBoat("Flying Clipper", 125),
      fishingBoat("Viking", 200, 10),
      pleasureBoat("Black Pearl", 1000, 50, "Jack Sparrow"),
      pleasureBoat("Flying Dutchman", 500, 10, "Davy Jones"),
      sailBoat("Queen Anne's Revenge", 6700),
      fishingBoat("Sedov", 400, 50),
      pleasureBoat("Silent Mary", 1250, 60, "Armando Salazar"),
      fishingBoat("Otter", 180, 25),
      sailBoat("Preussen", 210),
      pleasureBoat("Interceptor", 25, 5, "Lord Becket")
   };

   const size_t NB_BOATS = sizeof(port) / sizeof(port[0]);

   // Affiche les informations des tous les bateaux.
   for (size_t i = 0; i < NB_BOATS; ++i) {
      printf("Bateau numero: %" PRIu64 "\n", i);
      if (port[i] == NULL) {
         printf("Erreur lors de la creation du bateau\n\n");
      } else {
         showBoat(port[i]);
      }
   }

   // Affiches les taxes des bateaux par catégorie.
   showTaxesPerCat((const Boat**) port, NB_BOATS);

   // Libère la mémoire.
   for (size_t i = 0; i < NB_BOATS; ++i) {
      destroyBoat(port[i]);
   }

   return 0;
}
