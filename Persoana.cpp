//
// Created by Diana on 2/25/2023.
//

#include "Persoana.h"
#include "cstring"
#include "iostream"


int Persoana::contorPersoana = 0;

istream &Persoana::citire(istream &in) {
    char aux[1000];

    cout << "Nume: ";
    in >> aux;
    if (this->nume != NULL)
        delete[] this->nume;
    this->nume = new char[strlen(aux) + 1];
    strcpy(this->nume, aux);

    cout << "Prenume: ";
    in >> aux;
    if (this->prenume != NULL)
        delete[] this->prenume;
    this->prenume = new char[strlen(aux) + 1];
    strcpy(this->prenume, aux);

    cout << "Initiala tata: ";
    in >> this->initialaTata;

    return in;
}

ostream &Persoana::afisare(ostream &out) const {
    out << "Id: " << this->idPersoana << endl;

    out << "Nume: " << this->nume << endl;

    out << "Prenume: " << this->prenume << endl;

    out << "Initiala tata: " << this->initialaTata << endl;

    return out;
}

Persoana &Persoana::operator=(const Persoana &persoana) {
    if (this != &persoana) {
        if (this->nume != NULL)
            delete[] this->nume;
        if (this->prenume != NULL)
            delete[] this->prenume;

        this->nume = new char[strlen(persoana.nume) + 1];
        strcpy(this->nume, persoana.nume);

        this->prenume = new char[strlen(persoana.prenume) + 1];
        strcpy(this->prenume, persoana.prenume);

        this->initialaTata = persoana.initialaTata;
    }

    return *this;
}

istream &operator>>(istream &in, Persoana &persoana) {
    return persoana.citire(in);
}

ostream &operator<<(ostream &out, const Persoana &persoana) {
    return persoana.afisare(out);
}

// Constructor fara parametrii
Persoana::Persoana() : idPersoana(contorPersoana++) {
    this->nume = new char[strlen("Necunoscut") + 1];
    strcpy(this->nume, "Necunoscut");

    this->prenume = new char[strlen("Necunoscut") + 1];
    strcpy(this->prenume, "Necunoscut");

    this->initialaTata = 'A';
}

// Copy Constructor
Persoana::Persoana(const Persoana &persoana) : idPersoana(contorPersoana++) {
    this->nume = new char[strlen(persoana.nume) + 1];
    strcpy(this->nume, persoana.nume);

    this->prenume = new char[strlen(persoana.prenume) + 1];
    strcpy(this->prenume, persoana.prenume);

    this->initialaTata = persoana.initialaTata;
}

// Constructor cu toti parametii
Persoana::Persoana(char *nume, char *prenume, char initialaTata) : idPersoana(contorPersoana++) {
    this->nume = new char[strlen(nume) + 1];
    strcpy(this->nume, nume);

    this->prenume = new char[strlen(prenume) + 1];
    strcpy(this->prenume, prenume);

    this->initialaTata = initialaTata;
}

// Destructor
Persoana::~Persoana() {
    if (this->nume)
        delete[] this->nume;
    if (this->prenume)
        delete[] this->prenume;
}
