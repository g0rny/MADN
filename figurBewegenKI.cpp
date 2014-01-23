#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <iostream>

/*void MainWindow::zugPhaseKI(int n)
{
    bool kannSpielen=gueltigerZugVorhanden(n,madn->getAnDerReihe());
    user[(madn->getAnDerReihe())-1]->setGueltigerZugVorhanden(kannSpielen);
    user[(madn->getAnDerReihe())-1]->zugPhaseKI(n);
}*/

/**Die Regeln besagen: Sofern die Startposition belegt ist, muss man diese "frei"
  *machen. Es sei denn eine eigene Figur verhindert das(Man hat eine Zahl gewürfelt
  *mit der man sich selbst schmeissen würde, was den Regeln nach aber nicht erlaubt ist).
  *Dies wird hier überprüft*/
/**Wenn eine Figur außerhalb der Startfeldern ist und man sie theoretisch bewegen kann,
  *geht es hier weiter(im weiteren Verlauf "normales Szenario" genannt).*/
/**Hier wird geprüft, ob man mit der ermittelten Augenzahl überhaupt einen Zug
  *beim normalen Szenario machen kann. Ansonsten wird gepasst.*/
/**Ist keine Figur auf der Startposition, kein normales Szenario vorhanden, hat man
  *noch nicht 3 mal gewürfelt und beim letzten würfeln keine 6 bekommen , darf
  *man nochmal würfeln. Dies wird hier überprüft. */
/**Hat man eine 6 gewürfelt, ist keine Figur auf der Startposition und kein
  *normales Szenario vorhanden, muss man eine Figur auf die Startposition gesetzt*/

void MainWindow::zugPhaseKI()
{
    Zustand amZug=madn->getAnDerReihe();
    int augen=ui->hauptwurfel->getAugen();
    user[amZug-1]->setzeAugen(augen);
    if (user[amZug-1]->getStartpositionBelegt())
    {
        ui->label->setText(QString("Startposition wird versucht frei zu machen."));
        startpositionFreiMachenKI();
    }
    else
    {
        if (user[amZug-1]->getAnzStartfeld()+user[amZug-1]->getAnzZielfeld()!=4)
        {
            if (gueltigerZugVorhanden(augen,amZug))
            {
                ui->label->setText(QString("Figur wird bewegt."));
                normalesSzenarioKI();
            }
            else
            {
                ui->label->setText(QString("Es gibt leider keinen moeglichen Zug."));
                delay(2000);
                user[amZug-1]->checkPhaseKI();
            }
        }
        else
        {
            if (augen!=6 && user[amZug-1]->getAnzGewurfelt()<3)
            {
                ui->label->setText(QString("Keine 6 gewuerfelt! Nochmal..."));
                user[amZug-1]->wurfelPhaseKI();
            }
            else
            {
                if (augen==6)
                {
                    user[amZug-1]->setAnzGewurfelt(0);
                    ui->label->setText(QString("Eine Figur wird von einem Startfeld auf die Startposition gesetzt."));
                    startpositionBelegenKI();
                }
                else
                {
                    ui->label->setText(QString("Es gibt leider keinen moeglichen Zug."));
                    delay(2000);
                    user[amZug-1]->checkPhaseKI();
                }
            }
        }
    }
}

void MainWindow::startpositionFreiMachenKI()
{
    int i,next,augen=ui->hauptwurfel->getAugen();
    switch (madn->getAnDerReihe())
    {
    case gelb: i=1;break;
    case grun: i=11;break;
    case rot: i=21;break;
    case blau: i=31;break;
    case nichtBelegt: i=0;break;
    }
    Zustand farbe=spielfeld[i]->getZustand();
    if (gueltigerZug(i,spielfeld[i]->getZustand(),augen))
    {
        for(int h=0;h<augen;h++)
        {
            next=spielfeld[i]->getNext();
            spielfeld[i]->freistellen();
            spielfeld[i]->setalterZustand(nichtBelegt);
            if(h<augen-1)
                spielfeld[next]->feldUeberspringen(farbe);
            else
            {
                Zustand farbeTemp=spielfeld[next]->getZustand();
                spielfeld[next]->feldBelegen(farbe);
                if(farbeTemp!=nichtBelegt)
                    fressen(farbeTemp);
            }
            i=next;
            ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));

        }
        user[madn->getAnDerReihe()-1]->setStartpositionBelegt(false);
    }
    else
    {
        while(!gueltigerZug(i,spielfeld[i]->getZustand(),augen))
        {
            spielfeld[i]->blinken();
            for (int j=0;j<augen;j++)
            {
                i=spielfeld[i]->getNext();
                next=spielfeld[i]->getNext();
            }
        }
        ui->label->setText(QString("Kann Startposition nicht frei machen, statt dessen wird die blockierende Figur bewegt."));
        user[madn->getAnDerReihe()-1]->setStartpositionBelegt(false);
        for(int h=0;h<augen;h++)
        {
            next=spielfeld[i]->getNext();
            spielfeld[i]->freistellen();
            spielfeld[i]->setalterZustand(nichtBelegt);
            if(h<augen-1)
                spielfeld[next]->feldUeberspringen(farbe);
            else
            {
                Zustand farbeTemp=spielfeld[next]->getZustand();
                spielfeld[next]->feldBelegen(farbe);
                if(farbeTemp!=nichtBelegt)
                    fressen(farbeTemp);
            }
            i=next;
            ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));
        }
        user[madn->getAnDerReihe()-1]->setStartpositionBelegt(true);
    }
    delay(2000);
    user[(madn->getAnDerReihe())-1]->checkPhaseKI();
}

