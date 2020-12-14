#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <QApplication>
#include <QFileInfo>
#include <QTextStream>
#include <QFileDialog>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 public slots:
    void on_pushButton_2_clicked();
private slots:
    void on_pushButton_clicked();



    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

};

enum Direction { L, R, S, Q, };

struct State
{
    QString name;
    char input_symbol;
    QString next_state;
    char output_symbol;
    Direction dir;

};


#endif // MAINWINDOW_H
