#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "spielfeld.h"
#include "wurfel.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1100,700);
    spielfelderInit();
    zielfelderInit();
    startfelderInit();
    wuerfelInit();
    for(int i=0;i<4;i++)
        user[i]->initSpieler(i);
    // Spielfelder mit MouseEvents verknüpfen
    for(int i=1;i<41;i++){
            connect(spielfeld[i], SIGNAL(mousePressed(int,int, Zustand)), this, SLOT(feldPressed(int,int, Zustand)));
        }
    // Zielfelder mit Mouseevents verknuepfen
    for(int i=1;i<17;i++)
        connect(zielfelder[i], SIGNAL(mousePressed(int,int,Zustand)), this, SLOT(zielfeldPressed(int,int,Zustand)));
    // Startfelder mit Mouseevents verknuepfen
    for(int i=0;i<16;i++)
       connect(startfelder[i], SIGNAL(mousePressed(int,int,Zustand)), this, SLOT(startfeldPressed(int,int,Zustand)));
    connect(ui->hauptwurfel, SIGNAL(wurfelPressed(int,int)), this, SLOT(wurfelPressed(int,int)));
    connect (madn, SIGNAL(spiele(Zustand)), this, SLOT(spiele(Zustand)));
    connect (ui->hauptwurfel, SIGNAL(zugPhase(int)), this, SLOT(zugPhase(int)));
    connect (ui->hauptwurfel, SIGNAL(zugPhaseKI()), this, SLOT(zugPhaseKI()));
    for (int i=0;i<4;i++)
    {
        connect (user[i], SIGNAL(wurfelFarbe(Zustand)),ui->hauptwurfel, SLOT(setzeFarbe(Zustand)));
        connect (user[i], SIGNAL(darfWurfeln(bool)),ui->hauptwurfel, SLOT(darfWurfelnSlot(bool)));
        connect (user[i], SIGNAL(spielerFertig()),madn, SLOT(naechster()));
        connect (user[i], SIGNAL(spielerFertig()),timeout, SLOT(starte()));
        connect (user[i], SIGNAL(setLabelText(QString)), ui->label, SLOT(setText(QString)));
        connect (user[i], SIGNAL(gewonnen()), madn, SLOT(siegerGefunden()));
        connect (user[i], SIGNAL(wurfelKI()), ui->hauptwurfel, SLOT(wurfelKI()));
//        connect (user[i], SIGNAL(figurBewegenKI()), this, SLOT(figurBewegenKI()));
    }
    connect (timeout, SIGNAL(zeitAbgelaufen()),this, SLOT(starteKI()));
    connect (madn, SIGNAL(timerStart()),timeout, SLOT(starte()));

    connect (timeout, SIGNAL(sekundeVorbei(int)), this, SLOT(anderTimer(int)));
    lokal=true;
    connect (ui->hauptwurfel, SIGNAL(setLabelText(QString)), ui->label, SLOT(setText(QString)));
    connect (madn, SIGNAL(setLabelText(QString)), ui->label, SLOT(setText(QString)));

}

MainWindow::~MainWindow()
{
    delete timeout;
    delete ui;
}

void MainWindow::on_actionBeenden_triggered()
{
    this->close();
}
void MainWindow::settext()
{
    QString s= ui->lineEdit->text();
    ui->textBrowser->setText(s);
}

void MainWindow::on_actionSpiel_beitreten_triggered()
{
    this->d = new Dialog(this);
    connect(d, SIGNAL(verbindungHergestellt(Netzwerkverbindung*)), this, SLOT(setzeNetzwerkverbindung(Netzwerkverbindung*)));
    connect(d, SIGNAL(sendeName(QString)), this, SLOT(setzeName(QString)));
    d->show();
}

void MainWindow::on_actionSpiel_erstellen_triggered()
{
    std::cout<<"Zustand:"<<ui->zielfeldgrun1->getZustand();
    this->e=new Erstellen(this);
    connect(e, SIGNAL(spielparameter(int,int,int,bool,QString)),
            this, SLOT(empfangeSpielparamter(int,int,int,bool,QString)));
    connect(e, SIGNAL(serverGestartet(Netzwerkverbindung*)), this, SLOT(setzeNetzwerkverbindung(Netzwerkverbindung*)));
    connect(e, SIGNAL(sendeName(QString)), this, SLOT(setzeName(QString)));
    e->show();
}
void MainWindow::wurfelPressed(int augen,int i)
{
    wuerfelAnimation(i,augen);
    ui->textBrowser->append(QString("wurfel %1").arg(augen));
}

void MainWindow::spiele(Zustand n)
{
    timeout->starte();
    user[n-1]->spiele();
}

void MainWindow::starteKI()
{
    user[madn->getAnDerReihe()-1]->starteKI();
}

void MainWindow::zugPhase(int n)
{
    bool kannSpielen=gueltigerZugVorhanden(n,madn->getAnDerReihe());
    user[(madn->getAnDerReihe())-1]->setGueltigerZugVorhanden(kannSpielen);
    user[(madn->getAnDerReihe())-1]->zugPhase(n);
}

void MainWindow::anderTimer(int n)
{
    ui->timer->display(n);
}

void MainWindow::empfangeSpielparamter(int timer, int anzSpieler,
                                       int figurArt, bool lokalesSpiel, QString name)
{
    figurenInit(anzSpieler,figurArt);
    timeout->setSekunden(timer);
    spielInit(anzSpieler,lokalesSpiel);
    eigenName = name;
    for(int i=0;i<4;i++)
        user[i]->initSpieler(i);
    if (lokalesSpiel)
        spiele(gelb);
    else
    {
        ui->textBrowser->append(QString("Netzwerkspiel starten mit folgenden Einstellungen:"));
        ui->textBrowser->append(QString("Timer %1").arg(timer));
        ui->textBrowser->append(QString("Spieleranzahl %1").arg(anzSpieler));
        ui->textBrowser->append(QString("Figurtyp %1").arg(figurArt));
        ui->textBrowser->append(QString("Benutzername: %1").arg(name));

    }
    /*Spielparameter:
     timer in sekunden
     anzSpieler: 2,3 oder 4;
     spielfiguren: 1=standardfiguren, 2=schneemann, 3=smiley
     lokalesspiel: 0=nein, 1=ja
     name: Benutzername des Servers
    */
}

void MainWindow::setzeNetzwerkverbindung(Netzwerkverbindung *verbindung) {
    connect(verbindung, SIGNAL(chatEmpfangen(QString)), ui->textBrowser, SLOT(append(QString)));
    connect(this, SIGNAL(nachrichtZuSenden(QString, QString)), verbindung, SLOT(sendeChat(QString, QString)));
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    ui->lineEdit->clear();
    ui->textBrowser->append(QString::fromUtf8("<b>") + eigenName + QString::fromUtf8("</b>: ") + text);
    emit nachrichtZuSenden(eigenName, text);
}

//Cheat-Button
void MainWindow::on_actionOptionen_triggered()
{
    ui->hauptwurfel->sechs();
}

void MainWindow::setzeName(QString name) {
    eigenName = name;
}
