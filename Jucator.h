#ifndef JUCATOR_H
#define JUCATOR_H

#include <string>
#include <chrono>
#include "Tabla.h"

class Jucator {
    std::string nume;
    int timpUltimulJoc;

    std::chrono::time_point<std::chrono::steady_clock> timpStart;

    static int recordGlobal;
    static int jocuriJucate;

    void valideazaCoordonate(const Tabla& tabla, int r, int c) const;
    void valideazaActiune(char actiune) const;

public:
    Jucator(const std::string& nume);

    void incepeJoc();
    void terminaJoc(bool castigat);

    // Returneaza: 0 = continua, -1 = explozie, 1 = victorie
    int actioneaza(Tabla& tabla, int r, int c, char actiune);

    static void afiseazaStatistici();
};

#endif