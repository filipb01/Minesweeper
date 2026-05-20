#ifndef MINESWEEPER_CELULAFACTORY_H
#define MINESWEEPER_CELULAFACTORY_H

class CelulaFactory {
public:
    enum class Tip {Mina,Goala,Numar};//set de valori predeterminate,folosite pt creare

    static std::shared_ptr<Celula> creazaCelula(Tip tip,int r,int c,int mineVecine = 0) {
        if (tip == Tip::Mina)
            return std::make_shared<CelulaMina>(r,c);
        if (tip == Tip::Goala)
            return std::make_shared<CelulaGoala>(r,c);
        if (tip == Tip::Numar)
            return std::make_shared<CelulaNumar>(r,c,mineVecine);
        return nullptr;
    }
};

#endif