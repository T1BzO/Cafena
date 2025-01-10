#ifndef STOC_H
#define STOC_H

#include <vector>
#include "Produs.h"

class Stoc {
public:
    void adaugaProdus(const Produs& produs);
    bool scadeProdus(const std::string& nume, int cantitate);
    bool modificaProdus(const std::string& nume, double pretNou, int cantitateNoua, double costNou);
    bool stergeProdus(const std::string& nume);
    void afiseazaStoc() const;
    const std::vector<Produs>& getProduse() const;
    void genereazaRaportCSV(const std::string& filename) const;

private:
    std::vector<Produs> produse;
};


#endif
