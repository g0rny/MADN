#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::spielInit(int anzSpieler,bool n)
{
    madn->initSpiel(anzSpieler);
    if (lokal && !n)
    {
        for (int i=0;i<4;i++)
            disconnect (user[i], SIGNAL(spielerFertig()),madn, SLOT(naechster()));
        disconnect (madn, SIGNAL(spiele(Zustand)), this, SLOT(spiele(Zustand)));
        lokal=false;
    }
    if (!lokal && n)
    {
        lokal=true;
        for (int i=0;i<4;i++)
            connect (user[i], SIGNAL(spielerFertig()),madn, SLOT(naechster()));
        connect (madn, SIGNAL(spiele(Zustand)), this, SLOT(spiele(Zustand)));
    }
}

