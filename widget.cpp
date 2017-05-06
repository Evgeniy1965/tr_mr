#include "widget.h"
#include "ui_widget.h"
#include <QHash>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_3_clicked()
{

translate_cod();
}

void Widget::translate_cod(){

    QHash<QString, QString> dict;
    QString source,dest,buf;
    int cb,j;
    dict.insert("A",".-");  dict.insert("B","-...");  dict.insert("C","-.-.");
    dict.insert("D",".-");  dict.insert("E",".");  dict.insert("F","..-.");
    dict.insert("G","--."); dict.insert("H","...."); dict.insert("I","..");
    dict.insert("J",".---"); dict.insert("K","-.-");dict.insert("L",".-..");
    dict.insert("M","--"); dict.insert("N","-.");dict.insert("O","---");
    dict.insert("P",".--."); dict.insert("Q","--.-");dict.insert("R",".-.");
    dict.insert("S","..."); dict.insert("T","-");dict.insert("U","..-");
    dict.insert("V","...-"); dict.insert("W",".--");dict.insert("X","-..-");
    dict.insert("Y","-.--"); dict.insert("Z","--..");
    source = ui ->textEdit->toPlainText().toUpper();
    int count_char=source.length();
    dest="";
    if(fl){
         ui ->label->setText("Латиница");

         for( int i=0;i<count_char;i++){
             dest=dest+dict.value(source.at(i));
             dest+=" ";
             if(source.at(i)==' ')
                 dest=dest+" ";
         }
         ui ->textEdit_2->setPlainText(dest);
    }
    else{
         ui ->label ->setText("Морзе");
         QStringList list;
         list = source.split(" ");
         for(int i=0;i<list.size();i++){
             if(list.at(i)!="")dest+=dict.key(list.at(i)); else dest+=" ";
         }
         ui ->textEdit_2->setPlainText(dest);
    }
}

void Widget::on_textEdit_textChanged()
{
    QString source;
    QRegExp rx("[A-Z]+");

    source = ui ->textEdit->toPlainText().toUpper();

    if (rx.indexIn(source)>=0){
            fl=1;
            ui ->label->setText("Латиница");
    }
    else {
            fl=0;
            ui ->label->setText("Морзе");
    }
}

void Widget::on_pushButton_clicked()
{   QString fileName=QFileDialog::getOpenFileName(this,"Выберите файл.");
    QFile fileDat(fileName);
    QString buf="";
    if(!fileDat.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Ошибка окрытия файла";
    }
    else{
        while (!fileDat.atEnd()) {
            buf+=fileDat.readLine();
        }
        ui ->textEdit ->setPlainText(buf);
    }
    fileDat.close();
}


void Widget::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"введите имя файла");
    QFile fileDat(fileName);
    QString buf="";
    if(!fileDat.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"Ошибка открытия файла";
    }
    else{
        QTextStream writeStr(&fileDat);
        buf=ui ->textEdit_2->toPlainText();
        writeStr<<buf;
        fileDat.close();
    }

}
