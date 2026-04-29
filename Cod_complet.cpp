//Pentru review : Olteanu Luca
#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <chrono>
#include <sstream>
#include <vector>
#include <exception>

class Celula {
protected:
    int x,y;
    bool descoperita,areSteag;
public:
    Celula(int x,int y);
    virtual ~Celula() = default;
    virtual std::shared_ptr<Celula> clone() const =0;

    int dezvaluie();
    void marcheaza();

    char getSimbol() const;
    bool esteDescoperita() const;
    bool Steag() const;
private:
    virtual int executaDezvaluire() = 0;
    virtual char executaAfisare() const = 0;
};
//Celula

class CelulaNumar : public Celula {
    int mineVecine;
public:
    CelulaNumar(int x, int y,int mineVecine);
    std::shared_ptr<Celula> clone() const override;

private:
    int executaDezvaluire() override;
    char executaAfisare() const override;
};
//CelulaNumar

class CelulaMina : public Celula {
public:
    CelulaMina(int x,int y);
    std::shared_ptr<Celula> clone() const override;
private:
    int executaDezvaluire() override;
    char executaAfisare() const override;
};
//CelulaMina

class CelulaGoala : public Celula {
public:
    CelulaGoala(int x,int y);
    std::shared_ptr<Celula> clone() const override;
private:
    int executaDezvaluire() override;
    char executaAfisare() const override;
};
//CelulaGoala

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

class EroareMinesweeper : public std::exception {
protected:
    std::string mesaj;
public:
    explicit EroareMinesweeper(const std::string& m);
    const char* what() const noexcept override;
};

class EroareCoordonateOutofBounds : public EroareMinesweeper {
public:
    EroareCoordonateOutofBounds();
};

class EroareComandaInvalida : public EroareMinesweeper {
public:
    EroareComandaInvalida();
};

class EroareActiuneIlegala : public EroareMinesweeper {
public:
    EroareActiuneIlegala();
};

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

int Tabla::getIndex(int r, int c) const {
    return r * coloane + c;
}
std::shared_ptr<Celula> &Tabla::operator()(int r, int c) {
    return tabla[getIndex(r,c)];
}

void Tabla::plaseazaMine() {
    int bombePuse = 0;

    std::random_device rd;//sursa de generare a nr random,bazata pe hardware
    std::mt19937_64 gen(rd()); // algoritmul matematic care foloseste nr de mai sus ca pe un seed(samanta)
    //are stare interna,e un array pe 312 elemente
    std::uniform_int_distribution<int> rand(0,linii - 1); // definim limitele
    std::uniform_int_distribution<int> coloana(0, coloane - 1);

    while (bombePuse < nrBombe) {
        int r = rand(gen);//creeaza un numar aleator folosind gen si il reduce in intervalul precizat
        int c = coloana(gen);

        if ((*this)(r,c) == nullptr) {
            (*this)(r,c) = std::make_shared<CelulaMina>(r,c);
            bombePuse++;
        }
    }
}
void Tabla::calculeazaNumere() {
    for (int r = 0; r < linii; r++)
        for (int c = 0; c < coloane; c++) {
            if ((*this)(r,c) == nullptr)/*daca nu se afla o mina acolo*/ {
                int bombeVecine = 0;
                for (int i = -1; i <= 1; i++)//vecinii se afla pe linia de sus,aceeasi,sau cea de sub(-1,0,+1)
                    for (int j = -1; j <= 1; j++)//analog la coloane
                        if (i+r < linii && i+r >=0 && c+j < coloane && c+j >= 0 && (i!=0 || j!=0)) /*daca e in bounds si nu e acelasi element*/{
                            std::shared_ptr<CelulaMina> dc2 = std::dynamic_pointer_cast<CelulaMina>((*this)(r+i,c+j));//downcast in tip celula mina ca sa vf daca e mina
                            if (dc2 != nullptr) // daca celula de langa e cu mina
                               ++bombeVecine; //crestem nr de mine vecine
                        }
                if (bombeVecine == 0)//daca nu am gasit mine
                    (*this)(r,c) = std::make_shared<CelulaGoala>(r,c);//obiectul devine de tip celula goala
                else
                    (*this)(r,c) =std::make_shared<CelulaNumar>(r,c,bombeVecine);//obiectul devine tip celula numar
            }
        }
}
void swap(Tabla& t1,Tabla& t2) {
    using std::swap;
    swap(t1.coloane,t2.coloane);
    swap(t1.linii,t2.linii);
    swap(t1.nrBombe,t2.nrBombe);
    swap(t1.tabla,t2.tabla);
}

