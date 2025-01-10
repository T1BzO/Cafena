#ifndef RAPORT_H
#define RAPORT_H

#include <string>
#include <vector>
#include "Angajat.h"
#include "Produs.h"
#include "Comanda.h"

class Raport {
public:
    static void genereazaRaport(const std::vector<Angajat>& angajati, const std::vector<Produs>& produse, const std::vector<Comanda>& comenzi);
};

#endif
