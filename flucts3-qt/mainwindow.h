#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStringList>
#include <QString>
#include <QKeySequence>

#include "files.h"
#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    //on_deductFluctsOfBB_click();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QStringList filesList;
    std::vector<int> frequencies;
    QString source;
    QString from, to;
    ffactory* factory;
    txtfile* tfile;
    int b12timesPressed = 0;
};

#endif // MAINWINDOW_H
