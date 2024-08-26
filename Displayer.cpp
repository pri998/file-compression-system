#include "Displayer.h"

Displayer::Displayer(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialize central widget and set it for the main window
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the scroll area and text edit components
    scrollArea = new QScrollArea(this);
    displayArea = new QTextEdit(this);
    displayArea->setColumnCount(20);
    displayArea->setRowCount(5);

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    centralWidget->setLayout(layout);

    // Set the scroll area to contain the text edit widget
    scrollArea->setWidget(displayArea);
    scrollArea->setWidgetResizable(true);

    // Set window properties
    setWindowTitle("Displayer");
    setGeometry(100, 100, 800, 600); // Example size, adjust as needed
    setWindowFlags(Qt::WindowCloseButtonHint); // Similar to `DISPOSE_ON_CLOSE`
}

Displayer::~Displayer()
{
}
