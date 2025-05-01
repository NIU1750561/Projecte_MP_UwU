#ifndef POSICIO_H
#define POSICIO_H

#include <string>
using namespace std;

class Posicio 
{

private:
    int m_fila;
    int m_columna;

public:
    Posicio();
    Posicio(int fila, int columna);
    Posicio(const string& posicio);

    int getFila() const;
    int getColumna() const;

    void setFila(int fila);
    void setColumna(int columna);

    string toString() const;

    bool operator==(const Posicio& altra) const;
};

#endif