#include "Tauler.h"
#include <fstream>
#include <sstream>

void Tauler::inicialitza(const string& nomFitxer) 
{
    ifstream fitxer(nomFitxer);
    string posicio;
    char tipus;

    // Buidem el tauler
    for (int i = 0; i < N_FILES; ++i)
        for (int j = 0; j < N_COLUMNES; ++j)
            m_tauler[i][j] = Fitxa();

    while (fitxer >> tipus >> posicio) 
    {
        Posicio p(posicio);
        int f = p.getFila();
        int c = p.getColumna();

        TipusFitxa tf;
        ColorFitxa cf;

        if (tipus == 'O') { tf = TIPUS_NORMAL; cf = COLOR_BLANC; }
        else if (tipus == 'X') { tf = TIPUS_NORMAL; cf = COLOR_NEGRE; }
        else if (tipus == 'D') { tf = TIPUS_DAMA; cf = COLOR_BLANC; }
        else if (tipus == 'R') { tf = TIPUS_DAMA; cf = COLOR_NEGRE; }

        m_tauler[f][c] = Fitxa(tf, cf);
    }
}

bool Tauler::esPosicioValida(int fila, int columna) const 
{
    return fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES;
}

void Tauler::calculaMovimentsFitxa(int f, int c) 
{
    Fitxa& fitxa = m_tauler[f][c];
    fitxa.buidaMoviments();

    if (fitxa.esBuida())
        return;

    int df[] = { -1, -1, 1, 1 };
    int dc[] = { -1, 1, -1, 1 };

    for (int i = 0; i < 4; ++i) 
    {
        int nf = f + df[i];
        int nc = c + dc[i];
        if (esPosicioValida(nf, nc) && m_tauler[nf][nc].esBuida()) 
        {
            Moviment m;
            m.afegeixPosicio(Posicio(nf, nc));
            fitxa.afegeixMovimentValid(m);
        }
    }
}

void Tauler::actualitzaMovimentsValids() 
{
    for (int i = 0; i < N_FILES; ++i)
        for (int j = 0; j < N_COLUMNES; ++j)
            calculaMovimentsFitxa(i, j);
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) 
{
    int f = origen.getFila();
    int c = origen.getColumna();

    Fitxa& fitxa = m_tauler[f][c];
    nPosicions = 0;

    for (int i = 0; i < fitxa.getNMoviments(); ++i) 
    {
        const Moviment& m = fitxa.getMoviment(i);
        for (int j = 0; j < m.getNPosicions(); ++j) 
        {
            posicionsPossibles[nPosicions] = m.getPosicio(j);
            nPosicions++;
        }
    }
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) 
{
    int fOri = origen.getFila();
    int cOri = origen.getColumna();
    int fDes = desti.getFila();
    int cDes = desti.getColumna();

    Fitxa& fitxa = m_tauler[fOri][cOri];

    bool trobat = false;
    for (int i = 0; i < fitxa.getNMoviments(); ++i) 
    {
        const Moviment& m = fitxa.getMoviment(i);
        if (m.getPosicio(0) == desti) 
        {
            trobat = true;
            break;
        }
    }

    if (!trobat)
        return false;

    m_tauler[fDes][cDes] = fitxa;
    m_tauler[fOri][cOri] = Fitxa();
    return true;
}

string Tauler::toString() const 
{
    stringstream ss;
    for (int i = N_FILES - 1; i >= 0; --i) 
    {
        for (int j = 0; j < N_COLUMNES; ++j) 
        {
            ss << m_tauler[i][j].toChar() << ' ';
        }
        ss << '\n';
    }
    return ss.str();
}