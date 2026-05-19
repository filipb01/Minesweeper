// #include "Jucator.h"
// #include "Exceptii.h"
// #include <iostream>

// int Jucator::recordGlobal = 999999;
// int Jucator::jocuriJucate = 0;
//
// Jucator::Jucator(const std::string& nume) : nume(nume), timpUltimulJoc(0) {}
//
// void Jucator::incepeJoc() {
//     timpStart = std::chrono::steady_clock::now();
// }
//
// void Jucator::terminaJoc(bool castigat) {
//     auto stop = std::chrono::steady_clock::now();
//
//     timpUltimulJoc = std::chrono::duration_cast<std::chrono::seconds>(stop - timpStart).count();
//
//     jocuriJucate++;
//
//     if (castigat && timpUltimulJoc < recordGlobal) {
//         recordGlobal = timpUltimulJoc;
//     }
// }
//
// void Jucator::valideazaCoordonate(const Tabla& tabla, int r, int c) {
//     if (r < 0 || r >= tabla.linii || c < 0 || c >= tabla.coloane) {
//         throw EroareCoordonateOutofBounds();
//     }
// }
//
// void Jucator::valideazaActiune(char actiune) {
//     if (actiune != 'D' && actiune != 'd' && actiune != 'M' && actiune != 'm') {
//         throw EroareComandaInvalida();
//     }
// }
//
// int Jucator::actioneaza(Tabla& tabla, int r, int c, char actiune) {
//     valideazaCoordonate(tabla, r, c);
//     valideazaActiune(actiune);
//
//     auto& celula = tabla(r, c);
//
//     if (actiune == 'M' || actiune == 'm') {
//         if (celula->esteDescoperita()) {
//             throw EroareActiuneIlegala();
//         }
//         celula->marcheaza();
//         return 0;
//     }
//     else {
//         if (celula->esteDescoperita() || celula->Steag()) {
//             throw EroareActiuneIlegala();
//         }
//         std::shared_ptr<CelulaGoala> dc = std::dynamic_pointer_cast<CelulaGoala>(celula);
//         if (dc != nullptr)
//             tabla.fill(r,c);
//
//         int rezultat = celula->dezvaluie();
//
//         if (rezultat == -1) return -1; // Mină
//
//         return 0;
//     }
// }
// void Jucator::afiseazaStatistici() {
//     std::cout << "\n=== STATISTICI GLOBALE SESIUNE ===\n";
//     std::cout << "Jocuri jucate: " << jocuriJucate << "\n";
//     if (recordGlobal != 999999) {
//         std::cout << "Record global de timp: " << recordGlobal << " secunde!\n";
//     } else {
//         std::cout << "Record global: Nicio victorie inregistrata inca.\n";
//     }
//     std::cout << "==================================\n";
// }