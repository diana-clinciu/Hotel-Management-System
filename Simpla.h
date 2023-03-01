//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_SIMPLA_H
#define PROIECT_SIMPLA_H

#include "Camera.h"

// Clasa Simpla <- parinte (mostenirea diamant)
class Simpla : virtual public Camera
{
protected:
    char* tipPat;
public:
    Simpla();
    Simpla(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte, char* tipPat);
    Simpla(const Simpla& simpla);
    virtual ~Simpla();

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Simpla& operator = (const Simpla& simpla);
};

#endif //PROIECT_SIMPLA_H
