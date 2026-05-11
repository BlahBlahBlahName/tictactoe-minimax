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
            button[i][j]->setIcon(QIcon(":/new/image/Empty.png"));
            button[i][j]->setIconSize(QSize(60, 60));

            hlayout->addWidget(button[i][j]);
            connect(button[i][j], &QPushButton::clicked, this, &MainWindow::handlePlayerMove);
        }
        vlayout->addLayout(hlayout);
    }
    setCentralWidget(centralWidget);
}

void MainWindow::handlePlayerMove()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (button[i][j] == clickedButton && board[i][j] == ' ') {
                board[i][j] = 'X';
                button[i][j]->setIcon(QIcon(":/new/image/PlayerCheck.png"));
                button[i][j]->setEnabled(false);

                if (checkWinner() == 'X') {
                    QMessageBox::information(this, "Game Over", "You win!");
                    disableAllButtons();
                    return;
                }
                if (!isMovesLeft()) {
                    QMessageBox::information(this, "Game Over", "It's a draw!");
                    return;
                }

                makeAImove();
                return;
            }
        }
    }
}

char MainWindow::checkWinner()
{
    // Rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][1] == board[i][0] && board[i][2] == board[i][0])
            return board[i][0];
        if (board[0][i] != ' ' && board[1][i] == board[0][i] && board[2][i] == board[0][i])
            return board[0][i];
    }
    // Diagonals
    if (board[0][0] != ' ' && board[1][1] == board[0][0] && board[2][2] == board[0][0])
        return board[0][0];
    if (board[0][2] != ' ' && board[1][1] == board[0][2] && board[2][0] == board[0][2])
        return board[0][2];

    return ' '; // No winner
}

int MainWindow::evaluate()
{
    char winner = checkWinner();
    if (winner == 'O') return +10;
    if (winner == 'X') return -10;
    return 0;
}

bool MainWindow::isMovesLeft()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return true;
    return false;
}

int MainWindow::minimax(int depth, bool isMaximizing)
{
    int score = evaluate();

    if (score == +10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = std::max(best, minimax(depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = +1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = std::min(best, minimax(depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void MainWindow::makeAImove()
{
    int bestVal = -1000;
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    if (bestRow != -1) {
        board[bestRow][bestCol] = 'O';
        button[bestRow][bestCol]->setIcon(QIcon(":/new/image/EnemyCheck.png"));
        button[bestRow][bestCol]->setEnabled(false);

        if (checkWinner() == 'O') {
            QMessageBox::information(this, "Game Over", "AI wins!");
            disableAllButtons();
        } else if (!isMovesLeft()) {
            QMessageBox::information(this, "Game Over", "It's a draw!");
        }
    }
}

void MainWindow::disableAllButtons()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            button[i][j]->setEnabled(false);
}

MainWindow::~MainWindow() = default;
