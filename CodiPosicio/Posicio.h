#ifndef POSICIO_H
#define POSICIO_H

#include <iostream>
#include <string>

using namespace std;

class Posicio 
{
private:
    int m_fila;    // 0 a 7
    int m_columna; // 0 a 7

public:
    // Constructors
    Posicio();
    Posicio(int fila, int columna);
    Posicio(const string& posicioStr); // Ex: "b2"

    // Getters
    int getFila() const;
    int getColumna() const;

    // Setters
    void setFila(int fila);
    void setColumna(int columna);

    // Conversió a string (ex: "a1")
    string toString() const;

    // Operador ==
    bool operator==(const Posicio& altre) const;
};

#endif