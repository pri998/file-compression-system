#include "MainWindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    scrollArea = new QScrollArea(this);
    textEdit = new QTextEdit(this);
    textEdit->setColumnCount(20);
    textEdit->setRowCount(5);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    centralWidget->setLayout(layout);

    scrollArea->setWidget(textEdit);
    scrollArea->setWidgetResizable(true);
}

MainWindow::~MainWindow()
{
}
