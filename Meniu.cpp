//
// Created by Diana on 2/26/2023.
//


#include "Camera.h"
#include "Angajat.h"
#include "Client.h"
#include "Cazare.h"
#include "CameraCuBucatarie.h"
#include "Simpla.h"
#include "Apartament.h"
#include "EmptyInputFile.h"
#include "cauta.h"
#include "Meniu.h"
#include "fstream"

ifstream fin("angajati.in");
ofstream fout("angajati.out");

Meniu *Meniu::obiect = NULL;

EmptyInputFile emptyInputFile;

// functie care sterge si afiseaza dublurile unui client
// dublura = client care are acelasi nume, prenume, telefon si email cu un alt client
void stergeDubluriClient(list <Client*>& client)
{
    char nume[100], prenume[100], email[100], intialaTata, telefon[11];
    int gasit = 0, primul = -1;
    list <Client*>::iterator poz;

    cout << "Introduceti nume client: ";
    cin >> nume;
    cout << "Introduceti prenume client: ";
    cin >> prenume;
    cout << "Introduceti intiala tatalui: ";
    cin >> intialaTata;
    cout << "Introduceti numarul de telefon: ";
    cin >> telefon;
    cout << "Introuduceti adresa de email: ";
    cin >> email;
    Client clientInput(nume, prenume, intialaTata, telefon, email);
    cout << "Dubluri gasite:" << endl;

    auto it = client.begin();
    while(it!=client.end())
    {
        if (clientInput == *(*it))
            if (primul == -1)
            {
                primul = 1;
                poz = it;
                it++;
            }
            else
            {
                cout << *(*it) << endl;
                cout << "\n-------------------------------------\n";
                gasit = 1;
                *(*poz) = *(*poz) + *(*it);
                delete (*it);
                it = client.erase(it);
            }
        else
            it++;
    }
    if (gasit == 0)
        cout << "Nu exista dubluri gasite!" << endl;
}

// functie care cauta o cazare dupa numele si prenumele clientului si data la care s-a facut check-in
// utila in caz ca un client si-a uitat codul de cazare
void cautaCazareDupaNumeData(vector<Cazare *> &cazare) {
    char numeClient[100], prenumeClient[100];
    tuple<int, int, int> dataCheckIn, dataCheckOut;
    int zi, luna, an, gasit = 0;

    cout << "Introduceti nume client: ";
    cin >> numeClient;

    cout << "Introduceti prenume client: ";
    cin >> prenumeClient;

    cout << "Introduceti data check-in: ";
    cin >> zi >> luna >> an;
    dataCheckIn = make_tuple(zi, luna, an);

    cout << "Introduceti data check-out: ";
    cin >> zi >> luna >> an;
    dataCheckOut = make_tuple(zi, luna, an);

    Cazare cazareDeCautat(numeClient, prenumeClient, dataCheckIn, dataCheckOut);

    for (int i = 0; i < cazare.size(); i++)
        if (cazareDeCautat == *cazare[i]) {
            cout << *cazare[i];
            cout << "\n--------------------------------------\n";
            gasit = 1;
        }
    if (gasit == 0)
        cout << "Nu exista o astfel de cazare.\n";
}


// functie template care afiseaza descresc un vector
template<class T>
void afiseazaDescresc(vector<T *> &vector) {
    int sortat;
    T *aux;
    do {
        sortat = 1;
        for (int i = 0; i < (int) vector.size() - 1; i++)
            if (*(vector[i]) < *(vector[i + 1])) {
                aux = vector[i];
                vector[i] = vector[i + 1];
                vector[i + 1] = aux;
                sortat = 0;
            }
    } while (sortat == 0);
    for (int i = 0; i < vector.size(); i++) {
        cout << *(vector[i]);
        cout << "\n--------------------------------------\n";
    }
}

void afiseazaDescresc(list<Client *> &list) {
    int sortat;
    Client *aux;
    do {
        sortat = 1;
        for (auto it = list.begin(); it != prev(list.end()); it++)
            if (*(*it) < *(*(next(it)))) {
                aux = (*it);
                (*it) = *(next(it));
                (*(next(it))) = aux;
                sortat = 0;
            }
    } while (sortat == 0);

    for (auto it = list.begin(); it != list.end(); it++) {
        cout << *(*it);
        cout << "\n--------------------------------------\n";
    }
}

