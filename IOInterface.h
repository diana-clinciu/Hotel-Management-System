//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_IOINTERFACE_H
#define PROIECT_IOINTERFACE_H

using namespace std;

class IOInterface {
public:
    // virtualizarea citirii si a afisarii
    virtual istream &citire(istream &in) = 0;

    virtual ostream &afisare(ostream &out) const = 0;
};


#endif //PROIECT_IOINTERFACE_H
