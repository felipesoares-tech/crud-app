#ifndef NEWCONTACT_H
#define NEWCONTACT_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class newContact;
}

class newContact : public QDialog
{
    Q_OBJECT

public:
    explicit newContact(QWidget *parent = nullptr,QListWidget *lista = nullptr);
    ~newContact();

private slots:
    void on_btnBack_clicked();
    void on_btnSave_clicked();


private:
    Ui::newContact *ui;
};

#endif // NEWCONTACT_H
