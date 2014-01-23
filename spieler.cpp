#include "spieler.h"
#include "mainwindow.h"
#include "zustand.h"
#include <iostream>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

/**
 * @param n
 * Die Verzoegerung in Millisekunden
 */
void Spieler::delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Spieler::Spieler(QObject *parent) :
    QObject(parent)
{
}

/**
 * @param i
 * Die Nummer des Spielers, welche die Spielerfarbe festlegt
 */
void Spieler::initSpieler(int i)
{
    anzStartfeld=4;
    anzZielfeld=0;
    startpositionBelegt=false;
    gueltigerZugVorhanden=false;
    darfKlicken=false;
    anzGewurfelt=0;
    switch (i)
    {
    case 0:spielerFarbe=gelb;break;
    case 1:spielerFarbe=grun;break;
    case 2:spielerFarbe=rot;break;
    case 3:spielerFarbe=blau;break;
    }
}

void Spieler::wurfelPhase()
{
    if (anzStartfeld+anzZielfeld==4 && anzGewurfelt<3)
    {
        anzGewurfelt++;
        emit setLabelText(QString("Bitte wuerfeln sie zum %1. mal").arg(anzGewurfelt));
        emit darfWurfeln(true);
    }
    else
    {
        if (anzGewurfelt<1)
        {
            anzGewurfelt++;
            emit setLabelText(QString("Bitte wuerfeln"));
            emit darfWurfeln(true);
        }
        else
            checkPhase();
    }
}

void Spieler::wurfelPhaseKI()
{
    if (anzStartfeld+anzZielfeld==4 && anzGewurfelt<3)
    {
        anzGewurfelt++;
        emit setLabelText(QString("Es wird zum %1. mal gewuerfelt.").arg(anzGewurfelt));
        emit wurfelKI();
    }
    else
    {
        if (anzGewurfelt<1)
        {
            anzGewurfelt++;
            emit setLabelText(QString("Es wird gewuerfelt"));
            emit wurfelKI();
        }
        else
            checkPhaseKI();
    }
}

void Spieler::spiele()
{
    emit wurfelFarbe(spielerFarbe);
    anzGewurfelt=0;
    wurfelPhase();
}

void Spieler::starteKI()
{
    emit darfWurfeln(false);
    anzGewurfelt=0;
    wurfelPhaseKI();
}

/**
 * @param n
 * Die gewürfelte Augenzahl
 */
void Spieler::zugPhase(int n)
{
    augen=n;
    if (startpositionBelegt)
    {
        emit setLabelText(QString("Bitte Startposition frei machen"));
        darfKlicken=true;
    }
    else
    {
        if (anzStartfeld+anzZielfeld!=4)
        {
            if (gueltigerZugVorhanden)
            {
                emit setLabelText(QString("Bitte Figur zum bewegen aussuchen"));
                darfKlicken=true;
            }
            else
            {
                emit setLabelText(QString("Sie können keine Figur bewegen und müssen somit passen."));
                delay(2000);
                checkPhase();
            }
        }
        else
        {
            if (augen!=6 && anzGewurfelt<3)
            {
                emit setLabelText(QString("Keine 6 gewuerfelt! Nochmal..."));
                wurfelPhase();
            }
            else
            {
                if (augen==6)
                {
                    anzGewurfelt=0;
                    darfKlicken=true;
                    emit setLabelText(QString("Bitte eine Figur von einem Startfeld auf die Startposition setzen"));
                }
                else
                {
                    checkPhase();
                }
            }
        }
    }
}

void Spieler::checkPhase()
{
    if (anzZielfeld==4)
    {
        emit gewonnen();
    }
    else
    {
        if (augen==6)
        {
           emit setLabelText(QString("Sie haben eine 6 gewuerfelt und duerfen somit nochmal wuerfeln."));
           anzGewurfelt=0;
           wurfelPhase();
        }
        else
        {
            emit setLabelText(QString("Spieler ist fertig..."));
            emit spielerFertig();
        }
    }
}

void Spieler::checkPhaseKI()
{
    if (anzZielfeld==4)
    {
        delay(2000);
        emit gewonnen();
    }
    else
    {
        if (augen==6)
        {
           emit setLabelText(QString("Sie haben eine 6 gewuerfelt und duerfen somit nochmal wuerfeln."));
           anzGewurfelt=0;
           delay(2000);
           wurfelPhaseKI();
        }
        else
        {
            emit setLabelText(QString("Spieler ist fertig..."));
            delay(2000);
            emit spielerFertig();
        }
    }
}
