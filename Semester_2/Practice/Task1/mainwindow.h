#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "journals.h"
#include <QMainWindow>
#include <QFile>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenu>
#include <QKeyEvent>
#include <QInputDialog>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void filltable();

    void on_comboBox_activated(int index);

    void on_pushButton_customContextMenuRequested(const QPoint &pos);

    void keyPressEvent(QKeyEvent *event);

    void showDialog();

    void updatelist(QString filename);

    void push_back();

    void pop_back();

    void quicksort(int left, int right);

    void countsort();

private:
    Ui::MainWindow *ui;
    Journals*array;
    int size;
    int capacity;
    int ind;
    QMenu *contextMenu;
};
#endif // MAINWINDOW_H
