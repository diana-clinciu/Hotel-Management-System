//
// Created by Diana on 2/26/2023.
//

#ifndef PROIECT_CAUTA_H
#define PROIECT_CAUTA_H

#include "Client.h"
#include "Cazare.h"
#include "Angajat.h"

// functie care cauta un client dupa id
list<Client *>::iterator cauta(int codClient, list<Client *> &client);

// functie care cauta o camera dupa numarul de camera
int cauta(int nrCamera, vector<Camera *> &camera);

// functie care cauta o cazare dupa codul de cazare
int cauta(int codCazare, vector<Cazare *> &cazare);

// functie care cauta un angajat dupa id
int cauta(int idAngajat, vector<Angajat *> &angajat);

// functie care cauta angajatii cu job-ul X
vector<Angajat *> cauta(vector<Angajat *> const &angajat, char *jobX);

#endif //PROIECT_CAUTA_H
