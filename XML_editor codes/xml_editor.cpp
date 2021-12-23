#include "xml_editor.h"
#include "ui_xml_editor.h"
#include "Formatting.h"
#include "minify.h"
#include "Consistency.h"
#include "compress.h"
#include "decompress.h"
#include "tree.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <string>

static QString file_name;
static QString spare_file_name = NULL;
static QString mext;
static QString corrected_file;
static bool pox;


XML_editor::XML_editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XML_editor)
{
    ui->setupUi(this);
   // setStyleSheet("XML_editor {background-image: url(:/image/image/violet-linear-turquoise-gradient-1440x1920-c2-9c23fc-38e99d-a-15-f-14.png);}");

    ui->Output->setReadOnly(true);
    ui->Input->setReadOnly(true);
}

XML_editor::~XML_editor()
{
    delete ui;
}

void XML_editor::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/violet-linear-turquoise-gradient-1440x1920-c2-9c23fc-38e99d-a-15-f-14.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QMainWindow::resizeEvent(evt); // call inherited implementation
}


   void XML_editor::on_load_clicked()
{


    QString filter = "*.xml ;; *.json";
    file_name = QFileDialog::getOpenFileName(this,"Select a file","C://",filter);
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text)){

      //  QMessageBox::warning(this,"Warning","You did not select a file");
        pox = true;
        ui->Input->setText(mext);
        return;


    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->Input->setText(text);
    file.close();


     mext = text;
    spare_file_name= file_name;
    pox = false;





}


 void XML_editor::on_format_clicked()
{
      QString text;
     if(pox == true){
         QDir m = QFileInfo(spare_file_name).dir();
         QString direc=m.absolutePath();
         QFile file(direc + "/Corrected.xml");
         if(!file.open(QFile::ReadOnly | QFile::Text)){

         }
         QTextStream in(&file);
         text = in.readAll();

         file.close();

     }
     else{
         text = ui->Input->toPlainText();
         }

    if (text.isEmpty())
    {
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;
    }
    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();

    if(pox == true)
    {
         format(text.toStdString(),direc.toStdString()+"/Formatted.xml");
    }
    else{
         format(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Formatted.xml");
        }
//    format(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Formatted.xml");

    QString file_name1 = direc + "/Formatted.xml";
    QFile file(file_name1);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File is not open");

    }
    QTextStream in(&file);
    QString text2 = in.readAll();
    ui->Output->setText(text2);
     QMessageBox::information(this,"Congrats","File is successfully formatted and saved in the same directory as original file");
    file.close();
}


void XML_editor::on_minify_clicked()
{
    QString text;
    if(pox == true){
        QDir m = QFileInfo(spare_file_name).dir();
        QString direc=m.absolutePath();
        QFile file(direc + "/Corrected.xml");
        if(!file.open(QFile::ReadOnly | QFile::Text)){

        }
        QTextStream in(&file);
        text = in.readAll();
        file.close();
//        text = ui->Output->toPlainText();

    }
    else{
        text = ui->Input->toPlainText();
        }
    if (text.isEmpty()){
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;

    }
    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();
    //QDir d = QFileInfo(filePath).absoluteDir();
    if(pox == true){
       minify(text.toStdString(),direc.toStdString()+"/Minified.xml");

    }
    else{
       minify(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Minified.xml");
        }
//    minify(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Minified.xml");

    QString file_name = direc + "/Minified.xml";
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File is not open");
    }
    QTextStream in(&file);
    QString text2 = in.readAll();
    ui->Output->setText(text2);
     QMessageBox::information(this,"Congrats","File is successfully minified and saved in the same directory as original file");
    file.close();
}


void XML_editor::on_convert_clicked()
{
    QString text;
    if(pox == true){
        QDir m = QFileInfo(spare_file_name).dir();
        QString direc=m.absolutePath();
        QFile file(direc + "/Corrected.xml");
        if(!file.open(QFile::ReadOnly | QFile::Text)){

        }
        QTextStream input_text(&file);
        text = input_text.readAll();

        file.close();
//        text = ui->Output->toPlainText();

    }
    else{
        text = ui->Input->toPlainText();
        }
    if (text.isEmpty()){
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;

    }


    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();
    if(pox == true){
//        QString correct = direc + "/Corrected.xml";
//        QFile file3(correct);

//        if(!file3.open(QFile::ReadOnly | QFile::Text)){

//          //  QMessageBox::warning(this,"Warning","You did not select a file");

//            return;

//        }


        Tree xml(direc.toStdString()+"/ConvertedtoJSON.json");
        xml.insert(spare_file_name.toStdString());
        xml.print_Json(xml.get_root());


    }
    else{
        Tree xml(direc.toStdString()+"/ConvertedtoJSON.json");
        xml.insert(spare_file_name.toStdString());
        xml.print_Json(xml.get_root());
        qDebug() << spare_file_name;

        }


//    Tree xml(direc.toStdString()+"/ConvertedtoJSON.json");
//    xml.insert(spare_file_name.toStdString());
//    xml.print_Json(xml.get_root());

    QString file_name = direc + "/ConvertedtoJSON.json";
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File is not open");
    }
    QTextStream in(&file);

    QString output_text = in.readAll();
    ui->Output->setText(output_text);

     QMessageBox::information(this,"Congrats","File is successfully converted to JSON and saved in the same directory as original file");
     file.flush();
     file.close();

}


