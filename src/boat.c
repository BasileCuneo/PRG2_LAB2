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
#include <inttypes.h>
#include "boat.h"
#include "calcul.h"

// ------------------------------------------------------------------------------
// Crée un bateau à voile avec un nom et une surface de voile.
// ------------------------------------------------------------------------------
Boat sailBoat(Name boatName, uint16_t sailSurface) {
   return (Boat) {.name = boatName, .propulsionType = SAIL,
      .properties = {.sailing = {.sailSurface = sailSurface}}};
}

// ------------------------------------------------------------------------------
// Crée un bateau de pêche (sous classe de bateau moteur) avec
// un nom et une puissance moteur et un tonnage maximum de pêche.
// ------------------------------------------------------------------------------
Boat fishingBoat(Name boatName, uint16_t motorPower, uint8_t fishMaxWeight) {
   return (Boat) {.name = boatName, .propulsionType = MOTOR,
      .properties = {.motor = {.power = motorPower, .type = FISHING,
         .properties = {.fishing = {.fishMaxWeight = fishMaxWeight}}}}};
}

// ------------------------------------------------------------------------------
// Crée un bateau de plaisance (sous classe de bateau moteur) avec
// un nom et une longueur et un nom de propriétaire.
// ------------------------------------------------------------------------------
Boat pleasureBoat(Name boatName, uint16_t motorPower, uint8_t length, Name ownerName) {
   return (Boat) {.name = boatName, .propulsionType = MOTOR,
      .properties = {.motor = {.power = motorPower, .type = PLEASURE,
         .properties = {.pleasure = { .length = length, .ownerName = ownerName}}}}};
}

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau à voile, false sinon.
// ------------------------------------------------------------------------------
bool isSailing(const Boat* boat) {
   return boat != NULL && boat->propulsionType == SAIL;
}

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau de pêche, false sinon.
// ------------------------------------------------------------------------------
bool isFishing(const Boat* boat) {
   return boat != NULL && boat->propulsionType != SAIL &&
          boat->properties.motor.type == FISHING;
}

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau de plaisance, false sinon.
// ------------------------------------------------------------------------------
bool isPleasure(const Boat* boat) {
   return boat != NULL && boat->propulsionType != SAIL &&
          boat->properties.motor.type == PLEASURE;
}

// ------------------------------------------------------------------------------
// Présente le bateau passé en paramètre.
// ------------------------------------------------------------------------------
void showBoat(const Boat* boat) {
   printf("Nom: %s\n", boat->name);
   printf("Type: %s\n", PROPULSION_NAMES[boat->propulsionType]);

   // switch pour permettre l'ajout de nouvelles catégories
   switch (boat->propulsionType) {
      case SAIL:
         printf("Surface de la voile : %" PRIu16 " m2\n",
                boat->properties.sailing.sailSurface);
         break;

      case MOTOR:
         printf("Sous-type: %s\n",
                MOTOR_BOAT_NAMES[boat->properties.motor.type]);
         printf("Puissance moteur : %" PRIu16 " CV\n",
                boat->properties.motor.power);

         switch (boat->properties.motor.type) {
            case FISHING:
               printf("Poids maximum de poisson pecher : %" PRIu8 " t\n",
                      boat->properties.motor.properties.fishing.fishMaxWeight);
               break;

            case PLEASURE:
               printf("Longueur : %" PRIu8 " m\n",
                      boat->properties.motor.properties.pleasure.length);
               printf("Nom du proprietaire : %s\n",
                      boat->properties.motor.properties.pleasure.ownerName);
               break;
         }
         break;
   }

   printf("Taxe annuelle: %.*f chf\n", NB_DECIMAL, taxe(boat));
   printf("\n");
}
