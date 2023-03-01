//
// Created by Diana on 2/26/2023.
//

#ifndef PROIECT_EMPTYINPUTFILE_H
#define PROIECT_EMPTYINPUTFILE_H

#include "exception"

using namespace std;

class EmptyInputFile : public exception {
public:
    virtual const char* what() const throw() {

        return "Input file is empty.\n";

    }

};

#endif //PROIECT_EMPTYINPUTFILE_H
