//
// Created by Diana on 2/26/2023.
//

#ifndef PROIECT_CAMERACUBUCATARIE_H
#define PROIECT_CAMERACUBUCATARIE_H

#include "Camera.h"
#include "set"

// Clasa CameraCuBucatarie <- parinte (mostenirea diamant)
class CameraCuBucatarie : virtual public Camera {
protected:
    int nrObiecteBucatarie;
    map<string, bool> obiecteBucatarie;
    int nrAlimente;
    set <pair<string, tuple < int, int, int>>>
    alimente; // #set
public:
    CameraCuBucatarie();

    CameraCuBucatarie(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte,
                      int nrObiecteBucararie, map<string, bool> obiecteBucatarie, int nrAlimente,
                      set <pair<string, tuple < int, int, int>>> alimente);

    CameraCuBucatarie(const CameraCuBucatarie &cameraCuBucatarie);

    virtual ~CameraCuBucatarie();

    istream &citire(istream &in);

    ostream &afisare(ostream &out) const;

    CameraCuBucatarie &operator=(const CameraCuBucatarie &cameraCuBucatarie);

    void aruncaAlimente(tuple<int, int, int> data);

    void curataCamera();

    void murdaresteCamera();
};


#endif //PROIECT_CAMERACUBUCATARIE_H
