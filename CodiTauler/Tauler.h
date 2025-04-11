#ifndef TAULER_H
#define TAULER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Fitxa.h"
#include "Posicio.h"

using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Tauler 
{
private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    // Inicialitza des de fitxer
    void inicialitza(const string& nomFitxer);

    // Actualitza moviments vàlids per totes les peces
    void actualitzaMovimentsValids();

    // Retorna les posicions possibles de moviment per una posició origen
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);

    // Mou la fitxa si el moviment és vàlid
    bool mouFitxa(const Posicio& origen, const Posicio& desti);

    // Retorna un string amb l’estat del tauler
    string toString() const;
};

#endif