void MainWindow::normalesSzenarioKI()
{
    Zustand farbe;
    bool figurBewegt=false;
    int i,next,augen=ui->hauptwurfel->getAugen();
    if (augen==6 && user[madn->getAnDerReihe()-1]->getAnzStartfeld()>0)
    {
        switch (madn->getAnDerReihe())
        {
        case gelb: i=0;next=1;break;
        case grun: i=4;next=11;break;
        case rot: i=8;next=21;break;
        case blau: i=12;next=31;break;
        case nichtBelegt: i=0;next=0;break;
        }
        for (int j=i;j<i+4;j++)
        {
            if (startfelder[j]->getZustand()!=nichtBelegt && !figurBewegt)
            {
                ui->label->setText(QString("Figur wird von Startfeld auf Startposition gesetzt"));
                ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));
                startfelder[j]->freistellen();
                Zustand Farbe=spielfeld[next]->getZustand();
                spielfeld[next]->feldBelegen(madn->getAnDerReihe());
                if(Farbe!=nichtBelegt)
                   fressen(Farbe);
                user[madn->getAnDerReihe()-1]->setStartpositionBelegt(true);
                user[(madn->getAnDerReihe())-1]->anzStartfeldVerringern();
                figurBewegt=true;
            }
        }
    }
    if (!figurBewegt)
    {
        switch (madn->getAnDerReihe())
        {
        case gelb: i=3;break;
        case grun: i=7;break;
        case rot: i=11;break;
        case blau: i=15;break;
        case nichtBelegt: i=16;break;
        }
        for (int j=i;j>=i-2;j--)
        {
            Zustand zustaende=zielfelder[j]->getZustand();
            if (zustaende!=nichtBelegt)
            {
                if (gueltigerZugZiel(j,zustaende,augen) && !figurBewegt)
                {
                    for(int h=0;h<augen;h++)
                    {
                        next=zielfelder[j]->getNext();
                        zielfelder[j]->freistellen();
               //         spielfeld[j]->setalterZustand(nichtBelegt);
                        zielfelder[next]->feldUeberspringen(zustaende);
                        j=next;
                    }
                    amZielAngelangt(madn->getAnDerReihe());
                    figurBewegt=true;
                }
            }
        }
    }
    if (!figurBewegt)
    {
        switch (madn->getAnDerReihe())
        {
        case gelb: i=40;break;
        case grun: i=10;break;
        case rot: i=20;break;
        case blau: i=30;break;
        case nichtBelegt: i=0;break;
        }
        for (int j=0;j<40;j++)
        {
            std::cout << j << std::endl;
            if (i==0)
                i=40;
            if (next==0)
                next=40;
            if (gueltigerZug(i,spielfeld[i]->getZustand(),augen) && !figurBewegt && madn->getAnDerReihe()==spielfeld[i]->getZustand())
            {
                int aktuell=i;
                farbe=spielfeld[aktuell]->getZustand();
                for(int h=0;h<augen;h++)
                {
                    next=spielfeld[aktuell]->getNext();
                    if(next==0)
                    {
                        next=spielfeld[aktuell]->getnextZielposition();
                        spielfeld[aktuell]->freistellen();
                        spielfeld[aktuell]->setalterZustand(nichtBelegt);
                        zielfelder[next]->feldUeberspringen(farbe);
                        aktuell=next;
                        // nach Verzweigungsfeld wird ja noch auf Zielfelder gelaufen( restlichen Bewegungen)
                        for(int k=h+1;k<augen;k++)
                        {
                            next=zielfelder[aktuell]->getNext();
                            zielfelder[aktuell]->freistellen();
                            zielfelder[next]->feldBelegen(farbe);
                            aktuell=next;
                        }
                        amZielAngelangt(madn->getAnDerReihe());
                        // Break da Zielfelder den Rest der Bewegungen verbraucht hat
                        break;
                    }
                    // Für den normalen Fall, in dem ganz normal weiter gelaufen wird
                    else
                    {
                        spielfeld[aktuell]->freistellen();
                        spielfeld[aktuell]->setalterZustand(nichtBelegt);
                        if(h<augen-1)
                            spielfeld[next]->feldUeberspringen(farbe);
                        else
                        {
                            Zustand farbeTemp=spielfeld[next]->getZustand();
                            spielfeld[next]->feldBelegen(farbe);
                            if(farbeTemp!=nichtBelegt)
                                fressen(farbeTemp);
                        }
                        aktuell=next;
                        ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));
                    }
                }
                figurBewegt=true;
            }
            i--;
            next--;
        }
    }
    delay(2000);
    user[madn->getAnDerReihe()-1]->checkPhaseKI();
}

void MainWindow::startpositionBelegenKI()
{
    bool figurBewegt=false;
    int i,next;
    switch (madn->getAnDerReihe())
    {
    case gelb: i=0;next=1;break;
    case grun: i=4;next=11;break;
    case rot: i=8;next=21;break;
    case blau: i=12;next=31;break;
    case nichtBelegt: i=0;next=0;break;
    }
    for (int j=i;j<i+4;j++)
    {
        if (startfelder[j]->getZustand()!=nichtBelegt && !figurBewegt)
        {
            ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));
            startfelder[j]->freistellen();
            Zustand Farbe=spielfeld[next]->getZustand();
            spielfeld[next]->feldBelegen(madn->getAnDerReihe());
            if(Farbe!=nichtBelegt)
               fressen(Farbe);
            user[madn->getAnDerReihe()-1]->setStartpositionBelegt(true);
            user[madn->getAnDerReihe()-1]->anzStartfeldVerringern();
            figurBewegt=true;
        }
    }
    delay(2000);
    user[(madn->getAnDerReihe())-1]->checkPhaseKI();
}

