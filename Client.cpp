//
// Created by Diana on 2/25/2023.
//

#include "Client.h"
#include "iostream"
#include "cstring"

using namespace std;

// functie pentru a vedea daca un client este "fidel"
// daca media cheltuielilor este mai mare ca 1000 si ultimele 5 chelutuieli sunt mai mari decat 200,
// clientul este considerat fidel, deci beneficiaza de o reducere de 20% la cazare
bool Client::clientFidel() {
    float suma = 0;

    if (this->nrCheltuieli == 0 || this->istoricCheltuieli == NULL || this->nrCheltuieli < 5)
        return false;

    for (int i = 0; i < this->nrCheltuieli; i++) {
        suma += this->istoricCheltuieli[i];
        if (i >= this->nrCheltuieli - 5 && this->istoricCheltuieli[i] < 200)
            return false;
    }
    if (suma / this->nrCheltuieli < 1000)
        return false;
    return true;
}

istream &Client::citire(istream &in) {
    char aux[1000];

    Persoana::citire(in);

    cout << "Varsta: ";
    in >> this->varsta;

    cout << "Telefon: ";
    in >> aux;
    if (this->telefon != NULL)
        delete[] this->telefon;
    this->telefon = new char[strlen(aux) + 1];
    strcpy(this->telefon, aux);

    cout << "Email: ";
    in >> aux;
    if (this->email != NULL)
        delete[] this->email;
    this->email = new char[strlen(aux) + 1];
    strcpy(this->email, aux);

    cout << "Numar de cheltuieli pana in momentul actual: ";
    in >> this->nrCheltuieli;

    cout << "Cheltuielile: ";
    if (this->istoricCheltuieli != NULL)
        delete[] this->istoricCheltuieli;
    this->istoricCheltuieli = new float[this->nrCheltuieli];
    for (int i = 0; i < this->nrCheltuieli; i++)
        in >> this->istoricCheltuieli[i];
    return in;

}

ostream &Client::afisare(ostream &out) const {
    Persoana::afisare(out);

    out << "Varsta: " << this->varsta << endl;

    out << "Telefon: " << this->telefon << endl;

    out << "Email: " << this->email << endl;

    out << "Numar de cheltuieli pana in momentul actual: " << this->nrCheltuieli << endl;

    out << "Cheltuielile: ";
    for (int i = 0; i < this->nrCheltuieli; i++)
        out << this->istoricCheltuieli[i] << ' ';
    return out;

}

Client &Client::operator=(const Client &client) {
    if (this != &client) {
        if (this->telefon != NULL)
            delete[] this->telefon;

        if (this->email != NULL)
            delete[] this->email;

        if (this->istoricCheltuieli != NULL)
            delete[] this->istoricCheltuieli;

        Persoana::operator=(client);

        this->varsta = client.varsta;

        this->telefon = new char[strlen(client.telefon) + 1];
        strcpy(this->telefon, client.telefon);

        this->email = new char[strlen(client.email) + 1];
        strcpy(this->email, client.email);

        this->istoricCheltuieli = new float[client.nrCheltuieli];
        for (int i = 0; i < client.nrCheltuieli; i++)
            this->istoricCheltuieli[i] = client.istoricCheltuieli[i];

        this->nrCheltuieli = client.nrCheltuieli;
    }

    return *this;
}


// returneaza a i-a cheltuiala a clientului
float Client::operator[](int index) {
    if (0 <= index && index < this->nrCheltuieli)
        return this->istoricCheltuieli[index];
    cout << "Index introdus gresit!" << endl;
    return -1;
}

// incrementeaza varsta clientului
const Client &Client::operator++() {
    this->varsta++;
    return *this;
}

// incrementeaza varsta clientului
const Client Client::operator++(int) {
    Client aux(*this);
    this->varsta++;
    return aux;
}

// returneaza true daca clientii au acelasi nume, prenume, telefon si email
// cu ea putem descoperii duplicatele clientilor
bool Client::operator==(const Client &client) {
    if (strcmp(this->nume, client.nume) != 0)
        return false;
    if (strcmp(this->prenume, client.prenume) != 0)
        return false;
    if (strcmp(this->telefon, client.telefon) != 0)
        return false;
    if (strcmp(this->email, client.email) != 0)
        return false;
    if (this->initialaTata != client.initialaTata)
        return false;

    return true;
}

// compara doi clienti dupa suma totala cheltuita in hotel
bool Client::operator<(const Client &client) {
    float s1 = 0, s2 = 0;
    for (int i = 0; i < this->nrCheltuieli; i++)
        s1 += this->istoricCheltuieli[i];
    for (int i = 0; i < client.nrCheltuieli; i++)
        s2 += client.istoricCheltuieli[i];
    if (s1 < s2)
        return true;
    return false;
}

// adauga cheltuiala data ca parametru la istoricul de cheltuieli al clientului
Client Client::operator+(float cheltuiala) {
    Client aux(*this);
    float auxCheltuieli[1000];
    for (int i = 0; i < aux.nrCheltuieli; i++)
        auxCheltuieli[i] = aux.istoricCheltuieli[i];
    if (aux.istoricCheltuieli != NULL)
        delete[] aux.istoricCheltuieli;
    aux.nrCheltuieli++;
    aux.istoricCheltuieli = new float[aux.nrCheltuieli];
    for (int i = 0; i <= aux.nrCheltuieli - 2; i++)
        aux.istoricCheltuieli[i] = auxCheltuieli[i];
    aux.istoricCheltuieli[aux.nrCheltuieli - 1] = cheltuiala;
    return aux;
}

