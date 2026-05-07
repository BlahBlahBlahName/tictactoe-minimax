#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* vlayout = new QVBoxLayout(centralWidget);

    for (int i = 0; i < 3; ++i) {
        QHBoxLayout* hlayout = new QHBoxLayout();
        for (int j = 0; j < 3; ++j) {
            button[i][j] = new QPushButton("");
            button[i][j]->setFixedSize(60, 60);
            board[i][j] = ' ';
            button[i][j]->setIcon(QIcon("Empty.png"));
            button[i][j]->setIconSize(QSize(60,60));    // Initialize internal board

            hlayout->addWidget(button[i][j]);
            connect(button[i][j], &QPushButton::clicked, this, &MainWindow::handlePlayerMove);
            // Connect the button to our slot
        }
        vlayout->addLayout(hlayout);
    }
    setCentralWidget(centralWidget);
}

void MainWindow::handlePlayerMove()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;
    for(int i = 0; i <3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(button[i][j] == clickedButton && board[i][j] == ' ')
            {
                board[i][j] = 'X';
                button[i][j]->setIcon(QIcon("PlayerCheck.png"));
                if (checkWinner())
                {
                    QMessageBox::information(this, "Title", "You've won!");
                }
            }
        }
    }
}

bool MainWindow::checkWinner()
{
    for(int i = 0; i < 3; i++)
    {
        if(!(board[i][0] == ' ') && board[i][1] == board[i][0] && board[i][2] == board[i][0])
        {
            return true;
        }
        if(!(board[0][i] == ' ') && board[1][i] == board[0][i] && board[2][i] == board[0][i])
        {
            return true;
        }

    }
    if(!(board[0][0] == ' ') && board[1][1] == board[0][0] && board[2][2] == board[0][0])
    {
        return true;
    }
    if(!(board[0][2] == ' ') && board[1][1] == board[0][2] && board[2][0] == board[0][2])
    {
        return true;
    }
    return false;
}

MainWindow::~MainWindow() = default;