// functie care cauta si afiseaza angajatii care au vechema mai mare ca toti angajatii dati ca parametru la un loc
// utila daca vrem sa dam acei angajati afata (gasim angajati suficienti de competenti ca sa-i inlocuiasca -> PAC! AFARA!)
void afisareAngajatiVechimeMaiMareCa(vector<Angajat *> const &angajat, vector<Angajat *> const &angajatAles) {
    Angajat ang;
    bool exista = false;
    for (int i = 0; i < angajatAles.size(); i++)
        ang = ang + *(angajatAles[i]);
    for (int i = 0; i < angajat.size(); i++)
        if (ang < *(angajat[i])) {
            cout << *(angajat[i]) << endl;
            cout << "\n--------------------------------------\n";
            exista = true;
        }
    if (!exista)
        cout << "Nu exista astfel de angajati" << endl;
}

void Meniu::gestionareHotel() {
    list<Client *> client; // #list
    vector<Cazare *> cazare;
    vector<Angajat *> angajat, rez, angajatAles;
    //exemplu de polimorfism // #upcast
    vector<Camera *> camera; // #vector
    Client cl;
    Cazare caz;
    Angajat ang;
    string spor;
    double sporNr;
    char job[100], op[20];
    int indAngajat, r, codAngajat, reducere, scumpire, codCazare, indCazare, indCamera, nrCamera, nrZile, n, nrMariri, idClient, suma, ok, nrAngajati, idAngajat[1000];
    int optiune2, optiune3, optiune4, optiune5, optiune;
    int zi, luna, an;
    CameraCuBucatarie *bucatarie;


    do {
        cout << "\n+----------------------------------------------------+\n"
             << "|                       MENIU                        |\n"
             << "+----------------------------------------------------+\n"
             << "|   1. Adaugare client                               |\n"
             << "|   2. Adaugare camera                               |\n"
             << "|   3. Adaugare angajat                              |\n"
             << "|   4. Import informatii angajat                     |\n"
             << "|   5. Export informatii angajat                     |\n"
             << "|   6. Check-in                                      |\n"
             << "|   7. Check-out                                     |\n"
             << "|   8. Mai multe comenzi client                      |\n"
             << "|   9. Mai multe comenzi camera                      |\n"
             << "|   10. Mai multe comenzi angajat                    |\n"
             << "|   11. Mai multe comenzi cazare                     |\n"
             << "|   12. Iesire                                       |\n"
             << "+----------------------------------------------------+\n";


        cin >> op;

        optiune = atoi(op);

        switch (optiune) {
            case 1:
                cin >> cl;
                client.push_back(new Client(cl));
                cout << "Id client: " << client.back()->getIdPersoana() << endl;
                break;
            case 2:
                int tipCamera;
                cout << "Alegeti tipul de camera:\n\t1. Simpla\n\t2. Camera cu bacatarie\n\t3. Apartament\n";
                try {
                    cin >> op;

                    tipCamera = atoi(op);

                    switch (tipCamera) {
                        case 1: {
                            Simpla simpla;
                            cin >> simpla;
                            camera.push_back(new Simpla(simpla));
                            break;
                        }
                        case 2: {
                            CameraCuBucatarie cameraCuBucatarie;
                            cin >> cameraCuBucatarie;
                            camera.push_back(new CameraCuBucatarie(cameraCuBucatarie));
                            break;
                        }
                        case 3: {
                            Apartament apartament;
                            cin >> apartament;
                            camera.push_back(new Apartament(apartament));
                            break;
                        }
                        default:
                            throw runtime_error("Optiune invalida\n");
                            break;
                    }
                    cout << "Numar camera: " << camera[camera.size() - 1]->getNrCamera() << endl;
                }
                catch (runtime_error e) {
                    cout << "Runtime error: " << e.what();
                }
                break;
            case 3:
                cin >> ang;
                angajat.push_back(new Angajat(ang));
                cout << "Id angajat: " << angajat[angajat.size() - 1]->getIdPersoana() << endl;
                break;
            case 4:
                try {
                    if (fin.peek() == EOF)   // #exceptie custom
                        throw emptyInputFile;
                    ang.citireFisier(fin);
                    angajat.push_back(new Angajat(ang));
                    cout << "Import realizat cu succes.\n";
                    cout << "Id angajat: " << angajat[angajat.size() - 1]->getIdPersoana() << endl;
                }
                catch (EmptyInputFile e) {
                    cout << "Error: " << e.what();
                    cout << "Import esuat.\n";
                }
                break;
            case 5:
                ang.afisareFisier(fout);
                cout << "Export realizat cu succes.\n";
                break;
            case 6:
                cazare.push_back(new Cazare(caz));
                r = cazare[cazare.size() - 1]->checkIn(client, camera);
                if (r == -1) {
                    delete cazare[cazare.size() - 1];
                    cazare.pop_back();
                    cout << "Check-in esuat!" << endl;
                }
                break;
            case 7:
                r = checkOut(camera, cazare);
                if (r == -1) {
                    cout << "Check-out esuat!" << endl;
                }
                break;

            case 8:
                do {
                    cout << "\n+-------------------------------------------------------------------+\n"
                         << "|   1. Stergere dubluri client                                      |\n"
                         << "|   2. Afisare client descrescator dupa cheltuielile totale         |\n"
                         << "|   3. Sterge cheltuiala client                                     |\n"
                         << "|   4. Creste varsta client                                         |\n"
                         << "|   5. Revenire meniu principal                                     |\n"
                         << "+-------------------------------------------------------------------+\n";
                    cin >> op;

                    optiune2 = atoi(op);

                    switch (optiune2) {
                        case 1:
                            stergeDubluriClient(client);
                            cout << "Stergere realizata cu succes." << endl;
                            break;
                        case 2:
                            afiseazaDescresc(client);
                            break;
                        case 3: {
                            cout << "Introduceti id client: ";
                            cin >> idClient;
                            auto it = cauta(idClient, client);
                            if (it != client.end()) {
                                cout << "Introduceti cheltuiala: ";
                                cin >> suma;
                                *(*it) = *(*it) - suma;
                                cout << "Cheltuiala stearsa cu succes" << endl;
                                cout << "Cheltuieli: " << endl;
                                for (int i = 0; i < (*it)->getNrCheltuieli(); i++)
                                    cout << (*(*it))[i] << ' ';
                            } else
                                cout << "Clientul nu exista" << endl;
                            break;
                        }
                        case 4: {
                            cout << "Introduceti id client: ";
                            cin >> idClient;
                            auto it = cauta(idClient, client);
                            if (it != client.end()) {
                                (*(*it))++;
                                cout << "Varsta incrementata cu succes!" << endl;
                                cout << "Varsta client: " << (*it)->getVarsta() << " ani" << endl;
                            } else
                                cout << "Clientul nu exista" << endl;
                            break;
                        }
                        case 5:
                            break;
                        default:
                            cout << "Optiune invalida" << endl;
                    }
                } while (optiune2 != 5);
                break;

            case 9:
                do {
                    cout << "\n+--------------------------------------------------------------+\n"
                         << "|   1. Crestere pret camera                                    |\n"
                         << "|   2. Reducere pret camera                                    |\n"
                         << "|   3. Curata camera                                           |\n"
                         << "|   4. Afisare camere descrescator dupa pret                   |\n"
                         << "|   5. Arunca alimente din bucatarie cu data de expirare data  |\n"
                         << "|   6. Revenire meniu principal                                |\n"
                         << "+--------------------------------------------------------------+\n";
                    cin >> op;

                    optiune3 = atoi(op);

                    switch (optiune3) {
                        case 1:
                            cout << "Introduceti numar camera: ";
                            cin >> nrCamera;
                            indCamera = cauta(nrCamera, camera);
                            if (indCamera != -1) {
                                cout << "Introduceti scumpire camera: ";
                                cin >> scumpire;
                                *camera[indCamera] = *camera[indCamera] + scumpire;
                                cout << *camera[indCamera] << endl;
                            } else
                                cout << "Nu exista camera." << endl;
                            break;
                        case 2:
                            cout << "Introduceti numar camera: ";
                            cin >> nrCamera;
                            indCamera = cauta(nrCamera, camera);
                            if (indCamera != -1) {
                                cout << "Introduceti reducere camera: ";
                                cin >> reducere;
                                *camera[indCamera] = *camera[indCamera] - reducere;
                                cout << *camera[indCamera] << endl;
                            } else
                                cout << "Nu exista camera." << endl;
                            break;
                        case 3:
                            cout << "Introduceti numar camera: ";
                            cin >> nrCamera;
                            indCamera = cauta(nrCamera, camera);
                            if (indCamera != -1) {
                                camera[indCamera]->curataCamera();
                                cout << "Camera curatata cu succes." << endl;
                            } else
                                cout << "Nu exista camera." << endl;
                            break;
                        case 4:
                            afiseazaDescresc<Camera>(camera);
                            break;
                        case 5:
                            cout << "Introduceti numar camera: ";
                            cin >> nrCamera;
                            indCamera = cauta(nrCamera, camera);
                            if (indCamera != -1) {
                                bucatarie = dynamic_cast<CameraCuBucatarie *> (camera[indCamera]); // #downcast
                                if (bucatarie != nullptr) {
                                    cout << "Data expirare";
                                    cin >> zi >> luna >> an;
                                    bucatarie->aruncaAlimente(make_tuple(zi, luna, an));
                                    cout << "S-au aruncat alimentele." << endl;
                                }
                            } else
                                cout << "Nu exista camera." << endl;
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Optiune invalida" << endl;
                            break;
                    }
                } while (optiune3 != 6);
                break;


            case 10:
                do {
                    cout
                            << "\n+-------------------------------------------------------------------------------------------+\n"
                            << "|   1. Acorda marire la angajat                                                             |\n"
                            << "|   2. Afisare angajati care au vechimea mai mare decat niste angajati alesi la un loc      |\n"
                            << "|   3. Afisare top 10 cei mai harnici angajati                                              |\n"
                            << "|   4. Afisare toti angajatii cu job-ul X                                                   |\n"
                            << "|   5. Creste vechime angajat                                                               |\n"
                            << "|   6. Scade vechime angajat                                                                |\n"
                            << "|   7. Afisare ultimele N mariri ale unui angajat                                           |\n"
                            << "|   8. Afisare salariu angajat                                                              |\n"
                            << "|   9. Revenire meniu principal                                                             |\n"
                            << "+-------------------------------------------------------------------------------------------+\n";
                    cin >> op;

                    optiune4 = atoi(op);

                    switch (optiune4) {
                        case 1:
                            cout << "Introduceti codul angajatului: ";
                            cin >> codAngajat;

                            indAngajat = cauta(codAngajat, angajat);

                            if (indAngajat != -1) {
                                cout << "Introduceti spor (puneti - daca vreti sporul implicit): \n";
                                cin >> spor;
                                if (spor == "-")
                                    angajat[indAngajat]->acordaMarire();
                                else {
                                    sporNr = stoi(spor);
                                    if (sporNr < 0)
                                        cout << "Spor invalid!" << endl;
                                    else
                                        angajat[indAngajat]->acordaMarire(sporNr);
                                }
                            } else
                                cout << "Angajatul nu exista!" << endl;
                            break;
                        case 2:
                            cout << "Introduceti numarul de angajati alesi: ";
                            cin >> nrAngajati;
                            cout << "Introduceti id-urile angajatilor alesi: ";
                            for (int i = 0; i < nrAngajati; i++)
                                cin >> idAngajat[i];
                            ok = 1;
                            for (int i = 0; i < nrAngajati; i++) {
                                indAngajat = cauta(idAngajat[i], angajat);
                                if (indAngajat == -1) {
                                    cout << "Angajatul " << idAngajat[i] << " nu exista." << endl;
                                    ok = 0;
                                    break;
                                } else {
                                    angajatAles.push_back(angajat[indAngajat]);
                                }
                            }
                            if (ok) {
                                afisareAngajatiVechimeMaiMareCa(angajat, angajatAles);
                                cout << "Cautare finalizata cu succes." << endl;
                            } else
                                cout << "Cautare esuata." << endl;
                            angajatAles.clear();
                            break;
                        case 3:
                            afiseazaDescresc<Angajat>(angajat);
                            break;
                        case 4:
                            cout << "Introduceti job: ";
                            cin >> job;
                            rez = cauta(angajat, job);
                            if (rez.size() != 0)
                                afiseazaDescresc<Angajat>(rez);
                            else
                                cout << "Nu exista angajatii cu jobul cautat." << endl;
                            break;
                        case 5:
                            cout << "Introduceti codul angajatului: ";
                            cin >> codAngajat;

                            indAngajat = cauta(codAngajat, angajat);

                            if (indAngajat != -1) {
                                (*angajat[indAngajat])++;
                                cout << "S-a crescut vechimea angajatului cu o zi." << endl;
                                cout << "Numar total de zile: " << angajat[indAngajat]->getZileLucrate() << endl;
                            } else
                                cout << "Angajatul nu exista!" << endl;
                            break;
                        case 6:
                            cout << "Introduceti codul angajatului: ";
                            cin >> codAngajat;

                            indAngajat = cauta(codAngajat, angajat);

                            if (indAngajat != -1) {
                                cout << "Introduceti numarul de zile: ";
                                cin >> nrZile;
                                *angajat[indAngajat] = *angajat[indAngajat] - nrZile;
                                cout << "S-a scazut vechimea angajatului cu " << nrZile << " zile" << endl;
                                cout << "Numar total de zile: " << angajat[indAngajat]->getZileLucrate() << endl;
                            } else
                                cout << "Angajatul nu exista!" << endl;
                            break;
                        case 7:
                            cout << "Introduceti codul angajatului: ";
                            cin >> codAngajat;

                            indAngajat = cauta(codAngajat, angajat);

                            if (indAngajat != -1) {
                                cout << "Introduceti N: ";
                                cin >> n;
                                nrMariri = angajat[indAngajat]->getNrMariri();
                                if (n > nrMariri)
                                    cout << "Nu exista " << n << " mariri." << endl;
                                n = min(n, nrMariri);
                                cout << "Mariri: " << endl;
                                for (int i = nrMariri - n; i < nrMariri; i++)
                                    cout << (*angajat[indAngajat])[i] << ' ';
                                cout << endl;
                            } else
                                cout << "Angajatul nu exista!" << endl;
                            break;
                        case 8:
                            cout << "Introduceti codul angajatului: ";
                            cin >> codAngajat;

                            indAngajat = cauta(codAngajat, angajat);

                            if (indAngajat != -1) {
                                cout << "Salariu: " << angajat[indAngajat]->getSalariu() << endl;
                                cout << "Salariu rotunjit: " << (int) (*angajat[indAngajat]) << endl;
                            } else
                                cout << "Angajatul nu exista!" << endl;
                            break;
                        case 9:
                            break;
                        default:
                            cout << "Optiune invalida" << endl;
                            break;
                    }
                } while (optiune4 != 9);
                break;

            case 11:
                do {
                    cout
                            << "\n+-------------------------------------------------------------------------------------------+\n"
                            << "|   1. Cauta cazare dupa nume si prenume client, data de check-in si data de check-out      |\n"
                            << "|   2. Crestere pret cazare                                                                 |\n"
                            << "|   3. Reducere pret cazare                                                                 |\n"
                            << "|   4. Afisare cazari descrescator dupa cost                                                |\n"
                            << "|   5. Afiseaza camere cazare                                                               |\n"
                            << "|   6. Revenire meniu principal                                                             |\n"
                            << "+-------------------------------------------------------------------------------------------+\n";
                    cin >> op;

                    optiune5 = atoi(op);

                    switch (optiune5) {
                        case 1:
                            cautaCazareDupaNumeData(cazare);
                            break;
                        case 2:
                            cout << "Introduceti cod cazare: ";
                            cin >> codCazare;
                            indCazare = cauta(codCazare, cazare);
                            if (indCazare != -1) {
                                cout << "Introduceti scumpire cost: ";
                                cin >> scumpire;
                                *cazare[indCazare] = *cazare[indCazare] + scumpire;
                            } else
                                cout << "Nu exista cazarea." << endl;
                            break;
                        case 3:
                            cout << "Introduceti cod cazare: ";
                            cin >> codCazare;
                            indCazare = cauta(codCazare, cazare);
                            if (indCazare != -1) {
                                cout << "Introduceti reducere cost: ";
                                cin >> reducere;
                                *cazare[indCazare] = *cazare[indCazare] - reducere;
                            } else
                                cout << "Nu exista cazarea." << endl;
                            break;
                        case 4:
                            afiseazaDescresc<Cazare>(cazare);
                            break;
                        case 5:
                            cout << "Introduceti cod cazare: ";
                            cin >> codCazare;
                            indCazare = cauta(codCazare, cazare);
                            if (indCazare != -1) {
                                cout << "Camere: " << endl;
                                for (int i = 0; i < cazare[indCazare]->getNrCamere(); i++) {
                                    cout << *((*cazare[indCazare])[i]);
                                    cout << "\n-------------------------------------\n";
                                }
                                cout << "Cost total: " << cazare[indCazare]->getCost() << "("
                                     << (int) (*cazare[indCazare]) << ")" << endl;
                            } else
                                cout << "Nu exista cazarea." << endl;
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Optiune invalida" << endl;
                            break;
                    }
                } while (optiune5 != 6);
                break;

            case 12:
                break;
            default:
                cout << "Optiune invalida\n";
                break;
        }
    } while (optiune != 12);


    for (int i = 0; i < camera.size(); i++)
        delete camera[i];
    for (auto it = client.begin(); it != client.end(); it++)
        delete (*it);
    for (int i = 0; i < cazare.size(); i++)
        delete cazare[i];
    for (int i = 0; i < angajat.size(); i++)
        delete angajat[i];
}