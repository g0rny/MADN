/**
 * \Klasse MainWindow
 *
 * Die Klasse MainWindow beschreibt das Hauptfenster des Programms
 * Da von hier aus alle UI Objekte zugreifbar sind, werden Aktionen,
 * die sich ueber mehrere Objekte erstrecken hier implementiert.
 * Das Spiel Mensch ärgere dich nicht und der Chat-Bereich sind Bestandteile
 * des Hauptfensters.
 *
 * \author $Author: Softwarepraktikum Team $
 *
 * \version $Revision: 1.1 $
 *
 * \date $Date: 18.01.2014 $
 *
 *
 * Created on: 13.11.2013
 *
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "dialog.h"
#include "erstellen.h"
#include "feld.h"
#include "Netzwerkverbindung.h"
#include "spielfeld.h"
#include "startfeld.h"
#include "zielfeld.h"
#include "zustand.h"
#include "spiel.h"
#include "spieler.h"
#include "timeout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * Die Funktion sorgt dafuer, dass alle Spielfelder korrekt initialisiert werden.
     * Die Funktion wird im Konstruktor einmal aufgerufen und wird nicht wieder verwendet.
     */
    void spielfelderInit();
    /**
     * Die Funktion sorgt dafuer, dass alle Zielfelder korrekt initialisiert werden.
     * Die Funktion wird im Konstruktor einmal aufgerufen und wird nicht wieder verwendet.
     */
    void zielfelderInit();
    /**
     * Die Funktion sorgt dafuer, dass alle Startfelder korrekt aufgerufen werden.
     * Die Funktion wird im Konstruktor einmal aufgerufen und wird nicht wieder verwendet.
     */
    void startfelderInit();
    /**
     * Die Funktion ist zustaendig fuer das korrekte initialisieren von den Figuren nach Anzahl der Spieler.
     * Die Funktion wird immer dann aufgerufen, wenn ein neues Spiel erstellt wird.
     */
    void figurenInit(int,int);
    /**
     * Die Funktion initialisert die QLabel die benoetigt werden fuer
     * die Wuerfelanimation.
     */
    void wuerfelInit();
    /**
     *
     */
    void spielInit(int,bool);
    /**
     * Die Funktion ist wird dann aufgerufen eine Figur ein Feld belegt, welches von einer anderen Figur einer
     * anderen Farbe bereits belegt ist. Diese andere Figur wird von der belegenden Figur auf ihr Startfeld
     * zurueckgewiesen.
     */

    void fressen(Zustand);
    /**

     * Bevor ein Zug durchgefuehrt wird muss erstmal ueberprueft werden, ob der Zug gemacht werden darf.
     * Hierfuer sorgt diese Funktion. Ist der Zug zulaessig, soll der Zug durchgefuehrt werden.
     */
    bool gueltigerZug(int,Zustand,int);
    /**
     * Da es Unterschiede gibt zwischen der Klasse zielfeld und spielfeld, wird fuer den Fall, dass wenn eine Figur von
     * einem Zielfeld startet eine andere Funktion aufgerufen, wie fuer den Fall,
     * wenn die Funktion auf einem normalen Spielfeld steht.
     * Diese Funktion prueft die Gueltigkeit eines Zuges.
     */
    bool gueltigerZugZiel(int,Zustand,int);
    bool gueltigerZugVorhanden(int,Zustand);
    bool startpositionGueltig(int);
    void amZielAngelangt(Zustand);
    /**
     * Die Funktion wird benoetigt fuer die auf dem Spielbrett sichtbare Wuerfelanimation
     * und wird immer dann aufgerufen, wenn gewuerfelt wird.
     */
    void wuerfelAnimation(int,int);
    /**
     * Sie ist zustaendig dafuer, dass das richtige Wuerfelbild fuer die Animation auf dem
     * Spielbrett geladen wird.
     */
    void setzeBild(int,int);

private slots:
    void on_pushButton_clicked();
    void on_actionBeenden_triggered();
    void on_actionSpiel_beitreten_triggered();
    void on_actionSpiel_erstellen_triggered();
    void on_actionOptionen_triggered();

public slots:
    void settext();
    void wurfelPressed(int,int);
    void startfeldPressed(int,int,Zustand);
    /**
     * Slot fuers Empfangen von FeldNr, Next und Zustand nach Mausklick auf Feld
     */
    void feldPressed(int,int,Zustand);
    /**
     * Slot fuers Empfangen von FeldNr, Next und Zustand nach Mausklick auf Zielfeld
     */
    void zielfeldPressed(int,int,Zustand); ///<
    void spiele(Zustand);
    void starteKI();
    void zugPhase(int);
//    void zugPhaseKI(int);
    void zugPhaseKI();
    void startpositionFreiMachenKI();
    void normalesSzenarioKI();
    void startpositionBelegenKI();
    void anderTimer(int);
    void empfangeSpielparamter(int,int,int,bool,QString);
    void setzeNetzwerkverbindung(Netzwerkverbindung *verbindung);
    void setzeName(QString name);

private:
    Ui::MainWindow *ui; ///< UI Objekt
    Dialog *d;          ///< Spiel beitreten Dialogfenster
    Erstellen *e;       ///< Spiel erstellen Fenster
    Spielfeld* spielfeld[45]; ///< Alle Spielfelder ausgeschlossen Zielfelder in Array
    Startfeld* startfelder[16]; ///< Alle Startfelder in Array
    Zielfeld* zielfelder[17]; ///< Alle Zielfelder in Array
    Spiel *madn=new Spiel();
    Spieler* user[4]={new Spieler(),new Spieler(),new Spieler(),new Spieler()};
    QString eigenName;
    Timeout* timeout=new Timeout();
    QLabel* animationGelb[5],*animationGrun[5],*animationRot[5],*animationBlau[5]; ///< Arrays fuer die Wuerfelanimation auf dem Spielbrett
    bool lokal;
    void delay(int);

signals:
    void nachrichtZuSenden(QString name, QString nachricht);
};

#endif // MAINWINDOW_H
