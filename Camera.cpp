//
// Created by Diana on 2/25/2023.
//

#include "Camera.h"


int Camera::contorCamera = 0;

Camera &Camera::operator=(const Camera &camera) {
    if (this != &camera) {

        this->pret = camera.pret;

        this->etaj = camera.etaj;

        this->ocupata = camera.ocupata;

        this->nrObiecte = camera.nrObiecte;

        this->obiecte = camera.obiecte;

    }

    return *this;
}

istream &Camera::citire(istream &in) {
    string obiect;
    bool curat;
    int maybeBool;

    cout << "Pret: ";
    in >> this->pret;

    cout << "Etaj: ";
    in >> this->etaj;

    cout << "Ocupata [0(Nu)/1(Da)]: ";
    try {
        in >> maybeBool;
        if (maybeBool > 1 || maybeBool < 0)
            throw runtime_error("Input-ul nu este 0 sau 1\n"); // #exceptie runtime
        this->ocupata = maybeBool;
    }
    catch (runtime_error e) {
        cout << "Runtime error: " << e.what();
        this->ocupata = true;
    }
    cout << "Numar de obiecte: ";
    in >> this->nrObiecte;

    cout << "Obiecte [ (nume_obiect, curatat [0(Nu)/1(Da)]) ]: ";
    this->obiecte.clear();
    for (int i = 0; i < this->nrObiecte; i++) {
        in >> obiect >> curat;
        this->obiecte[obiect] = curat;
    }
    return in;
}

istream &operator>>(istream &in, Camera &camera) {
    return camera.citire(in);
}

ostream &Camera::afisare(ostream &out) const {
    out << "\tNumar: " << this->nrCamera << endl;

    out << "\tPret: " << this->pret << endl;

    out << "\tEtaj: " << this->etaj << endl;

    out << "\tOcupata: ";
    if (this->getOcupata())
        out << "Da";
    else
        out << "Nu";
    out << endl;

    out << "\tNumar de obiecte: " << this->nrObiecte << endl;

    out << "\tObiecte:" << endl;
    for (auto it = this->obiecte.begin(); it != this->obiecte.end(); it++) {
        out << "\t\t" << (*it).first << ": ";
        if ((*it).second)
            out << "curatat";
        else
            out << "necuratat";
        out << endl;
    }
    return out;
}

ostream &operator<<(ostream &out, const Camera &camera) {
    return camera.afisare(out);
}

// doua camere sunt egale daca au acelasi numar de camera
bool Camera::operator==(const Camera &camera) {
    if (this->nrCamera == camera.nrCamera)
        return true;
    return false;
}

// compara camerele dupa pret
bool Camera::operator<(const Camera &camera) {
    if (this->pret < camera.pret)
        return true;
    return false;
}

// creste pretul camerei cu pretul dat ca parametru
Camera Camera::operator+(float pret) {
    Camera aux(*this);
    aux.pret += pret;
    return aux;
}

// creste pretul camerei cu pretul dat ca parametru
Camera operator+(float pret, Camera camera) {
    camera.pret += pret;
    return camera;
}

// scade pretul camerei cu pretul dat ca parametru
Camera Camera::operator-(float pret) {
    Camera aux(*this);
    aux.pret -= pret;
    return aux;
}

// scade pretul camerei cu pretul dat ca parametru
Camera operator-(float pret, Camera camera) {
    camera.pret -= pret;
    return camera;
}

// seteaza toate obiectele din camera ca "curate"
// afiseaza si un mesaj corespunzator
void Camera::curataCamera() {
    cout << "Curatare camera in desfasurare..." << endl;
    for (auto it = this->obiecte.begin(); it != this->obiecte.end(); it++) {
        (*it).second = true;
        cout << (*it).first << "... curat" << endl;
    }
}

// seteaza toate obiectele ca "murdare"
void Camera::murdaresteCamera() {
    for (auto it = this->obiecte.begin(); it != this->obiecte.end(); it++)
        (*it).second = false;
}

// Constructor fara parametrii
Camera::Camera() : nrCamera(contorCamera++) {
    this->pret = 0;

    this->etaj = 0;

    this->ocupata = 0;

    this->nrObiecte = 0;

    this->obiecte = {};
}

// Constructor cu toti parametrii
Camera::Camera(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte) : nrCamera(
        contorCamera++) {
    this->pret = pret;

    this->etaj = etaj;

    this->ocupata = ocupata;

    this->nrObiecte = nrObiecte;

    this->obiecte = obiecte;
}

// Copy Construcor
Camera::Camera(const Camera &camera) : nrCamera(contorCamera++) {
    this->pret = camera.pret;

    this->etaj = camera.etaj;

    this->ocupata = camera.ocupata;

    this->nrObiecte = camera.nrObiecte;

    this->obiecte = camera.obiecte;
}

// Destructor
Camera::~Camera() {
    // sa fie
}
