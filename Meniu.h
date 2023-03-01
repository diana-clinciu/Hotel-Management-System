//
// Created by Diana on 2/26/2023.
//

#ifndef PROIECT_MENIU_H
#define PROIECT_MENIU_H

#include "iostream"

class Meniu {
private:
    static Meniu *obiect;

    Meniu() {};

    Meniu(const Meniu &m);

    Meniu &operator=(const Meniu &m);

    ~Meniu() {};
public:
    static Meniu *getInstance() {
        if (!obiect)
            obiect = new Meniu();
        return obiect;
    }

    static void deleteInstance() {
        if (obiect)
            delete obiect;
        obiect = NULL;
    }

    void gestionareHotel();
};



#endif //PROIECT_MENIU_H
