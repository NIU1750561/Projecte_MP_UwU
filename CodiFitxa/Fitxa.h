#ifndef FITXA_H
#define FITXA_H

#include "Moviment.h"
#include <string>
using namespace std;

typedef enum { TIPUS_NORMAL, TIPUS_DAMA, TIPUS_EMPTY } TipusFitxa;
typedef enum { COLOR_NEGRE, COLOR_BLANC } ColorFitxa;

const int MAX_MOVIMENTS = 50; 

class Fitxa {
private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_nMoviments;

public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);

    void afegeixMovimentValid(const Moviment& moviment);
    void buidaMoviments();
    int getNMoviments() const;
    const Moviment& getMoviment(int index) const;

    bool esBuida() const;
    char toChar() const;
};

#endif
