#include "newcontact.h"
#include "ui_newcontact.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

static QListWidget *listWidget;

newContact::newContact(QWidget *parent,QListWidget *lista) :
    QDialog(parent),
    ui(new Ui::newContact)
{
    ui->setupUi(this);
    listWidget = lista;
    load_combo(ui->dd,ui->mm);
}

newContact::~newContact()
{
    delete ui;
}

void newContact::on_btnBack_clicked()
{
    hide();
    parentWidget()->show();
}


void newContact::on_btnSave_clicked()
{
    QString name= ui->name_txt->text();
    QString month = ui->mm->currentText();
    QString day = ui->dd->currentText();

    QSqlQuery query;
    query.prepare("INSERT INTO tb_contatos (name,day,month) VALUES"
                  "('"+name+"','"+day+"','"+month+"')");

    if(query.exec())
        qDebug()<<"Registro Gravado com Sucesso";
    else
        qDebug()<<"Erro ao inserir registro";

    QListWidgetItem *item = new QListWidgetItem(QIcon(":/new/icons/person-circle.png"),name);
    listWidget->addItem(item);
    listWidget->sortItems(Qt::SortOrder::AscendingOrder);
    hide();
    parentWidget()->show();
}

