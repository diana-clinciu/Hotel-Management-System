//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_CLIENT_H
#define PROIECT_CLIENT_H

#include "Persoana.h"

using namespace std;

// Clasa Client
class Client : public Persoana {
private:
    char *email, *telefon;
    int varsta;
    float *istoricCheltuieli;
    int nrCheltuieli;

public:
    Client();

    Client(char *nume, char *prenume, char initialaTata, int varsta, char *telefon, char *email,
           float *istoricCheltuieli, int nrCheltuieli);

    Client(char *nume, char *prenume, char initialaTata, char *telefon, char *email);

    Client(const Client &client);

    ~Client();

    istream &citire(istream &in);

    ostream &afisare(ostream &out) const;

    Client &operator=(const Client &persoana);

    float operator[](int index);

    const Client &operator++();        //pre-incremetare
    const Client operator++(int);    //post-incrementare
    bool operator==(const Client &client);

    bool operator<(const Client &client);

    Client operator+(float cheltuiala);

    friend Client operator+(float cheltuiala, Client client);

    Client operator+(Client &client);

    Client operator-(float cheltuiala);

    friend Client operator-(float cheltuiala, Client client);

    bool clientFidel();


    int getVarsta() const {
        return this->varsta;
    }

    int getNrCheltuieli() const {
        return this->nrCheltuieli;
    }

};

#endif //PROIECT_CLIENT_H
