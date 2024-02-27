import qtawesome
from tkinter import *
import os
import time
import threading
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import webbrowser
from PyQt5 import QtGui, QtCore, QtWidgets, QtSql, Qt
import pymysql
import xlrd
import datetime
from SQL import *
import beauty
from beauty import *

ID = '00001'  # 全局变量，登录时修改


class MainUi(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setFixedSize(960, 700)
        self.main_widget = QtWidgets.QWidget()  # 创建窗口主部件
        self.main_layout = QtWidgets.QGridLayout()  # 创建主部件的网格布局
        self.main_widget.setLayout(self.main_layout)  # 设置窗口主部件布局为网格布局

        self.left_widget = QtWidgets.QWidget()  # 创建左侧部件
        self.left_widget.setObjectName('left_widget')
        self.left_layout = QtWidgets.QGridLayout()  # 创建左侧部件的网格布局层
        self.left_widget.setLayout(self.left_layout)  # 设置左侧部件布局为网格

        self.right_widget = QStackedWidget()
        self.right_widget.setObjectName('right_widget')
        self.right_layout = QtWidgets.QGridLayout()
        self.right_widget.setLayout(self.right_layout)  # 设置右侧部件布局为网格

        self.main_layout.addWidget(self.left_widget, 0, 0, 12, 2)  # 左侧部件在第0行第0列，占8行3列
        self.main_layout.addWidget(self.right_widget, 0, 2, 12, 10)  # 右侧部件在第0行第3列，占8行9列

        self.setCentralWidget(self.main_widget)  # 设置窗口主部件
        self.left_close = QtWidgets.QPushButton("")  # 关闭按钮
        self.left_close.clicked.connect(self.close)  # 关闭窗口
        self.left_visit = QtWidgets.QPushButton("")  # 空白按钮
        self.left_visit.clicked.connect(self.close)  # 关闭窗口
        self.left_mini = QtWidgets.QPushButton("")  # 最小化按钮
        self.left_mini.clicked.connect(self.showMinimized)  # 最小化窗口

        self.left_label_1 = QtWidgets.QPushButton("图书")
        self.left_label_1.setObjectName('left_label')
        self.left_label_2 = QtWidgets.QPushButton("用户")
        self.left_label_2.setObjectName('left_label')
        self.left_label_3 = QtWidgets.QPushButton("帮助")
        self.left_label_3.setObjectName('left_label')

        self.left_button_showbook = QtWidgets.QPushButton(qtawesome.icon('fa.address-book-o', color='white'), "图书总览")
        self.left_button_showbook.setObjectName('left_button')
        self.left_button_showbook.clicked.connect(lambda: self.right_cliked(0))
        self.left_button_borrowbook = QtWidgets.QPushButton(qtawesome.icon('fa.book', color='white'), "图书借阅")
        self.left_button_borrowbook.setObjectName('left_button')
        self.left_button_borrowbook.clicked.connect(lambda: self.right_cliked(1))
        self.left_button_returnbook = QtWidgets.QPushButton(qtawesome.icon('fa.pencil-square-o', color='white'), "图书归还")
        self.left_button_returnbook.setObjectName('left_button')
        self.left_button_returnbook.clicked.connect(lambda: self.right_cliked(2))
        self.left_button_borrowcase = QtWidgets.QPushButton(qtawesome.icon('fa.bookmark', color='white'), "借阅情况")
        self.left_button_borrowcase.setObjectName('left_button')
        self.left_button_borrowcase.clicked.connect(lambda: self.right_cliked(3))
        self.left_button_userCenter = QtWidgets.QPushButton(qtawesome.icon('fa.user-o', color='white'), "个人中心")
        self.left_button_userCenter.setObjectName('left_button')
        self.left_button_userCenter.clicked.connect(lambda: self.right_cliked(4))
        self.left_button_problem = QtWidgets.QPushButton(qtawesome.icon('fa.question', color='white'), "遇到问题")
        self.left_button_problem.setObjectName('left_button')
        # self.left_button_9.clicked.connect(self.left_button1_clicked1)
        # self.left_xxx = QtWidgets.QPushButton(" ")
        self.left_layout.addWidget(self.left_mini, 0, 2, 1, 1)
        self.left_layout.addWidget(self.left_visit, 0, 1, 1, 1)
        self.left_layout.addWidget(self.left_close, 0, 0, 1, 1)
        self.left_layout.addWidget(self.left_label_1, 1, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_showbook, 2, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_borrowbook, 3, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_returnbook, 4, 0, 1, 3)
        self.left_layout.addWidget(self.left_label_2, 5, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_borrowcase, 6, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_userCenter, 7, 0, 1, 3)
        self.left_layout.addWidget(self.left_label_3, 8, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_problem, 9, 0, 1, 3)

        right_style_beauty(self)
        left_style_beauty(self)
        # self.right_layout.addWidget(self.right_bar_widget, 0, 0, 1, 9)

        self.setWindowOpacity(0.9)  # 设置窗口透明度
        self.setAttribute(QtCore.Qt.WA_TranslucentBackground)  # 设置窗口背景透明
        self.main_widget.setStyleSheet('''
                QWidget#left_widget{
                background:gray;
                border-top:1px solid white;
                border-bottom:1px solid white;
                border-left:1px solid white;
                border-top-left-radius:10px;
                border-bottom-left-radius:10px;
                }
                ''')
        self.main_layout.setSpacing(0)
        self.setWindowFlag(QtCore.Qt.FramelessWindowHint)  # 隐藏边框

        # 1.查找图书界面
        self.search_widget = QWidget()
        self.right_widget.addWidget(self.search_widget)
        self.search_layout = QtWidgets.QGridLayout(self.search_widget)

        # 1.1 信息提示对话框
        self.right_message_Alter = QMessageBox()
        self.right_message_Alter.setObjectName("right_message_Alter")
        self.right_message_Alter.setWindowOpacity(0.9)  # 设置窗口透明度
        self.right_message_Alter.setWindowFlag(QtCore.Qt.FramelessWindowHint)  # 隐藏边框
        # 1.2查找图书右侧顶端搜索框
        self.search_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.search_bar_layout1 = QtWidgets.QGridLayout()  # 右侧顶部搜索框网格布局
        self.search_bar_widget1.setLayout(self.search_bar_layout1)

        self.search_input = QLineEdit("ISBN号/书名/出版社/作者")
        self.search_bar_layout1.addWidget(self.search_input, 0, 4, 1, 8)
        self.search_layout.addWidget(self.search_bar_widget1, 0, 0, 1, 9)

        self.search_button = QtWidgets.QPushButton(qtawesome.icon('fa.book', color="black"), "查找图书")
        self.search_button.setFont(qtawesome.font('fa', 10))
        self.search_button.clicked.connect(lambda: self.search_book(self.search_input.text()))
        self.search_bar_layout1.addWidget(self.search_button, 0, 0, 1, 3)

        # 1.3右侧底部结果框
        self.right_bar_widget2 = QtWidgets.QWidget()
        self.right_bar_layout2 = QtWidgets.QGridLayout(self.right_bar_widget2)  # 右侧顶部搜索框网格布局
        self.search_view_table = QtWidgets.QLabel(self.showBook())

        # self.search_view_table = QtWidgets.QTableView()
        self.right_bar_layout2.addWidget(self.search_view_table, 1, 6)
        self.right_bar_layout2.update()
        self.search_layout.addWidget(self.right_bar_widget2, 1, 0, 1, 9)

        # 借书界面
        self.borrow_widget = QtWidgets.QWidget()
        self.right_widget.addWidget(self.borrow_widget)
        self.borrow_layout = QtWidgets.QGridLayout(self.borrow_widget)

        # 借书界面顶端借书选项
        self.borrow_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.borrow_bar_layout1 = QtWidgets.QGridLayout(self.borrow_bar_widget1)  # 右侧顶部搜索框网格布局
        self.borrow_label = QtWidgets.QLabel("请输入ISBN号：")
        self.borrow_bar_layout1.addWidget(self.borrow_label, 0, 0, 1, 2)

        self.borrow_input = QtWidgets.QLineEdit("ISBN在此键入")
        self.borrow_bar_layout1.addWidget(self.borrow_input, 0, 3, 1, 5)

        self.borrow_button = QPushButton(qtawesome.icon("fa.book"), "借书")
        self.borrow_button.setFont(qtawesome.font('fa', 10))
        self.borrow_button.clicked.connect(lambda: self.lend_book(self.borrow_input.text()))
        self.borrow_bar_layout1.addWidget(self.borrow_button, 0, 9, 1, 1)
        self.borrow_layout.addWidget(self.borrow_bar_widget1, 0, 0, 1, 9)

        # 借书结果，借书界面底部显示
        self.borrow_bar_widget2 = QtWidgets.QWidget()
        self.borrow_bar_layout2 = QtWidgets.QGridLayout(self.borrow_bar_widget2)
        self.borrow_output_label = QtWidgets.QLabel('')
        self.borrow_bar_layout2.addWidget(self.borrow_output_label, 0, 0, 1, 9)
        self.borrow_layout.addWidget(self.borrow_bar_widget2, 1, 0, 1, 9)

        # 还书界面
        self.returnBook_widget = QtWidgets.QWidget()
        self.right_widget.addWidget(self.returnBook_widget)
        self.returnBook_layout = QtWidgets.QGridLayout(self.returnBook_widget)

        # 还书界面顶端借书选项
        self.returnBook_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.returnBook_bar_layout1 = QtWidgets.QGridLayout(self.returnBook_bar_widget1)  # 右侧顶部搜索框网格布局
        self.returnBook_label = QtWidgets.QLabel("请输入ISBN号：")
        self.returnBook_bar_layout1.addWidget(self.returnBook_label, 0, 0, 1, 2)

        self.returnBook_input = QtWidgets.QLineEdit("ISBN在此键入")
        self.returnBook_bar_layout1.addWidget(self.returnBook_input, 0, 3, 1, 5)

        self.borrow_button = QPushButton(qtawesome.icon("fa.mail-forward"), "还书")
        self.borrow_button.setFont(qtawesome.font('fa', 10))
        self.borrow_button.clicked.connect(lambda: self.return_book(self.returnBook_input.text()))
        self.returnBook_bar_layout1.addWidget(self.borrow_button, 0, 9, 1, 1)
        self.returnBook_layout.addWidget(self.returnBook_bar_widget1, 0, 0, 1, 9)

        # 还书结果，借书界面底部显示
        self.returnBook_bar_widget2 = QtWidgets.QWidget()
        self.returnBook_bar_layout2 = QtWidgets.QGridLayout(self.returnBook_bar_widget2)
        self.returnBook_output_label = QtWidgets.QLabel("")
        self.returnBook_bar_layout2.addWidget(self.returnBook_output_label, 0, 0, 1, 9)

        self.returnBook_layout.addWidget(self.returnBook_bar_widget2, 1, 0, 1, 9)

        # 借阅情况界面
        self.borrow_case = QtWidgets.QWidget()
        self.right_widget.addWidget(self.borrow_case)
        self.borrowCase_layout = QtWidgets.QGridLayout(self.borrow_case)

        self.lend_label = QtWidgets.QLabel(self.lend_case(ID))
        self.borrowCase_layout.addWidget(self.lend_label, 0, 0, 2, 10)
        self.lend_view = QtWidgets.QLabel(self.history_view(ID))
        self.borrowCase_layout.addWidget(self.lend_view, 1, 0, 7, 10)
        self.case_reflash_button = QPushButton("刷新")
        self.borrowCase_layout.addWidget(self.case_reflash_button, 2, 0, 2, 10)

        # 个人中心
        self.userCenter = QWidget()
        self.right_widget.addWidget(self.userCenter)
        self.userCenter_layout = QtWidgets.QGridLayout(self.userCenter)
        self.user_info = QtWidgets.QPushButton(qtawesome.icon('fa.question-circle-o', color="black"), "个人信息")

        self.user_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.user_bar_layout1 = QtWidgets.QGridLayout(self.user_bar_widget1)  # 右侧顶部搜索框网格布局

        self.user_info.setFont(qtawesome.font('fa', 22))
        self.user_bar_layout1.addWidget(self.user_info, 8, 3, 1, 4)
        # self.user.clicked.connect(self.right_folder_button_clicked3)
        self.user_info.setStyleSheet(beauty.button_style())

        self.user1 = QtWidgets.QPushButton(qtawesome.icon('fa.envelope-open-o', color="black"), "反馈问题")
        self.user1.setFont(qtawesome.font('fa', 22))
        self.user_bar_layout1.addWidget(self.user1, 9, 3, 1, 4)
        # self.user1.clicked.connect(self.right_folder_button_clicked4)
        self.user1.setStyleSheet(beauty.button_style())

        self.user2 = QtWidgets.QPushButton(qtawesome.icon('fa.internet-explorer', color="black"), "注销")
        self.user2.setFont(qtawesome.font('fa', 22))
        self.user_bar_layout1.addWidget(self.user2, 10, 3, 1, 4)
        # self.user2.clicked.connect(self.right_folder_button_clicked5)
        self.user2.setStyleSheet(beauty.button_style())
        self.userCenter_layout.addWidget(self.user_bar_widget1, 0, 0, 1, 5)

        self.user_bar_widget2 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.user_bar_layout2 = QtWidgets.QGridLayout(self.right_bar_widget2)  # 右侧顶部搜索框网格布局
        self.userCenter_layout.addWidget(self.user_bar_widget2, 1, 0, 1, 9)

        self.show()

    def center(self):
        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def right_cliked(self, index):
        self.right_widget.setCurrentIndex(index)

    def showBook(self):
        sql = SQLOperator('root', '123456')
        com = "select * from books_view"
        title = ("%-15s\t%-15s\t%-15s\t%-15s\t%-10s\t%-15s\n" % ("ISBN", '书名', '出版社', '作者', '库存量', '价格/元'))
        sql.select(com)
        return title + sql.showResult()

    def search_book(self, keyword):
        sql = SQLOperator('root', '123456')
        com = "select * from books_view where 书名 like %s or 作者 like %s or 出版社 like %s or ISBN = %s"
        title = ("%-15s\t%-15s\t%-15s\t%-15s\t%-10s\t%-15s\n" % ("ISBN", '书名', '出版社', '作者', '库存量', '价格/元'))
        para = ("%" + keyword + "%","%" + keyword + "%","%" + keyword + "%",keyword)
        sql.select_para(com, para)
        self.search_view_table.setText(title + sql.showResult())

    def lend_book(self, ISBN):
        # 对应图书库存-1
        sql = SQLOperator('root', '123456')
        com1 = "update books set Bsur= Bsur-1 where ISBN = %s"
        para1 = ISBN
        sql.update_para(com1, para1)
        # 对应用户借书余量-1
        com2 = "update readers set remaining = remaining-1 where ID = %s"
        para2 = ID
        sql.update_para(com2, para2)
        # 添加借书事件
        com3 = "insert into lend values(%s,%s,%s,%s)"
        para3 = (ID, ISBN, datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
                 datetime.datetime.now() + datetime.timedelta(days=30))
        sql.insert_para(com3, para3)
        # 添加借书历史记录
        com4 = "insert into history values(%s,%s,%s,%s,%s)"
        para4 = (ID, ISBN, datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'), "2099-12-31", 'N')
        sql.insert_para(com4, para4)
        self.borrow_output_label.setText('已成功借阅图书')

    def return_book(self, ISBN):
        sql = SQLOperator('root', '123456')
        # 查找对应借书事件
        com3 = "select Ldate from lend where ID = %s and ISBN = %s"
        para3 = (ID, ISBN)
        sql.select_para(com3, para3)
        ldate = sql.showResult().strip()
        # 对应图书库存+1
        com1 = "update books set Bsur= Bsur+1 where ISBN = %s"
        para1 = ISBN
        sql.update_para(com1, para1)
        # 对应用户借书余量+1
        com2 = "update readers set remaining = remaining+1 where ID = %s"
        para2 = ID
        sql.update_para(com2, para2)
        # 删除借书事件
        com4 = "delete from lend where ID = %s and ISBN = %s"
        para4 = (ID, ISBN)
        sql.delete_para(com4, para4)
        # 删除借书历史记录
        com5 = "delete from history where ID = %s and ISBN = %s and Ldate =%s"
        para5 = (ID, ISBN, ldate)
        sql.delete_para(com5, para5)
        # 写入新的历史记录
        com6 = "insert into history values(%s,%s,%s,%s,%s)"
        para6 = (ID, ISBN, ldate, datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'), 'Y')
        sql.insert_para(com6, para6)
        self.returnBook_output_label.setText('已归还图书')

    def lend_case(self, ID):
        sql = SQLOperator('root', '123456')
        com = "select * from lend_case where ID = %s"
        sql.select_para(com, ID)
        title = ("%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n" % ("ID", 'ISBN号', '书名', '借书时间', '最大还书时间'))
        return "用户" + ID + "的借书情况" + '\n' + title + sql.showResult()

    def history_view(self, ID):
        sql = SQLOperator('root', '123456')
        com = "select ISBN号,书名,Ldate,Hreturn,Hcheck from history_view where ID = %s order by Ldate"
        sql.select_para(com, ID)
        title = ("%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n" % ('ISBN号', '书名', '借书时间', '还书时间', '是否还书'))
        return "借书历史记录：" + '\n' + title + sql.showResult()


