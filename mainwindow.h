#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    char board[3][3];
    QPushButton* button[3][3];
    void updateUI();
    void makeAImove();
    bool checkWinner();

private slots:
    void handlePlayerMove();
};
#endif // MAINWINDOW_H
