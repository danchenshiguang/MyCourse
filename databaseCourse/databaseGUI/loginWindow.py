import sys
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import manager_ui
import DB
from DB import *
class LoginWindow(QWidget):
    loadInfoSig=pyqtSignal(str,str)
    # loginSig=pyqtSignal()
    def __init__(self):
        super(LoginWindow, self).__init__()
        self.initUI()
        self.setWindowTitle("Login")
    def initUI(self):
        self.welcomeLabel=QLabel("Welcome!")
        self.userLabel=QLabel("User:",self)
        self.passwordLabel=QLabel("Password",self)
        self.userText=QLineEdit(self)
        self.passwordText=QLineEdit(self)
        self.user_loginButton=QPushButton("用户登录",self)
        self.user_loginButton.clicked.connect(self.userLogin)
        self.manager_loginButton=QPushButton("管理员登录",self)
        self.manager_loginButton.clicked.connect(self.managerLogin)
        self.grid=QGridLayout()
        self.grid.addWidget(self.welcomeLabel,0,0)
        self.grid.addWidget(self.userLabel,1,0)
        self.grid.addWidget(self.userText,1,1)
        self.grid.addWidget(self.passwordLabel, 2, 0)
        self.grid.addWidget(self.passwordText, 2, 1)
        self.grid.addWidget(self.user_loginButton, 2, 2)
        self.grid.addWidget(self.manager_loginButton, 3, 2)
        self.setLayout(self.grid)
    def userLogin(self):
        self.loadInfoSig.emit(self.userText.text(), self.passwordText.text())
        self.window().destroy()
        e = DB.MainUi()

    def managerLogin(self):
        self.loadInfoSig.emit(self.userText.text(),self.passwordText.text())
        self.window().destroy()
        e = manager_ui.MainUi()
    def showConnectError(self):
        QMessageBox.information(self, "Connect Error", "Fail to connect the server, check your Server and Internet", QMessageBox.Ok)
    def showLoginError(self):
        QMessageBox.information(self, "Login Error", "Fail to login, check your ID and password as well as the Internet connection", QMessageBox.Ok)


if __name__ == '__main__':

    app = QApplication(sys.argv)
    l = LoginWindow()
    l.show()
    sys.exit(app.exec_())