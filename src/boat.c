/*
 -----------------------------------------------------------------------------------
 Nom du fichier : boat.c
 Auteur(s)      : Clément Dieperink, Basile Cuneo, Joris Schaller
 Date creation  : 28.05.2021

 Description    : Fichier contenant toutes les implémentations nécessaires
 à la gestion de bateaux

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "boat.h"
#include "calcul.h"

// ------------------------------------------------------------------------------
// Crée un bateau à voile avec un nom et une surface de voile
// ------------------------------------------------------------------------------
Boat* sailBoat(Name boatName, uint16_t sailSurface) {
   // Alloue la mémoire pour la partie voile du bateau
   SailingBoat* sailingBoat = (SailingBoat*) malloc(sizeof(SailingBoat));
   if (sailingBoat == NULL) { // Vérification de l'allocation mémoire
      return NULL;
   }
   *sailingBoat = (SailingBoat) {.sailSurface = sailSurface};

   // Alloue la mémoire pour la partie principale du bateau
   Boat* b = (Boat*) malloc(sizeof(Boat));
   if (b == NULL) { // Vérification de l'allocation mémoire
      free(sailingBoat); // Désallocation de la partie voile
      return NULL;
   }
   *b = (Boat) {.name = boatName, .propulsionType = SAIL, .properties = {.sailing = sailingBoat}};
   return b;
}

// ------------------------------------------------------------------------------
// Crée un bateau de pêche (sous classe de bateau moteur) avec
// un nom boatName et une puissance power et un tonnage fishMaxWeight
// ------------------------------------------------------------------------------
Boat* fishingBoat(Name boatName, uint16_t motorPower, uint8_t fishMaxWeight) {
   // Alloue la mémoire pour la partie pèche
   FishingBoat* fishingBoat = (FishingBoat*) malloc(sizeof(FishingBoat));
   if (fishingBoat == NULL) { // Vérifiecation de l'allocation mémoire
      return NULL;
   }
   *fishingBoat = (FishingBoat) {.fishMaxWeight = fishMaxWeight};

   // Alloue la mémoire pour la partie moteur
   MotorBoat* motorBoat = (MotorBoat*) malloc(sizeof(MotorBoat));
   if (motorBoat == NULL) { // Vérification de l'allocation mémoire
      free(fishingBoat); // Désallocation de la partie pèche
      return NULL;
   }
   *motorBoat = (MotorBoat) {.power = motorPower, .type = FISHING,
      .properties = {.fishing = fishingBoat}};

   // Alloue la mémoire pour la partie principale du bateau
   Boat* b = (Boat*) malloc(sizeof(Boat));
   if (b == NULL) { // Vérification de l'allocation mémoire
      free(fishingBoat); // Désallocation de la partie pèche
      free(motorBoat); // Désallocation de la partie moteur
      return NULL;
   }
   *b = (Boat) {.name = boatName, .propulsionType = MOTOR, .properties = {.motor = motorBoat}};
   return b;
}

// ------------------------------------------------------------------------------
// Crée un bateau de plaisance (sous classe de bateau moteur) avec
// un nom et une taille et un nom de propriétaire
// ------------------------------------------------------------------------------
Boat* pleasureBoat(Name boatName, uint16_t motorPower, uint8_t length, Name ownerName) {
   // Alloue la mémoire pour la partie plaisance
   PleasureBoat* pleasureBoat = (PleasureBoat*) malloc(sizeof(PleasureBoat));
   if (pleasureBoat == NULL) { // Vérification de l'allocation mémoire
      return NULL;
   }
   *pleasureBoat = (PleasureBoat) {.length = length, .ownerName = ownerName};

   // Alloue la mémoire pour la partie moteur
   MotorBoat* motorBoat = (MotorBoat*) malloc(sizeof(MotorBoat));
   if (motorBoat == NULL) { // Vérification de l'allocation mémoire
      free(pleasureBoat); // Désallocation de la partie plaisance
      return NULL;
   }
   *motorBoat = (MotorBoat) {.power = motorPower, .type = PLEASURE,
      .properties = {.pleasure = pleasureBoat}};

   // Alloue la mémoire pour la partie principale du bateau
   Boat* b = (Boat*) malloc(sizeof(Boat));
   if (b == NULL) { // Vérification de l'allocation mémoire
      free(pleasureBoat); // Désallocation de la partie plaisance
      free(motorBoat); // Désallocation de la partie moteur
      return NULL;
   }
   *b = (Boat) {.name = boatName, .propulsionType = MOTOR, .properties = {.motor = motorBoat}};
   return b;
}


// ------------------------------------------------------------------------------
// Détruit un bateau et libère correctement la mémoire allouée
// ------------------------------------------------------------------------------
void destroyBoat(Boat* boat) {
   if (boat == NULL) return;
   if (boat->propulsionType == MOTOR) {
      // Désalloue la sous catégorie du moteur, désallouer la sous catégorie pèche ou plaisance revient
      // au même étant donné que les deux pointeurs sont stockés de la même façon dans une même union
      free(boat->properties.motor->properties.fishing);
   }
   // Désalloue la sous catégorie du bateau, désallouer la sous catégorie moteur ou voile revient
   // au même étant donné que les deux pointeurs sont stockés de la même façon dans une même union
   free(boat->properties.motor);
   free(boat); // Désaloue la partie principale du bateau
   boat = NULL;
}

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau à voile, false sinon
// ------------------------------------------------------------------------------
bool isSailing(const Boat* boat) {
   return boat != NULL && boat->propulsionType == SAIL;
}

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau de pêche, false sinon
// ------------------------------------------------------------------------------
bool isFishing(const Boat* boat) {
   return boat != NULL && boat->propulsionType != SAIL &&
          boat->properties.motor->type == FISHING;
}

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau de plaisance, false sinon
// ------------------------------------------------------------------------------
bool isPleasure(const Boat* boat) {
   return boat != NULL && boat->propulsionType != SAIL &&
          boat->properties.motor->type == PLEASURE;
}

// ------------------------------------------------------------------------------
// Présente le bateau passé en paramètre
// ------------------------------------------------------------------------------
void showBoat(const Boat* boat) {
   printf("Nom: %s\n", boat->name);
   printf("Type: %s\n", PROPULSION_NAMES[boat->propulsionType]);

   // switch pour permettre l'ajout de nouvelles catégories
   switch (boat->propulsionType) {
      case SAIL:
         printf("Surface de la voile : %" PRIu16 " m2\n",
                boat->properties.sailing->sailSurface);
         break;

      case MOTOR:
         printf("Sous-type: %s\n",
                MOTOR_BOAT_NAMES[boat->properties.motor->type]);
         printf("Puissance moteur : %" PRIu16 " CV\n",
                boat->properties.motor->power);

         switch (boat->properties.motor->type) {
            case FISHING:
               printf("Poids maximum de poisson pecher : %" PRIu8 " t\n",
                      boat->properties.motor->properties.fishing->fishMaxWeight);
               break;

            case PLEASURE:
               printf("Longueur : %" PRIu8 " m\n",
                      boat->properties.motor->properties.pleasure->length);
               printf("Nom du proprietaire : %s\n",
                      boat->properties.motor->properties.pleasure->ownerName);
               break;
         }
         break;
   }

   printf("Taxe annuelle: %.*f chf\n", NB_DECIMAL, taxe(boat));
   printf("\n");
}
