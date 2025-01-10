#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(const std::string& nume, const std::string& id);

    std::string getNume() const;
    std::string getId() const;
    void incrementComenzi();
    double calculeazaReducere() const;

private:
    std::string nume;
    std::string id;
    int numarComenzi;
};

#endif
