#include "spiel.h"

Spiel::Spiel(QObject *parent) :
    QObject(parent)
{
}

void Spiel::initSpiel(int n)
{
    for (int i=0;i<4;i++)
        fertig[i]=false;
    anDerReihe=gelb;
    anzSpieler=n;
}

void Spiel::starteSpiel()
{
    for (int i=0;i<4;i++)
        fertig[i]=false;
    anDerReihe=gelb;
    emit spiele(anDerReihe);
}

 void Spiel::naechster()
 {
     switch (anDerReihe)
     {
         case gelb: anDerReihe=grun;break;
         case grun: anDerReihe=rot;break;
         case rot: anDerReihe=blau;break;
         case blau: anDerReihe=gelb;break;
         case nichtBelegt: anDerReihe=nichtBelegt;break;
     }
     if (anDerReihe>anzSpieler)
         anDerReihe=gelb;
     emit spiele(anDerReihe);
     emit timerStart();
 }

void Spiel::siegerGefunden()
{
    emit setLabelText(QString("Das Spiel ist vorbei, der Spieler mit der Farbe %1 hat gewonnen").arg(anDerReihe));
}
