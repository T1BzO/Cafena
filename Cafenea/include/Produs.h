#ifndef PRODUS_H
#define PRODUS_H

#include <string>

class Produs {
public:
    Produs(const std::string& nume, double pret, int cantitate);
    std::string getNume() const;
    double getPret() const;
    int getCantitate() const;
    void setPret(double pretNou);
    void adaugaStoc(int cantitate);
    bool scadeStoc(int cantitate);
    void setCantitate(int cantitate);
    void afiseazaProdus() const;
    Produs() : nume(""), pret(0.0), cantitate(0) {}
    friend std::ostream& operator<<(std::ostream& os, const Produs& produs);
    




private:
    std::string nume;
    double pret;
    int cantitate;
};

#endif
