#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QMainWindow>
#include <QTextEdit>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>

class Displayer : public QMainWindow
{
    Q_OBJECT

public:
    Displayer(QWidget *parent = nullptr);
    ~Displayer();

private:
    QWidget *centralWidget;
    QScrollArea *scrollArea;
    QTextEdit *displayArea;
};

#endif // DISPLAYER_H
