/**
 * \Klasse Startfeld
 *
 * Die Klasse Verzweigungsfeld ist abgeleitet von Spielfeld und
 * beschreibt jeweils das Spielfeld, welches genau vor dem Zielfeld
 * ist. So wird dies benötigt, um festzustellen, wie es nun weitergeht
 * mit der Figur( ob diese vorbeiläuft oder in die Zielfelder läuft).
 *
 * \author Softwarepraktikum Team Mensch aergere dich nicht $
 *
 * \version 1.4 $
 *
 * \date 08.01.2014 $
 *
 *
 * Created on: 10.12.2013
 *
 *
 */
#ifndef VERZWEIGUNGSFELD_H
#define VERZWEIGUNGSFELD_H

#include <QLabel>
#include "spielfeld.h"
class Verzweigungsfeld : public Spielfeld
{
    Q_OBJECT
private:
    Zustand farbe; ///< Beschreibt die Farbe, die ins Zielfeld gelangt von da aus
    int nextZielposition; ///< Liefert den Zielposition zurueck
public:
    explicit Verzweigungsfeld(QWidget *parent = 0);
    /**
     * @param _farbe
     * Farbe die gesetzt werden soll fuer das jeweilige Verzweigungsfeld.
     */
    void setFarbe(Zustand _farbe){farbe=_farbe;}
    int getNext();
    /**
     * @param _nextZielposition
     * Zeigt auf die naechste Zielposition.
     */
    void setnextZielposition(int _nextZielposition){nextZielposition=_nextZielposition;}
    /**
     * @return
     * Liefert nextZielposition zurueck.
     */
    int getnextZielposition(){return nextZielposition;}
signals:
public slots:
};

#endif // VERZWEIGUNGSFELD_H
