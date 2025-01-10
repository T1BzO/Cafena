#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CSVUtils.h"
#include "Angajat.h"
#include "Comanda.h"
#include "Eveniment.h"
#include "Stoc.h"
#include "Raport.h"

// Functie pentru autentificare
Angajat *autentificare(const std::vector<Angajat *> &angajati)
{
    std::string id, parola;
    std::cout << "Introduceti ID-ul angajatului: ";
    std::cin >> id;
    std::cout << "Introduceti parola angajatului: ";
    std::cin >> parola;

    for (auto *angajat : angajati)
    {
        if (angajat->getId() == id && angajat->verificaParola(parola))
        {
            return angajat;
        }
    }

    std::cerr << "ID sau parola incorecta. Incercati din nou.\n";
    return nullptr;
}

int main()
{
    try
    {
        // Citim produsele si preturile din CSV
        std::map<std::string, Produs> produse;
        citesteProduseDinCSV("data/Produse.csv", produse);

        // Citim angajatii din fisierul CSV
        std::vector<Angajat *> angajati;
        citesteAngajatiDinCSV("data/Angajati.csv", angajati);

        // Variabila pentru baza de date a clientilor
        std::map<std::string, std::tuple<std::string, int, int>> clienti;
        citesteClientiDinCSV("data/Clienti.csv", clienti);

        // Vector pentru comenzi si evenimente
        std::vector<Comanda> comenzi;
        std::vector<Eveniment> evenimente;

        // Citim ID-ul ultimului client din baza de date
        lastClientId = getLastClientId("data/Clienti.csv");

        // Ciclu principal
        bool ruleazaAplicatia = true;
        while (ruleazaAplicatia)
        {
            Angajat *utilizatorCurent = nullptr;

            // Autentificare
            while (!utilizatorCurent)
            {
                utilizatorCurent = autentificare(angajati);
                if (!utilizatorCurent)
                {
                    char optiune;
                    std::cout << "Doriti sa incercati din nou? (y/n): ";
                    std::cin >> optiune;
                    if (optiune == 'n' || optiune == 'N')
                    {
                        ruleazaAplicatia = false;
                        break;
                    }
                }
            }

            if (!ruleazaAplicatia)
            {
                break;
            }

            // Gestionare actiuni specifice rolului
            bool conectat = true;
            while (conectat)
            {
                std::cout << "\nBine ati venit, " << utilizatorCurent->getNume() << "!\n";
                std::cout << "Functie: " << utilizatorCurent->getFunctie() << "\n";

                if (dynamic_cast<Manager *>(utilizatorCurent))
                {
                    int optiune;
                    std::cout << "\nMeniu Manager:\n";
                    std::cout << "1. Adauga eveniment\n";
                    std::cout << "2. Sterge eveniment\n";
                    std::cout << "3. Adauga angajat\n";
                    std::cout << "4. Sterge angajat\n";
                    std::cout << "5. Genereaza raport\n";
                    std::cout << "6. Modifica stoc\n";
                    std::cout << "7. Vizualizeaza angajati\n";
                    std::cout << "8. Modifica angajat\n";
                    std::cout << "9. Deconectare\n";
                    std::cout << "0. Iesire din aplicatie\n";
                    std::cout << "Optiunea: ";
                    std::cin >> optiune;

                    switch (optiune)
                    {
                    case 1:
                        dynamic_cast<Manager *>(utilizatorCurent)->adaugaEveniment(evenimente);
                        break;
                    case 2:
                        dynamic_cast<Manager *>(utilizatorCurent)->stergeEveniment(evenimente);
                        break;
                    case 3:
                        dynamic_cast<Manager *>(utilizatorCurent)->adaugaAngajat(angajati);
                        break;
                    case 4:
                        dynamic_cast<Manager *>(utilizatorCurent)->stergeAngajat(angajati);
                        break;
                    case 5:
                        dynamic_cast<Manager *>(utilizatorCurent)->genereazaRaport(comenzi, evenimente, angajati);
                        break;
                    case 6:
                        dynamic_cast<Manager *>(utilizatorCurent)->modificaStoc(produse);
                        break;
                    case 7:
                        dynamic_cast<Manager *>(utilizatorCurent)->vizualizeazaAngajati(angajati);
                        break;

                    case 8:
                        dynamic_cast<Manager *>(utilizatorCurent)->modificaAngajat(angajati);
                        break;
                    case 9:
                        conectat = false;
                        break;

                    case 0:
                        conectat = false;
                        ruleazaAplicatia = false;
                        break;
                    default:
                        std::cerr << "Optiune invalida! Incercati din nou.\n";
                    }
                }

                else if (dynamic_cast<Ospatar *>(utilizatorCurent))
                {
                    Ospatar *ospatar = dynamic_cast<Ospatar *>(utilizatorCurent);
                    int optiune;
                    std::cout << "\nMeniu Ospatar:\n";
                    std::cout << "1. Adauga comanda\n";
                    std::cout << "2. Deconectare\n";
                    std::cout << "0. Iesire din aplicatie\n";
                    std::cout << "Optiunea: ";
                    std::cin >> optiune;

                    switch (optiune)
                    {
                    case 1:
                    {
                        std::string clientId;
                        std::cout << "Introduceti ID-ul clientului (sau 'nou' daca este client nou): ";
                        std::cin >> clientId;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (clientId == "nou")
                        {
                            std::string numeClient;
                            std::cout << "Introduceti numele clientului: ";
                            std::cin.ignore();
                            std::getline(std::cin, numeClient);

                            lastClientId++;
                            clientId = std::to_string(lastClientId);
                            clienti[clientId] = {numeClient, 0, 0};

                            std::cout << "Clientul nou a fost creat cu ID-ul: " << clientId << "\n";
                        }
                        else if (clienti.find(clientId) == clienti.end())
                        {
                            std::cerr << "ID-ul introdus nu exista. Verificati si incercati din nou.\n";
                            return 1;
                        }

                        // Actualizarea comenzilor si discounturilor
                        int reducere = std::get<2>(clienti[clientId]);
                        dynamic_cast<Ospatar *>(utilizatorCurent)->adaugaComanda(comenzi, produse, reducere);
                        std::get<1>(clienti[clientId])++;
                        if (std::get<1>(clienti[clientId]) >= 30)
                        {
                            std::get<2>(clienti[clientId]) = 20;
                        }
                        else if (std::get<1>(clienti[clientId]) >= 10)
                        {
                            std::get<2>(clienti[clientId]) = 10;
                        }

                        // Salveaza doar o data clientii actualizati
                        scrieClientiInCSV("data/Clienti.csv", clienti);

                        break;
                    }

                    case 2:
                        conectat = false;
                        break;
                    case 0:
                        conectat = false;
                        ruleazaAplicatia = false;
                        break;
                    default:
                        std::cout << "Optiune invalida! Incercati din nou.\n";
                    }
                }

                else if (dynamic_cast<Barista *>(utilizatorCurent))
                {
                    int optiune;
                    std::cout << "\nMeniu Barista:\n";
                    std::cout << "1. Vizualizare bauturi disponibile\n";
                    std::cout << "2. Deconectare\n";
                    std::cout << "0. Iesire din aplicatie\n";
                    std::cout << "Optiunea: ";
                    std::cin >> optiune;

                    switch (optiune)
                    {
                    case 1:
                        for (const auto &produs : produse)
                        {
                            std::cout << "Produs: " << produs.first << ", Pret: " << produs.second << " RON\n";
                        }
                        break;
                    case 2:
                        conectat = false;
                        break;
                    case 0:
                        conectat = false;
                        ruleazaAplicatia = false;
                        break;
                    default:
                        std::cout << "Optiune invalida! Incercati din nou.\n";
                    }
                }
            }
        }

        // Eliberare memorie
        for (auto *angajat : angajati)
        {
            delete angajat;
        }

        std::cout << "Aplicatia s-a inchis. La revedere!\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "A aparut o eroare: " << e.what() << "\n";
    }

    return 0;
}
