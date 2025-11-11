#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    double sensitivity = 1 * 0.0000000000001;
    qDebug()<<QString::number(sensitivity);
    qDebug()<<QString("Sensitivity : %1").arg(sensitivity);


    QString data = "30 40 50 66 70 80 FF FF FF FF FF FF FF FF 33 33 FF EE FF";
    QByteArray rawData = QByteArray::fromHex(data.toUtf8());

    int fIndex = rawData.indexOf(QByteArray::fromHex("FF FF FF FF FF FF"));

    qDebug()<<rawData.indexOf(QByteArray::fromHex("FF FF FF FF FF FF"));

    rawData.remove(fIndex,(rawData.size() - fIndex) - 5);

    qDebug()<<rawData.toHex(' ').toUpper();


    //startsWith exploration

    //QString randomData = "duskTillDawn";
    QString randomData = "duskTillHome";

    if(randomData.startsWith("dusk"))
    {
        qDebug()<<"Passed";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showDialog(const QString &text, int seconds)
{
    //heap , lambdas and timers

    QDialog *newDlg = new QDialog(this);
    newDlg->setWindowTitle("Heap Visualization");
    newDlg->resize(200,200);
    qDebug()<<"Creating : "<<newDlg;


    int *remSeconds = new int(seconds);
    QTimer *timer = new QTimer(newDlg);
    timer->setInterval(1000);

    QVBoxLayout *layout = new QVBoxLayout(newDlg);

    QLabel *newLabel = new QLabel(newDlg);
    QLabel *timerLabel = new QLabel(newDlg);

    newLabel->setText(text);
    connect(timer,&QTimer::timeout,newDlg,[timerLabel,remSeconds](){
        (*remSeconds)--;
        timerLabel->setText(QString::number(*remSeconds));
        timerLabel->repaint();
    });


    newLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setAlignment(Qt::AlignCenter);


    newLabel->setStyleSheet("font:16px;background-color:#5634FF;font-weight:bold;color:yellow");
    timerLabel->setStyleSheet("font:16px;background-color:#6512FF;font-weight:bold;color:yellow");

    layout->addWidget(newLabel);
    layout->addWidget(timerLabel);


    newDlg->show();
    timer->start();

    QTimer::singleShot(seconds*1000,[newDlg,newLabel,remSeconds]()
    {
        newLabel->setStyleSheet("font:16px;background-color:red;font-weight:bold;color:yellow");
        newLabel->setText("CLOSING");
        newDlg->repaint();

        QTimer::singleShot(1000, [newDlg, remSeconds]() {
                   qDebug() << "Deleting : " << newDlg;
                   newDlg->close();
                   delete newDlg;
                   delete remSeconds;
               });
    });
}

void MainWindow::on_pushButton_clicked()
{
    zSec = ui->spinBox_seconds->value();

    if(ui->spinBox_seconds->value() > 10 && ui->spinBox_seconds->value() < 80)
    {
        showDialog("Zubair",zSec);
    }
    else
    {
        QMessageBox::warning(this,"Error","Please enter a value between 11 to 79");
    }
}
