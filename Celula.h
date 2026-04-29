#ifndef CELULA_H
#define CELULA_H
#include <memory>

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
#endif