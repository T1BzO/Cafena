#ifndef EVENIMENT_H
#define EVENIMENT_H

#include <string>

class Eveniment {
public:
    Eveniment(const std::string& nume, double cost);
    std::string getNume() const;
    double getCost() const;
    void afiseazaEveniment() const;

private:
    std::string nume;
    double cost;
};

#endif
