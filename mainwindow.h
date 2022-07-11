#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newcontact.h"
#include "editcontact.h"
#include <qcombobox.h>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QSqlError>
#include <QSqlRecord>

typedef struct NO{
    QString name,mm,dd;
}agenda;

void load_combo(QComboBox *, QComboBox *);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_addNew_clicked();
    void edit_window();
    void on_pesquisa_textChanged(const QString &arg1);

private:
    newContact * window_contact;
    editContact * window_edit;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
