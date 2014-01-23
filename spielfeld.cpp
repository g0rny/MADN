#include "spielfeld.h"

Spielfeld::Spielfeld(QWidget *parent) :
   Feld(parent)
{
}

/**
 * @param _zustaende
 * Der Zustand mit dem das Feld zu ueberspringen.
 */
void Spielfeld::feldUeberspringen(Zustand _zustaende){
    alterZustand=zustaende;
    zustaende=_zustaende;
    setFigur();
    delayBelegen(200);
}
