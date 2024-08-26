#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QTimer>
#include <QApplication>
#include <QMessageBox>

class ProgressBar : public QWidget {
    Q_OBJECT

public:
    explicit ProgressBar(QWidget *parent = nullptr);

private slots:
    void updateProgress();

private:
    QProgressBar *progressBar;
    QTimer *timer;
    int currentValue;
};

// Implementation
ProgressBar::ProgressBar(QWidget *parent)
    : QWidget(parent), currentValue(0) {
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 50);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(progressBar);

    setLayout(layout);
    setWindowTitle("Please wait");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ProgressBar::updateProgress);
    timer->start(50); // Update every 50 ms

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void ProgressBar::updateProgress() {
    if (currentValue < 50) {
        currentValue++;
        progressBar->setValue(currentValue);
    } else {
        timer->stop();
        QMessageBox::information(this, "Information", "Compressed File saved successfully");
        close();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ProgressBar window;
    window.show();
    return app.exec();
}

#endif // PROGRESSBAR_H
