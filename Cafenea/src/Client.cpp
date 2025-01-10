#include "Client.h"

Client::Client(const std::string& nume, const std::string& id)
    : nume(nume), id(id), numarComenzi(0) {}

std::string Client::getNume() const {
    return nume;
}

std::string Client::getId() const {
    return id;
}

void Client::incrementComenzi() {
    numarComenzi++;
}

double Client::calculeazaReducere() const {
    if (numarComenzi >= 30) {
        return 0.2; // 20% reducere
    } else if (numarComenzi >= 10) {
        return 0.1; // 10% reducere
    }
    return 0.0; // Fara reducere
}
