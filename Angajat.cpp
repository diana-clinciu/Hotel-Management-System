//
// Created by Diana on 2/25/2023.
//

#include <fstream>
#include "Angajat.h"
#include "cstring"
#include"iostream"


Angajat &Angajat::operator=(const Angajat &angajat) {
    if (this != &angajat) {
        if (this->job != NULL)
            delete[] this->job;

        Persoana::operator=(angajat);

        this->job = new char[strlen(angajat.job) + 1];
        strcpy(this->job, angajat.job);

        this->salariu = angajat.salariu;

        this->dataAngajarii = angajat.dataAngajarii;

        this->zileLucrate = angajat.zileLucrate;

        this->nrMariri = angajat.nrMariri;

        this->istoricMariri = angajat.istoricMariri;
    }

    return *this;
}

istream &Angajat::citire(istream &in) {
    double x;
    int zi, luna, an;

    Persoana::citire(in);

    cout << "Job: ";
    in >> this->job;

    cout << "Salariu: ";
    in >> this->salariu;

    cout << "Data angajarii: ";
    in >> zi >> luna >> an;
    this->dataAngajarii = make_tuple(zi, luna, an);

    cout << "Numar de zile lucrate: ";
    in >> this->zileLucrate;

    cout << "Numar de mariri acordate: ";
    in >> this->nrMariri;

    cout << "Mariri: ";
    this->istoricMariri.clear();
    for (int i = 0; i < this->nrMariri; i++) {
        in >> x;
        this->istoricMariri.push_back(x);
    }

    return in;
}


ifstream &Angajat::citireFisier(ifstream &fin) {
    double x;
    int zi, luna, an;

    fin >> this->nume;

    fin >> this->prenume;

    fin >> this->initialaTata;

    //cout << "Job: ";
    fin >> this->job;

    //cout << "Salariu: ";
    fin >> this->salariu;

    //cout << "Data angajarii: ";
    fin >> zi >> luna >> an;
    this->dataAngajarii = make_tuple(zi, luna, an);

    //cout << "Numar de zile lucrate: ";
    fin >> this->zileLucrate;

    //cout << "Numar de mariri acordate: ";
    fin >> this->nrMariri;

    //cout << "Mariri: ";
    this->istoricMariri.clear();
    for (int i = 0; i < this->nrMariri; i++) {
        fin >> x;
        this->istoricMariri.push_back(x);
    }

    return fin;
}

ofstream &Angajat::afisareFisier(ofstream &fout) {
    fout << "Nume: " << this->nume << endl;

    fout << "Prenume: " << this->prenume << endl;

    fout << "Initiala tata: " << this->initialaTata << endl;

    fout << "Job: " << this->job << endl;

    fout << "Salariu: " << this->salariu << endl;

    fout << "Data angajarii: " << get<0>(this->dataAngajarii) << "/" << get<1>(this->dataAngajarii) << "/"
         << get<2>(this->dataAngajarii) << endl;

    fout << "Numar de zile lucrate: " << this->zileLucrate << endl;

    fout << "Numar de mariri acodate: " << this->nrMariri << endl;

    fout << "Mariri: ";
    for (int i = 0; i < this->nrMariri; i++)
        fout << this->istoricMariri[i] << ' ';

    return fout;
}

ostream &Angajat::afisare(ostream &out) const {

    Persoana::afisare(out);

    out << "Job: " << this->job << endl;

    out << "Salariu: " << this->salariu << endl;

    out << "Data angajarii: " << get<0>(this->dataAngajarii) << "/" << get<1>(this->dataAngajarii) << "/"
        << get<2>(this->dataAngajarii) << endl;

    out << "Numar de zile lucrate: " << this->zileLucrate << endl;

    out << "Numar de mariri acodate: " << this->nrMariri << endl;

    out << "Mariri: ";
    for (int i = 0; i < this->nrMariri; i++)
        out << this->istoricMariri[i] << ' ';

    return out;
}

// returneaza a i-a marire a unui angajat
double Angajat::operator[](int index) {
    if (0 <= index && index < this->nrMariri)
        return this->istoricMariri[index];
    cout << "Index introdus gresit! ";
    return -1;
}

// incrementeaza numarul de zile lucrate cu 1
const Angajat &Angajat::operator++() {
    this->zileLucrate++;
    return *this;
}

