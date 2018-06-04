#ifndef BOJA_H
#define BOJA_H

#include <QDialog>

namespace Ui {
class Boja;
}

class Boja : public QDialog
{
    Q_OBJECT

public:
    explicit Boja(QWidget *parent = 0);
    ~Boja();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_lineEditSifra_editingFinished();

    void on_pushButtonObrisi_clicked();

    void on_pushButtonUpisi_clicked();

    void on_pushButtonIzmeni_clicked();

private:
    Ui::Boja *ui;
};

#endif // BOJA_H
