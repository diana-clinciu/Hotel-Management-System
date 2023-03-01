//
// Created by Diana on 2/25/2023.
//

#include "cstring"
#include "cauta.h"
#include "Cazare.h"


int Cazare::contorCazare = 0;

Cazare Cazare::operator+(float scumpire) {
    Cazare aux(*this);
    aux.cost += scumpire;
    return aux;
}

Cazare Cazare::operator-(float reducere) {
    Cazare aux(*this);
    aux.cost -= reducere;
    return aux;
}

Cazare operator+(float scumpire, Cazare cazare) {
    cazare.cost += scumpire;
    return cazare;
}

Cazare operator-(float reducere, Cazare cazare) {
    cazare.cost -= reducere;
    return cazare;
}


Camera *Cazare::operator[](int index) {
    if (0 <= index && index < this->nrCamere)
        return this->camereCazare[index];
    cout << "Index introdus gresit!" << endl;
}

bool Cazare::operator==(const Cazare &cazare) {
    if (strcmp(this->numeClient, cazare.numeClient) != 0)
        return false;
    if (strcmp(this->prenumeClient, cazare.prenumeClient) != 0)
        return false;
    if (this->dataCheckIn != cazare.dataCheckIn)
        return false;
    if (this->dataCheckOut != cazare.dataCheckOut)
        return false;
    return true;
}

// compara doua cazari dupa cost
bool Cazare::operator<(const Cazare &cazare) {
    if (this->cost < cazare.cost)
        return true;
    return false;
}

// incrementeaza costul cu 1
const Cazare &Cazare::operator++() {
    this->cost++;
    return *this;
}

// incrementeaza costul cu 1
const Cazare Cazare::operator++(int) {
    Cazare aux(*this);
    this->cost++;
    return aux;
}

// adauga o camera la o cazare
Cazare operator+(Cazare cazare, Camera &camera) {
    cazare.camereCazare.push(&camera);
    cazare.nrCamere++;
    cazare.cost += camera.getPret();
    return cazare;
}

// adauga o camera la o cazare
Cazare operator+(Camera &camera, Cazare cazare) {
    cazare.camereCazare.push(&camera);
    cazare.nrCamere++;
    cazare.cost += camera.getPret();
    return cazare;
}

Cazare &Cazare::operator=(const Cazare &cazare) {
    if (this != &cazare) {
        if (this->numeClient != NULL)
            delete this->numeClient;
        if (this->prenumeClient != NULL)
            delete this->prenumeClient;

        this->numeClient = new char[strlen(cazare.numeClient) + 1];
        strcpy(this->numeClient, cazare.numeClient);

        this->prenumeClient = new char[strlen(cazare.prenumeClient) + 1];
        strcpy(this->prenumeClient, cazare.prenumeClient);

        this->cost = cazare.cost;

        this->dataCheckIn = cazare.dataCheckIn;

        this->dataCheckOut = cazare.dataCheckOut;

        this->nrCamere = cazare.nrCamere;

        this->camereCazare = cazare.camereCazare;

    }
    return *this;
}

ostream &operator<<(ostream &out, const Cazare &cazare) {
    out << "Cod cazare: " << cazare.codCazare << endl;

    out << "Nume client: " << cazare.numeClient << endl;

    out << "Prenume client: " << cazare.prenumeClient << endl;

    out << "Camere:" << endl;
    for (int i = 0; i < cazare.nrCamere; i++) {
        out << *cazare.camereCazare[i];
        cout << "\n--------------------------------------\n";
    }

    out << "Cost total: " << cazare.cost << endl;

    out << "Data check-in: " << get<0>(cazare.dataCheckIn) << '/' << get<1>(cazare.dataCheckIn) << '/'
        << get<2>(cazare.dataCheckIn) << endl;

    out << "Data check-out: " << get<0>(cazare.dataCheckOut) << '/' << get<1>(cazare.dataCheckOut) << '/'
        << get<2>(cazare.dataCheckOut) << endl;

    return out;
}

// functie care afiseaza toate camerele libere (daca exista)
void afisareCamereLibere(vector<Camera *> &camera, bool &existaCamereLibere) {
    for (int i = 0; i < camera.size(); i++) {
        if (camera[i]->getOcupata() == 0) {
            existaCamereLibere = true;
            cout << *(camera[i]) << endl;
            cout << "* Pret cu reducere: " << camera[i]->getPret() - camera[i]->getPret() * 0.2 << endl;
            cout << "\n--------------------------------------\n";
        }
    }
}

