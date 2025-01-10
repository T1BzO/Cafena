#include "Produs.h"
#include <iostream>

Produs::Produs(const std::string& nume, double pret, int cantitate)
    : nume(nume), pret(pret), cantitate(cantitate) {}

std::string Produs::getNume() const {
    return nume;
}

double Produs::getPret() const {
    return pret;
}

int Produs::getCantitate() const {
    return cantitate;
}

void Produs::setPret(double pretNou) {
    pret = pretNou;
}

void adaugaStoc(int cantitate) {
    cantitate += cantitate;
}

void Produs::setCantitate(int cantitateNoua) {
    cantitate = cantitateNoua;
}

bool Produs::scadeStoc(int cantitateScazuta) {
    if (cantitateScazuta > cantitate) {
        std::cerr << "Stoc insuficient!" << std::endl;
        return false;
    }
    cantitate -= cantitateScazuta;
    return true;
}

void Produs::afiseazaProdus() const {
    std::cout << "Produs: " << nume << ", Pret: " << pret << ", Stoc: " << cantitate << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Produs& produs) {
    os << "Nume: " << produs.nume << ", Pret: " << produs.pret << ", Cantitate: " << produs.cantitate;
    return os;
}
