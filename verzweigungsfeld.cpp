#include "verzweigungsfeld.h"

Verzweigungsfeld::Verzweigungsfeld(QWidget *parent) :
    Spielfeld(parent)
{
}
/**
 * @return
 * Liefert next zurueck und ueberschreibt getNext() von Feld,
 * da Verzweigungsfelder zwei Faelle betrachten.
 */
int Verzweigungsfeld::getNext(){
    if(farbe==zustaende || farbe==pseudoZustand)
        return 0;
    else
        return next;
}

