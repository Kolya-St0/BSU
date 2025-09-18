#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    conv = {{0,1},{1,60},{2,3600},{3,86400},{4,604800},
           {5,2592000},{6,31104000},{7,311040000},
           {8,3110400000}};

    times = {{0,"секунды"},{1,"минуты"},{2,"часы"},{3,"дни"},{4,"недели"},
            {5,"месяцы"},{6,"годы"},{7,"десятилетия"},
            {8,"столетия"}};

    model.setStringList(log);

    ind1 = 0;
    ind2 = 0;

    ui->radioButton->setChecked(true);
    ui->listView->setModel(&model);

    dial = new Dialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked()
{
    ind1 = 0;
}


void MainWindow::on_radioButton_2_clicked()
{
    ind1 = 1;
}


void MainWindow::on_radioButton_3_clicked()
{
    ind1 = 2;
}


void MainWindow::on_radioButton_4_clicked()
{
    ind1 = 3;
}


void MainWindow::on_radioButton_5_clicked()
{
    ind1 = 4;
}


void MainWindow::on_radioButton_6_clicked()
{
    ind1 = 5;
}


void MainWindow::on_radioButton_7_clicked()
{
    ind1 = 6;
}


void MainWindow::on_radioButton_8_clicked()
{
    ind1 = 7;
}


void MainWindow::on_radioButton_9_clicked()
{
    ind1 = 8;
}


void MainWindow::on_comboBox_activated(int index)
{
    ind2 = index;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    time = arg1.toDouble(&check);
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Ошибка", "ты че тупой?");
        return;
    }

    if(check && time >= 0){
        time = time*conv[ind1];
        ui->label->setText(QString::number(time/conv[ind2]));
        time = ui->lineEdit->text().toDouble();
        log.push_front(ui->lineEdit->text()+" "+times[ind1]+" -> "+ui->label->text()+" "+times[ind2]);

        if(dial->isCheckBoxChecked()){
            QFile file("log.txt");
            file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
            QTextStream out(&file);
            out<<log.front()<<Qt::endl;
            file.close();
        }

        model.setStringList(log);
        ui->listView->setModel(&model);
    }

    else {
        ui->label->setText("ты че тупой?");
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    log.clear();
    model.setStringList(log);
    ui->listView->setModel(&model);
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.close();
}


void MainWindow::on_pushButton_3_clicked()
{
    dial->show();
}

