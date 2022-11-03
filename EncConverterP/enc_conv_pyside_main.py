# -*- coding: utf-8 -*-

import sys, os
from enc_conv_pyside_gui import *
from PySide2 import QtCore, QtGui, QtWidgets

class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent=None)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.actionExit.triggered.connect(self.close)
        self.ui.actionNew.triggered.connect(self.newFile)
        self.ui.actionOpen.triggered.connect(self.openFile)
        self.ui.actionEncoding.triggered.connect(self.encodingFile)
        self.ui.actionSave.triggered.connect(self.saveFile)
        self.ui.actionSave_As.triggered.connect(self.saveFileAs)
        self.ui.actionClose.triggered.connect(self.closeFile)
        self.ui.actionAbout.triggered.connect(self.about)
        self.ui.actionAbout_Qt.triggered.connect(self.aboutQt)
        self.NewOpened = ""
        self.FileOpened = ""

    def newFile(self):
        self.NewOpened = ""
        self.ui.textEdit.clear()
        self.NewOpened = "new window"

    def openFile(self):
        self.NewOpened = ""
        options = QtWidgets.QFileDialog.Options()
        self.fileName, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File", "",
                                                                     "All Files (*.*)", options=options)
        if self.fileName:
            self.ui.textEdit.clear()
            try:
                self.openF = open(self.fileName, 'r', encoding='utf-8')
            except UnicodeDecodeError:
                self.openF = open(self.fileName, 'r', encoding='utf-8-sig')
            self.ui.textEdit.insertPlainText(self.openF.read())
            self.openF.close()

        else:
            QtWidgets.QMessageBox.information(self, "Error", "Unable to open file.",
                                              QtWidgets.QMessageBox.Ok)

        self.FileOpened = self.fileName

    def encodingFile(self):
        items = ["UTF-8", "Unicode (UTF-16)", "Windows-1251 (Cyrillic)", "KOI8-R (Cyrillic)", \
        "CP866 / IBM866 (Cyrillic)", "ISO 8859-5 (Cyrillic)", \
        "Windows-1250 (Central European)", "Windows-1252 (Western)", \
        "Windows-1253 (Greek)","Windows-1254 (Turkish)", \
        "Windows-1255 (Hebrew)", "Windows-1256 (Arabic)", "Windows-1257 (Baltic)", \
        "ISO 8859-1 (Latin-1)", "ISO 8859-2 (Latin-2)", \
        "ISO 8859-3 (Latin-3)", "ISO 8859-4 (Latin-4)", \
        "ISO 8859-9 (Latin-5)", "ISO 8859-10 (Latin-6)", \
        "ISO 8859-13 (Latin-7)", "ISO 8859-14 (Latin-8)", \
        "ISO 8859-15 (Latin-9)", "ISO 8859-16 (Latin-10)", \
        "ISO 8859-6 (Arabic)", "ISO 8859-7 (Greek)","ISO 8859-8 (Hebrew)"]

        item = QtWidgets.QInputDialog.getItem(self, "Changing encoding", "Choose encoding: ",
                              items, current=0, editable=False)

        EncodingDocument = ""

        if item[0] != "" and item[1] == True:
            if item[0] == "UTF-8":
                EncodingDocument = "utf-8"
            elif item[0] == "Unicode (UTF-16)":
                #EncodingDocument = "utf-16"
                #EncodingDocument = "utf-16be"
                EncodingDocument = "utf-16le"
            elif item[0] == "Windows-1251 (Cyrillic)":
                EncodingDocument = "cp1251"
            elif item[0] == "KOI8-R (Cyrillic)":
                EncodingDocument = "koi8_r"
            elif item[0] == "CP866 / IBM866 (Cyrillic)":
                EncodingDocument = "cp866"
            elif item[0] == "ISO 8859-5 (Cyrillic)":
                EncodingDocument = "iso8859-5"
            elif item[0] == "Windows-1250 (Central European)":
                EncodingDocument = "cp1250"
            elif item[0] == "Windows-1252 (Western)":
                EncodingDocument = "cp1252"
            elif item[0] == "Windows-1253 (Greek)":
                EncodingDocument = "cp1253"
            elif item[0] == "Windows-1254 (Turkish)":
                EncodingDocument = "cp1254"
            elif item[0] == "Windows-1255 (Hebrew)":
                EncodingDocument = "cp1255"
            elif item[0] == "Windows-1256 (Arabic)":
                EncodingDocument = "cp1256"
            elif item[0] == "Windows-1257 (Baltic)":
                EncodingDocument = "cp1257"
            elif item[0] == "ISO 8859-1 (Latin-1)":
                EncodingDocument = "iso8859-1"
            elif item[0] == "ISO 8859-2 (Latin-2)":
                EncodingDocument = "iso8859-2"
            elif item[0] == "ISO 8859-3 (Latin-3)":
                EncodingDocument = "iso8859-3"
            elif item[0] == "ISO 8859-4 (Latin-4)":
                EncodingDocument = "iso8859-4"
            elif item[0] == "ISO 8859-9 (Latin-5)":
                EncodingDocument = "iso8859-9"
            elif item[0] == "ISO 8859-10 (Latin-6)":
                EncodingDocument = "iso8859-10"
            elif item[0] == "ISO 8859-13 (Latin-7)":
                EncodingDocument = "iso8859-13"
            elif item[0] == "ISO 8859-14 (Latin-8)":
                EncodingDocument = "iso8859-14"
            elif item[0] == "ISO 8859-15 (Latin-9)":
                EncodingDocument = "iso8859-15"
            elif item[0] == "ISO 8859-16 (Latin-10)":
                EncodingDocument = "iso8859-16"
            elif item[0] == "ISO 8859-6 (Arabic)":
                EncodingDocument = "iso8859-6"
            elif item[0] == "ISO 8859-7 (Greek)":
                EncodingDocument = "iso8859-7"
            elif item[0] == "ISO 8859-8 (Hebrew)":
                EncodingDocument = "iso8859-8"
            else:
                EncodingDocument = "utf-8"

        file = ""
        if self.FileOpened:
            file = self.FileOpened
        elif self.NewOpened:
            file = "temp.txt"
            f = open(r"temp.txt", "w", encoding="utf-8")
            notepad_text = self.ui.textEdit.toPlainText()
            f.write(notepad_text)
            f.close()
        else:
            options = QtWidgets.QFileDialog.Options()
            file, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File", "",
                                                                 "All Files (*.*)", options=options)
        if file:
            self.ui.textEdit.clear()
            self.openF = open(self.FileOpened, 'r', encoding=EncodingDocument)
            self.ui.textEdit.insertPlainText(self.openF.read())
            self.openF.close()

        else:
            QtWidgets.QMessageBox.information(self, "Error", "Unable to open file.",
                                              QtWidgets.QMessageBox.Ok)


    def saveFile(self):
        options = QtWidgets.QFileDialog.Options()
        file, _ = QtWidgets.QFileDialog.getSaveFileName(self, "Save To File", "",
                                                                     "All Files (*.*)", options=options)
        if file:
            f = open(file, 'w', encoding='utf-8')
            notepad_text = self.ui.textEdit.toPlainText()
            f.write(notepad_text)
            f.close()
            QtWidgets.QMessageBox.information(self, "File was saved",
                                              "File was saved as" + file)


    def saveFileAs(self):
        options = QtWidgets.QFileDialog.Options()
        file, _ = QtWidgets.QFileDialog.getSaveFileName(self, "Save To File", "",
                                                                 "All Files (*.*)", options=options)


        if file:
            items = ["UTF-8", "Unicode (UTF-16)", "Windows-1251 (Cyrillic)", "KOI8-R (Cyrillic)", \
            "CP866 / IBM866 (Cyrillic)", "ISO 8859-5 (Cyrillic)", \
            "Windows-1250 (Central European)", "Windows-1252 (Western)", \
            "Windows-1253 (Greek)","Windows-1254 (Turkish)", \
            "Windows-1255 (Hebrew)", "Windows-1256 (Arabic)", "Windows-1257 (Baltic)", \
            "ISO 8859-1 (Latin-1)", "ISO 8859-2 (Latin-2)", \
            "ISO 8859-3 (Latin-3)", "ISO 8859-4 (Latin-4)", \
            "ISO 8859-9 (Latin-5)", "ISO 8859-10 (Latin-6)", \
            "ISO 8859-13 (Latin-7)", "ISO 8859-14 (Latin-8)", \
            "ISO 8859-15 (Latin-9)", "ISO 8859-16 (Latin-10)", \
            "ISO 8859-6 (Arabic)", "ISO 8859-7 (Greek)","ISO 8859-8 (Hebrew)"]

            item = QtWidgets.QInputDialog.getItem(self, "Changing encoding", "Choose encoding: ",
                              items, current=0, editable=False)

            EncodingDocument = ""

            if item[0] != "" and item[1] == True:
                if item[0] == "UTF-8":
                    EncodingDocument = "utf-8"
                elif item[0] == "Unicode (UTF-16)":
                    #EncodingDocument = "utf-16"
                    #EncodingDocument = "utf-16be"
                    EncodingDocument = "utf-16le"
                elif item[0] == "Windows-1251 (Cyrillic)":
                    EncodingDocument = "cp1251"
                elif item[0] == "KOI8-R (Cyrillic)":
                    EncodingDocument = "koi8_r"
                elif item[0] == "CP866 / IBM866 (Cyrillic)":
                    EncodingDocument = "cp866"
                elif item[0] == "ISO 8859-5 (Cyrillic)":
                    EncodingDocument = "iso8859-5"
                elif item[0] == "Windows-1250 (Central European)":
                    EncodingDocument = "cp1250"
                elif item[0] == "Windows-1252 (Western)":
                    EncodingDocument = "cp1252"
                elif item[0] == "Windows-1253 (Greek)":
                    EncodingDocument = "cp1253"
                elif item[0] == "Windows-1254 (Turkish)":
                    EncodingDocument = "cp1254"
                elif item[0] == "Windows-1255 (Hebrew)":
                    EncodingDocument = "cp1255"
                elif item[0] == "Windows-1256 (Arabic)":
                    EncodingDocument = "cp1256"
                elif item[0] == "Windows-1257 (Baltic)":
                    EncodingDocument = "cp1257"
                elif item[0] == "ISO 8859-1 (Latin-1)":
                    EncodingDocument = "iso8859-1"
                elif item[0] == "ISO 8859-2 (Latin-2)":
                    EncodingDocument = "iso8859-2"
                elif item[0] == "ISO 8859-3 (Latin-3)":
                    EncodingDocument = "iso8859-3"
                elif item[0] == "ISO 8859-4 (Latin-4)":
                    EncodingDocument = "iso8859-4"
                elif item[0] == "ISO 8859-9 (Latin-5)":
                    EncodingDocument = "iso8859-9"
                elif item[0] == "ISO 8859-10 (Latin-6)":
                    EncodingDocument = "iso8859-10"
                elif item[0] == "ISO 8859-13 (Latin-7)":
                    EncodingDocument = "iso8859-13"
                elif item[0] == "ISO 8859-14 (Latin-8)":
                    EncodingDocument = "iso8859-14"
                elif item[0] == "ISO 8859-15 (Latin-9)":
                    EncodingDocument = "iso8859-15"
                elif item[0] == "ISO 8859-16 (Latin-10)":
                    EncodingDocument = "iso8859-16"
                elif item[0] == "ISO 8859-6 (Arabic)":
                    EncodingDocument = "iso8859-6"
                elif item[0] == "ISO 8859-7 (Greek)":
                    EncodingDocument = "iso8859-7"
                elif item[0] == "ISO 8859-8 (Hebrew)":
                    EncodingDocument = "iso8859-8"
                else:
                    EncodingDocument = "utf-8"

                f = open(file, 'w', encoding=EncodingDocument)
                notepad_text = self.ui.textEdit.toPlainText()
                f.write(notepad_text)
                f.close()
                QtWidgets.QMessageBox.information(self, "File was saved",
                                                  "File was saved as" + file)


    def closeFile(self):
        self.ui.textEdit.clear()

    def about(self):
        about_text = "Program for changing encoding in a text" + "\n\n"

        about_text += "Copyright (C) 2022 Aleksandr Migunov" + "\n\n"

        about_text += "This program is free software; you can redistribute it and/or modify "
        about_text += "it under the terms of the GNU General Public License as published by "
        about_text += "the Free Software Foundation; either version 3 of the License, or "
        about_text += "(at your option) any later version. \n\n"

        about_text += "This program is distributed in the hope that it will be useful, "
        about_text += "but WITHOUT ANY WARRANTY; without even the implied warranty of "
        about_text += "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
        about_text += "GNU General Public License for more details. \n\n"

        about_text += "You should have received a copy of the GNU General Public License "
        about_text += "along with this program. If not, see <https://www.gnu.org/licenses/>."

        QtWidgets.QMessageBox.about(self, "About Program", about_text)

    def aboutQt(self):
        QtWidgets.QMessageBox.aboutQt(self)


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
