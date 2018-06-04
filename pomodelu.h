#ifndef POMODELU_H
#define POMODELU_H

#include <QDialog>

namespace Ui {
class PoModelu;
}

class PoModelu : public QDialog
{
    Q_OBJECT

public:
    explicit PoModelu(QWidget *parent = 0);
    ~PoModelu();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonPrikazi_clicked();

private:
    Ui::PoModelu *ui;
};

#endif // POMODELU_H
