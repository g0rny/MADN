#ifndef LOBBY_H
#define LOBBY_H

#include <QDialog>

namespace Ui {
class Lobby;
}

class Lobby : public QDialog
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent = 0);
    ~Lobby();

signals:
    void spielerzahl(int);

private slots:
    void abbrechen();
    void starten();

private:
    Ui::Lobby *ui;
    int anzSpieler=1;
};

#endif // LOBBY_H
