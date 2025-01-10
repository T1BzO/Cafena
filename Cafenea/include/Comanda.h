#ifndef COMANDA_H
#define COMANDA_H

#include <string>
#include <vector>

class Comanda {
private:
    std::string client;
    std::vector<std::string> produse;
    double total;
    std::string oras;

public:
    // Constructor
    Comanda(const std::string& client, const std::vector<std::string>& produse, double total, const std::string& oras);

    // Metode inline
    std::string getClient() const { return client; }
    std::vector<std::string> getProduse() const { return produse; }
    double getTotal() const { return total; }
    std::string getOras() const { return oras; }

    // Metodă non-inline
    void afiseazaComanda() const;
};

#endif
