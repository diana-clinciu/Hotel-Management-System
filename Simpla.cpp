//
// Created by Diana on 2/25/2023.
//

#include "Simpla.h"
#include "cstring"

// Constructor fara parametrii
Simpla::Simpla() : Camera() {
    this->tipPat = new char[strlen("Necunoscut") + 1];
    strcpy(this->tipPat, "Necunoscut");
}

// Constructor cu toti parametrii
Simpla::Simpla(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte, char *tipPat) : Camera(
        pret, etaj, ocupata, nrObiecte, obiecte) {
    this->tipPat = new char[strlen(tipPat) + 1];
    strcpy(this->tipPat, tipPat);
}

// Copy Constructor
Simpla::Simpla(const Simpla &simpla) : Camera(simpla) {
    this->tipPat = new char[strlen(simpla.tipPat) + 1];
    strcpy(this->tipPat, simpla.tipPat);
}

// Destructor
Simpla::~Simpla() {
    if (this->tipPat != NULL)
        delete[] this->tipPat;
}

Simpla &Simpla::operator=(const Simpla &simpla) {
    if (this != &simpla) {
        Camera::operator=(simpla);

        if (this->tipPat != NULL)
            delete[] this->tipPat;

        this->tipPat = new char[strlen(simpla.tipPat) + 1];
        strcpy(this->tipPat, simpla.tipPat);
    }

    return *this;
}

istream &Simpla::citire(istream &in) {
    char aux[1000];

    Camera::citire(in);

    cout << "Tip de pat: ";
    in >> aux;

    if (this->tipPat != NULL)
        delete[] this->tipPat;

    this->tipPat = new char[strlen(aux) + 1];
    strcpy(this->tipPat, aux);

    return in;
}

ostream &Simpla::afisare(ostream &out) const {
    Camera::afisare(out);

    out << "\tTip de pat: " << this->tipPat << endl;

    return out;
}