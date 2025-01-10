#include "Raport.h"
#include <iostream>

void Raport::genereazaRaport(const std::vector<Angajat>& angajati, const std::vector<Produs>& produse, const std::vector<Comanda>& comenzi) {
    double venituri = 0.0;
    double costuriAngajati = 0.0;

    // Calculam costurile pentru angajati
    for (const auto& angajat : angajati) {
        int oreLucrate = angajat.getOraSfarsit() - angajat.getOraInceput();
        double costAngajat = oreLucrate * angajat.getTarifPeOra();
        costuriAngajati += costAngajat;
    }

    // Calculam veniturile din comenzi
    for (const auto& comanda : comenzi) {
        venituri += comanda.getTotal();
    }

    std::cout << "=== RAPORT ZILNIC ===\n";
    std::cout << "Venituri totale: " << venituri << " RON\n";
    std::cout << "Costuri angajati: " << costuriAngajati << " RON\n";
    std::cout << "Profit: " << venituri - costuriAngajati << " RON\n";
}
