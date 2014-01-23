#ifndef ERSTELLEN_H
#define ERSTELLEN_H

#include <QDialog>
#include <QStringList>
#include <lobby.h>

#include "Netzwerkverbindung.h"

namespace Ui {
class Erstellen;
}

class Erstellen : public QDialog
{
    Q_OBJECT

private:
    Ui::Erstellen *ui;
    int timer=60;
    bool lokalesSpiel=false;
    int anzSpieler=2;
    int spielfiguren=1;
    Lobby *l;
    QString benutzername;

    QStringList figuren;
    QStringList spieler;

private slots:
    void settimer(int);
    void setlokalesSpiel(int);
    void setanzSpieler(int);
    void setspielfiguren(int);
    void setBenutzername(QString);
    void abbrechen();
    void bestaetigen();
    void setanzSpielerNW(int);

public:
    explicit Erstellen(QWidget *parent = 0);
    ~Erstellen();
    int getTimer(){return timer;}
    int getanzSpieler(){return anzSpieler;}
    int getspielfiguren(){return spielfiguren;}
    bool getlokalesSPiel(){return lokalesSpiel;}

signals:
    void spielparameter(int,int,int,bool,QString);
    //void spielparameterNW(int,int,int);
    void serverGestartet(Netzwerkverbindung *verbindung);
    void sendeName(QString name);
};

#endif // ERSTELLEN_H
