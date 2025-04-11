#ifndef FITXA_H
#define FITXA_H

#include <iostream>
#include "Posicio.h"
#include "Moviment.h"

using namespace std;

const int MAX_MOVIMENTS = 10;

typedef enum 
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY

} TipusFitxa;

typedef enum 
{
    COLOR_NEGRE,
    COLOR_BLANC

} ColorFitxa;

class Fitxa
{
private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;

    Moviment m_movimentsValids[MAX_MOVIMENTS];

    int m_numMoviments;

public:
    // Constructors
    Fitxa(); // Fitxa buida
    Fitxa(ColorFitxa color, TipusFitxa tipus);

    // Getters
    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;

    bool esBuida() const;
    bool esDama() const;

    // Setters
    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);

    // Gestió moviments
    void afegeixMovimentValid(const Moviment& mov);
    void netejaMoviments();

    int getNumMoviments() const;

    Moviment getMoviment(int i) const;

    // Conversió a dama
    void convertirEnDama();
};

#endif