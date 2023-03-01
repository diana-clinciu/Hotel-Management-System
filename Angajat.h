//
// Created by Diana on 2/25/2023.
//
#include "Persoana.h"
#include "vector"
#include "tuple"

using namespace std;

#ifndef PROIECT_ANGAJAT_H
#define PROIECT_ANGAJAT_H


// Clasa Angajat
class Angajat : public Persoana {
private:
    char *job;
    double salariu;
    tuple<int, int, int> dataAngajarii;
    int zileLucrate;
    int nrMariri;
    vector<double> istoricMariri;

public:
    Angajat();

    Angajat(char *nume, char *prenume, char *job, char initialaTata, double salariu, tuple<int, int, int> dataAngajarii,
            int zileLucrate, int nrMariri, vector<double> istoricMariri);

    Angajat(char *job);

    Angajat(const Angajat &angajat);

    ~Angajat();

    ifstream &citireFisier(ifstream &fin);
    ofstream &afisareFisier(ofstream &fout);

    istream &citire(istream &in);

    ostream &afisare(ostream &out) const;

    Angajat &operator=(const Angajat &angajat);

    double operator[](int index);

    const Angajat &operator++();        //pre-incremetare
    const Angajat operator++(int);        //post-incrementare
    bool operator==(const Angajat &angajat);

    bool operator<(const Angajat &angajat);

    Angajat operator+(Angajat angajat);

    Angajat &operator+=(double marire);

    Angajat operator-(int nrZile);

    friend Angajat operator-(int nrZile, Angajat angajat);

    explicit operator int() {
        return (int) this->salariu;
    }

    void acordaMarire(double spor = -1);

    double getSalariu() const {
        return this->salariu;
    }

    int getZileLucrate() const {
        return this->zileLucrate;
    }

    int getNrMariri() const {
        return this->nrMariri;
    }
};


#endif //PROIECT_ANGAJAT_H
