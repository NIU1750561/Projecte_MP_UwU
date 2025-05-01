#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "Posicio.h"

const int MAX_POSICIONS = 12;

class Moviment {
private:
    Posicio m_posicions[MAX_POSICIONS];
    int m_nPosicions;

public:
    Moviment();

    void afegeixPosicio(const Posicio& pos);
    int getNPosicions() const;
    const Posicio& getPosicio(int index) const;
};

#endif
