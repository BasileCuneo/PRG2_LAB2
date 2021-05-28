#ifndef PRG2_LAB2_CALCUL_H
#define PRG2_LAB2_CALCUL_H

size_t[] sumAnnualTaxes(const Boat[] port, size_t nbBoats);

double[] meanAnnualTaxes(const Boat[] port, size_t nbBoats);

size_t[] medianAnnualTaxes(const Boat[] port, size_t nbBoats);

double[] stddevAnnualTaxes(const Boat[] port, size_t nbBoats);

void show(const size_t[] sums, const double[] mean, const size_t[] median, const double[] stddev);

#endif //PRG2_LAB2_CALCUL_H
