#include <tuple>
#include "CSVUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>

void citesteAngajatiDinCSV(const std::string &filename, std::vector<Angajat *> &angajati)
{
    std::ifstream fisier(filename);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    std::string linie;
    std::getline(fisier, linie); // Ignoram header-ul

    while (std::getline(fisier, linie))
    {
        std::istringstream linieStream(linie);
        std::string nume, functie, id, parola, oras;
        double tarifPeOra;
        int oraInceput, oraSfarsit;

        std::getline(linieStream, nume, ',');
        std::getline(linieStream, functie, ',');
        linieStream >> tarifPeOra;
        linieStream.ignore(1, ',');
        std::getline(linieStream, id, ',');
        std::getline(linieStream, parola, ',');
        std::getline(linieStream, oras, ',');
        linieStream >> oraInceput;
        linieStream.ignore(1, ',');
        linieStream >> oraSfarsit;

        Angajat *nouAngajat = nullptr;
        if (functie == "Manager")
        {
            nouAngajat = new Manager(nume, tarifPeOra, id, parola);
        }
        else if (functie == "Ospatar")
        {
            nouAngajat = new Ospatar(nume, tarifPeOra, id, parola);
        }
        else if (functie == "Barista")
        {
            nouAngajat = new Barista(nume, tarifPeOra, id, parola);
        }

        if (nouAngajat)
        {
            nouAngajat->setOras(oras);
            nouAngajat->setProgram(oraInceput, oraSfarsit);
            angajati.push_back(nouAngajat);
        }
    }

    fisier.close();
}

#include <fstream>
#include "CSVUtils.h"

void scrieAngajatiInCSV(const std::string &filename, const std::vector<Angajat *> &angajati)
{
    std::ofstream fisier(filename, std::ios::trunc); // Deschidem fisierul in modul "trunc" pentru a suprascrie
    if (!fisier.is_open())
    {
        std::cerr << "Nu se poate deschide fisierul " << filename << " pentru scriere.\n";
        return;
    }

    // Scriem header-ul
    fisier << "Nume,Functie,TarifPeOra,ID,Parola,Oras,OraInceput,OraSfarsit\n";

    // Scriem fiecare angajat
    for (const auto &angajat : angajati)
    {
        fisier << angajat->getNume() << ","
               << angajat->getFunctie() << ","
               << angajat->getTarifPeOra() << ","
               << angajat->getId() << ","
               << angajat->getParola() << ","
               << angajat->getOras() << ","
               << angajat->getOraInceput() << ","
               << angajat->getOraSfarsit() << "\n";
    }

    fisier.close();
    std::cout << "Fisierul Angajati.csv a fost actualizat cu succes.\n";
}

void citesteProduseDinCSV(const std::string& filename, std::map<std::string, Produs>& produse) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nu se poate deschide fisierul " << filename << '\n';
        return;
    }

    std::string linie;
    int linieCurenta = 0;

    // Ignoram prima linie (header-ul)
    if (std::getline(file, linie)) {
        linieCurenta++;
        std::cout << "Header ignorat: " << linie << "\n";
    }

    while (std::getline(file, linie)) {
        linieCurenta++;
        std::stringstream ss(linie);
        std::string nume;
        std::string pretStr, cantitateStr;
        double pret = 0.0;
        int cantitate = 0;

        if (std::getline(ss, nume, ',') && std::getline(ss, pretStr, ',') && std::getline(ss, cantitateStr, ',')) {
            try {
                // Eliminam spatiile din jurul valorilor
                nume.erase(0, nume.find_first_not_of(" \t"));
                nume.erase(nume.find_last_not_of(" \t") + 1);
                pret = std::stod(pretStr);
                cantitate = std::stoi(cantitateStr);

                // Adaugam produsul in map
                produse[nume] = Produs(nume, pret, cantitate);
            } catch (const std::exception& e) {
                std::cerr << "Eroare la linia " << linieCurenta << ": \"" << linie << "\" - " << e.what() << '\n';
                continue;
            }
        } else {
            std::cerr << "Format invalid la linia " << linieCurenta << ": \"" << linie << "\"\n";
        }
    }

    file.close();
    std::cout << "Produsele au fost incarcate cu succes din " << filename << ".\n";
}

void scrieProduseInCSV(const std::string& filename, const std::map<std::string, Produs>& produse) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Nu se poate deschide fisierul " << filename << '\n';
        return;
    }
     file << "Nume,Pret,Cantitate\n";
    for (const auto& pair : produse) {
        const auto& produs = pair.second;
        file << produs.getNume() << "," << produs.getPret() << "," << produs.getCantitate() << '\n';
    }

    file.close();
    std::cout << "Produsele au fost salvate cu succes in " << filename << ".\n";
}

