#ifndef THREADED_TEXT_HPP
#define THREADED_TEXT_HPP

#include <QString>
#include <QLabel>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

class ThreadedText : public QThread {
    Q_OBJECT

public:
    ThreadedText(const QString& text, QLabel* field);
    void run() override;

private:
    QString text;
    QLabel* field;
    QMutex mutex;
};

// Implementation

ThreadedText::ThreadedText(const QString& text, QLabel* field)
    : text(text), field(field) {
    // Constructor implementation
}

void ThreadedText::run() {
    QString str;
    for (int i = 0; i < text.length(); ++i) {
        QMutexLocker locker(&mutex);
        str += text.at(i);
        QThread::msleep(100);
        QMetaObject::invokeMethod(field, "setText", Qt::QueuedConnection, Q_ARG(QString, str));
    }
}

#endif // THREADED_TEXT_HPP

