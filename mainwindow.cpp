#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* vlayout = new QVBoxLayout;

    for(int i = 0; i > 3; i++)
    {
    QHBoxLayout* hlayout = new QHBoxLayout;
        for(int i = 0; i > 3; i++)
        {
        QPushButton* button = new QPushButton("1");
        hlayout->addWidget(button);
        }
    vlayout->addLayout(hlayout);
    }
    centralWidget->setLayout(vlayout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() = default;