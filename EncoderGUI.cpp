#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QFile>
#include <QString>
#include <iostream>

class EncoderGUI : public QWidget {
    Q_OBJECT

public:
    EncoderGUI(QWidget *parent = nullptr);

private slots:
    void compressBitsAction();
    void compBytesAction();
    void openFile();
    void saveFile();

private:
    bool ensureValidityOfPath(const QString &path);
    QString convertFileToString(const QFile &file);
    bool fileCompressed;
    QString filePath;
    QString savePath;
    QLineEdit *fileLineEdit;
    QLineEdit *saveLineEdit;
    // HuffmanEncoder encoder; // Assuming you have a HuffmanEncoder class
    bool hasBeenCompressed;
};

EncoderGUI::EncoderGUI(QWidget *parent) : QWidget(parent), fileCompressed(false), hasBeenCompressed(false) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *introLabel = new QLabel("Select a File To Compress:", this);
    layout->addWidget(introLabel);

    fileLineEdit = new QLineEdit(this);
    layout->addWidget(fileLineEdit);

    QPushButton *openButton = new QPushButton("Browse", this);
    connect(openButton, &QPushButton::clicked, this, &EncoderGUI::openFile);
    layout->addWidget(openButton);

    QPushButton *compressButton = new QPushButton("Compress", this);
    connect(compressButton, &QPushButton::clicked, this, &EncoderGUI::compressBitsAction);
    layout->addWidget(compressButton);

    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &EncoderGUI::saveFile);
    layout->addWidget(saveButton);

    saveLineEdit = new QLineEdit(this);
    layout->addWidget(saveLineEdit);

    QPushButton *compBytesButton = new QPushButton("CompSize", this);
    connect(compBytesButton, &QPushButton::clicked, this, &EncoderGUI::compBytesAction);
    layout->addWidget(compBytesButton);

    setLayout(layout);
}

void EncoderGUI::openFile() {
    filePath = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
    if (!filePath.isEmpty()) {
        fileLineEdit->setText(filePath);
    }
}

void EncoderGUI::saveFile() {
    savePath = QFileDialog::getSaveFileName(this, "Save Compressed File", "", "Text Files (*.txt);;All Files (*)");
    if (!savePath.isEmpty()) {
        saveLineEdit->setText(savePath);
        // Save the compressed data to the savePath
    }
}

bool EncoderGUI::ensureValidityOfPath(const QString &path) {
    return QFile::exists(path);
}

QString EncoderGUI::convertFileToString(const QFile &file) {
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QTextStream in(&file);
    return in.readAll();
}

void EncoderGUI::compressBitsAction() {
    if (!ensureValidityOfPath(fileLineEdit->text())) {
        QMessageBox::critical(this, "ERROR", "Invalid Path");
        return;
    }

    QFile file(fileLineEdit->text());
    QString contents = convertFileToString(file);
    
    // encoder = HuffmanEncoder(Message(contents.toStdString()));
    // encoder.compress();
    hasBeenCompressed = true;

    QMessageBox::information(this, "Compression", "Compression done successfully");
}

void EncoderGUI::compBytesAction() {
    if (!saveLineEdit->text().isEmpty() && hasBeenCompressed) {
        QFile file(saveLineEdit->text());
        if (file.exists()) {
            qint64 fileSize = file.size();
            QMessageBox::information(this, "Compressed Size", "Compressed Size: " + QString::number(fileSize * 0.001) + " KB");
        }
    } else {
        QMessageBox::warning(this, "No File Selected", "No file has been selected");
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EncoderGUI window;
    window.resize(400, 300);
    window.setWindowTitle("Huffman Encoder");
    window.show();

    return app.exec();
}

#include "main.moc"