void citesteComenziDinCSV(const std::string &filename, std::vector<Comanda> &comenzi)
{
    std::ifstream fisier(filename);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    std::string linie;
    std::getline(fisier, linie); // Ignoram header-ul

    while (std::getline(fisier, linie))
    {
        std::istringstream linieStream(linie);
        std::string client, produseStr, oras;
        double total;

        std::getline(linieStream, client, ',');
        std::getline(linieStream, produseStr, ',');
        linieStream >> total;
        linieStream.ignore(1, ',');
        std::getline(linieStream, oras);

        std::vector<std::string> produse;
        std::istringstream produseStream(produseStr);
        std::string produs;
        while (std::getline(produseStream, produs, ';'))
        {
            produse.push_back(produs);
        }

        comenzi.emplace_back(client, produse, total, oras);
    }

    fisier.close();
}

void citesteEvenimenteDinCSV(const std::string &filename, std::vector<Eveniment> &evenimente)
{
    std::ifstream fisier(filename);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    std::string linie;
    std::getline(fisier, linie); // Ignora header-ul

    while (std::getline(fisier, linie))
    {
        std::istringstream linieStream(linie);
        std::string nume;
        double cost;

        std::getline(linieStream, nume, ',');
        linieStream >> cost;

        evenimente.emplace_back(nume, cost);
    }

    fisier.close();
}

void scrieRapoarteInCSV(const std::string &filename, double venituri, double costuri, double profit, const std::string &oras)
{
    std::ofstream fisier(filename, std::ios::app);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    fisier << "Oras," << oras << ",Venituri," << venituri << ",Costuri," << costuri << ",Profit," << profit << "\n";
    fisier.close();
}

void scrieComenziInCSV(const std::string &filename, const std::vector<Comanda> &comenzi)
{
    std::ofstream fisier(filename, std::ios::trunc); // Rescriem complet fisierul
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    // Scriem header-ul
    fisier << "Client,Produse,Total,Oras\n";

    // Scriem fiecare comanda
    for (const auto &comanda : comenzi)
    {
        fisier << comanda.getClient() << ",";

        for (size_t i = 0; i < comanda.getProduse().size(); ++i)
        {
            fisier << comanda.getProduse()[i];
            if (i != comanda.getProduse().size() - 1)
            {
                fisier << ";";
            }
        }

        fisier << "," << comanda.getTotal() << "," << comanda.getOras() << "\n";
    }

    fisier.close();
    std::cout << "Comenzile au fost scrise in fisierul " << filename << " cu succes.\n";
}

void scrieEvenimenteInCSV(const std::string &filename, const std::vector<Eveniment> &evenimente)
{
    std::ofstream fisier(filename, std::ios::app);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    for (const auto &eveniment : evenimente)
    {
        fisier << eveniment.getNume() << "," << eveniment.getCost() << "\n";
    }

    fisier.close();
}

int lastClientId = 0;

void citesteClientiDinCSV(const std::string &filename, std::map<std::string, std::tuple<std::string, int, int>> &clienti)
{
    std::ifstream fisier(filename);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    std::string linie, id, nume;
    int numarComenzi, reducere;
    std::getline(fisier, linie); // Ignoram header-ul

    while (std::getline(fisier, linie))
    {
        std::istringstream linieStream(linie);
        std::getline(linieStream, id, ',');
        std::getline(linieStream, nume, ',');
        linieStream >> numarComenzi;
        linieStream.ignore(1, ',');
        linieStream >> reducere;

        clienti[id] = std::make_tuple(nume, numarComenzi, reducere);

        // Actualizam ultimul ID numeric
        int numericId = std::stoi(id);
        if (numericId > lastClientId)
        {
            lastClientId = numericId;
        }
    }

    fisier.close();
}

void scrieClientiInCSV(const std::string &filename, const std::map<std::string, std::tuple<std::string, int, int>> &clienti)
{
    std::ofstream fisier(filename, std::ios::trunc);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    // Scriem header-ul
    fisier << "ID,Nume,NumarComenzi,Reducere\n";

    // Iteram prin map si accesam elementele tuplelor
    for (const auto &client : clienti)
    {
        const std::string &id = client.first;
        const std::string &nume = std::get<0>(client.second);
        int numarComenzi = std::get<1>(client.second);
        int reducere = std::get<2>(client.second);

        fisier << id << "," << nume << "," << numarComenzi << "," << reducere << "\n";
    }

    fisier.close();
}

int getLastClientId(const std::string &filename)
{
    std::ifstream fisier(filename);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return 0; // ID-ul implicit daca fisierul nu exista
    }

    std::string linie;
    int lastId = 0;

    // Ignoram header-ul
    std::getline(fisier, linie);

    // Citim ultima linie pentru a prelua ID-ul
    while (std::getline(fisier, linie))
    {
        std::istringstream linieStream(linie);
        std::string idStr;
        std::getline(linieStream, idStr, ',');

        try
        {
            int id = std::stoi(idStr);
            lastId = std::max(lastId, id);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Eroare la conversia ID-ului: " << idStr << std::endl;
        }
    }

    fisier.close();
    return lastId;
}
