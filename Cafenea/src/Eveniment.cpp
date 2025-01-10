#include "Eveniment.h"
#include <iostream>

Eveniment::Eveniment(const std::string& nume, double cost)
    : nume(nume), cost(cost) {}

std::string Eveniment::getNume() const {
    return nume;
}

double Eveniment::getCost() const {
    return cost;
}

void Eveniment::afiseazaEveniment() const {
    std::cout << "Eveniment: " << nume << ", Cost: " << cost << "\n";
}
