/*
 -----------------------------------------------------------------------------------
 Nom du fichier : boat.h
 Auteur(s)      : Clément Dieperink, Basile Cuneo, Joris Schaller
 Date creation  : 28.05.2021

 Description    : Librairie permettant la gestion de bateau

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#ifndef PRG2_LAB2_BOAT_H
#define PRG2_LAB2_BOAT_H

#include <stdbool.h>
#include <stdint.h>

typedef const char* Name;

typedef enum {
   SAIL, MOTOR
} PropulsionType;

typedef enum {
   FISHING, PLEASURE
} MotorBoatType;

// Tableaux pour permettre contenant le nom des catégories et sous-catégories.
static const Name PROPULSION_NAMES[] = {"Voilier", "Bateau a moteur"};
static const Name MOTOR_BOAT_NAMES[] = {"Bateau de peche", "Bateau de plaisance"};

// ------------------------------------------------------------------------------
// Structure contenant les propriétés relatives à la voile.
// ------------------------------------------------------------------------------
typedef struct {
   uint16_t sailSurface; // Mètre carré [m2]
} SailingBoat;

// ------------------------------------------------------------------------------
// Structure contenant les propriétés relatives à la pêche.
// ------------------------------------------------------------------------------
typedef struct {
   uint8_t fishMaxWeight; // Tonne [t]
} FishingBoat;

// ------------------------------------------------------------------------------
// Structure contenant les propriétés relatives à la plaisance.
// ------------------------------------------------------------------------------
typedef struct {
   uint8_t length; // Mètre [m]
   Name ownerName;
} PleasureBoat;

// ------------------------------------------------------------------------------
// Union contenant soit les caractéristiques d'un bateau de pêche,
// soit les caractéristiques d'un bateau de plaisance.
// ------------------------------------------------------------------------------
typedef union {
   FishingBoat fishing;
   PleasureBoat pleasure;
} MotorBoatProperties;

// ------------------------------------------------------------------------------
// Structure contenant les caractéristiques d'un bateau à moteur
// c'est à dire : sa puissance son type et les propriétés relatives à son type.
// ------------------------------------------------------------------------------
typedef struct {
   uint16_t power; // Cheval-vapeur [CV]
   MotorBoatType type;
   MotorBoatProperties properties;
} MotorBoat;

// ------------------------------------------------------------------------------
// Union contenant les caractéristiques d'un bateau à moteur ou les propriétés
// d'un bateau à voile.
// ------------------------------------------------------------------------------
typedef union {
   SailingBoat sailing;
   MotorBoat motor;
} BoatProperties;

// ------------------------------------------------------------------------------
// Structure contenant le nom du bateau,son type de propulsion
// et ses propriétés, dépendantes du type de propulsion.
// ------------------------------------------------------------------------------
typedef struct {
   Name name;
   PropulsionType propulsionType;
   BoatProperties properties;
} Boat;

// ------------------------------------------------------------------------------
// Crée un bateau à voile avec un nom et une surface de voile.
// ------------------------------------------------------------------------------
Boat sailBoat(Name boatName, uint16_t sailSurface);

// ------------------------------------------------------------------------------
// Crée un bateau de pêche (sous classe de bateau moteur) avec
// un nom et une puissance moteur et un tonnage maximum de pêche.
// ------------------------------------------------------------------------------
Boat fishingBoat(Name boatName, uint16_t motorPower, uint8_t fishMaxWeight);

// ------------------------------------------------------------------------------
// Crée un bateau de plaisance (sous classe de bateau moteur) avec
// un nom et une longueur et un nom de propriétaire.
// ------------------------------------------------------------------------------
Boat pleasureBoat(Name boatName, uint16_t motorPower, uint8_t length, Name ownerName);

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau à voile, false sinon.
// ------------------------------------------------------------------------------
bool isSailing(const Boat* boat);

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau de pêche, false sinon.
// ------------------------------------------------------------------------------
bool isFishing(const Boat* boat);

// ------------------------------------------------------------------------------
// Renvoie true si le bateau est un bateau de plaisance, false sinon.
// ------------------------------------------------------------------------------
bool isPleasure(const Boat* boat);

// ------------------------------------------------------------------------------
// Présente le bateau passé en paramètre.
// ------------------------------------------------------------------------------
void showBoat(const Boat* boat);

#endif //PRG2_LAB2_BOAT_H
