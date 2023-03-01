//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_CAMERA_H
#define PROIECT_CAMERA_H

#include "iostream"
#include "IOInterface.h"
#include "map"

// Clasa Camara <- Bunic (mostenire diamant)
class Camera : public IOInterface
{
protected:
    float pret;
    int etaj;
    bool ocupata;
    int nrObiecte;
    // map de perechi de tipul (nume obiect, curat(0/1))
    map<string, bool> obiecte; // #map
    static int contorCamera;
    const int nrCamera;

public:
    Camera();
    Camera(float pret, int etaj, bool ocupata, int nrObiecte, map<string, bool> obiecte);
    Camera(const Camera& camera);
    virtual ~Camera();

    istream& citire(istream& is);
    ostream& afisare(ostream& os) const;

    Camera& operator = (const Camera& camera);
    friend ostream& operator << (ostream& out, const Camera& camera);
    friend istream& operator >> (istream& in, Camera& camera);

    bool operator==(const Camera& camera);
    bool operator<(const Camera& camera);
    Camera operator+(float pret);
    friend Camera operator+(float pret, Camera camera);
    Camera operator-(float pret);
    friend Camera operator-(float pret, Camera camera);

    // exemplu de virtualizare + reutilizare de cod in derivate
    virtual void curataCamera();
    virtual void murdaresteCamera();

    bool getOcupata() const
    {
        return this->ocupata;
    }

    void setOcupata(bool status)
    {
        this->ocupata = status;
    }

    float getPret() const
    {
        return this->pret;
    }

    const int getNrCamera() const
    {
        return this->nrCamera;
    }
};


#endif //PROIECT_CAMERA_H
