#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "boat.h"

Boat* sailBoat(Name boatName, uint16_t sailSurface) {
   SailingBoat* sailingBoat = (SailingBoat*) malloc(sizeof(SailingBoat));
   sailingBoat->sailSurface = sailSurface;

   Boat* b = (Boat*) malloc(sizeof(Boat));
   *b = (Boat) {.boatName = boatName, .propulsionType = SAIL, .boatProperties = {.sailingBoat = sailingBoat}};
   return b;
}

Boat* fishingBoat(Name boatName, uint16_t motorPower, uint8_t fishMaxWeight) {
   FishingBoat* fishingBoat = (FishingBoat*) malloc(sizeof(FishingBoat));
   fishingBoat->fishMaxWeight = fishMaxWeight;

   MotorBoat* motorBoat = (MotorBoat*) malloc(sizeof(MotorBoat));
   *motorBoat = (MotorBoat) {.motorPower = motorPower, .motorBoatType = FISHING,
           .motorBoatProperties = {.fishingBoat = fishingBoat}};

   Boat* b = (Boat*) malloc(sizeof(Boat));
   *b = (Boat) {.boatName = boatName, .propulsionType = MOTOR, .boatProperties = {.motorBoat = motorBoat}};
   return b;
}

Boat* pleasureBoat(Name boatName, uint16_t motorPower, uint8_t length, Name ownerName) {
   PleasureBoat* pleasureBoat = (PleasureBoat*) malloc(sizeof(PleasureBoat));
   *pleasureBoat = (PleasureBoat) {.length = length, .ownerName = ownerName};

   MotorBoat* motorBoat = (MotorBoat*) malloc(sizeof(MotorBoat));
   *motorBoat = (MotorBoat) {.motorPower = motorPower, .motorBoatType = PLEASURE,
           .motorBoatProperties = {.pleasureBoat = pleasureBoat}};

   Boat* b = (Boat*) malloc(sizeof(Boat));
   *b = (Boat) {.boatName = boatName, .propulsionType = MOTOR, .boatProperties = {.motorBoat = motorBoat}};
   return b;
}


void destroyBoat(Boat* boat) {
   if (boat->propulsionType == MOTOR) {
      free(boat->boatProperties.motorBoat->motorBoatProperties.fishingBoat);
   }

   free(boat->boatProperties.motorBoat);
   free(boat);
   boat = NULL;
}

bool isSailing(const Boat* boat) {
    return boat->propulsionType == SAIL;
}

bool isFishing(const Boat* boat) {
    if(boat->propulsionType != SAIL)
        return boat->boatProperties.motorBoat->motorBoatType == FISHING;
    return false;
}

bool isPleasure(const Boat* boat) {
    if(boat->propulsionType != SAIL)
        return boat->boatProperties.motorBoat->motorBoatType == PLEASURE;
    return false;
}

void showBoat(const Boat* boat) {
   printf("Nom: %s\n", boat->boatName);
   printf("Type: %s\n", PROPULSION_NAMES[boat->propulsionType]);

   // TODO: revoir position de l'unité.
   switch (boat->propulsionType) {
      case SAIL:
         printf("Surface de la voile [m2]: %" PRIu16 "\n",
                boat->boatProperties.sailingBoat->sailSurface);
         break;

      case MOTOR:
         printf("Sous-type: %s\n",
                MOTOR_BOAT_NAMES[boat->boatProperties.motorBoat->motorBoatType]);
         printf("Puissance moteur [CV]: %" PRIu16 "\n",
                boat->boatProperties.motorBoat->motorPower);

         switch (boat->boatProperties.motorBoat->motorBoatType) {
            case FISHING:
               printf("Poids maximum de poisson pecher [t] : %" PRIu8 "\n",
                      boat->boatProperties.motorBoat->motorBoatProperties.fishingBoat->fishMaxWeight);
               break;

            case PLEASURE:
               printf("Longueur [m] : %" PRIu8 "\n",
                      boat->boatProperties.motorBoat->motorBoatProperties.pleasureBoat->length);
               printf("Nom du proprietaire : %s\n",
                      boat->boatProperties.motorBoat->motorBoatProperties.pleasureBoat->ownerName);
               break;
         }
         break;
   }

   printf("\n");
}