// incrementeaza numarul de zile lucrate cu 1
const Angajat Angajat::operator++(int) {
    Angajat aux(*this);
    this->zileLucrate++;
    return aux;
}

// doi angajati sunt egali daca au acelasi job
bool Angajat::operator==(const Angajat &angajat) {
    if (strcmp(this->job, angajat.job) == 0)
        return true;
    return false;
}

// compara angajatii dupa numarul de zile lucrate (vechime)
bool Angajat::operator<(const Angajat &angajat) {
    if (this->zileLucrate < angajat.zileLucrate)
        return true;
    return false;
}

// scade din numarul de zile lucrate ale unui angajat numarul dat ca parametru
Angajat Angajat::operator-(int nrZile) {
    Angajat aux(*this);
    aux.zileLucrate = aux.zileLucrate - nrZile;
    return aux;
}

// scade din numarul dat ca parametru numarul de zile lucrate ale unui angajat
Angajat operator-(int nrZile, Angajat angajat) {
    angajat.zileLucrate = nrZile - angajat.zileLucrate;
    return angajat;
}

// aduna numarul de zile lucrate a doi angajati si returneaza un angajat nou
Angajat Angajat::operator+(Angajat angajat) {
    angajat.zileLucrate = angajat.zileLucrate + this->zileLucrate;
    return angajat;
}

Angajat &Angajat::operator+=(double marire) {
    this->nrMariri++;
    this->istoricMariri.push_back(marire);
    return *this;
}

// functie care acorda o marire unui angajat
// daca parametrul default primeste o valoare, atunci se acorda o marire de spor%
// altfel se acorda o marire calculata astfel:
// fie max = cea mai mare marire de pana acum
// daca max > 2000 se acorda o marire de 5% (stiu, sunt darnica azi :))) )
// daca  1000 <= max <= 2000 se acorda o marire de 30%
// daca max < 1000 se acorda o marire de 50%
void Angajat::acordaMarire(double spor /** = -1 **/) {
    double maxMarire = -1, marire = 0;
    if (spor == -1) {
        for (int i = 0; i < this->istoricMariri.size(); i++)
            if (this->istoricMariri[i] > maxMarire)
                maxMarire = this->istoricMariri[i];
        if (maxMarire > 2000)
            marire = this->salariu * 0.05;
        if (1000 <= maxMarire && maxMarire <= 2000)
            marire = this->salariu * 0.3;
        if (maxMarire < 1000)
            marire = this->salariu * 0.5;
    } else
        marire = this->salariu * spor / 100;

    this->salariu = this->salariu + marire;

    (*this) += marire;

    cout << "Marire acordata cu succes! Marire: " << marire << " lei." << endl;
}

// Constructor fara parametrii
Angajat::Angajat() : Persoana() {
    this->job = new char[strlen("Necunoscut") + 1];
    strcpy(this->job, "Necunoscut");

    this->salariu = 0;

    this->dataAngajarii = make_tuple(0, 0, 0);

    this->zileLucrate = 0;

    this->nrMariri = 0;

    this->istoricMariri = vector<double>();
}

// Constructor cu toti parametrii
Angajat::Angajat(char *nume, char *prenume, char *job, char initialaTata, double salariu,
                 tuple<int, int, int> dataAngajarii, int zileLucrate, int nrMariri, vector<double> istoricMariri)
        : Persoana(nume, prenume, initialaTata) {
    this->job = new char[strlen(job) + 1];
    strcpy(this->job, job);

    this->salariu = salariu;

    this->dataAngajarii = dataAngajarii;

    this->zileLucrate = zileLucrate;

    this->nrMariri = nrMariri;

    this->istoricMariri = istoricMariri;
}

// Constructor cu mai multi parametrii
Angajat::Angajat(char *job) {
    this->job = new char[strlen(job) + 1];
    strcpy(this->job, job);
}

// Copy Constructor
Angajat::Angajat(const Angajat &angajat) : Persoana(angajat) {
    this->job = new char[strlen(angajat.job) + 1];
    strcpy(this->job, angajat.job);

    this->salariu = angajat.salariu;

    this->dataAngajarii = angajat.dataAngajarii;

    this->zileLucrate = angajat.zileLucrate;

    this->nrMariri = angajat.nrMariri;

    this->istoricMariri = angajat.istoricMariri;
}

// Destructor
Angajat::~Angajat() {
    if (this->job != NULL)
        delete[] this->job;
}
