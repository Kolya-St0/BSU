#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "journals.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setContentsMargins(0, 0, 0, 0);
    capacity = 20;
    array = new Journals[capacity];
    size = 0;
    ind = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete[]array;
}

void MainWindow::filltable()
{
    ui->tableWidget->setRowCount(size);
    for(int i = 0; i < size; i++){
        QTableWidgetItem*name = new QTableWidgetItem(array[i].getname());
        QTableWidgetItem*date = new QTableWidgetItem(array[i].getdate());
        QTableWidgetItem*pages = new QTableWidgetItem(QString::number(array[i].getpages()));
        ui->tableWidget->setItem(i,0,name);
        ui->tableWidget->setItem(i,1,date);
        ui->tableWidget->setItem(i,2,pages);
    }
}

void MainWindow::on_pushButton_clicked()
{
    updatelist("papich1.jpg");
    QFile file("input.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    if(!size){
        Journals temp;
        while(!in.atEnd()){
            in >> temp;
            size++;
        }
        file.seek(0);
        in.seek(0);
    }
    int i = 0;
    while(i < size && !in.atEnd()){
        in >> array[i];
        i++;
    }
    filltable();
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(array[0].isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Нечего сортировать");
        return;
    }
    if(!ind){
        countsort();
    }
    else{
        quicksort(0,size - 1);
    }
    updatelist("papich2.jpg");
    ui->tableWidget->reset();
    filltable();
}

void MainWindow::on_comboBox_activated(int index)
{
    ind = index;
}

void MainWindow::on_pushButton_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);
    QAction *readAction = menu.addAction("Прочитать определенное количество");
    connect(readAction, &QAction::triggered, this, &MainWindow::showDialog);
    menu.exec(ui->pushButton->mapToGlobal(pos));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        this->close();
        return;
    }
    if(event->key() == Qt::Key_Backspace){
        pop_back();
        ui->tableWidget->removeRow(size);
        return;
    }
    if(event->key() == Qt::Key_Return){
        push_back();
        ui->tableWidget->reset();
        filltable();
        return;
    }
}

void MainWindow::showDialog()
{
    size = QInputDialog::getInt(this, "Ввод количества", "Сколько строк прочитать?",0,0,8,1);
}

void MainWindow::updatelist(QString filename)
{
    ui->listWidget->clear();
    QPixmap pixmap(filename);
    ui->listWidget->setIconSize(pixmap.size());
    QListWidgetItem* item = new QListWidgetItem();
    item->setIcon(QIcon(pixmap));
    ui->listWidget->addItem(item);
    ui->listWidget->setFixedSize(pixmap.size() + QSize(10,10));
}

void MainWindow::push_back()
{
    if(size == capacity){
        capacity *= 2;
        Journals* newarray = new Journals[capacity];
        for (int i = 0; i < size; i++) {
            newarray[i] = array[i];
        }
        delete[] array;
        array = newarray;
    }
    QString temp = QInputDialog::getText(this, "Добавить журнал", "Поля через пробел:", QLineEdit::Normal, "");
    QStringList parts = temp.split(' ');
    array[size] = Journals(parts[0], parts[1], parts[2].toInt());
    size++;
}

void MainWindow::pop_back()
{
    if (size == 0 || array == nullptr) {
        QMessageBox::warning(this, "Ошибка", "Нечего удалять");
        return;
    }
    array[size - 1] = Journals();
    size--;
}

void MainWindow::quicksort(int left, int right)
{
    if(left > right) return;
    Journals mid = array[(left + right)/2];
    int i = left;
    int j = right;
    while(i <= j){
        while(array[i]<mid) i++;
        while(array[j]>mid) j--;
        if(i <= j){
            std::swap(array[i],array[j]);
            i++;
            j--;
        }
    }
    quicksort(left, j);
    quicksort(i, right);
}

void MainWindow::countsort()
{
    int max = array[0].getpages();
    for(int i = 0; i < size; i++){
        if(array[i].getpages() > max){
            max = array[i].getpages();
        }
    }
    int *tempcount = new int[max + 1];
    Journals *tempelem = new Journals[size];
    for(int i = 0; i < max + 1; i++){
        tempcount[i] = 0;
    }
    for(int i = 0; i < size; i++){
        tempcount[array[i].getpages()]++;
    }

    for(int i = 0; i < size; i++){
        tempelem[i] = array[i];
    }
    for(int i = 1; i < max + 1; i++){
        tempcount[i] += tempcount[i - 1];
    }
    for(int i = size - 1; i >= 0; i--){
        tempelem[tempcount[array[i].getpages() - 1]] = array[i];
        tempcount[array[i].getpages() - 1]--;
    }
    for(int i = 0; i < size; i++){
        array[i] = tempelem[i];
    }
    delete[]tempcount;
    delete[]tempelem;
}
