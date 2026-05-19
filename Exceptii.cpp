#include "Exceptii.h"

EroareMinesweeper::EroareMinesweeper(const std::string& m) : mesaj(m) {}

const char* EroareMinesweeper::what() const noexcept {
    return mesaj.c_str();
}

EroareCoordonateOutofBounds::EroareCoordonateOutofBounds()
    : EroareMinesweeper("Eroare: Coordonatele introduse sunt in afara tablei de joc!") {}

EroareComandaInvalida::EroareComandaInvalida()
    : EroareMinesweeper("Eroare: Comanda necunoscuta. Folositi doar 'D' pentru dezvaluire sau 'M' pentru marcaj.") {}

EroareActiuneIlegala::EroareActiuneIlegala()
    : EroareMinesweeper("Eroare: Actiune respinsa. Celula este deja descoperita sau marcata cu steag.") {}

EroareFormatGresit::EroareFormatGresit()
    : EroareMinesweeper("Eroare: Formatul este incorect,va rugam sa introduceti 2 numere si o litera separate prin spatii."){}
