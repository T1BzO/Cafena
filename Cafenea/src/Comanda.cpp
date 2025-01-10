#include "Comanda.h"
#include <iostream>

// Constructorul clasei Comanda
Comanda::Comanda(const std::string& client, const std::vector<std::string>& produse, double total, const std::string& oras)
    : client(client), produse(produse), total(total), oras(oras) {}

// Metoda afiseazaComanda
void Comanda::afiseazaComanda() const {
    std::cout << "Client: " << client << "\nProduse:\n";
    for (const auto& produs : produse) {
        std::cout << "- " << produs << "\n";
    }
    std::cout << "Total: " << total << " RON\nOras: " << oras << "\n";
}
