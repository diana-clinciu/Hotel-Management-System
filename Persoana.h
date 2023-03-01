//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_PERSOANA_H
#define PROIECT_PERSOANA_H

#include "iostream"
#include "IOInterface.h"

// Clasa Persoana (baza pt Client si Angajat)
class Persoana : public IOInterface
{
protected:
    char* nume, * prenume, initialaTata;
    const int idPersoana;
    static int contorPersoana;
public:
    Persoana();
    Persoana(const Persoana& persoana);
    Persoana(char* nume, char* prenume, char intialaTata);
    virtual ~Persoana() = 0;


    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Persoana& operator = (const Persoana& persoana);
    friend istream& operator >> (istream& in, Persoana& persoana);
    friend ostream& operator << (ostream& out, const Persoana& persoana);

    const int getIdPersoana() const
    {
        return this->idPersoana;
    }
};



#endif //PROIECT_PERSOANA_H
