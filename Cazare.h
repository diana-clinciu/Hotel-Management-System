//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_CAZARE_H
#define PROIECT_CAZARE_H

#include "tuple"
#include "Camera.h"
#include "Vector.h"
#include "Client.h"
#include "vector"
#include "list"

// clasa Cazare
class Cazare {
private:
    char *numeClient, *prenumeClient;
    float cost;
    tuple<int, int, int> dataCheckIn, dataCheckOut;
    Vector<Camera *> camereCazare;
    int nrCamere;
    static int contorCazare;
    const int codCazare;
public:
    Cazare();

    Cazare(char *numeClient, char *prenumeClient, tuple<int, int, int> dataCheckIn, tuple<int, int, int> dataCheckOut);

    Cazare(char *numeClient, char *prenumeClient);

    Cazare(char *numeClient, char *prenumeClient, float cost, tuple<int, int, int> dataCheckIn,
           tuple<int, int, int> dataCheckOut, int nrCamere, Vector<Camera *> camereCazare);

    Cazare(const Cazare &cazare);

    ~Cazare();

    Cazare &operator=(const Cazare &cazare);

    friend ostream &operator<<(ostream &out, const Cazare &cazare);


    friend Cazare operator+(Cazare cazare, Camera &camera);

    friend Cazare operator+(Camera &camera, Cazare cazare);

    Camera *operator[](int index);

    const Cazare &operator++();        //pre-incremetare
    const Cazare operator++(int);    //post-incrementare
    bool operator==(const Cazare &cazare);

    bool operator<(const Cazare &cazare);

    Cazare operator+(float scumpire);

    friend Cazare operator+(float scumpire, Cazare cazare);

    Cazare operator-(float reducere);

    friend Cazare operator-(float reducere, Cazare cazare);

    explicit operator int() {
        return (int) this->cost;
    }

    const int getCodCazare() const {
        return this->codCazare;
    }

    void setCost(float cost) {
        this->cost = cost;
    }

    float getCost() const {
        return this->cost;
    }

    int getNrCamere() const {
        return this->nrCamere;
    }

    int checkIn(list<Client *> &client, vector<Camera *> &camera);

    friend int checkOut(vector<Camera *> &camera, vector<Cazare *> &cazare);
};



#endif //PROIECT_CAZARE_H
