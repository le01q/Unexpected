# -*- coding: utf-8 -*-
import os,sqlite3,datetime
from PyQt5 import QtCore, QtGui, QtWidgets
LOCAL = os.getenv("LOCALAPPDATA")
TEMP = os.getenv("TEMP")
Browsers_Chromium = {"Chrome":LOCAL+"\\Google\\Chrome\\User Data\\Default",
               "Brave":LOCAL+"\\BraveSoftware\\Brave-Browser\\User Data\\Default"}
_translate = QtCore.QCoreApplication.translate
def date_from_webkit(webkit_timestamp): #Convert Chrome format time to human time 
    epoch_start = datetime.datetime(1601,1,1)
    delta = datetime.timedelta(microseconds=int(webkit_timestamp))
    return epoch_start + delta
def format_datetime(dt, template='{0.day:02d}/{0.month:02d}/{0.year:4d} {0.hour:2d}:{0.minute:2d}'):
    return template.format(dt)
class Ui_MainWindow(object):
    Browser_data=None
    Navigator_History=[]
    offset=0
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.setWindowModality(QtCore.Qt.NonModal)
        MainWindow.resize(800, 608)
        MainWindow.setMinimumSize(QtCore.QSize(800, 0))
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setMinimumSize(QtCore.QSize(0, 0))
        self.centralwidget.setMaximumSize(QtCore.QSize(16777215, 16777214))
        self.centralwidget.setMouseTracking(False)
        self.centralwidget.setAutoFillBackground(False)
        self.centralwidget.setObjectName("centralwidget")
        self.navigators = QtWidgets.QTreeWidget(self.centralwidget)
        self.navigators.setGeometry(QtCore.QRect(80, 20, 201, 161))
        self.navigators.setProperty("showDropIndicator", True)
        self.navigators.setObjectName("navigators")
        self.navigators.headerItem().setTextAlignment(0, QtCore.Qt.AlignCenter)
        item_0 = QtWidgets.QTreeWidgetItem(self.navigators)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_0 = QtWidgets.QTreeWidgetItem(self.navigators)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        self.history = QtWidgets.QListWidget(self.centralwidget)
        self.history.setGeometry(QtCore.QRect(80, 190, 201, 391))
        self.history.setObjectName("history")
        self.next = QtWidgets.QPushButton(self.centralwidget)
        self.next.setGeometry(QtCore.QRect(280, 190, 75, 23))
        self.next.setObjectName("next")
        self.back = QtWidgets.QPushButton(self.centralwidget)
        self.back.setGeometry(QtCore.QRect(0, 190, 75, 23))
        self.back.setObjectName("back")
        self.page_number = QtWidgets.QLabel(self.centralwidget)
        self.page_number.setGeometry(QtCore.QRect(290, 230, 81, 16))
        self.page_number.setObjectName("page_number")
        self.separator = QtWidgets.QFrame(self.centralwidget)
        self.separator.setGeometry(QtCore.QRect(360, 10, 31, 571))
        self.separator.setFrameShape(QtWidgets.QFrame.VLine)
        self.separator.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.separator.setObjectName("separator")
        self.info = QtWidgets.QGroupBox(self.centralwidget)
        self.info.setGeometry(QtCore.QRect(380, 10, 411, 561))
        self.info.setObjectName("info")
        self.title = QtWidgets.QLabel(self.info)
        self.title.setGeometry(QtCore.QRect(10, 30, 391, 61))
        font = QtGui.QFont()
        font.setFamily("Tunga")
        font.setPointSize(15)
        font.setBold(True)
        font.setWeight(75)
        self.title.setFont(font)
        self.title.setAlignment(QtCore.Qt.AlignCenter)
        self.title.setObjectName("title")
        self.title.setScaledContents(True);
        self.title.setWordWrap(True);
        self.url = QtWidgets.QLabel(self.info)
        self.url.setGeometry(QtCore.QRect(20, 70, 381, 51))
        self.url.setCursor(QtGui.QCursor(QtCore.Qt.IBeamCursor))
        self.url.setTextFormat(QtCore.Qt.RichText)
        self.url.setScaledContents(True)
        self.url.setAlignment(QtCore.Qt.AlignCenter)
        self.url.setWordWrap(True)
        self.url.setOpenExternalLinks(True)
        self.url.setTextInteractionFlags(QtCore.Qt.TextBrowserInteraction)
        self.url.setObjectName("url")
        self.navigator_2 = QtWidgets.QLabel(self.info)
        self.navigator_2.setGeometry(QtCore.QRect(30, 130, 361, 16))
        self.navigator_2.setAlignment(QtCore.Qt.AlignCenter)
        self.navigator_2.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
        self.navigator_2.setObjectName("navigator_2")
        self.visitas = QtWidgets.QLCDNumber(self.info)
        self.visitas.setGeometry(QtCore.QRect(10, 180, 381, 23))
        self.visitas.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.visitas.setFrameShape(QtWidgets.QFrame.NoFrame)
        self.visitas.setSmallDecimalPoint(False)
        self.visitas.setSegmentStyle(QtWidgets.QLCDNumber.Filled)
        self.visitas.setObjectName("visitas")
        self.label = QtWidgets.QLabel(self.info)
        self.label.setGeometry(QtCore.QRect(10, 230, 401, 20))
        font = QtGui.QFont()
        font.setItalic(True)
        font.setKerning(True)
        self.label.setFont(font)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.navigators.setToolTip(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Navegadores soportados</span></p></body></html>"))
        self.navigators.headerItem().setText(0, _translate("MainWindow", "Navegadores"))
        __sortingEnabled = self.navigators.isSortingEnabled()
        self.navigators.setSortingEnabled(False)
        self.navigators.topLevelItem(0).setText(0, _translate("MainWindow", "Basados en Chromium"))
        self.navigators.topLevelItem(0).child(0).setText(0, _translate("MainWindow", "Chrome"))
        self.navigators.topLevelItem(0).child(1).setText(0, _translate("MainWindow", "Brave"))
        self.navigators.topLevelItem(1).setText(0, _translate("MainWindow", "Otros"))
        self.navigators.topLevelItem(1).child(0).setText(0, _translate("MainWindow", "Mozilla Firefox"))
        self.navigators.topLevelItem(1).child(1).setText(0, _translate("MainWindow", "Safari"))
        self.navigators.setSortingEnabled(__sortingEnabled)
        self.navigators.itemClicked.connect(self.onItemClick)
        self.history.setToolTip(_translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Lista de paginas del historial</span></p></body></html>"))
        self.next.setText(_translate("MainWindow", "Siguiente"))
        self.next.clicked.connect(self.forward)
        self.back.setText(_translate("MainWindow", "Anterior"))
        self.back.clicked.connect(self.backf)
        self.history.itemClicked.connect(self.history_viewer)
        self.page_number.setText(_translate("MainWindow", "Pagina 1/50"))
        self.info.setToolTip(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Informacion del sitio</span></p></body></html>"))
        self.info.setTitle(_translate("MainWindow", "Información"))
        self.title.setText(_translate("MainWindow", "Titulo de prueba"))
        self.url.setText(_translate("MainWindow", "https://google.com"))
        self.navigator_2.setText(_translate("MainWindow", "Google Chrome"))
        self.visitas.setToolTip(_translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Contador de visitas</span></p></body></html>"))
        self.label.setText(_translate("MainWindow", "Ultima vez: 2/11/2021 22:40"))
        self.info.hide()
        self.back.hide()
        self.page_number.hide()
        self.next.hide()
    def onItemClick(self,item,id):
        if item.parent():
            if item.parent().text(0)=="Basados en Chromium":
                self.setupChromiumBrowser(item.text(0))
    def history_viewer(self):
        row = self.history.currentRow()
        data = self.Navigator_History[row]
        title = data[2] #The title of website
        url = data[1] #The url
        last_timed=date_from_webkit(data[5]) # The last time that visited the site 
        last_timer=format_datetime(last_timed) #Solve the bug that happend if year is <=1900
        views=data[3] #The views of site
        self.navigator_2.setText(_translate("MainWindow",self.nav))
        self.title.setText(_translate("MainWindow",title))
        self.url.setText(_translate("MainWindow",url))
        self.visitas.setProperty("value",int(views))
        self.label.setText(_translate("MainWindow",f"Ultima vez visitado:{last_timer}"))
        self.info.show()
    def forward(self): 
        if self.offset+10<len(self.Browser_data):
            self.history.clear()
            self.Navigator_History.clear()
            self.addPages(self.offset+10,10)
            d=round((self.offset+10)/10)
            r=round((len(self.Browser_data)/10))
            self.next.show()
            self.back.hide()
            if self.offset-10>0:
                self.back.show()
            self.page_number.setText(_translate("MainWindow",f"Pagina {d}/{r}"))
        else:
            self.next.hide()
    def backf(self):
        if self.offset-10>0:
            self.history.clear()
            self.Navigator_History.clear()
            self.addPages(self.offset-10,10)
            d=round((self.offset-10)/10)
            r=round((len(self.Browser_data)/10))
            self.back.show()
            self.next.hide()
            if self.offset+10<len(self.Browser_data):
                self.next.show()
            self.page_number.setText(_translate("MainWindow",f"Pagina {d}/{r}"))
        else:
            self.back.hide()
    def setupChromiumBrowser(self,browser):
        history_path = self.getHistory(Browsers_Chromium[browser])
        self.history.clear()
        self.next.show()
        self.page_number.show()
        if history_path==False:
            return
        pathn = TEMP+"\\History"+browser #Create a temp file 
        with open(pathn,'wb') as f: #Copy file into the temp file to bypass any database block
            with open(history_path,'rb') as l:
                f.write(l.read())
        
        path=pathn
        
        db =sqlite3.connect(path)
        cur = db.cursor()
        try:
            z = cur.execute("SELECT * FROM urls") #Select urls 
        except sqlite3.OperationalError:
            os.remove(path) #Remove the file if dont exists history
            return
        result = z.fetchall()
        cur.close()
        db.close()
        self.Browser_data=None
        self.Navigator_History=[]
        self.Browser_data=result
        os.remove(path)
        self.nav=browser
        self.offset=0
        self.addPages(0,10)
    def addPages(self,offset,limit):
        self.offset=offset
        for x in self.getPage(offset,limit):
            self.Navigator_History.append(x)
            item = QtWidgets.QListWidgetItem()
            item.setText(_translate("MainWindow",x[2]))
            self.history.addItem(item)
    def getPage(self,offset,limit):
        for x in range(offset,offset+limit):
            try:
                yield self.Browser_data[x]
            except IndexError:
                return
    def getHistory(self,Path):
        if os.path.isfile(Path+"\\History"):
            return Path+"\\History"
        return False

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
