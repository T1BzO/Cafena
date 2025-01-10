#include "Angajat.h"
#include "CSVUtils.h"
#include <iostream>
#include <algorithm>
#include <fstream>

// Implementarea clasei de bază
Angajat::Angajat(const std::string& nume, const std::string& functie, double tarifPeOra, const std::string& id, const std::string& parola)
    : nume(nume), functie(functie), tarifPeOra(tarifPeOra), idAngajat(id), parolaAngajat(parola), oraInceput(0), oraSfarsit(0) {}


std::string Angajat::getNume() const {
    return nume;
}

std::string Angajat::getFunctie() const {
    return functie;
}

int Angajat::getOraInceput() const {
    return oraInceput;
}

int Angajat::getOraSfarsit() const {
    return oraSfarsit;
}

double Angajat::getTarifPeOra() const {
    return tarifPeOra;
}

void Angajat::setProgram(int inceput, int sfarsit) {
    if (inceput < 0 || sfarsit > 24 || inceput >= sfarsit) {
        std::cerr << "Program invalid! Ora de început trebuie să fie mai mică decât ora de sfârșit.\n";
        return;
    }
    oraInceput = inceput;
    oraSfarsit = sfarsit;
}

void Angajat::setTarifPeOra(double tarif) {
    tarifPeOra = tarif;
}

double Angajat::calculeazaSalariuZilnic() const {
    int oreLucrate = oraSfarsit - oraInceput;
    return oreLucrate * tarifPeOra;
}


std::string Angajat::getOras() const {
    return oras;
}
void Angajat::setOras(const std::string& orasNou) {
    oras = orasNou;
}

std::string Angajat::getId() const {
    return idAngajat;
}

std::string Angajat::getParola() const {
    return parolaAngajat;
}

bool Angajat::verificaParola(const std::string& parola) const {
    return parola == parolaAngajat;
}


// Constructor
Manager::Manager(const std::string& nume, double salariu, const std::string& id, const std::string& parola)
    : Angajat(nume, "Manager", salariu, id, parola) {}

void Manager::actiuni(const std::map<std::string, double>& produse) {
    std::cout << "Managerul poate adauga/sterge angajati, evenimente si genera rapoarte.\n";
}
// Adăugare eveniment
void Manager::adaugaEveniment(std::vector<Eveniment>& evenimente) {
    std::string nume;
    double cost;

    std::cout << "Introduceti numele evenimentului: ";
    std::cin.ignore();
    std::getline(std::cin, nume);

    std::cout << "Introduceti costul evenimentului: ";
    std::cin >> cost;

    evenimente.emplace_back(nume, cost);
    std::cout << "Eveniment adaugat cu succes!\n";

    // Salvează evenimentele în fișierul CSV
    scrieEvenimenteInCSV("data/Evenimente.csv", evenimente);
}


// Ștergere eveniment
void Manager::stergeEveniment(std::vector<Eveniment>& evenimente) {
    std::string nume;
    std::cout << "Introduceti numele evenimentului de sters: ";
    std::cin.ignore();
    std::getline(std::cin, nume);

    auto it = std::remove_if(evenimente.begin(), evenimente.end(), [&](const Eveniment& eveniment) {
        return eveniment.getNume() == nume;
    });

    if (it != evenimente.end()) {
        evenimente.erase(it, evenimente.end());
        std::cout << "Eveniment sters cu succes!\n";

        // Actualizează fișierul CSV
        scrieEvenimenteInCSV("data/Evenimente.csv", evenimente);
    } else {
        std::cerr << "Evenimentul nu a fost gasit.\n";
    }
}

