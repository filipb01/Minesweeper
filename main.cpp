#include <iostream>
#include <string>
#include <sstream>
#include "Tabla.h"
#include "Jucator.h"
#include "Exceptii.h"

int main() {
    std::cout << "Introdu numele tau: ";
    std::string nume;
    std::cin >> nume;

    Jucator<int> jucator1(nume);//int => fara zecimale
    char raspuns;

    do {
        Tabla joc(5, 5, 3);

        jucator1.incepeJoc();
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
                    std::cout << "\nBOOM! Ai lovit o mina! Jocul s-a terminat.\n";
                } else {
                    if (joc.verificaVictorie()) {
                        victorie = true;
                        std::cout << "\nFELICITARI " << nume << "! Ai gasit toate minele!\n";
                    }
                }

            }
            catch (const EroareMinesweeper& e) {
                std::cout << "\n[!] " << e.what() << " Incearca din nou!\n";
            }
            catch (const std::exception& e) {
                std::cout << "\nEroare de sistem: " << e.what() << "\n";
            }
        }

        std::cout << "\nTABLA FINALA:\n" << joc << "\n";

        jucator1.terminaJoc(victorie);
        Jucator<int>::afiseazaStatistici();

        std::cout << "\nVrei sa joci din nou? (Y/N): ";
        std::cin >> raspuns;

    } while (raspuns == 'Y' || raspuns == 'y');

    std::cout << "\nLa revedere, " << nume << "!\n";

    return 0;
}