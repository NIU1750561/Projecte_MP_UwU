#include "Fitxa.h"

// Constructor per defecte: fitxa buida
Fitxa::Fitxa() 
{
    m_tipus = TIPUS_EMPTY;
    m_numMoviments = 0;
    // m_color no cal inicialitzar si és empty
}

// Constructor amb paràmetres
Fitxa::Fitxa(ColorFitxa color, TipusFitxa tipus) 
{
    m_color = color;
    m_tipus = tipus;
    m_numMoviments = 0;
}

// Getters
TipusFitxa Fitxa::getTipus() const 
{
    return m_tipus;
}

ColorFitxa Fitxa::getColor() const 
{
    return m_color;
}

bool Fitxa::esBuida() const 
{
    return m_tipus == TIPUS_EMPTY;
}

bool Fitxa::esDama() const 
{
    return m_tipus == TIPUS_DAMA;
}

// Setters
void Fitxa::setTipus(TipusFitxa tipus) 
{
    m_tipus = tipus;
}

void Fitxa::setColor(ColorFitxa color) 
{
    m_color = color;
}

// Conversió a dama
void Fitxa::convertirEnDama() 
{
    if (m_tipus == TIPUS_NORMAL) 
    {
        m_tipus = TIPUS_DAMA;
    }
}

// Moviments vàlids
void Fitxa::afegeixMovimentValid(const Moviment& mov) 
{
    if (m_numMoviments < MAX_MOVIMENTS) 
    {
        m_movimentsValids[m_numMoviments] = mov;
        m_numMoviments++;
    }
}

void Fitxa::netejaMoviments() 
{
    m_numMoviments = 0;
}

int Fitxa::getNumMoviments() const 
{
    return m_numMoviments;
}

Moviment Fitxa::getMoviment(int i) const 
{
    if (i >= 0 && i < m_numMoviments) 
    {
        return m_movimentsValids[i];
    }
    // Retornem moviment buit si l'índex no és vàlid
    return Moviment();
}