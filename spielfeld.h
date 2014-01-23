/**
 * \Klasse Spielfeld
 *
 *
 * Die Klasse Spielfeld beschreibt alle Felder auf dem Spielbrett
 * ausgeschlossen Startfelder. Die Vaterklasse ist die Klasse Feld.
 *
 *
 * \author Softwarepraktikum Team Mensch aergere dich nicht $
 *
 * \version 1.4 $
 *
 * \date 04.10.2013 $
 *
 *
 * Created on: 10.12.2013
 *
 *
 */

#ifndef SPIELFELD_H
#define SPIELFELD_H
#include <QLabel>
#include "feld.h"
#include "zustand.h"
class Spielfeld : public Feld
{
    Q_OBJECT
private:
    int spielfeldNr; ///< SpielfeldNr
protected:
    Zustand pseudoZustand; ///< Zum Ueberpruefen der Gueltigkeit eines Zuges ist ein Pseudozustand von Noeten
public:
   explicit Spielfeld(QWidget *parent = 0);
   /**
   * @param _spielfeldNr
   * Spielfeldnummer des jeweiligen Feldes.
   */
   void setSpielfeldNr(int _spielfeldNr){
       spielfeldNr=_spielfeldNr;
   }
   /**
    * @return
    * Liefert spielfeldNr zurueck.
    */
   int getSpielfeldNr(){return spielfeldNr;}
   virtual int getnextZielposition(){return 0;}
   /**
    * Um Felder nicht direkt zu belegen, wenn man noch weiterlaufen
    * muss mit einer Figur und somit keine Figur auffressen will.
    */
   void feldUeberspringen(Zustand);
   /**
    * @param pseudo
    * Ein voruebergehender Peseudozustand.
    */
   void setpseudoZustand(Zustand pseudo){ pseudoZustand=pseudo;}
   /**
    * @return
    * Liefert den pseudoZustand zurueck.
    */
   Zustand getpseudoZustand(){return pseudoZustand;}

signals:


public slots:

};

#endif // SPIELFELD_H
