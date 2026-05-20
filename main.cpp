#include <iostream>
#include <string>
#include <sstream>
#include "Tabla.h"
#include "Jucator.h"
#include "Exceptii.h"
#include "LoggerJoc.h"

int main() {
    std::cout << "Introdu numele tau: ";
    std::string nume;
    std::cin >> nume;

    Jucator<float> jucator1(nume);//int => fara zecimale | float => cu zecimale
    char raspuns;

    do {
        Tabla joc(5, 5, 3);

        jucator1.incepeJoc();
        LoggerJoc::getInstance().log("O noua sesiune de Minesweeper a inceput!");
        bool gameOver = false;
        bool victorie = false;

        while (!gameOver && !victorie) {
            std::cout << "\n" << joc << "\n";
            std::cout << "Introdu Randul, Coloana si Actiunea (D=Dezvaluie, M=Steag) (ex: 2 3 D): ";

            std::string linieInput;
            std::getline(std::cin >> std::ws, linieInput);

            try {
                std::stringstream ss(linieInput);
                int r, c;
                char actiune;

                if (!(ss >> r >> c >> actiune)) {
                    throw EroareFormatGresit();
                }

                std::string restulLiniei;
                if (ss >> restulLiniei) {
                    throw EroareFormatGresit();
                }

                int stare = jucator1.actioneaza(joc, r, c, actiune);

                if (stare == -1) {
                    gameOver = true;
                    LoggerJoc::getInstance().log("Jucatorul a lovit o mina. Game Over.");
                } else {
                    if (joc.verificaVictorie()) {
                        victorie = true;
                        std::cout << "\nFELICITARI " << nume << "! Ai gasit toate minele!\n";
                    }
                }

            }
            catch (const EroareMinesweeper& e) {
                LoggerJoc::getInstance().logEroare(e.what());
            }
            catch (const std::exception& e) {
                LoggerJoc::getInstance().logEroare(e.what());
            }
        }

        std::cout << "\nTABLA FINALA:\n" << joc << "\n";

        jucator1.terminaJoc(victorie);
        jucator1.afiseazaStatistici();

        std::cout << "\nVrei sa joci din nou? (Y/N): ";
        std::cin >> raspuns;

    } while (raspuns == 'Y' || raspuns == 'y');

    std::cout << '\n' << jucator1 << "!\n";

    return 0;
}