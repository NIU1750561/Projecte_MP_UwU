#include "Fitxa.h"

Fitxa::Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC), m_nMoviments(0) {}

Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color)
    : m_tipus(tipus), m_color(color), m_nMoviments(0) {
}

TipusFitxa Fitxa::getTipus() const { return m_tipus; }
ColorFitxa Fitxa::getColor() const { return m_color; }

void Fitxa::setTipus(TipusFitxa tipus) { m_tipus = tipus; }
void Fitxa::setColor(ColorFitxa color) { m_color = color; }

void Fitxa::afegeixMovimentValid(const Moviment& moviment) {
    if (m_nMoviments < MAX_MOVIMENTS) {
        m_movimentsValids[m_nMoviments] = moviment;
        m_nMoviments++;
    }
}

void Fitxa::buidaMoviments() { m_nMoviments = 0; }

int Fitxa::getNMoviments() const { return m_nMoviments; }

const Moviment& Fitxa::getMoviment(int index) const {
    return m_movimentsValids[index];
}

bool Fitxa::esBuida() const {
    return m_tipus == TIPUS_EMPTY;
}

char Fitxa::toChar() const {
    if (m_tipus == TIPUS_EMPTY)
        return '-';
    if (m_tipus == TIPUS_NORMAL)
        return (m_color == COLOR_BLANC) ? 'O' : 'X';
    if (m_tipus == TIPUS_DAMA)
        return (m_color == COLOR_BLANC) ? 'D' : 'R';
    return '?';
}
