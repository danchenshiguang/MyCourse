import sys

from PyQt5.QtWidgets import QApplication, QWidget, QMessageBox, QDesktopWidget


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()


    def initUI(self):

        self.resize(500, 450)
        self.center()
        self.setWindowTitle('Message box')
        self.show()


    def closeEvent(self, event):

        reply = QMessageBox.question(self, 'Message',
            "Are you sure to quit?", QMessageBox.Yes |
            QMessageBox.No, QMessageBox.No)

        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    def center(self):

        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
app = QApplication(sys.argv)
w = QWidget()
e = Example()
sys.exit(app.exec_())
