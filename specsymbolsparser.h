#ifndef SPECSYMBOLSPARSER_H
#define SPECSYMBOLSPARSER_H

#include <QObject>
#include <QTextEdit>
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>

class SpecSymbolsParser : public QObject
{
    Q_OBJECT

protected:
    QMap<QString, QString> m_commandsAndSpecSymbols;
    QTextEdit* m_textEdit;
public:
    SpecSymbolsParser(QObject*);
    void setTextEdit(QTextEdit*);

public slots:
    void changeOnSpecSymbol();
};

#endif // SPECSYMBOLSPARSER_H