// functie cu care facem check-in la un client
// verifica daca clientul si camerele exista si daca camerele sunt libere
// daca totul e ok, seteaza camerele ca fiind ocupate
// de asemenea, calculeaza pretul final si il adauga la cheltuielile clientului
int Cazare::checkIn(list<Client *> &client, vector<Camera *> &camera) {
    try {
        int codClient, zi, luna, an, nrDeCamera[1000], indCamera, nrCamere;
        bool existaCamereLibere;

        char aux[1000];

        cout << "Nume client: ";
        cin >> aux;
        if (this->numeClient != NULL)
            delete[] this->numeClient;
        this->numeClient = new char[strlen(aux) + 1];
        strcpy(this->numeClient, aux);

        cout << "Prenume client: ";
        cin >> aux;
        if (this->prenumeClient != NULL)
            delete[] this->prenumeClient;
        this->prenumeClient = new char[strlen(aux) + 1];
        strcpy(this->prenumeClient, aux);

        cout << "Introduceti cod client: ";
        cin >> codClient;

        auto it = cauta(codClient, client);

        if (it == client.end()) {
            throw 4;
        }


        existaCamereLibere = false;
        cout << "\nCamere libere:\n";
        afisareCamereLibere(camera, existaCamereLibere);


        if (!existaCamereLibere) {
            throw 1; // #exceptie int
        }

        cout << "Introduceti numar de camere alese: ";
        cin >> nrCamere;

        cout << "Introduceti numarul fiecarei camere alese:";
        for (int i = 0; i < nrCamere; i++)
            cin >> nrDeCamera[i];

        this->camereCazare.clear();
        for (int i = 0; i < nrCamere; i++) {
            indCamera = cauta(nrDeCamera[i], camera);
            if (indCamera == -1) {
                throw 3;
            }
            if (camera[indCamera]->getOcupata() == true) {
                throw 2;
            }
            *this = *this + (*camera[indCamera]);    // folosit + (camera)
        }

        for (int i = 0; i < this->nrCamere; i++)
            this->camereCazare[i]->setOcupata(true);

        cout << "Introduceti data check-in (DD MM YYYY): ";
        cin >> zi >> luna >> an;
        this->dataCheckIn = make_tuple(zi, luna, an);

        if ((*it)->clientFidel())
            this->cost -= this->cost * 0.2;

        *(*it) = *(*it) + this->cost;

        cout << "Cost final: " << this->cost << endl;
        cout << "Check-in facut cu succes!!! <3" << endl;
        cout << "Cod cazare: " << this->codCazare << endl;
    }
    catch (int i) {
        if (i == 1)
            cout << "Nu exista camere libere momentan." << endl;
        if (i == 2)
            cout << "Camera ocupata." << endl;
        if (i == 3)
            cout << "Camera nu exista." << endl;
        if (i == 4)
            cout << "Clientul nu exista." << endl;
        return -1;
    }
    catch (...) {
        cout << "Exceptie necunoscuta\n";
        return -1;
    }
}

