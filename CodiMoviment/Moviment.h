#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <iostream>
#include "Posicio.h"

using namespace std;

const int MAX_POSICIONS = 10;
const int MAX_MENJADES = 10;

class Moviment 
{
private:
    Posicio m_posicions[MAX_POSICIONS];
    int m_numPosicions;

    Posicio m_fitxesMenjades[MAX_MENJADES];
    int m_numFitxesMenjades;

public:
    // Constructor
    Moviment();

    // Afegir passos
    void afegeixPas(const Posicio& pos);
    void afegeixFitxaMenjada(const Posicio& pos);

    // Getters
    int getNumPosicions() const;
    int getNumFitxesMenjades() const;

    Posicio getPas(int i) const;
    Posicio getFitxaMenjada(int i) const;

    Posicio getOrigen() const;
    Posicio getDesti() const;
};

#endif