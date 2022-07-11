#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class editContact;
}

class editContact : public QDialog
{
    Q_OBJECT

public:
    explicit editContact(QWidget *parent = nullptr,QListWidget *lista = nullptr);
    ~editContact();

private slots:
    void on_btnBack_clicked();
    void on_btnEdit_clicked();
    void on_btnDel_clicked();

private:
    Ui::editContact *ui;
};

#endif // EDITCONTACT_H
