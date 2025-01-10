#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include "Angajat.h"
#include "Produs.h"
#include "Comanda.h"
#include "Eveniment.h"

void citesteAngajatiDinCSV(const std::string& filename, std::vector<Angajat*>& angajati);
void scrieAngajatiInCSV(const std::string& filename, const std::vector<Angajat*>& angajati);
void citesteProduseDinCSV(const std::string& filename, std::map<std::string, Produs>& produse);
void citesteComenziDinCSV(const std::string& filename, std::vector<Comanda>& comenzi);
void citesteEvenimenteDinCSV(const std::string& filename, std::vector<Eveniment>& evenimente);
void scrieRapoarteInCSV(const std::string& filename, double venituri, double costuri, double profit, const std::string& oras);
void scrieComenziInCSV(const std::string& filename, const std::vector<Comanda>& comenzi);
void scrieEvenimenteInCSV(const std::string& filename, const std::vector<Eveniment>& evenimente);
void citesteClientiDinCSV(const std::string& filename, std::map<std::string, std::tuple<std::string, int, int>>& clienti);
void scrieClientiInCSV(const std::string& filename, const std::map<std::string, std::tuple<std::string, int, int>>& clienti);
int getLastClientId(const std::string& filename);
void scrieProduseInCSV(const std::string& filename, const std::map<std::string, Produs>& produse);


inline std::string normalize(const std::string& input) {
    std::string normalized = input;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}



extern int lastClientId;


#endif
