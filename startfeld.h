/**
 * \Klasse Startfeld
 *
 *
 * Die Klasse Startfeld beschreibt alle Startfelder auf dem Spielbrett
 * und ist von Feld abgeleitet.
 * Jeweils vier Startfelder fuer alle Farben (4x4).
 *
 *
 * \author (last to touch it) $Author: Softwarepraktikum Team Mensch aergere dich nicht $
 *
 * \version $Revision: 1.3 $
 *
 * \date $Date: 02.01.2014 $
 *
 *
 * Created on: 10.12.2013
 *
 *
 */

#ifndef STARTFELD_H
#define STARTFELD_H

#include <QLabel>
#include "feld.h"

class Startfeld : public Feld
{
    Q_OBJECT
private:
public:
    explicit Startfeld(QWidget *parent = 0);

signals:

public slots:

};

#endif // STARTFELD_H
