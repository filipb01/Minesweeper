#ifndef EXCEPTII_H
#define EXCEPTII_H
#include <exception>
#include <string>

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

#endif