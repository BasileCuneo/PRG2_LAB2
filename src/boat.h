#ifndef PRG2_LAB2_BOAT_H
#define PRG2_LAB2_BOAT_H

#include <stdbool.h>
#include <stdint.h>

typedef const char* Name;

typedef enum {SAIL, MOTOR} PropulsionType;

typedef enum {FISHING, PLEASURE} MotorBoatType;

static const Name PROPULSION_NAMES[] = {"Voilier", "Bateau a moteur"};
static const Name MOTOR_BOAT_NAMES[] = {"Bateau de peche", "Bateau de plaisance"};

typedef struct {
   uint16_t sailSurface;
} SailingBoat;

typedef struct {
   uint8_t fishMaxWeight;
} FishingBoat;

typedef struct {
   uint8_t length;
   Name ownerName;
} PleasureBoat;

typedef union {
   FishingBoat* fishingBoat;
   PleasureBoat* pleasureBoat;
} MotorBoatProperties;

typedef struct {
   uint16_t motorPower;
   MotorBoatType motorBoatType;
   MotorBoatProperties motorBoatProperties;
} MotorBoat;

typedef union {
   SailingBoat* sailingBoat;
   MotorBoat* motorBoat;
} BoatProperties;

typedef struct {
   Name boatName;
   PropulsionType propulsionType;
   BoatProperties boatProperties;
} Boat;

Boat* sailBoat(Name boatName, uint16_t sailSurface);

Boat* fishingBoat(Name boatName, uint16_t motorPower, uint8_t fishMaxWeight);

Boat* pleasureBoat(Name boatName, uint16_t motorPower, uint8_t length, Name ownerName);

void destroyBoat(Boat* boat);

bool isSailing(const Boat* boat);

bool isFishing(const Boat* boat);

bool isPleasure(const Boat* boat);

void showBoat(const Boat* boat);

#endif //PRG2_LAB2_BOAT_H
