#include "feld.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <mainwindow.h>

 Feld::Feld(QWidget* parent) : QLabel(parent)
{
}

 /**
 * Behandelt Mausklicks auf ein Feld.
 * @param ev
 * Mausklickevent wird uebergeben.
 */
void Feld::mousePressEvent(QMouseEvent *ev)
{
    ev=ev;
    /// Nur dann, wenn das Feld belegt ist, soll auch wirklich ein Mausklick beachtet werden.
    if(zustaende!=nichtBelegt)
        emit mousePressed(next,feldNr,zustaende);
}

 void Feld::freistellen(){
     QPixmap p;
     setPixmap(p);
     // Zustand wird auf alterZustand gesetzt, fuer die Funktion feldUeberspringen(),
     // denn, wenn eine Figur auf dem Weg zu einem anderen Feld, dieses Feld kurzfristig
     // belegt, soll der alte Zustand aufgerufen werden koennen ( sei es, blau, rot,grun, gelb oder
     // nicht belegt).
     setZustand(alterZustand);
 }

 /**
  * @param _zustaende
  * Der Zustand der ein Feld belegt.
  */
 void Feld::feldBelegen(Zustand _zustaende){
    // hier wird garantiert, dass der alteZustand nichtBelegt ist
    // wichtig fuer das Freistellen des Feldes
    alterZustand=nichtBelegt;
    zustaende=_zustaende;
    setFigur();
    delayBelegen(200);
 }

  void Feld::setFigur(){

      QPixmap figur;
      if(zustaende!=nichtBelegt){
      if(figurArt==1){
      if(zustaende==gelb){
          QPixmap figur(":/figuren/grafiken/figuren/gelb.svg");
          setPixmap(figur);}
      else if(zustaende==grun){
          QPixmap figur(":/figuren/grafiken/figuren/grun.svg");
          setPixmap(figur); }
      else if(zustaende==rot){
          QPixmap figur(":/figuren/grafiken/figuren/rot.svg");
          setPixmap(figur);}
      else if(zustaende==blau){
          QPixmap figur(":/figuren/grafiken/figuren/blau.svg");
          setPixmap(figur);}
     }
      else if(figurArt==2)
      {
         if(zustaende==gelb){
            QPixmap figur(":/figuren/grafiken/figuren/schneemanngelb.svg");
            setPixmap(figur);}
         else if(zustaende==grun){
            QPixmap figur(":/figuren/grafiken/figuren/schneemanngrun.svg");
            setPixmap(figur);}
         else if(zustaende==rot){
            QPixmap figur(":/figuren/grafiken/figuren/schneemannrot.svg");
            setPixmap(figur);}
         else if(zustaende==blau){
            QPixmap figur(":/figuren/grafiken/figuren/schneemannblau.svg");
            setPixmap(figur);}
     }
     else if(figurArt==3){
          if(zustaende==gelb){
            QPixmap figur(":/figuren/grafiken/figuren/kugelgelb.svg");
            setPixmap(figur);}
          else if(zustaende==grun){
            QPixmap figur(":/figuren/grafiken/figuren/kugelgrun.svg");
            setPixmap(figur);}
          else if(zustaende==rot){
            QPixmap figur(":/figuren/grafiken/figuren/kugelrot.svg");
            setPixmap(figur);}
          else if(zustaende==blau){
            QPixmap figur(":/figuren/grafiken/figuren/kugelblau.svg");
            setPixmap(figur);}
     }
   }
      else{
          QPixmap figur("");
      setPixmap(figur);}
 }


  void Feld::blinken(){
      QPixmap figur("");
      for(int i=0;i<3;i++)
      {
          if(figurArt==1)
              setPixmap(figur);
          else if(figurArt==2)
              setPixmap(figur);
          else if(figurArt==3)
              setPixmap(figur);
          delayBelegen(180);
          setFigur();
          delayBelegen(180);
      }
  }

  /**
  * @param n
  * Die Anzahl der Millisekunden, die das Belegen verzoegert.
  */
 void Feld::delayBelegen(int n)
 {
     QTime dieTime= QTime::currentTime().addMSecs(n);
     while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
 }





