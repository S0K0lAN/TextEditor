#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText(tr("Simple text"));

    // Ищем файлы с языками и добавляем в комбобокс
    QDir dir(":/tr/Languages");
    QStringList langs = dir.entryList(QDir::Files);

    for(auto iter = langs.begin(); iter < langs.end(); iter++)
        *iter = iter->mid(iter->indexOf("_")+1, 2);

    ui->comboBox->addItems(langs);

    // подключаем к сигналу изменения пункта комбобокса лямбда функцию,
    // в которой будет изменяться перевод приложения
    // Здесь имеется интересный момент. Поскольку QComboBox имеет перегрузку сигнатуры сигнала,
    // то нам необходимо скастовать сигнал к нужной сигнатуре.
    // В данном случае будем использовать название пункта при его изменении
    connect(ui->comboBox, &QComboBox::currentIndexChanged,
            [=](qint32 i){
                qtLanguageTranslator.load(":tr/Languages/QtLanguage_" + ui->comboBox->currentText(), ".");   // Загружаем перевод
                qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
            });
    // Сделаем первоначальную инициализацию перевода для окна приложения
    qtLanguageTranslator.load(QString(":/tr/Languages/QtLanguage_") + QString("ru"));
    qApp->installTranslator(&qtLanguageTranslator);
    ui->comboBox->setCurrentIndex(ui->comboBox->findText("ru"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    // В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);    // переведём окно заново
    }
}
