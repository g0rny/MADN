#include "lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lobby)
{

    ui->setupUi(this);
    connect(ui->btnAbbrechen, SIGNAL(clicked()),
                    this, SLOT(abbrechen()));
    connect(ui->btnSpielStarten, SIGNAL(clicked()),
                    this, SLOT(starten()));
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::abbrechen(){
    ui->textBrowser->append(QString("teeest"));
    this->close();
}

void Lobby::starten()
{
    emit spielerzahl(anzSpieler);
    this->close();
}
