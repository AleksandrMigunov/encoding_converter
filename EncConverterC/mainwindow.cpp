/* Copyright (C) 2022 Aleksandr Migunov

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
  
You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>. */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
//#include <QDialog>
#include <QFileDialog>
//#include <QColorDialog>
//#include <QFontDialog>
//#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    NewOpened = "";
    ui->textEdit->clear();
    NewOpened = "new_window";
}

void MainWindow::on_actionOpen_triggered()
{
    NewOpened = "";
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("All Files(*.*)"));
    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");
            Encoding = "UTF-8";

            QString text = in.readAll();
            File.close();

            ui->textEdit->setAcceptRichText(false);
            ui->textEdit->setText(text);
        }
        else {
            QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
        }
    }
    FileOpened = file;
}

void MainWindow::on_actionEncoding_triggered()
{
    QStringList items;
    items << "UTF-8" << "Unicode (UTF-16)" << tr("Windows-1251 (Cyrillic)") << tr("KOI8-R (Cyrillic)") <<
             tr("CP866 / IBM866 (Cyrillic)") << tr("ISO 8859-5 (Cyrillic)") <<
             tr("Windows-1250 (Central European)") << tr("Windows-1252 (Western)") <<
             tr("Windows-1253 (Greek)") << tr("Windows-1254 (Turkish)") <<
             tr("Windows-1255 (Hebrew)") << tr("Windows-1256 (Arabic)") << tr("Windows-1257 (Baltic)") <<
             "ISO 8859-1 (Latin-1)" << "ISO 8859-2 (Latin-2)" <<
             "ISO 8859-3 (Latin-3)" << "ISO 8859-4 (Latin-4)" <<
             "ISO 8859-9 (Latin-5)" << "ISO 8859-10 (Latin-6)" <<
             "ISO 8859-13 (Latin-7)" << "ISO 8859-14 (Latin-8)" <<
             "ISO 8859-15 (Latin-9)" << "ISO 8859-16 (Latin-10)" <<
             tr("ISO 8859-6 (Arabic)") << tr("ISO 8859-7 (Greek)") << tr("ISO 8859-8 (Hebrew)");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Changing encoding"), tr("Choose encoding:"),
                                         items, 0, false, &ok);

    QString EncodingDocument;
    if (ok && !item.isEmpty()) {

        if (item == "UTF-8") EncodingDocument = "UTF-8";
        else if (item == "Unicode (UTF-16)") EncodingDocument = "Unicode";
        else if (item == tr("Windows-1251 (Cyrillic)")) EncodingDocument = "Windows-1251";
        else if (item == tr("KOI8-R (Cyrillic)")) EncodingDocument = "KOI8-R";
        else if (item == tr("CP866 / IBM866 (Cyrillic)")) EncodingDocument = "IBM866";
        else if (item == tr("ISO 8859-5 (Cyrillic)")) EncodingDocument = "ISO 8859-5";
        else if (item == tr("Windows-1250 (Central European)")) EncodingDocument = "Windows-1250";
        else if (item == tr("Windows-1252 (Western)")) EncodingDocument = "Windows-1252";
        else if (item == tr("Windows-1253 (Greek)")) EncodingDocument = "Windows-1253";
        else if (item == tr("Windows-1254 (Turkish)")) EncodingDocument = "Windows-1254";
        else if (item == tr("Windows-1255 (Hebrew)")) EncodingDocument = "Windows-1255";
        else if (item == tr("Windows-1256 (Arabic)")) EncodingDocument = "Windows-1256";
        else if (item == tr("Windows-1257 (Baltic)")) EncodingDocument = "Windows-1257";
        else if (item == "ISO 8859-1 (Latin-1)") EncodingDocument = "ISO 8859-1";
        else if (item == "ISO 8859-2 (Latin-2)") EncodingDocument = "ISO 8859-2";
        else if (item == "ISO 8859-3 (Latin-3)") EncodingDocument = "ISO 8859-3";
        else if (item == "ISO 8859-4 (Latin-4)") EncodingDocument = "ISO 8859-4";
        else if (item == "ISO 8859-9 (Latin-5)") EncodingDocument = "ISO 8859-9";
        else if (item == "ISO 8859-10 (Latin-6)") EncodingDocument = "ISO 8859-10";
        else if (item == "ISO 8859-13 (Latin-7)") EncodingDocument = "ISO 8859-13";
        else if (item == "ISO 8859-14 (Latin-8)") EncodingDocument = "ISO 8859-14";
        else if (item == "ISO 8859-15 (Latin-9)") EncodingDocument = "ISO 8859-15";
        else if (item == "ISO 8859-16 (Latin-10)") EncodingDocument = "ISO 8859-16";
        else if (item == tr("ISO 8859-6 (Arabic)")) EncodingDocument = "ISO 8859-6";
        else if (item == tr("ISO 8859-7 (Greek)")) EncodingDocument = "ISO 8859-7";
        else if (item == tr("ISO 8859-8 (Hebrew)")) EncodingDocument = "ISO 8859-8";
        else return;
    }

    QString file;
    if (!FileOpened.isEmpty())
    {
        file = FileOpened;
    }
    else if (!NewOpened.isEmpty())
    {
        file = "temp.txt";

        if(!file.isEmpty())
        {
            QDir direct;
            QString dir = direct.filePath(file);
            QString FileName = dir;
            QFile File(FileName);

            if(File.open(QFile::WriteOnly | QFile::Text))
            {
                QTextStream out(&File);
                out.setCodec("UTF-8");

                out << ui->textEdit->toPlainText();

                File.flush();
                File.close();
            }
        }


    }
    else
    {
        file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("All Files(*.*)"));
    }
    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            //in.setCodec("UTF-8");

            QString EncodingList = EncodingDocument;
            if (EncodingList == "UTF-8") in.setCodec("UTF-8");
            else if (EncodingList == "Unicode") in.setCodec("Unicode");
            else if (EncodingList == "Windows-1251") in.setCodec("Windows-1251");
            else if (EncodingList == "KOI8-R") in.setCodec("KOI8-R");
            else if (EncodingList == "IBM866") in.setCodec("IBM866");
            else if (EncodingList == "ISO 8859-5") in.setCodec("ISO 8859-5");
            else if (EncodingList == "Windows-1250") in.setCodec("Windows-1250");
            else if (EncodingList == "Windows-1252") in.setCodec("Windows-1252");
            else if (EncodingList == "Windows-1253") in.setCodec("Windows-1253");
            else if (EncodingList == "Windows-1254") in.setCodec("Windows-1254");
            else if (EncodingList == "Windows-1255") in.setCodec("Windows-1255");
            else if (EncodingList == "Windows-1256") in.setCodec("Windows-1256");
            else if (EncodingList == "Windows-1257") in.setCodec("Windows-1257");
            else if (EncodingList == "ISO 8859-1") in.setCodec("ISO 8859-1");
            else if (EncodingList == "ISO 8859-2") in.setCodec("ISO 8859-2");
            else if (EncodingList == "ISO 8859-3") in.setCodec("ISO 8859-3");
            else if (EncodingList == "ISO 8859-4") in.setCodec("ISO 8859-4");
            else if (EncodingList == "ISO 8859-9") in.setCodec("ISO 8859-9");
            else if (EncodingList == "ISO 8859-10") in.setCodec("ISO 8859-10");
            else if (EncodingList == "ISO 8859-13") in.setCodec("ISO 8859-13");
            else if (EncodingList == "ISO 8859-14") in.setCodec("ISO 8859-14");
            else if (EncodingList == "ISO 8859-15") in.setCodec("ISO 8859-15");
            else if (EncodingList == "ISO 8859-16") in.setCodec("ISO 8859-16");
            else if (EncodingList == "ISO 8859-6") in.setCodec("ISO 8859-6");
            else if (EncodingList == "ISO 8859-7") in.setCodec("ISO 8859-7");
            else if (EncodingList == "ISO 8859-8") in.setCodec("ISO 8859-8");
            else in.setCodec("UTF-8");

            Encoding = EncodingList;

            QString text = in.readAll();
            File.close();

            ui->textEdit->setAcceptRichText(false);
            ui->textEdit->setText(text);
        }
        else {
            QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    ui->textEdit->setReadOnly(false);
    ui->textEdit->setAcceptRichText(false);

    QString file = "";

    file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                        tr("All Files (*.*)"));

    if(!file.isEmpty())
    {
        QDir direct;
        QString dir = direct.filePath(file);
        QString FileName = dir;
        QFile File(FileName);

        if(File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&File);

            out.setCodec("UTF-8");
            out << ui->textEdit->toPlainText();

            File.flush();
            File.close();

            //QFileInfo fi(FileName);

            QMessageBox::information(this, tr("File was saved"),
                                     tr("File was saved as") + " " + FileName);
        }
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    ui->textEdit->setReadOnly(false);
    ui->textEdit->setAcceptRichText(false);

    QString file = "";

    file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                        tr("All Files (*.*)"));

    if(!file.isEmpty())
    {
        QDir direct;
        QString dir = direct.filePath(file);
        QString FileName = dir;
        QFile File(FileName);

        if(File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&File);

            QStringList items;
            items << "UTF-8" << "Unicode (UTF-16)" << tr("Windows-1251 (Cyrillic)") << tr("KOI8-R (Cyrillic)") <<
                     tr("CP866 / IBM866 (Cyrillic)") << tr("ISO 8859-5 (Cyrillic)") <<
                     tr("Windows-1250 (Central European)") << tr("Windows-1252 (Western)") <<
                     tr("Windows-1253 (Greek)") << tr("Windows-1254 (Turkish)") <<
                     tr("Windows-1255 (Hebrew)") << tr("Windows-1256 (Arabic)") << tr("Windows-1257 (Baltic)") <<
                     "ISO 8859-1 (Latin-1)" << "ISO 8859-2 (Latin-2)" <<
                     "ISO 8859-3 (Latin-3)" << "ISO 8859-4 (Latin-4)" <<
                     "ISO 8859-9 (Latin-5)" << "ISO 8859-10 (Latin-6)" <<
                     "ISO 8859-13 (Latin-7)" << "ISO 8859-14 (Latin-8)" <<
                     "ISO 8859-15 (Latin-9)" << "ISO 8859-16 (Latin-10)" <<
                     tr("ISO 8859-6 (Arabic)") << tr("ISO 8859-7 (Greek)") << tr("ISO 8859-8 (Hebrew)");

            bool ok;
            QString item = QInputDialog::getItem(this, tr("Changing encoding"), tr("Choose encoding:"),
                                                 items, 0, false, &ok);

            QString EncodingDocument;
            if (ok && !item.isEmpty()) {

                if (item == "UTF-8") EncodingDocument = "UTF-8";
                else if (item == "Unicode (UTF-16)") EncodingDocument = "Unicode";
                else if (item == tr("Windows-1251 (Cyrillic)")) EncodingDocument = "Windows-1251";
                else if (item == tr("KOI8-R (Cyrillic)")) EncodingDocument = "KOI8-R";
                else if (item == tr("CP866 / IBM866 (Cyrillic)")) EncodingDocument = "IBM866";
                else if (item == tr("ISO 8859-5 (Cyrillic)")) EncodingDocument = "ISO 8859-5";
                else if (item == tr("Windows-1250 (Central European)")) EncodingDocument = "Windows-1250";
                else if (item == tr("Windows-1252 (Western)")) EncodingDocument = "Windows-1252";
                else if (item == tr("Windows-1253 (Greek)")) EncodingDocument = "Windows-1253";
                else if (item == tr("Windows-1254 (Turkish)")) EncodingDocument = "Windows-1254";
                else if (item == tr("Windows-1255 (Hebrew)")) EncodingDocument = "Windows-1255";
                else if (item == tr("Windows-1256 (Arabic)")) EncodingDocument = "Windows-1256";
                else if (item == tr("Windows-1257 (Baltic)")) EncodingDocument = "Windows-1257";
                else if (item == "ISO 8859-1 (Latin-1)") EncodingDocument = "ISO 8859-1";
                else if (item == "ISO 8859-2 (Latin-2)") EncodingDocument = "ISO 8859-2";
                else if (item == "ISO 8859-3 (Latin-3)") EncodingDocument = "ISO 8859-3";
                else if (item == "ISO 8859-4 (Latin-4)") EncodingDocument = "ISO 8859-4";
                else if (item == "ISO 8859-9 (Latin-5)") EncodingDocument = "ISO 8859-9";
                else if (item == "ISO 8859-10 (Latin-6)") EncodingDocument = "ISO 8859-10";
                else if (item == "ISO 8859-13 (Latin-7)") EncodingDocument = "ISO 8859-13";
                else if (item == "ISO 8859-14 (Latin-8)") EncodingDocument = "ISO 8859-14";
                else if (item == "ISO 8859-15 (Latin-9)") EncodingDocument = "ISO 8859-15";
                else if (item == "ISO 8859-16 (Latin-10)") EncodingDocument = "ISO 8859-16";
                else if (item == tr("ISO 8859-6 (Arabic)")) EncodingDocument = "ISO 8859-6";
                else if (item == tr("ISO 8859-7 (Greek)")) EncodingDocument = "ISO 8859-7";
                else if (item == tr("ISO 8859-8 (Hebrew)")) EncodingDocument = "ISO 8859-8";
                else return;
            }

            QString EncodingList = EncodingDocument;
            if (EncodingList == "UTF-8") out.setCodec("UTF-8");
            else if (EncodingList == "Unicode") out.setCodec("Unicode");
            else if (EncodingList == "Windows-1251") out.setCodec("Windows-1251");
            else if (EncodingList == "KOI8-R") out.setCodec("KOI8-R");
            else if (EncodingList == "IBM866") out.setCodec("IBM866");
            else if (EncodingList == "ISO 8859-5") out.setCodec("ISO 8859-5");
            else if (EncodingList == "Windows-1250") out.setCodec("Windows-1250");
            else if (EncodingList == "Windows-1252") out.setCodec("Windows-1252");
            else if (EncodingList == "Windows-1253") out.setCodec("Windows-1253");
            else if (EncodingList == "Windows-1254") out.setCodec("Windows-1254");
            else if (EncodingList == "Windows-1255") out.setCodec("Windows-1255");
            else if (EncodingList == "Windows-1256") out.setCodec("Windows-1256");
            else if (EncodingList == "Windows-1257") out.setCodec("Windows-1257");
            else if (EncodingList == "ISO 8859-1") out.setCodec("ISO 8859-1");
            else if (EncodingList == "ISO 8859-2") out.setCodec("ISO 8859-2");
            else if (EncodingList == "ISO 8859-3") out.setCodec("ISO 8859-3");
            else if (EncodingList == "ISO 8859-4") out.setCodec("ISO 8859-4");
            else if (EncodingList == "ISO 8859-9") out.setCodec("ISO 8859-9");
            else if (EncodingList == "ISO 8859-10") out.setCodec("ISO 8859-10");
            else if (EncodingList == "ISO 8859-13") out.setCodec("ISO 8859-13");
            else if (EncodingList == "ISO 8859-14") out.setCodec("ISO 8859-14");
            else if (EncodingList == "ISO 8859-15") out.setCodec("ISO 8859-15");
            else if (EncodingList == "ISO 8859-16") out.setCodec("ISO 8859-16");
            else if (EncodingList == "ISO 8859-6") out.setCodec("ISO 8859-6");
            else if (EncodingList == "ISO 8859-7") out.setCodec("ISO 8859-7");
            else if (EncodingList == "ISO 8859-8") out.setCodec("ISO 8859-8");
            else out.setCodec("UTF-8");

            out << ui->textEdit->toPlainText();

            File.flush();
            File.close();

            //QFileInfo fi(FileName);

            QMessageBox::information(this, tr("File was saved"),
                                     tr("File was saved as") + " " + FileName);
        }
    }
}

//closing the program
void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox* messagebox = new QMessageBox (QMessageBox::Question,
                                               tr("Confirm Dialog"), tr("Really quit?"),
                                               QMessageBox::Yes | QMessageBox::No, this);
    messagebox->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox->setButtonText(QMessageBox::No, tr("No"));
    int n = messagebox->exec();
    delete messagebox;

    if (n == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_actionClose_triggered()
{
    ui->textEdit->clear();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text  = tr("Program for changing encoding in a text") + "\n\n";

    about_text += tr("Copyright (C) 2022 Aleksandr Migunov") + "\n\n";

    about_text += "This program is free software; you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by \
the Free Software Foundation; either version 3 of the License, or \
(at your option) any later version. \n\n";

    about_text += "This program is distributed in the hope that it will be useful, \
but WITHOUT ANY WARRANTY; without even the implied warranty of \
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \
GNU General Public License for more details. \n\n";

    about_text += "You should have received a copy of the GNU General Public License \
along with this program. If not, see <https://www.gnu.org/licenses/>.";

    QMessageBox::about(this, tr("About Program"), about_text);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(0);
}
