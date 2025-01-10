#include "Stoc.h"
#include <iostream>

void Stoc::adaugaProdus(const Produs& produs) {
    produse.push_back(produs);
}

bool Stoc::scadeProdus(const std::string& nume, int cantitate) {
    for (auto& produs : produse) {
        if (produs.getNume() == nume) {
            return produs.scadeStoc(cantitate);
        }
    }
    std::cerr << "Produsul " << nume << " nu exista in stoc.\n";
    return false;
}

void Stoc::afiseazaStoc() const {
    for (const auto& produs : produse) {
        produs.afiseazaProdus();
    }
}
