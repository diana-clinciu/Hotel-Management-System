//
// Created by Diana on 2/26/2023.
//

#ifndef PROIECT_APARTAMENT_H
#define PROIECT_APARTAMENT_H

#include "Simpla.h"
#include "CameraCuBucatarie.h"

// Clasa Apartament <- Copil (mostenirea diamant)
class Apartament : public Simpla, public CameraCuBucatarie
{
private:
    int nrCamere, nrObiecteSufragerie;
    map<string, bool> obiecteSufragerie;
public:
    Apartament();
    Apartament(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte, char* tipPat, int nrObiecteBucararie, map<string, bool> obiecteBucatarie,
               int nrAlimente, set<pair<string, tuple<int,int,int>>> alimente,
    int nrCamere, int nrObiecteSufragerie, map<string, bool> obiecteSufragerie);
    Apartament(const Apartament& apartament);
    ~Apartament();

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Apartament& operator = (const Apartament& apartament);

    void curataCamera();
    void murdaresteCamera();
};


#endif //PROIECT_APARTAMENT_H
