#ifndef SPIELER_H
#define SPIELER_H
#include "zustand.h"
#include <QString>
#include <QObject>

class Spieler : public QObject
{
    Q_OBJECT
private:
    int anzStartfeld; ///< Anzahl der Figuren auf den Startfeldern des Spielers.
    int anzZielfeld; ///< Anzahl der Figuren des Spieler die am Ziel angelangt sind.
    int anzGewurfelt; ///< Anzahl der Würfelvorgaenge im aktuellen Spielzug.
    int augen; ///< Aktuell gewürfelte Augenzahl.
    QString benutzerName; ///< Benutzername des Spielers. Nur bei Netzwerkspielen benötigt.
    QString ip; ///< IP des Spielers. Nur bei Netzwerkspielen benötigt.
    bool darfKlicken; ///< Regelt ob der Spieler auf ein Feld klicken und somit einen Spielzug mit der aktuellen Augenzahl vollziehen darf.
    bool startpositionBelegt; ///< Teilt mit ob die Startposition belegt oder nicht ist. Regelbedingt benötigt.
    bool gueltigerZugVorhanden; ///< Ist kein gueltiger Zug vorhanden, wird zum nächsten Spieler gewechselt.
    void delay(int); ///< Ein Delay das für eine Verzögerung innerhalb der Funktionen der KI sorgt.
public:
    Zustand spielerFarbe; ///< Die Farbe des Spielers.
    explicit Spieler(QObject *parent = 0);
    /**
     *Initialisiert die Variablen von Spieler für den Start einer Partie. Funktion
     *ist nötig, da bei einem zweiten Spiel nicht nochmal der Konstrukor aufgerufen
     *wird und so die Variablen zu Anfang des zweiten Spiels "falsche" Werte haetten
     */
    void initSpieler(int i);
    /**
     * Überprüft ob der Spieler regelbedingt Würfeln darf und emitiert gegenenfalls darfWurfeln(true).
     * Darf der Spieler nicht Würfeln, wird in die Funktion checkPhase() weiter geleitet.
     */
    void wurfelPhase();
    /**
     * Das gleiche wie wurfelPhase(). Nur für die KI. Bei erlaubten Würfelvorgang wird wurfelKI() emitiert, andernfalls wird in die checkPhaseKI() weiter geleitet.
     */
    void wurfelPhaseKI();
    /**
     * Get-Funktion für gueltigerZugVorhanden.
     * @return
     * Liefert gueltigerZugVorhanden
     */
    bool getGueltigerZugVorhanden() {return gueltigerZugVorhanden;}
    /**
     * Set-Funktion für gueltigerZugVorhanden.
     * @param n
     * Setzt gueltigerZugVorhanden auf @param
     */
    void setGueltigerZugVorhanden(bool n) {gueltigerZugVorhanden=n;}    
    /**
     * Get-Funktion für startpositionBelegt.
     * @return
     * Liefert startpositionBelegt
     */
    bool getStartpositionBelegt() {return startpositionBelegt;}
    /**
     * Set-Funktion für startpositionBelegt.
     * @param n
     * Setzt startpositionBelegt auf @param
     */
    void setStartpositionBelegt(bool n) {startpositionBelegt=n;}
    /**
     * Get-Funktion für darfKlicken.
     * @return
     * Liefert darfKlicken
     */
    bool getDarfKlicken() {return darfKlicken;}
    /**
     * Set-Funktion für darfKlicken.
     * @param n
     * Setzt darfKlicken auf @param
     */
    void setDarfKlicken(bool n) {darfKlicken=n;}
    /**
     * Dekrementiert anzStartfeld
     */
    void anzStartfeldVerringern() {anzStartfeld--;}
    /**
     * Inkrementiert anzStartfeld
     */
    void anzStartfeldErhoehen() {anzStartfeld++;}
    /**
     * Get-Funktion für anzStartfeld.
     * @return
     * Liefert anzStartfeld
     */
    int getAnzStartfeld() {return anzStartfeld;}
    /**
     * Get-Funktion für anzZielfeld.
     * @return
     * Liefert anzZielfeld
     */
    int getAnzZielfeld() {return anzZielfeld;}
    /**
     * Inkrementiert anzZielfeld
     */
    void anzZielfeldErhoehen() {anzZielfeld++;}
    /**
     * Get-Funktion für anzGewurfelt.
     * @return
     * Liefert anzGewurfelt
     */
    int getAnzGewurfelt() {return anzGewurfelt;}
    /**
     * Set-Funktion für anzGewurfelt.
     * @param i
     * Setzt anzGewurfelt auf @param
     */
    void setAnzGewurfelt(int i) {anzGewurfelt=i;}
signals:
    /**
     * Wird nach einem kompletten Spielzug emitiert und bewirkt, dass zum nächsten Spieler gewechselt wird.
     */
    void spielerFertig();
    /**
     * Teilt dem Objekt hauptwurfel der Klasse wurfel mit ob gewurfelt werden darf.
     */
    void darfWurfeln(bool);
    /**
     * Sofern die KI "arbeitet" wird hiermit der Würfelvorgang gestartet.
     */
    void wurfelKI();
    /**
     * Sofern die KI "arbeitet" wird hiermit die Funktion innerhalb der MainWindow aufgerufen die für das Bewegen einer Figur zuständig ist.
     */
    void figurBewegenKI();
    /**
     * Setzt die Würfelfarbe auf spielerFarbe
     */
    void wurfelFarbe(Zustand);
    /**
     * Wird genutzt um die Textausgabe auf label innerhalb des UI umzuleiten
     */
    void setLabelText(QString);
    /**
     * Hat ein Spieler die Siegbedingung erfüllt (alle Figuren im Ziel), wird nicht spielerFertig() emitiert sondern dieses Signal und teil somit dem Spiel den Sieger mit.
     */
    void gewonnen();
public slots:
    /**
     * Setzt die Würfelfarbe und startet den Spielzug des Spielers.
     */
    void spiele();
    /**
     * Nach abgelaufenen Timer wird von der Klasse Timeout die KI gestartet.
     */
    void starteKI();
    /**
     * Nach erfolgreicher Würfelphase und ermittelter Augenzahl, geht es in
     * die Zugphase. Hier wird entschieden, welche Figur/-en man regelbedingt
     * bewegen darf/muss und dies per Textausgabe mitgeteilt.
     */
    void zugPhase(int);
    /**
     * Es wird überprüft ob die Siegbedingung erfüllt ist und/oder ob man eine 6 gewürfelt hat.
     *Hat man die Siegbedingung erfüllt, ist man natürlich der Sieger und das Spiel ist vorbei.
     *Hat man eine 6 gewürfelt, darf man nochmal würfeln und somit geht es wieder in die Würfelphase.
     *Trifft beides nicht zu, ist der nächste Spieler an der Reihe
     */
    void checkPhase();
    /**
     * Das gleiche wie checkPhase(). Nur an die Bedürfnisse der KI angepasst.
     */
    void checkPhaseKI();
    /**
     * Set-Funktion für die Augenzahl.
     * @param n
     * Die übermittelte Augenzahl
     */
    void setzeAugen(int n) {augen=n;}
};

#endif // SPIELER_H
