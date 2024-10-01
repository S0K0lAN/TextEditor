#include "specsymbolsparser.h"

SpecSymbolsParser::SpecSymbolsParser(QObject* parent) : QObject(parent) {
    //openning file
    QFile file("../../specSymbols.txt");
    if(!file.open(QFile::ReadOnly)){
        QMessageBox::critical(nullptr, tr("Can't open file"), tr("Maybe you enter wrong file path"));
        return;
    }

    //moving data from file to QMap
    QTextStream ts(&file);
    ts.setEncoding(QStringConverter::Utf8);
    while(!ts.atEnd()){
        QString line = ts.readLine(255);
        if(line.startsWith("//")){
            continue;
        }
        QString command = line.mid( line.indexOf("#@"),
                                    line.indexOf("@", line.indexOf("#@")+2)-line.indexOf("#@")+1 );
        QString sign = line.mid( line.indexOf(" ", line.indexOf("@"))+1,
                                 line.size()-1);
        QMap<QString, QString> item;
        item.insert(command, sign);
        m_commandsAndSpecSymbols.insert(item);
    }


    //closing
    ts.flush();
    file.close();
}


void SpecSymbolsParser::setTextEdit(QTextEdit* textEdit){
    m_textEdit = textEdit;
    connect(m_textEdit, &QTextEdit::textChanged, this, &SpecSymbolsParser::changeOnSpecSymbol);
}


void SpecSymbolsParser::changeOnSpecSymbol(){
    //taking command
    QString text = m_textEdit->toPlainText();
    QRegularExpression regExp("#@[^@]*@");
    qint64 commandStartIndex = text.indexOf(regExp);
    if(commandStartIndex == -1) return;
    QString command;
    command = text.mid(
        commandStartIndex,
        command.size()-1
    );
    qDebug() << command;

    //searching right spec symbol
    QString specSymbol = m_commandsAndSpecSymbols[command];

    //adding spec symbol to text
    text.remove(regExp);
    text.insert(commandStartIndex, specSymbol);
    m_textEdit->clear();
    m_textEdit->setPlainText(text);
}
