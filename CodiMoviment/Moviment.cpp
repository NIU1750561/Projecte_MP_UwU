#include "Moviment.h"

Moviment::Moviment() : m_nPosicions(0) {}

void Moviment::afegeixPosicio(const Posicio& pos) {
    if (m_nPosicions < MAX_POSICIONS) {
        m_posicions[m_nPosicions] = pos;
        m_nPosicions++;
    }
}

int Moviment::getNPosicions() const {
    return m_nPosicions;
}

const Posicio& Moviment::getPosicio(int index) const {
    return m_posicions[index];
}
