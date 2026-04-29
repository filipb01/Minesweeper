#include "Celula.h"

Celula::Celula(int x,int y) : x(x), y(y),descoperita(false),areSteag(false){}

int Celula::dezvaluie() {
    if (areSteag || descoperita)
        return 0;
    descoperita = true;
    return executaDezvaluire();
}
void Celula :: marcheaza() {
    if (!descoperita)
        areSteag = !areSteag;
}

char Celula::getSimbol() const {
    if (areSteag) return 'F';
    if (!descoperita) return '#';
    return executaAfisare();
}
bool Celula::esteDescoperita() const {
    return descoperita;
}
bool Celula::Steag() const {
    return areSteag;
}
//Celula

CelulaNumar::CelulaNumar(int x, int y, int mineVecine) : Celula(x,y),mineVecine(mineVecine){}
std::shared_ptr<Celula> CelulaNumar::clone() const {
    return std::make_shared<CelulaNumar>(*this);
}

int CelulaNumar::executaDezvaluire() { return 1;}
char CelulaNumar::executaAfisare() const {
    return '0' + mineVecine;
}

//CelulaNumar

CelulaMina::CelulaMina(int x, int y) : Celula(x,y) {}
std::shared_ptr<Celula> CelulaMina::clone() const {
    return std::make_shared<CelulaMina>(*this);
}


int CelulaMina::executaDezvaluire() {return -1;}
char CelulaMina::executaAfisare() const {
    return '*';
}

//CelulaMina

CelulaGoala::CelulaGoala(int x,int y) : Celula(x,y){}
std::shared_ptr<Celula> CelulaGoala::clone() const {
    return std::make_shared<CelulaGoala>(*this);
}


int CelulaGoala::executaDezvaluire() {return 2;}
char CelulaGoala::executaAfisare() const {
    return '0';
}
//CelulaGoala