void Tabla::fill(int r,int c) {
    if (r>=0 && r<linii && c>=0 && c<coloane) {
        if ((*this)(r,c)->esteDescoperita() || (*this)(r,c)->Steag())
            return;//daca are steag sau e descoperita,nu incercam sa o dezvaluim si nici nu continuam alg in jurul ei
        (*this)(r,c)->dezvaluie(); // sau tabla[getIndex(r,c)]->dezvaluie();
        std::shared_ptr<CelulaGoala> dc = std::dynamic_pointer_cast<CelulaGoala>((*this)(r,c));
        if (dc != nullptr) {
            fill(r-1,c-1);
            fill(r-1,c);
            fill(r-1,c+1);
            fill(r,c-1);
            fill(r,c+1);
            fill(r+1,c-1);
            fill(r+1,c);
            fill(r+1,c+1);
        }
    }
}

Tabla::Tabla(int linii, int coloane,int nrBombe) : linii(linii), coloane(coloane),
                                                   nrBombe(nrBombe) {
    tabla.resize(linii * coloane,nullptr);
    plaseazaMine();
    calculeazaNumere();
}
Tabla::Tabla(const Tabla& t) : linii(t.linii), coloane(t.coloane),
nrBombe(t.nrBombe) {
    tabla.reserve(t.tabla.size());//alocam spatiu din timp

    for (const auto& cel : t.tabla)
        tabla.push_back(cel->clone());
}
Tabla& Tabla::operator=(const Tabla& t) {
    if (this == &t)
        return *this;
    Tabla copie = t;
    swap(*this,copie);
    return *this;
}

bool Tabla::verificaVictorie() const {
    int celuleAcoperite = 0;

    for (const auto& celula : tabla) {
        if (!celula->esteDescoperita()) {
            celuleAcoperite++;
        }
    }

    return celuleAcoperite == nrBombe;
}

std::ostream &operator<<(std::ostream &os, const Tabla &t) {
    for (int i=0; i < t.coloane * t.linii; i++) {
        os<<t.tabla[i]->getSimbol()<<' ';
        if (!( (i+1)% t.coloane))
            os<<'\n';
    }
    return os;
}

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

int Jucator::recordGlobal = 999999;
int Jucator::jocuriJucate = 0;

Jucator::Jucator(const std::string& nume) : nume(nume), timpUltimulJoc(0) {}

void Jucator::incepeJoc() {
    timpStart = std::chrono::steady_clock::now();
}

void Jucator::terminaJoc(bool castigat) {
    auto stop = std::chrono::steady_clock::now();

    timpUltimulJoc = std::chrono::duration_cast<std::chrono::seconds>(stop - timpStart).count();

    jocuriJucate++;

    if (castigat && timpUltimulJoc < recordGlobal) {
        recordGlobal = timpUltimulJoc;
    }
}

void Jucator::valideazaCoordonate(const Tabla& tabla, int r, int c) const {
    if (r < 0 || r >= tabla.linii || c < 0 || c >= tabla.coloane) {
        throw EroareCoordonateOutofBounds();
    }
}

void Jucator::valideazaActiune(char actiune) const {
    if (actiune != 'D' && actiune != 'd' && actiune != 'M' && actiune != 'm') {
        throw EroareComandaInvalida();
    }
}

int Jucator::actioneaza(Tabla& tabla, int r, int c, char actiune) {
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
void Jucator::afiseazaStatistici() {
    std::cout << "\n=== STATISTICI GLOBALE SESIUNE ===\n";
    std::cout << "Jocuri jucate: " << jocuriJucate << "\n";
    if (recordGlobal != 999999) {
        std::cout << "Record global de timp: " << recordGlobal << " secunde!\n";
    } else {
        std::cout << "Record global: Nicio victorie inregistrata inca.\n";
    }
    std::cout << "==================================\n";
}

int main() {
    std::cout << "Introdu numele tau: ";
    std::string nume;
    std::cin >> nume;

    Jucator jucator1(nume);
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
                    throw EroareComandaInvalida();
                }

                std::string restulLiniei;
                if (ss >> restulLiniei) {
                    throw EroareComandaInvalida();
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
        Jucator::afiseazaStatistici();

        std::cout << "\nVrei sa joci din nou? (Y/N): ";
        std::cin >> raspuns;

    } while (raspuns == 'Y' || raspuns == 'y');

    std::cout << "\nLa revedere, " << nume << "!\n";

    return 0;
}