#include <stdio.h>
#include <inttypes.h>

#include "boat.h"
#define NB_BOATS 10

int main(void) {
   Boat* port[NB_BOATS];

   port[0] = sailBoat("Flying Clipper", 125);
   port[1] = fishingBoat("Viking", 200, 10);
   port[2] = pleasureBoat("Black Pearl", 1000, 50, "Jack Sparrow");
   port[3] = pleasureBoat("Flying Dutchman", 500, 10, "Davy Jones");
   port[4] = sailBoat("Queen Anne's Revenge", 6700);
   port[5] = fishingBoat("Sedov", 400, 50);
   port[6] = pleasureBoat("Silent Mary", 1250, 60, "Armando Salazar");
   port[7] = fishingBoat("Otter", 180, 25);
   port[8] = sailBoat("Preussen", 210);
   port[9] = pleasureBoat("Interceptor", 25, 5, "Lord Becket");

   for (size_t i = 0; i < NB_BOATS; ++i) {
      printf("Bateau numero: %" PRIu64 "\n", i);
      showBoat(port[i]);
   }

   for (size_t i = 0; i < NB_BOATS; ++i) {
      destroyBoat(port[i]);
      port[i] = NULL;
   }

   return 0;
}
