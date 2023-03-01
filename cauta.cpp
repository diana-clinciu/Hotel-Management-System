//
// Created by Diana on 2/26/2023.
//


#include "Client.h"
#include "Cazare.h"
#include "Angajat.h"

// functie care cauta un client dupa id
list<Client *>::iterator cauta(int codClient, list<Client *> &client) {
    for (auto it = client.begin(); it != client.end(); it++) {
        if ((*it)->getIdPersoana() == codClient)
            return it;
    }
    return client.end();
}

// functie care cauta o camera dupa numarul de camera
int cauta(int nrCamera, vector<Camera *> &camera) {
    for (int i = 0; i < camera.size(); i++) {
        if (camera[i]->getNrCamera() == nrCamera)
            return i;
    }
    return -1;
}

// functie care cauta o cazare dupa codul de cazare
int cauta(int codCazare, vector<Cazare *> &cazare) {
    for (int i = 0; i < cazare.size(); i++) {
        if (cazare[i]->getCodCazare() == codCazare)
            return i;
    }
    return -1;
}

// functie care cauta un angajat dupa id
int cauta(int idAngajat, vector<Angajat *> &angajat) {
    for (int i = 0; i < angajat.size(); i++) {
        if (angajat[i]->getIdPersoana() == idAngajat)
            return i;
    }
    return -1;
}

// functie care cauta angajatii cu job-ul X
vector<Angajat *> cauta(vector<Angajat *> const &angajat, char *jobX) {
    vector<Angajat *> angajatiCuJobX;
    Angajat angajatCuJobX(jobX);

    for (int i = 0; i < angajat.size(); i++)
        if (angajatCuJobX == *(angajat[i]))
            angajatiCuJobX.push_back(angajat[i]);

    return angajatiCuJobX;
}