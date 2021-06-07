/*
 -----------------------------------------------------------------------------------
 Nom du fichier : calcul.h
 Auteur(s)      : Clément Dieperink, Basile Cuneo, Joris Schaller
 Date creation  : 30.05.2021

 Description    : Librairie permettant la gestion de bateaux

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#ifndef PRG2_LAB2_CALCUL_H
#define PRG2_LAB2_CALCUL_H

#include <stdlib.h>
#include <inttypes.h>
#include "boat.h"

#define TAXED_SAIL 200u          // Seuil de taxation surface de voile
#define TAXED_WEIGHT 20u         // Seuil de taxation tonnage de poisson
#define TAXED_POWER 100u         // Seuil de taxation puissance

#define BASE_SAIL 50u            // Frais fixe bateau à voile
#define BASE_MOTOR 100u          // Frais fixe bateau à voile

#define BIG_SAIL 25u             // Frais additionnels avec une grande voile
// Frais additionnels à partir de 20 tonnes de poisson
#define BIG_FISH_WEIGHT 100u
// Frais additionnels pour un bateau de plaisance à faible puissance
#define SMALL_PLEASURE_MOTOR 50u
#define LENGTH_MULT 15u          // Frais additionnels en fonction de la longueur

#define TITLE_L 20   // Nombre de caractères pour l'affichage du titre des taxes.
#define SUM_L 10     // Nombre de caractères pour l'affichage de la somme des taxes.
#define MEAN_L 10    // Nombre de caractères pour l'affichage de la moyenne des taxes.
#define MEDIAN_L 10  // Nombre de caractères pour l'affichage de la médiane des taxes.
#define STDDEV_L 10  // Nombre de caractères pour l'affichage de l'écart-type des taxes.
#define NB_DECIMAL 2 // Nombre de décimales pour l'affichage des prix.

typedef double Price;

// ------------------------------------------------------------------------------
// Calcule la taxe annuelle du bateau et la retourne.
// ------------------------------------------------------------------------------
Price taxe(const Boat* boat);

// ------------------------------------------------------------------------------
// Calcule la somme des taxes annuelles des bateaux du port qui
// correspondent à la condition passée en paramètre, retourne la somme.
// ------------------------------------------------------------------------------
Price sumAnnualTaxes(const Boat port[], size_t nbBoats,
                     bool (* condition)(const Boat* boat));

// ------------------------------------------------------------------------------
// Calcule la moyenne des taxes annuelles des bateaux du port qui
// correspondent à la condition passée en paramètre, retourne la moyenne.
// ------------------------------------------------------------------------------
Price meanAnnualTaxes(const Boat port[], size_t nbBoats,
                      bool (* condition)(const Boat* boat));

// ------------------------------------------------------------------------------
// Calcule la médiane des taxes annuelles des bateaux du port
// qui correspondent à la condition passée en paramètre, retourne la médiane.
// ------------------------------------------------------------------------------
Price medianAnnualTaxes(const Boat port[], size_t nbBoats,
                        bool (* condition)(const Boat* boat));

// ------------------------------------------------------------------------------
// Calcule la déviation standard des taxes annuelles des bateaux
// du port qui correspondent à la condition passée en paramètre,
// retourne la déviation.
// ------------------------------------------------------------------------------
Price stddevAnnualTaxes(const Boat port[], size_t nbBoats,
                        bool (* condition)(const Boat* boat));

// ------------------------------------------------------------------------------
// Affiche les taxes perçus du port.
// ------------------------------------------------------------------------------
void showTaxesPerCat(const Boat port[], size_t nbBoat);

#endif //PRG2_LAB2_CALCUL_H
