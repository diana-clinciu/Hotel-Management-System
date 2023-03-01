//
// Created by Diana on 2/26/2023.
//

#include "Apartament.h"

// Constructor fara parametrii
Apartament::Apartament() : CameraCuBucatarie(), Simpla(), Camera() {
    this->nrCamere = 0;
    this->nrObiecteSufragerie = 0;
    this->obiecteSufragerie = {};
}

// Constructor cu toti parametrii
Apartament::Apartament(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte, char *tipPat,
                       int nrObiecteBucararie, map<string, bool> obiecteBucatarie,
                       int nrAlimente, set <pair<string, tuple < int, int, int>>> alimente, int nrCamere,
                       int nrObiecteSufragerie, map<string, bool> obiecteSufragerie) :
                       CameraCuBucatarie(pret, etaj, ocupata, nrObiecte, obiecte,
                                         nrObiecteBucararie, obiecteBucatarie, nrAlimente, alimente),
                       Simpla(pret, etaj, ocupata, nrObiecte, obiecte, tipPat),
                       Camera(pret, etaj, ocupata, nrObiecte, obiecte){
    this->nrCamere = nrCamere;
    this->nrObiecteSufragerie = nrObiecteSufragerie;
    this->obiecteSufragerie = obiecteSufragerie;
}

// Copy Constructor
Apartament::Apartament(const Apartament &apartament) : CameraCuBucatarie(apartament), Simpla(apartament),
                                                       Camera(apartament) {
    this->nrCamere = apartament.nrCamere;
    this->nrObiecteSufragerie = apartament.nrObiecteSufragerie;
    this->obiecteSufragerie = apartament.obiecteSufragerie;
}

// Destructor
Apartament::~Apartament() {
    //optional
}

Apartament &Apartament::operator=(const Apartament &apartament) {
    if (this != &apartament) {
        Simpla::operator=(apartament);

        this->nrObiecteBucatarie = apartament.nrObiecteBucatarie;
        this->obiecteBucatarie = apartament.obiecteBucatarie;
        this->nrAlimente = apartament.nrAlimente;
        this->alimente = apartament.alimente;

        this->nrCamere = apartament.nrCamere;
        this->nrObiecteSufragerie = apartament.nrObiecteSufragerie;
        this->obiecteSufragerie = apartament.obiecteSufragerie;
    }

    return *this;
}

istream &Apartament::citire(istream &in) {
    bool curat;
    string obiect, aliment;
    int zi, luna, an;

    Simpla::citire(in);

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

    cout << "Numar de camere: ";
    in >> this->nrCamere;

    cout << "Numar obiecte sufragerie: ";
    in >> this->nrObiecteSufragerie;

    cout << "Obiecte sufragerie [ (nume_obiect, curatat [0(Nu)/1(Da)]) ]: ";
    this->obiecteSufragerie.clear();

    for (int i = 1; i <= this->nrObiecteSufragerie; i++) {
        in >> obiect >> curat;
        this->obiecteSufragerie[obiect] = curat;
    }

    return in;
}

ostream &Apartament::afisare(ostream &out) const {
    Simpla::afisare(out);

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

    out << "\tNumar camere: ";
    out << this->nrCamere << endl;

    out << "\tNumar obiecte sufragerie: ";
    out << this->nrObiecteSufragerie << endl;

    out << "\tObiecte sufragerie:" << endl;
    for (auto it = this->obiecteSufragerie.begin(); it != this->obiecteSufragerie.end(); it++) {
        out << "\t\t" << (*it).first << ": ";
        if ((*it).second)
            out << "curatat";
        else
            out << "necuratat";
        out << endl;
    }
    return out;
}

void Apartament::curataCamera() {
    CameraCuBucatarie::curataCamera();

    for (auto it = this->obiecteSufragerie.begin(); it != this->obiecteSufragerie.end(); it++) {
        (*it).second = true;
        cout << (*it).first << "... curat" << endl;
    }
}

void Apartament::murdaresteCamera() {
    CameraCuBucatarie::murdaresteCamera();

    for (auto it = this->obiecteSufragerie.begin(); it != this->obiecteSufragerie.end(); it++)
        (*it).second = false;
}