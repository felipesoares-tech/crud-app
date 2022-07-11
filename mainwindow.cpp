#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newcontact.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database");

    bool criar = QFile::exists("database") ? false: true;

    if(!db.open())
        qDebug()<<"Não foi possível abrir o banco de dados!!" << db.lastError().text();
    else
        qDebug()<<"Banco de dados aberto com sucesso =)";

    if(criar){
        QSqlQuery sql;
        if(!sql.exec("create table tb_contatos(name STRING, day VARCHAR(2), month VARCHAR(2))"))
            qDebug()<<"Erro ao criar tablela" << sql.lastError().text();
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_contatos");

    if(query.exec()){
        while (query.next()){
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/new/icons/person-circle.png"),query.value(0).toString());
            ui->listWidget->addItem(item);
            ui->listWidget->sortItems(Qt::SortOrder::AscendingOrder);
        }

    }else{
        qDebug()<<"Erro ao buscar contatos !!";

    }

    ui->pesquisa->setPlaceholderText("Pesquise pelo nome..");
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(edit_window()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void load_combo(QComboBox *day, QComboBox *month){

    for(size_t i=1; i<32; i++){
        QString s = QString::number(i);
        day->addItem(s);
        if(i <= 12)
            month->addItem(s);
    }
}

void MainWindow::edit_window()
{
    hide();
    window_edit = new editContact(this, this->ui->listWidget);
    window_edit->show();
}

void MainWindow::on_addNew_clicked()
{
    hide();
    window_contact = new newContact(this, this->ui->listWidget);
    window_contact->show();
}

void MainWindow::on_pesquisa_textChanged(const QString &arg1)
{
    ui->pesquisa->setInputMethodHints(Qt::ImhSensitiveData);
    for(int i=0; i<ui->listWidget->count(); i++)
        ui->listWidget->item(i)->setHidden(!ui->listWidget->item(i)->text().contains(arg1,Qt::CaseInsensitive));
}