// functie cu care facem check-out la un client
// verifica daca camerele si cazarea exista
// daca totul e ok, seteaza camerele ca fiind libere
int checkOut(vector<Camera *> &camera, vector<Cazare *> &cazare) {
    int nrCamere, indCazare, zi, luna, an, nrDeCamera[1000];
    vector<Camera *> camereCheckOut;

    cout << "Introduceti numarul de camere din cazare: ";
    cin >> nrCamere;
    cout << "Introduceti numarul fiecarei camerele din cazare: ";
    for (int i = 0; i < nrCamere; i++)
        cin >> nrDeCamera[i];

    for (int i = 0; i < nrCamere; i++)
        if (cauta(nrDeCamera[i], camera) == -1) {
            cout << "Camera " << nrDeCamera[i] << " nu exista!" << endl;
            return -1;
        }

    for (int i = 0; i < nrCamere; i++)
        camereCheckOut.push_back(camera[cauta(nrDeCamera[i], camera)]);


    indCazare = -1;
    for (int i = 0; i < cazare.size(); i++) {
        if (nrCamere == cazare[i]->nrCamere && cazare[i]->dataCheckOut == make_tuple(0, 0, 0)) {
            bool egale = true;
            for (int j = 0; j < camereCheckOut.size(); j++) {
                bool gasit = false;

                for (int k = 0; k < cazare[i]->camereCazare.getSize(); k++)
                    if (*camereCheckOut[j] == *(cazare[i]->camereCazare[k])) {
                        gasit = true;
                        break;
                    }
                if (!gasit) {
                    egale = false;
                    break;
                }
            }
            if (egale) {
                indCazare = i;
                break;
            }
        }
    }

    if (indCazare == -1) {
        cout << "Nu exista cazare cu aceste camere." << endl;
        return -1;
    }

    for (int i = 0; i < cazare[indCazare]->nrCamere; i++) {
        cazare[indCazare]->camereCazare[i]->setOcupata(false);
        cazare[indCazare]->camereCazare[i]->murdaresteCamera();
    }

    cout << "Introduceti data check-out (DD MM YYYY): ";
    cin >> zi >> luna >> an;
    cazare[indCazare]->dataCheckOut = make_tuple(zi, luna, an);

    cout << "Check-out facut cu succes!!! <3" << endl;
    cout << "Cod cazare: " << cazare[indCazare]->codCazare << endl;
}

// Constructor fara parametrii
Cazare::Cazare() : codCazare(contorCazare++) {
    this->numeClient = new char[strlen("Necunoscut") + 1];
    strcpy(this->numeClient, "Necunoscut");

    this->prenumeClient = new char[strlen("Necunoscut") + 1];
    strcpy(this->prenumeClient, "Necunoscut");

    this->cost = 0;

    this->nrCamere = 0;
    this->camereCazare = {};

    this->dataCheckIn = {0, 0, 0};
    this->dataCheckOut = {0, 0, 0};
}

// Constructor cu toti parametrii
Cazare::Cazare(char *numeClient, char *prenumeClient, float cost, tuple<int, int, int> dataCheckIn,
               tuple<int, int, int> dataCheckOut, int nrCamere, Vector<Camera *> camereCazare) : codCazare(
        contorCazare++) {
    this->numeClient = new char[strlen(numeClient) + 1];
    strcpy(this->numeClient, numeClient);

    this->prenumeClient = new char[strlen(prenumeClient) + 1];
    strcpy(this->prenumeClient, prenumeClient);

    this->cost = cost;

    this->dataCheckIn = dataCheckIn;

    this->dataCheckOut = dataCheckOut;

    this->nrCamere = nrCamere;

    this->camereCazare = camereCazare;
}

// Constructor cu mai multi parametrii
Cazare::Cazare(char *numeClient, char *prenumeClient, tuple<int, int, int> dataCheckIn,
               tuple<int, int, int> dataCheckOut) : codCazare(contorCazare++) {
    this->numeClient = new char[strlen(numeClient) + 1];
    strcpy(this->numeClient, numeClient);

    this->prenumeClient = new char[strlen(prenumeClient) + 1];
    strcpy(this->prenumeClient, prenumeClient);


    this->dataCheckIn = dataCheckIn;

    this->dataCheckOut = dataCheckOut;
}

// Constructor cu mai multi parametrii
Cazare::Cazare(char *numeClient, char *prenumeClient) : codCazare(contorCazare++) {
    this->numeClient = new char[strlen(numeClient) + 1];
    strcpy(this->numeClient, numeClient);

    this->prenumeClient = new char[strlen(prenumeClient) + 1];
    strcpy(this->prenumeClient, prenumeClient);
}

// Copy Constructor
Cazare::Cazare(const Cazare &cazare) : codCazare(contorCazare++) {
    this->numeClient = new char[strlen(cazare.numeClient) + 1];
    strcpy(this->numeClient, cazare.numeClient);

    this->prenumeClient = new char[strlen(cazare.prenumeClient) + 1];
    strcpy(this->prenumeClient, cazare.prenumeClient);

    this->cost = cazare.cost;

    this->dataCheckIn = cazare.dataCheckIn;

    this->dataCheckOut = cazare.dataCheckOut;

    this->nrCamere = cazare.nrCamere;

    this->camereCazare = cazare.camereCazare;
}

// Desctructor
Cazare::~Cazare() {
    if (this->numeClient != NULL)
        delete[]this->numeClient;

    if (this->prenumeClient != NULL)
        delete[]this->prenumeClient;
}