void XML_editor::on_compress_clicked()
{
    QFileInfo fi(spare_file_name);
    QString ext = fi.suffix();
    if(ext == "xml"){
    QString text;
    if(pox == true){
//        text = ui->Output->toPlainText();
        QDir m = QFileInfo(spare_file_name).dir();
        QString direc=m.absolutePath();
        QFile file(direc + "/Corrected.xml");
        if(!file.open(QFile::ReadOnly | QFile::Text)){

        }
        QTextStream in(&file);
        text = in.readAll();

        file.close();

    }
    else{
        text = ui->Input->toPlainText();
        }
    if (text.isEmpty()){
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;

    }
    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();

    if(pox == true)
    {

             compress1(text.toStdString(),direc.toStdString()+"/Compressed.xml");
    }
    else{
            compress1(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Compressed.xml");
        }

//    compress1(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Compressed.xml");

    QString file_name = direc + "/Compressed.xml";
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File is not open");
    }
    QTextStream in(&file);
    QString text2 = in.readAll();
    ui->Output->setText(text2);
     QMessageBox::information(this,"Congrats","File is successfully compressed and saved in the same directory as original file");
    file.close();}
    else{
        QString text;

            text = ui->Input->toPlainText();

        if (text.isEmpty()){
            QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
            return;

        }
        QDir d = QFileInfo(spare_file_name).dir();
        QString direc=d.absolutePath();


                compress1(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Compressed.json");


    //    compress1(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Compressed.xml");

        QString file_name = direc + "/Compressed.json";
        QFile file(file_name);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,"Warning","File is not open");
        }
        QTextStream in(&file);
        QString text2 = in.readAll();
        ui->Output->setText(text2);
         QMessageBox::information(this,"Congrats","File is successfully compressed and saved in the same directory as original file");
        file.close();


    }
}


void XML_editor::on_decompress_clicked()
{       QFileInfo fi(spare_file_name);
        QString ext = fi.suffix();
        if(ext == "xml"){

    QString text;
    if(pox == true){
        QDir m = QFileInfo(spare_file_name).dir();
        QString direc=m.absolutePath();
        QFile file(direc + "/Corrected.xml");
        if(!file.open(QFile::ReadOnly | QFile::Text)){

        }
        QTextStream in(&file);
        text = in.readAll();

        file.close();

    }
    else{
        text = ui->Input->toPlainText();
        }

    if (text.isEmpty()){
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;

    }

    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();


 if(pox == true)
 {
    decompress(compress(text.toStdString(),direc.toStdString()+"/Decompressed.xml"),direc.toStdString()+"/Decompressed.xml");

 }
 else{
    decompress(compress(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Decompressed.xml"),direc.toStdString()+"/Decompressed.xml");
     }






 QString file_name = direc + "/Decompressed.xml";
 QFile file(file_name);
 if(!file.open(QFile::ReadOnly | QFile::Text)){
     QMessageBox::warning(this,"Warning","File is not open");
 }
 QTextStream in(&file);
 QString text2 = in.readAll();
 ui->Output->setText(text2);
  QMessageBox::information(this,"Congrats","File is successfully decompressed and saved in the same directory as compressed file");
 file.close();}
        else{

                           QString text = ui->Input->toPlainText();


            if (text.isEmpty()){
                QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
                return;

            }

            QDir d = QFileInfo(spare_file_name).dir();
            QString direc=d.absolutePath();


            decompress(compress(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Decompressed.json"),direc.toStdString()+"/Decompressed.json");

         QString file_name = direc + "/Decompressed.json";
         QFile file(file_name);
         if(!file.open(QFile::ReadOnly | QFile::Text)){
             QMessageBox::warning(this,"Warning","File is not open");
         }
         QTextStream in(&file);
         QString text2 = in.readAll();
         ui->Output->setText(text2);
          QMessageBox::information(this,"Congrats","File is successfully decompressed and saved in the same directory as compressed file");
         file.close();

        }

 }



void XML_editor::on_check_clicked()
{
    QString text = ui->Input->toPlainText();
    if (text.isEmpty()){
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;

    }
    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();
    //QDir d = QFileInfo(filePath).absoluteDir();

    consistency(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Corrected.xml",direc.toStdString()+"/Checked.xml",true);

    QString file_name2 = direc + "/Checked.xml";
    QFile file(file_name2);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File is not open");

    }
    QTextStream in(&file);
    QString text2 = in.readAll();
    ui->Output->setText(text2);
     QMessageBox::information(this,"Congrats","File is successfully checked and saved in the same directory as original file. Arrows point to errors found in the file");
    file.close();

}


void XML_editor::on_correct_clicked()
{
    pox = true;
    QString text = ui->Input->toPlainText();
    if (text.isEmpty()){
        QMessageBox::warning(this,"Error detected in input","Input is empty. Please load a file to proceed.");
        return;

    }
    QDir d = QFileInfo(spare_file_name).dir();
    QString direc=d.absolutePath();
    //QDir d = QFileInfo(filePath).absoluteDir();

    consistency(ui->Input->toPlainText().toStdString(),direc.toStdString()+"/Corrected.xml",direc.toStdString()+"/error.xml",false);

    QString file_name2 = direc + "/Corrected.xml";
    corrected_file = file_name2;
    QFile file(file_name2);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File is not open");

    }
    QTextStream in(&file);
    QString text2 = in.readAll();
    ui->Output->setText(text2);
     QMessageBox::information(this,"Congrats","File is successfully corrected and saved in the same directory as original file");
    file.close();
}

