#include "Meniu.h"

int main() {
    Meniu *meniu = Meniu::getInstance();

    meniu->gestionareHotel();

    Meniu::deleteInstance();

    return 0;
}
