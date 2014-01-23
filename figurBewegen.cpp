#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

/**
 * @param aktuell
 * Beschreibt den Feldeintrag von dem aus gegangen werden soll.
 * @param zustaende
 * Beschreibt den Zustand, den das geklickte Feld hat
 * @param augen
 * Beschreibt die Augensumme, die gegangen werden soll.
 * @return
 * True fuer einen moeglichen Zug und False fuer einen nicht moeglichen Zug.
 */
bool MainWindow::gueltigerZug(int aktuell, Zustand zustaende,int augen){
    for(int i=0;i<augen;i++)
    {
        spielfeld[aktuell]->setpseudoZustand(zustaende);
        int next=spielfeld[aktuell]->getNext();
        // Für den Fall, dass im selben Zug in Zielfelder gelaufen wird
        if(next==0){
            next=spielfeld[aktuell]->getnextZielposition();
            spielfeld[aktuell]->setpseudoZustand(nichtBelegt);
            aktuell=next;
            if(zielfelder[aktuell]->getZustand()==nichtBelegt){
            for(int j=i+1;j<augen;j++)
               {
                next=zielfelder[aktuell]->getNext();
                if(next==0)
                    return false;
                else if(zielfelder[next]->getZustand()==zustaende)
                    return false;
                else
                    aktuell=next;
               }
            break;
         }
            else
                return false;
        }
        // Für den Fall, dass ganz normal im Spielfeld weitergelaufen wird
        else{
                if(i==augen-1 && spielfeld[next]->getZustand()==zustaende)
                    return false;
                    spielfeld[aktuell]->setpseudoZustand(nichtBelegt);
                aktuell=next;
                // Das ist für den Testlauf, es müssen ja quasi virtuell die Felder für einen kleinen Momemt belegt werden
                if(i!=augen-1){
                    spielfeld[aktuell]->setpseudoZustand(zustaende);
                }
            }
    }
    return true;
}
/**
 * @param aktuell
 * Beschreibt den Feldeintrag von dem aus gegangen werden soll.
 * @param zustaende
 * Beschreibt den Zustand, den das geklickte Feld hat
 * @param augen
 * Beschreibt die Augensumme, die gegangen werden soll.
 * @return
 * True fuer einen moeglichen Zug und False fuer einen nicht moeglichen Zug.
 */
bool MainWindow::gueltigerZugZiel(int aktuell,Zustand zustaende, int augen){
    for(int i=0;i<augen;i++)
       {
        int next=zielfelder[aktuell]->getNext();
        if(next==0)
            return false;
        else if(zielfelder[next]->getZustand()==zustaende)
            return false;
        else
            aktuell=next;
       }
    return true;
}

bool MainWindow::gueltigerZugVorhanden(int augen, Zustand spielerFarbe)
{
    Zustand aktuell;
    for (int j=1;j<41;j++)
    {
        aktuell=spielfeld[j]->getZustand();
        if (aktuell==spielerFarbe && gueltigerZug(j,aktuell,augen))
            return true;
    }
    for (int j=1;j<17;j++)
    {
        aktuell=zielfelder[j]->getZustand();
        if (aktuell==spielerFarbe && gueltigerZugZiel(j,aktuell,augen))
            return true;
    }
    if (augen==6 && user[spielerFarbe-1]->getAnzStartfeld()>0)
        return true;
    return false;
}


