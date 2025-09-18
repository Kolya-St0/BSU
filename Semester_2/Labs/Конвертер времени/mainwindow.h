#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <dialog.h>
#include <QMainWindow>
#include <QMap>
#include <QList>
#include <QStringListModel>
#include <QMessageBox>
#include <QFile>

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
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

    void on_comboBox_activated(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    bool check;

    int ind1;
    int ind2;

    double time;

    QMap <int,int> conv;
    QMap <int,QString> times;
    QList <QString> log;
    QStringListModel model;

    Dialog *dial = nullptr;
};
#endif // MAINWINDOW_H
