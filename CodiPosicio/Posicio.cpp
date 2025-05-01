#include "Posicio.h"

Posicio::Posicio() : m_fila(0), m_columna(0) {}
Posicio::Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}

Posicio::Posicio(const string& posicio) 
{
    m_columna = posicio[0] - 'a';
    m_fila = posicio[1] - '1';
}

int Posicio::getFila() const { return m_fila; }
int Posicio::getColumna() const { return m_columna; }

void Posicio::setFila(int fila) { m_fila = fila; }
void Posicio::setColumna(int columna) { m_columna = columna; }

string Posicio::toString() const 
{
    string s;
    s += ('a' + m_columna);
    s += ('1' + m_fila);
    return s;
}

bool Posicio::operator==(const Posicio& altra) const 
{
    return m_fila == altra.m_fila && m_columna == altra.m_columna;
}