// adauga cheltuiala data ca parametru la istoricul de cheltuieli al clientului
Client operator+(float cheltuiala, Client client) {
    float auxCheltuieli[1000];
    for (int i = 0; i < client.nrCheltuieli; i++)
        auxCheltuieli[i] = client.istoricCheltuieli[i];
    if (client.istoricCheltuieli != NULL)
        delete[] client.istoricCheltuieli;
    client.nrCheltuieli++;
    client.istoricCheltuieli = new float[client.nrCheltuieli];
    for (int i = 0; i <= client.nrCheltuieli - 2; i++)
        client.istoricCheltuieli[i] = auxCheltuieli[i];
    client.istoricCheltuieli[client.nrCheltuieli - 1] = cheltuiala;
    return client;
}


// concateneaza cheltuielile a doi clienti
// utila atunci cand nu vrem sa pierdem cheltuielile unui duplicat atunci cand il stergem
Client Client::operator+(Client &client) {
    Client aux(*this);
    float *auxCheltuieli;
    auxCheltuieli = new float[aux.nrCheltuieli + client.nrCheltuieli];
    for (int i = 0; i < aux.nrCheltuieli; i++)
        auxCheltuieli[i] = aux.istoricCheltuieli[i];
    for (int i = aux.nrCheltuieli; i < aux.nrCheltuieli + client.nrCheltuieli; i++)
        auxCheltuieli[i] = client.istoricCheltuieli[i - aux.nrCheltuieli];
    if (aux.istoricCheltuieli != NULL)
        delete[] aux.istoricCheltuieli;
    aux.nrCheltuieli += client.nrCheltuieli;
    aux.istoricCheltuieli = new float[aux.nrCheltuieli];
    for (int i = 0; i < aux.nrCheltuieli; i++)
        aux.istoricCheltuieli[i] = auxCheltuieli[i];
    delete[] auxCheltuieli;
    return aux;
}

// sterge toate aparitiile cheltuielii date ca parametru din instoricul clientului
Client operator-(float cheltuiala, Client client) {
    float auxCheltuieli[1000];
    int k = -1;
    for (int i = 0; i < client.nrCheltuieli; i++)
        if (client.istoricCheltuieli[i] != cheltuiala)
            auxCheltuieli[++k] = client.istoricCheltuieli[i];
    client.nrCheltuieli = k + 1;
    if (client.istoricCheltuieli != NULL)
        delete[] client.istoricCheltuieli;
    client.istoricCheltuieli = new float[k + 1];
    for (int i = 0; i < client.nrCheltuieli; i++)
        client.istoricCheltuieli[i] = auxCheltuieli[i];
    return client;
}

// sterge toate aparitiile cheltuielii date ca parametru din instoricul clientului
Client Client::operator-(float cheltuiala) {
    float auxCheltuieli[1000];
    int k = -1;
    Client aux(*this);
    for (int i = 0; i < aux.nrCheltuieli; i++)
        if (aux.istoricCheltuieli[i] != cheltuiala)
            auxCheltuieli[++k] = aux.istoricCheltuieli[i];
    aux.nrCheltuieli = k + 1;
    if (aux.istoricCheltuieli != NULL)
        delete[] aux.istoricCheltuieli;
    aux.istoricCheltuieli = new float[k + 1];
    for (int i = 0; i < aux.nrCheltuieli; i++)
        aux.istoricCheltuieli[i] = auxCheltuieli[i];
    return aux;
}


// Constructor fara parametrii
Client::Client() : Persoana() {
    this->varsta = 0;

    this->telefon = new char[strlen("0000000000") + 1];
    strcpy(this->telefon, "0000000000");

    this->email = new char[strlen("necunoscut@dom.com") + 1];
    strcpy(this->email, "necunoscut@dom.com");

    this->istoricCheltuieli = NULL;

    this->nrCheltuieli = 0;
}

// Constructor cu toti parametrii
Client::Client(char *nume, char *prenume, char initialaTata, int varsta, char *telefon, char *email,
               float *istoricCheltuieli, int nrCheltuieli) : Persoana(nume, prenume, initialaTata) {
    this->varsta = varsta;

    this->telefon = new char[strlen(telefon) + 1];
    strcpy(this->telefon, telefon);

    this->email = new char[strlen(email) + 1];
    strcpy(this->email, email);

    this->nrCheltuieli = nrCheltuieli;

    this->istoricCheltuieli = new float[nrCheltuieli];
    for (int i = 0; i < this->nrCheltuieli; i++)
        this->istoricCheltuieli[i] = istoricCheltuieli[i];
}

// Constructor cu mai multi parametrii
Client::Client(char *nume, char *prenume, char initialaTata, char *telefon, char *email) : Persoana(nume, prenume,
                                                                                                    initialaTata) {
    this->telefon = new char[strlen(telefon) + 1];
    strcpy(this->telefon, telefon);

    this->email = new char[strlen(email) + 1];
    strcpy(this->email, email);
}

// Copy contructor
Client::Client(const Client &client) : Persoana(client) {
    this->varsta = client.varsta;

    this->telefon = new char[strlen(client.telefon) + 1];
    strcpy(this->telefon, client.telefon);

    this->email = new char[strlen(client.email) + 1];
    strcpy(this->email, client.email);

    this->nrCheltuieli = client.nrCheltuieli;

    this->istoricCheltuieli = new float[client.nrCheltuieli];
    for (int i = 0; i < this->nrCheltuieli; i++)
        this->istoricCheltuieli[i] = client.istoricCheltuieli[i];
}

// Destructor
Client::~Client() {
    if (this->email != NULL)
        delete[] this->email;

    if (this->telefon != NULL)
        delete[] this->telefon;

    if (this->istoricCheltuieli != NULL)
        delete[] this->istoricCheltuieli;
}