/**
 * \Klasse Feld
 *
 *
 * Die Klasse Feld beschreibt alle Felder auf dem Spielbrett
 * auf der Figuren stehen können, sprich Startfelder,
 * Spielfelder und Zielfelder.
 *
 *
 * \author Softwarepraktikum Team Mensch aergere dich nicht $
 *
 * \version 1.5 $
 *
 * \date 05.01.2014 $
 *
 *
 * Created on: 10.12.2013
 *
 *
 */


#ifndef FELDL_H
#define FELDL_H
#include <QLabel>
#include "zustand.h"
class Feld : public QLabel
{
         Q_OBJECT
protected:
    Zustand zustaende; ///< Beschreibt den Zustand eines Feldes
    Zustand alterZustand; ///< Eine zweite Zustandsvariable ist benötigt für den Fall, fuer das Feld ueberspringen
    int next; ///< "Zeiger" auf das naechste Feldelement
    int feldNr; ///< Feldnummer eines jeden Feldes
    int figurArt; ///< Beschreibt die Figurart, um die richtigen Pixmaps zu laden in der Funktion setFigur()
public:
    explicit Feld(QWidget *parent = 0);
    /**
     * Das ist das Event was ausgeloest wird bei einem Mausklick auf das Feld.
     */
    void mousePressEvent(QMouseEvent *ev);
    /**
     * Diese Funktion setzt den Zustand eines Feldes auf
     * den der uebergeben wurde und belegt die jeweilige Figur damit.
     * @param _zustaende Das ist der Zustand der gesetzt werden soll.
     *
     *
     */
    void setZustand(Zustand _zustaende){zustaende=_zustaende;setFigur();}
    /**
     * @return
     * Liefert den Zustand des Feldes zurueck.
     */
    Zustand getZustand(){return zustaende;}
    /**
     * @param _feldNr
     * Die Feldnr, die gesetzt werden soll.
     */
    void setfeldNr(int _feldNr){feldNr=_feldNr;}
    /**
     * @param _next
     * Zeigt auf das naechste Element fuer das jeweilige Feld.
     */
    void setNext(int _next){next=_next;}
    /**
     * @param _zustaende
     * Der Zustand der fuer alterZustand gesetzt werden soll.
     */
    void setalterZustand(Zustand _zustaende){alterZustand=_zustaende;}
    /**
     * @return
     * Liefert alterZustand zurueck.
     */
    Zustand getalterZustand(){return alterZustand;}
    /**
     * @return
     * Gibt next zurueck.
     *
     */
    virtual int getNext(){return next;}
    /**
     * Setzt die Figur nach dem Zustand des Feldes.
     */
    void setFigur();
    /**
     * Legt die figurArt fest.
     * @param _figurArt
     * Die Figurart, die festgelegt werden soll.
     */
    void setFigurArt(int _figurArt){figurArt=_figurArt;}
    /**
     * Eine Funktion, die ein blinken, der auf dem
     * Feld stehenden Funktion verursacht.
     * In den meisten Faellen, wenn ein die angeklickte
     * Figur keinen gueltigen Zug durchfuehren kann.
     */
    void blinken();
    /**
     * Zustaendig fuer das Belegen von einem Feld mit einer Figur.
     */
    void feldBelegen(Zustand);
    /**
     * Das Feld wird freigestellt von der Figur.
     */
    void freistellen();
    /**
     * Eine Funktion, die eine Zeitverzoegerung einleitet,
     * um das Feld belegen zu animieren.
     */
    void delayBelegen(int);

signals:
    /**
     * Signal, welches feldNr, next und den Zustand
     * an ein Slot in MainWindow, um von dort aus den Zug
     * durchzuführen falls moeglich.
     */
    void mousePressed(int,int,Zustand);
};

#endif // FELD_H
