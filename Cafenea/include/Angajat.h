#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <vector>
#include <map>
#include "Produs.h"
#include "Comanda.h"
#include "Eveniment.h"

// Clasa de baza
class Angajat {
public:
    Angajat(const std::string& nume, const std::string& functie, double tarifPeOra, const std::string& id, const std::string& parola);
    virtual ~Angajat() = default;

    std::string getNume() const;
    std::string getFunctie() const;
    std::string getOras() const;
    std::string getParola() const;
    void setOras(const std::string& orasNou);
    int getOraInceput() const;
    int getOraSfarsit() const;
    double getTarifPeOra() const;
    void setProgram(int inceput, int sfarsit);
    void setTarifPeOra(double tarif);
    double calculeazaSalariuZilnic() const;


    virtual void actiuni(const std::map<std::string, double>& produse) = 0;

    std::string getId() const;
    bool verificaParola(const std::string& parola) const;

protected:
    std::string nume;
    std::string functie;

private:
    std::string idAngajat;
    std::string parolaAngajat;
    std::string oras;
    int oraInceput;
    int oraSfarsit;
    double tarifPeOra;
};

// Clasa Moderator
// Clasa Manager
class Manager : public Angajat {
public:
    Manager(const std::string& nume, double salariu, const std::string& id, const std::string& parola);

    void actiuni(const std::map<std::string, double>& produse) override;
    void adaugaEveniment(std::vector<Eveniment>& evenimente);
    void stergeEveniment(std::vector<Eveniment>& evenimente);
    void adaugaAngajat(std::vector<Angajat*>& angajati);
    void stergeAngajat(std::vector<Angajat*>& angajati);
    void genereazaRaport(std::vector<Comanda>& comenzi, const std::vector<Eveniment>& evenimente, const std::vector<Angajat*>& angajati) const;
    void modificaStoc(std::map<std::string, Produs>& produse);
    void modificaAngajat(std::vector<Angajat*>& angajati);

    void vizualizeazaAngajati(const std::vector<Angajat*>& angajati) const;
};


// Clasa Ospatar
class Ospatar : public Angajat {
public:
    Ospatar(const std::string& nume, double salariu, const std::string& id, const std::string& parola);
    void actiuni(const std::map<std::string, double>& produse) override;
    void adaugaComanda(std::vector<Comanda>& comenzi, std::map<std::string, Produs>& produse, int reducere); // Reducerea este acum un parametru
};


// Clasa Barista
class Barista : public Angajat {
public:
    Barista(const std::string& nume, double tarifPeOra, const std::string& id, const std::string& parola);
    void actiuni(const std::map<std::string, double>& produse) override;
   
    
};

#endif