bool MainWindow::startpositionGueltig(int aktuell)
{
    int i;
    int augen=ui->hauptwurfel->getAugen();
    switch (madn->getAnDerReihe())
    {
    case gelb: i=1;break;
    case grun: i=11;break;
    case rot: i=21;break;
    case blau: i=31;break;
    case nichtBelegt: i=0;break;
    }
    if (user[madn->getAnDerReihe()-1]->getStartpositionBelegt() && user[madn->getAnDerReihe()-1]->getDarfKlicken())
    {
        std::cout << "1 bestanden" << std::endl;
        if (i==aktuell)
        {
            Zustand zustaende=spielfeld[aktuell]->getZustand();
            if (gueltigerZug(aktuell,zustaende,augen))
            {
                user[madn->getAnDerReihe()-1]->setStartpositionBelegt(false);
                std::cout << "Startposition wird frei gemacht" << std::endl;
                return true;
            }
            else
            {
                spielfeld[aktuell]->blinken();
                int next;
                for (int j=0;j<augen;j++)
                {
                    aktuell=spielfeld[aktuell]->getNext();
                    next=spielfeld[aktuell]->getNext();
                }
                std::cout << "kann Startposition nicht frei machen, statt dessen wird die blockierende Figur bewegt." << std::endl;
                user[madn->getAnDerReihe()-1]->setStartpositionBelegt(false);
                feldPressed(next,aktuell,zustaende);
                delay(100);
                user[madn->getAnDerReihe()-1]->setStartpositionBelegt(true);
                return false;
            }
        }
        else

            std::cout << "tut  " << i << madn->getAnDerReihe() << aktuell << std::endl;
            return false;
    }
    else
        return true;
}
/**
 * @param next
 * Das naechste Element des Feldes mit der Feldnummer aktuell.
 * @param aktuell
 * Die Feldnummer des Feld auf das geklickt wurde.
 * @param zustaende
 * Der Zustand des Feldes auf das geklickt wurde.
 */
void MainWindow::feldPressed(int next,int aktuell, Zustand zustaende){
        int augen=ui->hauptwurfel->getAugen();
        // Abfrage bevor durchlaufen wird nach Gültigkeit des Spielzuges
        if(user[madn->getAnDerReihe()-1]->getDarfKlicken() && madn->getAnDerReihe()==spielfeld[aktuell]->getZustand()){
        if(startpositionGueltig(aktuell) && gueltigerZug(aktuell,zustaende,augen)){
            int augen=ui->hauptwurfel->getAugen();
              for(int i=0;i<augen;i++)
              {
                  next=spielfeld[aktuell]->getNext();
                  if(next==0){
                      next=spielfeld[aktuell]->getnextZielposition();
                      spielfeld[aktuell]->freistellen();
                      spielfeld[aktuell]->setalterZustand(nichtBelegt);
                      zielfelder[next]->feldUeberspringen(zustaende);
                      aktuell=next;
                      // nach Verzweigungsfeld wird ja noch auf Zielfelder gelaufen( restlichen Bewegungen)
                      for(int j=i+1;j<augen;j++)
                      {
                          next=zielfelder[aktuell]->getNext();
                          zielfelder[aktuell]->freistellen();
                          zielfelder[next]->feldBelegen(zustaende);
                          aktuell=next;
                               }
                      amZielAngelangt(madn->getAnDerReihe());
                      // Break da Zielfelder den Rest der Bewegungen verbraucht hat
                      break;
                  }
                  // Für den normalen Fall, in dem ganz normal weiter gelaufen wird
                  else{
                      spielfeld[aktuell]->freistellen();
                      spielfeld[aktuell]->setalterZustand(nichtBelegt);
                      if(i<augen-1)
                       spielfeld[next]->feldUeberspringen(zustaende);
                      else{
                          Zustand Farbe=spielfeld[next]->getZustand();
                          spielfeld[next]->feldBelegen(zustaende);
                          if(Farbe!=nichtBelegt)
                              fressen(Farbe);
                          }
                          aktuell=next;
                          ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));
                  }
              }
              user[madn->getAnDerReihe()-1]->setDarfKlicken(false);
              user[(madn->getAnDerReihe())-1]->checkPhase();
          }
        else
            spielfeld[aktuell]->blinken();
        }
}

/**
 * @param next
 * Das naechste Element des Feldes mit der Feldnummer aktuell.
 * @param aktuell
 * Die Feldnummer des Feld auf das geklickt wurde.
 * @param zustaende
 * Der Zustand des Feldes auf das geklickt wurde.
 */
void MainWindow::startfeldPressed(int next, int aktuell, Zustand zustaende){
    if(user[madn->getAnDerReihe()-1]->getDarfKlicken() && madn->getAnDerReihe()==startfelder[aktuell]->getZustand()){
        ui->textBrowser->append("ich habe Zugriff");
       if (ui->hauptwurfel->getAugen()==6)
       {
          ui->textBrowser->append(QString("Naechstes Element: %1").arg(next));
          startfelder[aktuell]->freistellen();
          Zustand Farbe=spielfeld[next]->getZustand();
          spielfeld[next]->feldBelegen(zustaende);
          if(Farbe!=nichtBelegt)
             fressen(Farbe);
          user[madn->getAnDerReihe()-1]->setDarfKlicken(false);
          user[madn->getAnDerReihe()-1]->setStartpositionBelegt(true);
          user[(madn->getAnDerReihe())-1]->anzStartfeldVerringern();
          user[(madn->getAnDerReihe())-1]->wurfelPhase();
       }
       else
       {
          startfelder[aktuell]->blinken();
          std::cout << "2 " << ui->hauptwurfel->getAugen() << user[madn->getAnDerReihe()-1]->getDarfKlicken() << madn->getAnDerReihe() << startfelder[aktuell]->getZustand() << std::endl;
       }
    }
}

