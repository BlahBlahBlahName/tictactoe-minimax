#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePlayerMove();

private:
    QPushButton* button[3][3];
    char board[3][3];

    char checkWinner();
    int  evaluate();
    bool isMovesLeft();
    int  minimax(int depth, bool isMaximizing);
    void makeAImove();
    void disableAllButtons();
};

#endif // MAINWINDOW_H