// Adăugare angajat
void Manager::adaugaAngajat(std::vector<Angajat*>& angajati) {
    std::string nume, functie, id, parola;
    double tarifPeOra;
    int oraInceput, oraSfarsit;

    std::cout << "Introduceti numele angajatului: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nume);

    std::cout << "Introduceti functia angajatului (Ospatar/Barista): ";
    std::getline(std::cin, functie);

    if (functie != "Ospatar" && functie != "Barista") {
        std::cerr << "Functie invalida! Angajatul nu a fost adaugat.\n";
        return;
    }

    std::cout << "Introduceti tariful pe ora: ";
    while (!(std::cin >> tarifPeOra) || tarifPeOra <= 0) {
        std::cerr << "Tarif invalid! Introduceti un numar pozitiv.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Introduceti ora de inceput a programului (0-24): ";
    while (!(std::cin >> oraInceput) || oraInceput < 0 || oraInceput > 24) {
        std::cerr << "Ora de inceput invalida! Introduceti un numar intre 0 si 24.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Introduceti ora de sfarsit a programului (0-24): ";
    while (!(std::cin >> oraSfarsit) || oraSfarsit <= oraInceput || oraSfarsit > 24) {
        std::cerr << "Ora de sfarsit invalida! Trebuie sa fie dupa ora de inceput si intre 0 si 24.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Introduceti ID-ul angajatului: ";
    std::cin >> id;

    std::cout << "Introduceti parola angajatului: ";
    std::cin >> parola;

    Angajat* nouAngajat = nullptr;
    if (functie == "Ospatar") {
        nouAngajat = new Ospatar(nume, tarifPeOra, id, parola);
    } else if (functie == "Barista") {
        nouAngajat = new Barista(nume, tarifPeOra, id, parola);
    }

    if (nouAngajat) {
        nouAngajat->setProgram(oraInceput, oraSfarsit);
        nouAngajat->setOras(this->getOras()); // Setăm orașul automat
        angajati.push_back(nouAngajat);

        scrieAngajatiInCSV("data/Angajati.csv", angajati);
        std::cout << "Angajatul " << nume << " a fost adaugat cu succes la orasul " << this->getOras() << ".\n";
    }
}
void Manager::modificaAngajat(std::vector<Angajat*>& angajati) {
    std::string id;
    std::cout << "Introduceti ID-ul angajatului de modificat: ";
    std::cin >> id;

    for (auto* angajat : angajati) {
        if (angajat->getId() == id) {
            if (angajat->getOras() != this->getOras()) {
                std::cerr << "Nu aveti permisiunea sa modificati angajati din alt oras.\n";
                return;
            }

            int optiune;
            std::cout << "Ce doriti sa modificati?\n";
            std::cout << "1. Program\n";
            std::cout << "2. Tarif pe ora\n";
            std::cout << "3. Oras\n";
            std::cin >> optiune;

            switch (optiune) {
                case 1: {
                    int oraInceput, oraSfarsit;
                    std::cout << "Introduceti noua ora de inceput: ";
                    std::cin >> oraInceput;
                    std::cout << "Introduceti noua ora de sfarsit: ";
                    std::cin >> oraSfarsit;
                    angajat->setProgram(oraInceput, oraSfarsit);
                    break;
                }
                case 2: {
                    double tarif;
                    std::cout << "Introduceti noul tarif pe ora: ";
                    std::cin >> tarif;
                    angajat->setTarifPeOra(tarif);
                    break;
                }
                case 3: {
                    std::cerr << "Nu aveti permisiunea sa modificati orasul angajatului.\n";
                    return;
                }
                default:
                    std::cerr << "Optiune invalida.\n";
                    return;
            }

            scrieAngajatiInCSV("data/Angajati.csv", angajati);
            std::cout << "Angajatul a fost actualizat cu succes.\n";
            return;
        }
    }
    std::cerr << "Angajatul cu ID-ul " << id << " nu a fost gasit.\n";
}

void Manager::vizualizeazaAngajati(const std::vector<Angajat*>& angajati) const {
    std::cout << "Angajatii din orasul " << this->getOras() << ":\n";
    for (const auto& angajat : angajati) {
        if (angajat->getOras() == this->getOras()) {
            std::cout << "- " << angajat->getNume() << " (" << angajat->getFunctie() << ", ID: " << angajat->getId() << ")\n";
        }
    }
}
// Ștergere angajat
void Manager::stergeAngajat(std::vector<Angajat*>& angajati) {
    std::string id;
    std::cout << "Introduceti ID-ul angajatului de sters: ";
    std::cin >> id;

    for (auto it = angajati.begin(); it != angajati.end(); ++it) {
        if ((*it)->getId() == id) {
            if ((*it)->getOras() != this->getOras()) {
                std::cerr << "Nu aveti permisiunea sa stergeti angajati din alt oras.\n";
                return;
            }

            std::cout << "Stergerea angajatului " << (*it)->getNume() << " (ID: " << id << ")...\n";
            delete *it;
            angajati.erase(it);

            scrieAngajatiInCSV("data/Angajati.csv", angajati);
            std::cout << "Angajatul a fost sters cu succes.\n";
            return;
        }
    }
    std::cerr << "Angajatul cu ID-ul " << id << " nu a fost gasit.\n";
}

// Generare raport
void Manager::genereazaRaport(std::vector<Comanda>& comenzi, const std::vector<Eveniment>& evenimente, const std::vector<Angajat*>& angajati) const {
    double venituri = 0.0;
    double costuriAngajati = 0.0;

    // Calculate total salaries for the city
    for (const auto& angajat : angajati) {
        if (angajat->getOras() == getOras()) {
            int oreLucrate = angajat->getOraSfarsit() - angajat->getOraInceput();
            costuriAngajati += oreLucrate * angajat->getTarifPeOra();
        }
    }

    // Prepare a vector for remaining commands and calculate revenue for the manager's city
    std::vector<Comanda> comenziRamase;
    for (const auto& comanda : comenzi) {
        if (comanda.getOras() == getOras()) {
            venituri += comanda.getTotal();
        } else {
            comenziRamase.push_back(comanda); // Keep commands from other cities
        }
    }

    // Overwrite the in-memory vector with the remaining commands
    comenzi = comenziRamase;

    // Write the updated commands back to Comenzi.csv
    scrieComenziInCSV("data/Comenzi.csv", comenzi);

    // Write the report using the helper function
    double profit = venituri - costuriAngajati;
    scrieRapoarteInCSV("data/Raport.csv", venituri, costuriAngajati, profit, getOras());
    // Display the report
    std::cout << "=== RAPORT ZILNIC PENTRU ORASUL " << getOras() << " ===\n";
    std::cout << "Venituri: " << venituri << " RON\n";
    std::cout << "Costuri angajați: " << costuriAngajati << " RON\n";
    std::cout << "Profit: " << profit << " RON\n";
}


void Manager::modificaStoc(std::map<std::string, Produs>& produse) {
    std::string numeProdus;
    int cantitate;

    std::cout << "Introduceti numele produsului pentru modificare: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, numeProdus);

    auto it = produse.find(numeProdus);
    if (it != produse.end()) {
        std::cout << "Introduceti noua cantitate pentru \"" << numeProdus << "\": ";
        while (!(std::cin >> cantitate) || cantitate < 0) {
            std::cerr << "Cantitate invalidă! Introduceți un număr pozitiv.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        it->second.setCantitate(cantitate);
        std::cout << "Cantitatea pentru produsul \"" << numeProdus << "\" a fost actualizată la " << cantitate << ".\n";

        // Actualizare fișier CSV
        scrieProduseInCSV("data/Produse.csv", produse);
    } else {
        std::cerr << "Produsul \"" << numeProdus << "\" nu există în stoc.\n";
    }
}

// Implementarea clasei Ospatar
Ospatar::Ospatar(const std::string& nume, double salariu, const std::string& id, const std::string& parola)
    : Angajat(nume, "Ospatar", salariu, id, parola) {}

// Define all virtual functions declared in the header

void Ospatar::adaugaComanda(std::vector<Comanda>& comenzi, std::map<std::string, Produs>& produse, int reducere) {
    std::string produs;
    int cantitate;
    std::vector<std::string> produseComanda;
    double total = 0.0;

    while (true) {
        std::cout << "Introduceti numele produsului (sau 'stop' pentru a incheia): ";
        std::getline(std::cin, produs);
        produs = normalize(produs);
        if (produs == "stop") break;

        // Normalize product name for case-insensitive matching
        auto it = produse.find(normalize(produs));
        if (it != produse.end()) {
            std::cout << "Introduceti cantitatea pentru " << produs << ": ";
            while (!(std::cin >> cantitate) || cantitate <= 0) {
                std::cerr << "Cantitate invalida. Va rugam sa introduceti un numar pozitiv.\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            std::cin.ignore(1000, '\n'); // Curățăm fluxul după citire

            if (cantitate <= it->second.getCantitate()) {
                it->second.setCantitate(it->second.getCantitate() - cantitate);
                produseComanda.push_back(produs + " x" + std::to_string(cantitate));
                total += it->second.getPret() * cantitate;
            } else {
                std::cerr << "Stoc insuficient pentru produsul \"" << produs << "\".\n";
            }
        } else {
            std::cerr << "Produsul \"" << produs << "\" nu exista in lista.\n";
        }
    }

    if (!produseComanda.empty()) {
        total -= total * (reducere / 100.0); // Aplicam reducerea
        comenzi.emplace_back("Client", produseComanda, total, this->getOras());
        std::cout << "Comanda a fost adaugata cu succes! Total: " << total << " RON\n";

        // Save updated stock to CSV
        scrieProduseInCSV("data/Produse.csv", produse);
        scrieComenziInCSV("data/Comenzi.csv", comenzi);
    } else {
        std::cout << "Nu a fost adaugat niciun produs. Comanda anulata.\n";
    }
}

void Ospatar::actiuni(const std::map<std::string, double>& produse) {
    std::cout << "Ospătarul poate adăuga comenzi.\n";
}


// Implementarea clasei Barista
Barista::Barista(const std::string& nume, double tarifPeOra, const std::string& id, const std::string& parola)
    : Angajat(nume, "Barista", tarifPeOra, id, parola) {}

void Barista::actiuni(const std::map<std::string, double>& produse) {
    std::cout << "Barista poate prepara bauturi.\n";
}
