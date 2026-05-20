#include "Tabla.h"
#include "CelulaFactory.h"
#include <random>

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
            (*this)(r,c) = CelulaFactory::creazaCelula(CelulaFactory::Tip::Mina,r,c);
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
                    (*this)(r,c) = CelulaFactory::creazaCelula(CelulaFactory::Tip::Goala,r,c);//obiectul devine de tip celula goala
                else
                    (*this)(r,c) =CelulaFactory::creazaCelula(CelulaFactory::Tip::Numar,r,c,bombeVecine);//obiectul devine tip celula numar
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
