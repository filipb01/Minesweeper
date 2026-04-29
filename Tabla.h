#ifndef TABLA_H
#define TABLA_H
#include <vector>
#include <iostream>
#include <memory>
#include "Celula.h"

class Tabla {
    std::vector<std::shared_ptr<Celula>> tabla;
    int nrBombe,coloane,linii;

    int getIndex(int r,int c) const;
    std::shared_ptr<Celula>& operator() (int r, int c);

    void plaseazaMine();
    void calculeazaNumere();
    friend void swap(Tabla& t1,Tabla& t2);

    void fill(int r,int c);

    friend class Jucator;
public:
    Tabla(int linii, int coloane, int nrBombe);
    Tabla(const Tabla& t);
    Tabla& operator=(const Tabla& t);

    bool verificaVictorie() const;

    friend std::ostream& operator<<(std::ostream& os,const Tabla& t);
};

#endif