#ifndef MINESWEEPER_LOGGERJOC_H
#define MINESWEEPER_LOGGERJOC_H

#include <iostream>
#include <string>

class LoggerJoc {
private:
    //constructorul este privat pentru a impiedica instantierea din exterior
    LoggerJoc() {
        std::cout << "[SISTEM] Logger initializat.\n";
    }

public:
    //stergem constructorul de copiere si operatorul de atribuire
    LoggerJoc(const LoggerJoc&) = delete;
    LoggerJoc& operator=(const LoggerJoc&) = delete;

    static LoggerJoc& getInstance() {
        static LoggerJoc instanta; // Se creeaza o singura data pt ca e static
        return instanta;
    }

    void log(const std::string& mesaj) {
        std::cout << "[LOG]: " << mesaj << "\n";
    }

    void logEroare(const std::string& mesaj) {
        std::cout << "[EROARE]: " << mesaj << "\n";
    }
};

#endif