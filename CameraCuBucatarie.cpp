//
// Created by Diana on 2/26/2023.
//

#include "CameraCuBucatarie.h"


// Constructor fara parametrii
CameraCuBucatarie::CameraCuBucatarie() : Camera() {
    this->nrObiecteBucatarie = 0;
    this->obiecteBucatarie = {};
    this->nrAlimente = 0;
    this->alimente = {};
}

// Constructor cu toti parametrii
CameraCuBucatarie::CameraCuBucatarie(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte,
                                     int nrObiecteBucararie, map<string, bool> obiecteBucatarie, int nrAlimente,
                                     set <pair<string, tuple < int, int, int>>> alimente) : Camera(pret, etaj, ocupata,
                                                                                                  nrObiecte, obiecte) {
    this->nrObiecteBucatarie = nrObiecteBucararie;
    this->obiecteBucatarie = obiecteBucatarie;
    this->nrAlimente = nrAlimente;
    this->alimente = alimente;
}

// Copy Constructor
CameraCuBucatarie::CameraCuBucatarie(const CameraCuBucatarie &cameraCuBucatarie) : Camera(cameraCuBucatarie) {
    this->nrObiecteBucatarie = cameraCuBucatarie.nrObiecteBucatarie;
    this->obiecteBucatarie = cameraCuBucatarie.obiecteBucatarie;
    this->nrAlimente = cameraCuBucatarie.nrAlimente;
    this->alimente = cameraCuBucatarie.alimente;
}

// Destructor
CameraCuBucatarie::~CameraCuBucatarie() {
    // optional
}

CameraCuBucatarie &CameraCuBucatarie::operator=(const CameraCuBucatarie &cameraCuBucatarie) {
    if (this != &cameraCuBucatarie) {
        Camera::operator=(cameraCuBucatarie);

        this->nrObiecteBucatarie = cameraCuBucatarie.nrObiecteBucatarie;
        this->obiecteBucatarie = cameraCuBucatarie.obiecteBucatarie;
        this->nrAlimente = cameraCuBucatarie.nrAlimente;
        this->alimente = cameraCuBucatarie.alimente;
    }

    return *this;
}

istream &CameraCuBucatarie::citire(istream &in) {
    bool curat;
    string obiect, aliment;
    int zi, luna, an;

    Camera::citire(in);

    cout << "Numar obiecte bucatarie: ";
    in >> this->nrObiecteBucatarie;

    cout << "Obiecte bucatarie [ (nume_obiect, curatat [0(Nu)/1(Da)]) ]: ";
    this->obiecteBucatarie.clear();

    for (int i = 1; i <= this->nrObiecteBucatarie; i++) {
        in >> obiect >> curat;
        this->obiecteBucatarie[obiect] = curat;
    }

    cout << "Numar alimente: ";
    in >> this->nrAlimente;

    cout << "Alimente + data expirare: ";
    this->alimente.clear();

    for (int i = 0; i < this->nrAlimente; i++) {
        in >> aliment >> zi >> luna >> an;
        this->alimente.insert(make_pair(aliment, make_tuple(zi, luna, an)));
    }

    return in;
}

ostream &CameraCuBucatarie::afisare(ostream &out) const {
    Camera::afisare(out);

    out << "\tNumar obiecte bucatarie: ";
    out << this->nrObiecteBucatarie << endl;

    out << "\tObiecte bucatarie:" << endl;
    for (auto it = this->obiecteBucatarie.begin(); it != this->obiecteBucatarie.end(); it++) {
        out << "\t\t" << (*it).first << ": ";
        if ((*it).second)
            out << "curatat";
        else
            out << "necuratat";
        out << endl;
    }

    out << "\tNumar alimente: ";
    out << this->nrAlimente << endl;

    out << "\tAlimente + data expirare: " << endl;

    for (auto it = this->alimente.begin(); it != this->alimente.end(); it++) {
        out << "\t\t" << (*it).first << ' ' << get<0>((*it).second) << '/' << get<1>((*it).second) << '/'
            << get<2>((*it).second) << endl;
    }

    return out;
}

void CameraCuBucatarie::aruncaAlimente(tuple<int, int, int> data) {
    auto it = this->alimente.begin();

    while (it != this->alimente.end()) {
        if ((*it).second == data) {
            it = this->alimente.erase(it);
            this->nrAlimente--;
        } else
            it++;
    }
}

void CameraCuBucatarie::curataCamera() {
    Camera::curataCamera();

    for (auto it = this->obiecteBucatarie.begin(); it != this->obiecteBucatarie.end(); it++) {
        (*it).second = true;
        cout << (*it).first << "... curat" << endl;
    }
}

void CameraCuBucatarie::murdaresteCamera() {
    Camera::murdaresteCamera();

    for (auto it = this->obiecteBucatarie.begin(); it != this->obiecteBucatarie.end(); it++)
        (*it).second = false;
}