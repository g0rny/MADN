/**
 * \Klasse Wurfel
 *
 *
 * Die Klasse Wurfel beschreibt den Hauptwurfeln
 *
 * $Author: Softwarepraktikum Team $
 *
 * $Revision: 1.6 $
 *
 * $Date: 15.01.2014 $
 *
 *
 * Created on: 20.11.2013
 *
 *
 */


#ifndef WURFEL_H
#define WURFEL_H

#include <QLabel>
#include "zustand.h"

class Wurfel : public QLabel
{
    Q_OBJECT

private:
    int alteAugen; ///< Die alte Augenzahl. Benötigt um auszuschließen, dass beim nächsten Roll die gleiche Augenzahl kommt.
    int vorlaeufigeAugen; ///< Die gerade gerollte Augenzahl.
    int augen; ///< Die Augenzahl, die letzt endlich als Würfel-Ergebnis dient.
    Zustand spielerFarbe; ///< Die Farbe des Spielers, der gerade an der Reihe ist. Benötigt für die Farbe des Würfels.
    bool darfWurfeln; ///< Regelt ob der Spieler überhaupt auf den Würfel klicken und somit würfeln darf.
    /**
     * Verzögerungsfunktion, die für die Animationen und die Anzeige genutzt wird.
     */
    void delay(int);
    /**
     * Das Bild des Würfels wird an die gewürfelte Augenzahl angepasst.
     */
    void setzeBild(int);
    /**
     * Ermittlung einer neuen, von der alten unterschiedlichen Augenzahl. Denn wenn man
     * würfelt, kann der Würfel beim "rollen" nicht zwei mal hintereinander die gleiche
     * Augenzahl bekommen, es sei denn eine Zahl ist mehrmals auf dem Würfel vorhanden.
     * @return
     * Gibt die gewürfelte Augenzahl zurück
     */
    int wurfeln();
public:
    explicit Wurfel(QWidget *parent = 0);
    /**
     * Liefert die momentane Augenzahl.
     * @return
     * Die Augenzahl wird übergeben
     */
    int getAugen(){return augen;}
    /**
     * Würfelt eine 6, Cheat-Button für die Testphase.
     */
    void sechs();
signals:
    /**
     * Signal, welches für die Würfelanimation auf dem Spielbrett benötigt wird. Übermittelt die momentane Augenzahl und die gewünschte Position des Würfels auf dem Spielbrett.
     */
    void wurfelPressed(int,int);
    /**
     * Signal für eine Netzwerk-Partie. Das Signal wird benötigt um den anderen Spielern mitzuteilen welche Augenzahl gewürfelt wurde.
     * Bildet das Gegenstück zu hatGewurfelt(int).
     */
    void habeGewurfelt(int);
    /**
     * Nach erfolgreichem Würfeln wird durch dieses Signal die zugPhase in der Klasse Spieler aufgerufen. Dabei wird die Augenzahl mit übermittelt.
     */
    void zugPhase(int);
    /**
     * Aehnlich zu zugPhase(int) nur für und von der KI benutzt. Startet die zugPhaseKI() innerhalb der MainWindow-Klasse.
     */
    void zugPhaseKI();
    /**
     * Signal für die Textausgabe des Würfels auf das dafür vorgesehene Label im MainWindow.
     */
    void setLabelText(QString);
public slots:
    /**
     * Dies passiert nach einem Klick auf den Hauptwürfel. Beinhaltet den Würfelvorgang inkl. Animation und sämtlichen Signals.
     */
    void mousePressEvent(QMouseEvent*);
    /**
     * Setzt die Variable darfWurfeln auf "true" damit es überhaupt möglich ist zu würfeln.
     */
    void darfWurfelnSlot(bool n){darfWurfeln=n;}
    /**
     * Setzt die Würfelfarbe auf die Spielerfarbe.
     */
    void setzeFarbe(Zustand);
    /**
     * Lässt die Würfelanimation mit vorgegebenen Endergebniss durchlaufen. Wird für eine Netzwerk-Partie benötigt.
     * Bildet das Gegenstück zu habeGewurfelt(int).
     */
    void hatGewurfelt(int);
    /**
     * An sich das gleiche wie wurfel(), nur für die KI und somit kein Mausklick nötig. Sendet nach dem Würfelvorgang das Signal zugPhaseKI().
     */
    void wurfelKI();
};

#endif // WURFEL_H
