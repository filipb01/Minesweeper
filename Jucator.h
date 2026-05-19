#ifndef JUCATOR_H
#define JUCATOR_H

#include <string>
#include <chrono>
#include "Tabla.h"
#include "Exceptii.h"
#include <iostream>

template <typename T>
class Jucator {
    std::string nume;
    T timpUltimulJoc;

    std::chrono::time_point<std::chrono::steady_clock> timpStart;

    static T recordGlobal;
    static int jocuriJucate;

    static void valideazaCoordonate(const Tabla& tabla, int r, int c) ;
    static void valideazaActiune(char actiune);

public:
    Jucator(const std::string& nume);

    void incepeJoc();
    void terminaJoc(bool castigat);

    // Returneaza: 0 = continua, -1 = explozie, 1 = victorie
    static int actioneaza(Tabla& tabla, int r, int c, char actiune);

    static void afiseazaStatistici();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,const Jucator<U>& j);
};
template <typename T>
T Jucator<T>::recordGlobal = 999999;

template <typename T>
int Jucator<T>::jocuriJucate = 0;

template <typename T>
Jucator<T>::Jucator(const std::string& nume) : nume(nume), timpUltimulJoc(0) {}

template <typename T>
void Jucator<T>::incepeJoc() {
    timpStart = std::chrono::steady_clock::now();
}

template <typename T>
void Jucator<T>::terminaJoc(bool castigat) {
    auto stop = std::chrono::steady_clock::now();

    timpUltimulJoc = std::chrono::duration_cast<std::chrono::duration<T>>(stop - timpStart).count();

    jocuriJucate++;

    if (castigat && timpUltimulJoc < recordGlobal) {
        recordGlobal = timpUltimulJoc;
    }
}

template <typename T>
void Jucator<T>::valideazaCoordonate(const Tabla& tabla, int r, int c) {
    if (r < 0 || r >= tabla.linii || c < 0 || c >= tabla.coloane) {
        throw EroareCoordonateOutofBounds();
    }
}

template <typename T>
void Jucator<T>::valideazaActiune(char actiune) {
    if (actiune != 'D' && actiune != 'd' && actiune != 'M' && actiune != 'm') {
        throw EroareComandaInvalida();
    }
}

template <typename T>
int Jucator<T>::actioneaza(Tabla& tabla, int r, int c, char actiune) {
    valideazaCoordonate(tabla, r, c);
    valideazaActiune(actiune);

    auto& celula = tabla(r, c);

    if (actiune == 'M' || actiune == 'm') {
        if (celula->esteDescoperita()) {
            throw EroareActiuneIlegala();
        }
        celula->marcheaza();
        return 0;
    }
    else {
        if (celula->esteDescoperita() || celula->Steag()) {
            throw EroareActiuneIlegala();
        }
        std::shared_ptr<CelulaGoala> dc = std::dynamic_pointer_cast<CelulaGoala>(celula);
        if (dc != nullptr)
            tabla.fill(r,c);

        int rezultat = celula->dezvaluie();

        if (rezultat == -1) return -1; // Mină

        return 0;
    }
}

template <typename T>
void Jucator<T>::afiseazaStatistici() {
    std::cout << "\n=== STATISTICI GLOBALE SESIUNE ===\n";
    std::cout << "Jocuri jucate: " << jocuriJucate << "\n";
    if (recordGlobal != 999999) {
        std::cout << "Record global de timp: " << recordGlobal << " secunde!\n";
    } else {
        std::cout << "Record global: Nicio victorie inregistrata inca.\n";
    }
    std::cout << "==================================\n";
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Jucator<U>& j) {
    os<<"Jucator: "<< j.nume << " | Timp ultim joc: " << j.timpUltimulJoc;
    return os;
}

#endif