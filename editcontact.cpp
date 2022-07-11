#include "editcontact.h"
#include "ui_editcontact.h"
#include "mainwindow.h"
#include <QMessageBox>


size_t press_edit=0;
static QListWidget *listWidget;
extern agenda *inicio,*fim;
QString current_name;

editContact::editContact(QWidget *parent,QListWidget *lista) :
    QDialog(parent),
    ui(new Ui::editContact)
{
    ui->setupUi(this);
    listWidget = lista;
    current_name = lista->currentItem()->text();

    QSqlQuery query;
    query.prepare("select * from tb_contatos where name='"+current_name+"'");
    if(query.exec()){
        query.first();
        qDebug()<< "Contato localizado com sucesso!";
    }else
        qDebug()<< "Contato não encontrado!";

    ui->name_txt->setText(query.value(0).toString());
    ui->name_txt->setReadOnly(true);
    ui->dd->setEnabled(false);
    ui->mm->setEnabled(false);

    ui->dd->addItem(query.value(1).toString());
    ui->mm->addItem(query.value(2).toString());
}

editContact::~editContact()
{
    delete ui;
}

void editContact::on_btnBack_clicked()
{
    hide();
    press_edit=0;
    listWidget->clearSelection();
    parentWidget()->show();
}


void editContact::on_btnEdit_clicked()
{

    if(press_edit == 0){

        ui->title->setText("Editando contato");
        ui->btnEdit->setText("SALVAR");
        ui->btnDel->setVisible(false);
        ui->name_txt->setReadOnly(false);
        ui->name_txt->setStyleSheet("background-color: #FFFFFF;");
        ui->dd->setEnabled(true);
        ui->mm->setEnabled(true);

        QString aux_d=ui->dd->currentText(),aux_m=ui->mm->currentText();
        ui->dd->clear();
        ui->mm->clear();
        load_combo(ui->dd,ui->mm);

        ui->dd->setCurrentText(aux_d);
        ui->mm->setCurrentText(aux_m);

        press_edit++;
    }else{
        QSqlQuery query;

        QString new_name = ui->name_txt->text();
        QString new_day = ui->dd->currentText();
        QString new_month = ui->mm->currentText();

        query.prepare("update tb_contatos set name='"+new_name+"',day='"+new_day+"',month='"+new_month+"' where name='"+current_name+"'");
        if(query.exec())
            qDebug()<<"Contato atualizado com sucesso!";



        listWidget->currentItem()->setText(ui->name_txt->text());
        listWidget->sortItems(Qt::SortOrder::AscendingOrder);
        listWidget->clearSelection();
        press_edit=0;
        hide();
        parentWidget()->show();
    }
}


void editContact::on_btnDel_clicked()
{
    QMessageBox::StandardButton resp = QMessageBox::question(this,"","Tem certeza que deseja excluir esse contato?",QMessageBox::Yes|QMessageBox::No);
    if(resp == QMessageBox::Yes){
        hide();
        parentWidget()->show();
        QListWidgetItem *item_del = listWidget->takeItem(listWidget->currentRow());
        delete item_del;
        listWidget->clearSelection();

        QSqlQuery query;
        query.prepare("delete from tb_contatos where name='"+current_name+"'");
        if(query.exec())
            qDebug()<<"Contato deletado com sucesso!";
        else
            qDebug()<<"Erro ao deletar contato";
    }
}