/**
 * @param next
 * Das naechste Element des Feldes mit der Feldnummer aktuell.
 * @param aktuell
 * Die Feldnummer des Feld auf das geklickt wurde.
 * @param zustaende
 * Der Zustand des Feldes auf das geklickt wurde.
 */
void MainWindow::zielfeldPressed(int next,int aktuell, Zustand zustaende){
    int augen=ui->hauptwurfel->getAugen();
        //hier muss selbstverstaendlich vor dem ausführen überprüft werden auf Gültigkeit des Zugs
    if(!(user[madn->getAnDerReihe()-1]->getStartpositionBelegt()) && user[madn->getAnDerReihe()-1]->getDarfKlicken() && madn->getAnDerReihe()==zielfelder[aktuell]->getZustand()){
    if(gueltigerZugZiel(aktuell,zustaende,augen)){
        for(int j=0;j<augen;j++)
        {
            next=zielfelder[aktuell]->getNext();
            zielfelder[aktuell]->freistellen();
            spielfeld[aktuell]->setalterZustand(nichtBelegt);
            zielfelder[next]->feldUeberspringen(zustaende);
            aktuell=next;
        }
        user[madn->getAnDerReihe()-1]->setDarfKlicken(false);
        amZielAngelangt(madn->getAnDerReihe());
        user[(madn->getAnDerReihe())-1]->checkPhase();
    }
    else
        zielfelder[aktuell]->blinken();
    }
}

void MainWindow::amZielAngelangt(Zustand n)
{
    int letztesZielfeld;
    int naechstesZielfeld;
    switch(n)
    {
    case gelb:letztesZielfeld=4; break;
    case grun:letztesZielfeld=8;break;
    case rot:letztesZielfeld=12;break;
    case blau:letztesZielfeld=16;break;
    case nichtBelegt:letztesZielfeld=99;break;
    }
    naechstesZielfeld=(letztesZielfeld-(user[madn->getAnDerReihe()-1]->getAnzZielfeld()));
    if (zielfelder[naechstesZielfeld]->getZustand()!=nichtBelegt)
        user[madn->getAnDerReihe()-1]->anzZielfeldErhoehen();
}

void MainWindow::fressen(Zustand Farbe){
    int i;
    std::cout << Farbe << " " << user[0]->spielerFarbe << " " << user[1]->spielerFarbe << " " << user[2]->spielerFarbe << " " << user[3]->spielerFarbe << " " << std::endl;
    if(Farbe==gelb){
        for(i=0;i<4;i++){
            if(startfelder[i]->getZustand()==nichtBelegt){
                startfelder[i]->feldBelegen(Farbe);
                user[Farbe-1]->anzStartfeldErhoehen();
                break;
            }
        }
            startfelder[i]->feldBelegen(Farbe);}
    else if(Farbe==grun){
        for(i=4;i<8;i++){
            if(startfelder[i]->getZustand()==nichtBelegt){
                startfelder[i]->feldBelegen(Farbe);
                user[Farbe-1]->anzStartfeldErhoehen();
                break;
            }
        }
            startfelder[i]->feldBelegen(Farbe);}
    else if(Farbe==rot){
        for(i=8;i<12;i++){
            if(startfelder[i]->getZustand()==nichtBelegt){
                startfelder[i]->feldBelegen(Farbe);
                user[Farbe-1]->anzStartfeldErhoehen();
                break;
            }
        }
            startfelder[i]->feldBelegen(Farbe);}
    else if(Farbe==blau){
        for(i=12;i<15;i++){
            if(startfelder[i]->getZustand()==nichtBelegt){
                startfelder[i]->feldBelegen(Farbe);
                user[Farbe-1]->anzStartfeldErhoehen();
                break;
            }
        }
   }
}

void MainWindow::delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

