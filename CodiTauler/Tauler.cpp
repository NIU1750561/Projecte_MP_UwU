#include "tauler.hpp"
#include <fstream>
#include <sstream>

void Tauler::inicialitza(const string& nomFitxer) {
    ifstream fitxer(nomFitxer);
    string posicio;
    char tipus;

    // Buidem tauler
    for (int i = 0; i < N_FILES; ++i)
        for (int j = 0; j < N_COLUMNES; ++j)
            m_tauler[i][j] = Fitxa();

    while (fitxer >> tipus >> posicio) {
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

bool Tauler::esPosicioValida(int fila, int columna) const {
    return fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES;
}

void Tauler::actualitzaMovimentsValids() {
    for (int i = 0; i < N_FILES; ++i)
        for (int j = 0; j < N_COLUMNES; ++j)
            calculaMovimentsFitxa(i, j);
}

void Tauler::calculaMovimentsFitxa(int f, int c) {
    Fitxa& fitxa = m_tauler[f][c];
    fitxa.buidaMoviments();

    if (fitxa.esBuida()) return;

    if (fitxa.getTipus() == TIPUS_NORMAL)
        calculaMovimentsCapturaNormal(f, c);
    else if (fitxa.getTipus() == TIPUS_DAMA)
        calculaMovimentsDama(f, c);
}
void Tauler::calculaMovimentsCapturaNormal(int f, int c) {
    Fitxa& fitxa = m_tauler[f][c];
    ColorFitxa color = fitxa.getColor();

    int df[] = { -1, -1, 1, 1 };
    int dc[] = { -1, 1, -1, 1 };

    bool capturaPossible = false;

    for (int i = 0; i < 4; ++i) {
        int nf = f + df[i];
        int nc = c + dc[i];
        int ff = f + 2 * df[i];
        int fc = c + 2 * dc[i];

        if (esPosicioValida(ff, fc)) {
            Fitxa& entre = m_tauler[nf][nc];
            Fitxa& desti = m_tauler[ff][fc];

            if (!entre.esBuida() && entre.getColor() != color && desti.esBuida()) {
                Moviment m;
                m.afegeixPosicio(Posicio(ff, fc));
                fitxa.afegeixMovimentValid(m);
                capturaPossible = true;
            }
        }
    }

    // Si no hi ha captures possibles, afegim moviments simples
    if (!capturaPossible) {
        for (int i = 0; i < 4; ++i) {
            int nf = f + df[i];
            int nc = c + dc[i];
            if (esPosicioValida(nf, nc) && m_tauler[nf][nc].esBuida()) {
                Moviment m;
                m.afegeixPosicio(Posicio(nf, nc));
                fitxa.afegeixMovimentValid(m);
            }
        }
    }
}
void Tauler::calculaMovimentsDama(int f, int c) {
    Fitxa& fitxa = m_tauler[f][c];
    ColorFitxa color = fitxa.getColor();

    int df[] = { -1, -1, 1, 1 };
    int dc[] = { -1, 1, -1, 1 };

    for (int dir = 0; dir < 4; ++dir) {
        int nf = f + df[dir];
        int nc = c + dc[dir];

        bool haTrobatRival = false;

        while (esPosicioValida(nf, nc)) {
            Fitxa& desti = m_tauler[nf][nc];

            if (desti.esBuida()) {
                if (!haTrobatRival) {
                    // Moviment simple
                    Moviment m;
                    m.afegeixPosicio(Posicio(nf, nc));
                    fitxa.afegeixMovimentValid(m);
                }
                else {
                    // Moviment de captura (ja hem saltat rival)
                    Moviment m;
                    m.afegeixPosicio(Posicio(nf, nc));
                    fitxa.afegeixMovimentValid(m);
                }
            }
            else {
                if (desti.getColor() == color)
                    break;
                if (!haTrobatRival)
                    haTrobatRival = true;
                else
                    break;  // dues peces rivals no és vàlid
            }

            nf += df[dir];
            nc += dc[dir];
        }
    }
}
void Tauler::eliminaFitxesCapturades(const Posicio& origen, const Posicio& desti) {
    int fOri = origen.getFila();
    int cOri = origen.getColumna();
    int fDes = desti.getFila();
    int cDes = desti.getColumna();

    int df = (fDes - fOri) / max(abs(fDes - fOri), 1);
    int dc = (cDes - cOri) / max(abs(cDes - cOri), 1);

    int nf = fOri + df;
    int nc = cOri + dc;

    while (nf != fDes || nc != cDes) {
        if (!m_tauler[nf][nc].esBuida())
            m_tauler[nf][nc] = Fitxa();  // eliminem peça capturada

        nf += df;
        nc += dc;
    }
}

void Tauler::promocionaSiCal(const Posicio& pos) {
    int f = pos.getFila();
    int c = pos.getColumna();
    Fitxa& fitxa = m_tauler[f][c];

    if (fitxa.getTipus() == TIPUS_NORMAL) {
        if ((fitxa.getColor() == COLOR_BLANC && f == N_FILES - 1) ||
            (fitxa.getColor() == COLOR_NEGRE && f == 0)) {
            fitxa.setTipus(TIPUS_DAMA);
        }
    }
}
bool Tauler::hiHaCapturaPossible(ColorFitxa colorJugador) const {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            const Fitxa& fitxa = m_tauler[i][j];
            if (fitxa.esBuida() || fitxa.getColor() != colorJugador)
                continue;

            for (int k = 0; k < fitxa.getNMoviments(); ++k) {
                const Moviment& m = fitxa.getMoviment(k);
                if (m.getNPosicions() > 0) {
                    int fDif = abs(m.getPosicio(0).getFila() - i);
                    if (fDif >= 2)  // distància 2 o més vol dir captura
                        return true;
                }
            }
        }
    }
    return false;
}
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
    int fOri = origen.getFila();
    int cOri = origen.getColumna();
    int fDes = desti.getFila();
    int cDes = desti.getColumna();

    Fitxa& fitxa = m_tauler[fOri][cOri];

    bool trobat = false;
    bool esCaptura = false;

    for (int i = 0; i < fitxa.getNMoviments(); ++i) {
        const Moviment& m = fitxa.getMoviment(i);
        if (m.getPosicio(0) == desti) {
            trobat = true;

            int fDif = abs(desti.getFila() - fOri);
            if (fDif >= 2)
                esCaptura = true;
            break;
        }
    }

    if (!trobat)
        return false;

    bool obligatCaptura = hiHaCapturaPossible(fitxa.getColor());
    if (obligatCaptura && !esCaptura) {
        // Bufa: eliminem peça perquè no ha fet captura quan tocava
        m_tauler[fOri][cOri] = Fitxa();
        return false;
    }

    m_tauler[fDes][cDes] = fitxa;
    m_tauler[fOri][cOri] = Fitxa();

    if (esCaptura)
        eliminaFitxesCapturades(origen, desti);

    promocionaSiCal(desti);

    return true;
}

string Tauler::toString() const {
    stringstream ss;
    for (int i = N_FILES - 1; i >= 0; --i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            ss << m_tauler[i][j].toChar() << ' ';
        }
        ss << '\n';
    }
    return ss.str();
}
