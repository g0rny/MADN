#include "wurfel.h"
#include "spiel.h"
#include "zustand.h"
#include <cmath>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>


Wurfel::Wurfel(QWidget *parent) :
    QLabel(parent)
{
    augen=0;
    darfWurfeln=false;
}

/**
 * @param n
 * Anzahl der Millisekunden um die verzögert werden soll
 */
void Wurfel::delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/**
 * @param p
 * Die gewürfelte Augenzahl
 */
void Wurfel::setzeBild(int p)
{
    switch(p)
    {
    case 1: switch(spielerFarbe)
        {
        case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb1.svg"))); break;
        case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun1.svg"))); break;
        case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau1.svg"))); break;
        case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot1.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 2: switch(spielerFarbe)
        {
        case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb2.svg"))); break;
        case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun2.svg"))); break;
        case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau2.svg"))); break;
        case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot2.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 3: switch(spielerFarbe)
        {
        case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb3.svg"))); break;
        case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun3.svg"))); break;
        case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau3.svg"))); break;
        case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot3.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 4: switch(spielerFarbe)
        {
        case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb4.svg"))); break;
        case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun4.svg"))); break;
        case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau4.svg"))); break;
        case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot4.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 5: switch(spielerFarbe)
        {
        case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb5.svg"))); break;
        case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun5.svg"))); break;
        case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau5.svg"))); break;
        case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot5.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 6: switch(spielerFarbe)
        {
        case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb6.svg"))); break;
        case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun6.svg"))); break;
        case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau6.svg"))); break;
        case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot6.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    }
}

int Wurfel::wurfeln()
{
    alteAugen=vorlaeufigeAugen;
    while(vorlaeufigeAugen==alteAugen)
       vorlaeufigeAugen=((rand()%6)+1) ;
    setzeBild(vorlaeufigeAugen);
    return (vorlaeufigeAugen);
}

void Wurfel::sechs()
{
    if (darfWurfeln)
    {
        darfWurfeln=false;
        augen=6;
        setzeBild(augen);
        emit zugPhase(augen);
    }
}

void Wurfel::mousePressEvent(QMouseEvent *ev)
{   /*Verhindert eine unschöne Warnung beim kompilieren. Es wird bemängelt,
      dass ev nicht genutzt wird. Aber ohne ev funktioniert das QMouseEvent nicht.*/
    ev=ev;
    if (darfWurfeln)
    {
        darfWurfeln=false;
        emit wurfelPressed(wurfeln(),0);
        augen=vorlaeufigeAugen;
        emit habeGewurfelt(augen);
        delay(150);
        emit wurfelPressed(wurfeln(),1);
        delay(150);
        emit wurfelPressed(wurfeln(),2);
        delay(150);
        emit wurfelPressed(wurfeln(),3);
        delay(150);
        emit wurfelPressed(wurfeln(),4);
        delay(150);
        emit wurfelPressed(wurfeln(),3);
        delay(250);
        emit wurfelPressed(wurfeln(),2);
        delay(350);
        emit wurfelPressed(augen,1);
        setzeBild(augen);
        emit zugPhase(augen);
    }
}

/**
 * @param farbe
 * Das ist die übermittelte Spielerfarbe
 */
void Wurfel::setzeFarbe(Zustand farbe)
{
    spielerFarbe=farbe;
    switch(farbe)
    {
    case gelb:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb.svg"))); break;
    case grun:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun.svg")));break;
    case rot:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot.svg")));break;
    case blau:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau.svg")));break;
    case nichtBelegt:this->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/wurfel.svg")));break;
    }
}

/**
 * @param n
 * Das vorgegebene Endergebniss des Würfelvorgangs
 */
void Wurfel::hatGewurfelt(int n)
{
    emit wurfelPressed(wurfeln(),0);
    delay(200);
    emit wurfelPressed(wurfeln(),1);
    delay(200);
    emit wurfelPressed(wurfeln(),2);
    delay(300);
    emit wurfelPressed(wurfeln(),3);
    delay(300);
    emit wurfelPressed(wurfeln(),4);
    delay(300);
    emit wurfelPressed(wurfeln(),3);
    delay(500);
    emit wurfelPressed(wurfeln(),2);
    delay(1000);
    emit wurfelPressed(n,1);
}

void Wurfel::wurfelKI()
{
    emit wurfelPressed(wurfeln(),0);
    augen=vorlaeufigeAugen;
    emit habeGewurfelt(augen);
    delay(150);
    emit wurfelPressed(wurfeln(),1);
    delay(150);
    emit wurfelPressed(wurfeln(),2);
    delay(150);
    emit wurfelPressed(wurfeln(),3);
    delay(150);
    emit wurfelPressed(wurfeln(),4);
    delay(150);
    emit wurfelPressed(wurfeln(),3);
    delay(250);
    emit wurfelPressed(wurfeln(),2);
    delay(350);
    emit wurfelPressed(augen,1);
    setzeBild(augen);
    delay(2000);
    emit zugPhaseKI();
}
