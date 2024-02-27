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
from PyQt5 import QtGui, QtCore, QtWidgets, QtSql
import pymysql
import xlrd


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

        self.left_button_1 = QtWidgets.QPushButton(qtawesome.icon('fa.address-card-o', color='white'), "图书总览")
        self.left_button_1.setObjectName('left_button')
        # self.left_button_1.clicked.connect(self.left_button1_clicked2)
        self.left_button_2 = QtWidgets.QPushButton(qtawesome.icon('fa.trash-o', color='white'), "图书借阅")
        self.left_button_2.setObjectName('left_button')
        # self.left_button_2.clicked.connect(self.left_button1_clicked3)
        self.left_button_3 = QtWidgets.QPushButton(qtawesome.icon('fa.pencil-square-o', color='white'), "图书归还")
        self.left_button_3.setObjectName('left_button')
        # self.left_button_3.clicked.connect(self.left_button1_clicked4)
        self.left_button_4 = QtWidgets.QPushButton(qtawesome.icon('fa.plus-square-o', color='white'), "信息增加")
        self.left_button_4.setObjectName('left_button')
        # self.left_button_4.clicked.connect(self.left_button1_clicked5)
        # self.left_button_5 = QtWidgets.QPushButton(qtawesome.icon('fa.line-chart', color='white'), "成绩排名")
        # self.left_button_5.setObjectName('left_button')
        # self.left_button_5.clicked.connect(self.left_button1_clicked6)
        self.left_button_6 = QtWidgets.QPushButton(qtawesome.icon('fa.bar-chart', color='white'), "借阅情况")
        self.left_button_6.setObjectName('left_button')
        # self.left_button_6.clicked.connect(self.left_button1_clicked7)
        self.left_button_7 = QtWidgets.QPushButton(qtawesome.icon('fa.user-o', color='white'), "个人中心")
        self.left_button_7.setObjectName('left_button')
        # self.left_button_7.clicked.connect(self.left_button1_clicked)
        self.left_button_8 = QtWidgets.QPushButton(qtawesome.icon('fa.pie-chart', color='white'), "遇到问题")
        self.left_button_8.setObjectName('left_button')
        # self.left_button_8.clicked.connect(self.left_button1_clicked8)
        self.left_button_9 = QtWidgets.QPushButton(qtawesome.icon('fa.question', color='white'), "遇到问题")
        self.left_button_9.setObjectName('left_button')
        # self.left_button_9.clicked.connect(self.left_button1_clicked1)
        self.left_xxx = QtWidgets.QPushButton(" ")
        self.left_layout.addWidget(self.left_mini, 0, 2, 1, 1)
        self.left_layout.addWidget(self.left_visit, 0, 1, 1, 1)
        self.left_layout.addWidget(self.left_close, 0, 0, 1, 1)
        self.left_layout.addWidget(self.left_label_1, 1, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_1, 2, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_2, 3, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_3, 4, 0, 1, 3)
        self.left_layout.addWidget(self.left_label_2, 6, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_4, 5, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_5, 7, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_6, 8, 0, 1, 3)
        self.left_layout.addWidget(self.left_label_3, 10, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_7, 11, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_8, 9, 0, 1, 3)
        self.left_layout.addWidget(self.left_button_9, 12, 0, 1, 3)
        self.form1 = QWidget()
        self.right_widget.addWidget(self.form1)
        self.formLayout1 = QtWidgets.QGridLayout(self.form1)

        self.right_bar_widget = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.right_bar_layout = QtWidgets.QGridLayout()  # 右侧顶部搜索框网格布局
        self.right_bar_widget.setLayout(self.right_bar_layout)

        self.right_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.right_bar_layout1 = QtWidgets.QGridLayout()  # 右侧顶部搜索框网格布局
        self.right_bar_widget1.setLayout(self.right_bar_layout1)

        self.right_folder_button22 = QtWidgets.QPushButton(qtawesome.icon('fa.folder', color='GoldenRod'), "")
        self.right_folder_button22.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:none}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.right_folder_button22.setObjectName('right_search_button')
        self.right_folder_button22.setFont(qtawesome.font('fa', 16))
        # self.right_folder_button22.clicked.connect(self.right_folder_button_clicked31)
        self.right_folder_button22.setFixedSize(30, 30)  # 设置按钮大小

        self.right_folder_button11 = QtWidgets.QPushButton("导入数据库")
        self.right_folder_button11.setObjectName('right_search_button')
        self.right_folder_button11.setFont(qtawesome.font('fa', 16))
        # self.right_folder_button11.clicked.connect(self.right_folder_button_clicked51)
        self.right_folder_button11.setFixedSize(140, 40)  # 设置按钮大小
        self.right_folder_button11.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.right_folder_button111 = QtWidgets.QPushButton("清空数据库")
        self.right_folder_button111.setObjectName('right_search_button')
        self.right_folder_button111.setFont(qtawesome.font('fa', 16))
        # self.right_folder_button111.clicked.connect(self.view_data23)
        self.right_folder_button111.setFixedSize(140, 40)  # 设置按钮大小
        self.right_folder_button111.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")

        self.right_bar_widget_folder_input9 = QtWidgets.QLineEdit()
        self.right_bar_widget_folder_input9.setPlaceholderText("填入或选择需要上传的文件夹")
        self.right_bar_widget_folder_input9.setObjectName("right_input_item")
        self.right_bar_widget_folder_input9.setStyleSheet(
            '''QLineEdit{
                    border:1px solid gray;
                    width:10px;
                    border-radius:10px;
                    padding:2px 4px;
            }''')
        self.user11 = QtWidgets.QLabel("数据的导入")
        self.user11.setFont(qtawesome.font('fa', 22))
        self.right_bar_layout1.addWidget(self.user11, 0, 0, 1, 10)

        self.recommend_button_11 = QtWidgets.QToolButton()
        self.recommend_button_11.setIcon(QtGui.QIcon('./5.jpg'))
        self.recommend_button_11.setIconSize(QtCore.QSize(1000, 1000))
        self.right_bar_layout1.addWidget(self.recommend_button_11, 0, 0, 10, 10)
        self.recommend_button_11.setStyleSheet('''
                                                       QToolButton{border:none;color:black;}
                                                       QToolButton:hover{color:white}
                                                        ''')
        self.right_bar_layout1.addWidget(self.right_folder_button22, 8, 1, 20, 6)
        self.right_bar_layout1.addWidget(self.right_folder_button11, 10, 3, 20, 1)
        self.right_bar_layout1.addWidget(self.right_folder_button111, 10, 5, 20, 1)
        self.right_bar_layout1.addWidget(self.right_bar_widget_folder_input9, 8, 2, 20, 6)
        self.formLayout1.addWidget(self.right_bar_widget1, 0, 0, 9, 0)

        # 个人中心
        self.form2 = QWidget()
        self.right_widget.addWidget(self.form2)
        self.formLayout2 = QtWidgets.QGridLayout(self.form2)

        # 2.1 信息提示对话框
        self.right_message_Alter = QMessageBox();
        self.right_message_Alter.setObjectName("right_message_Alter");
        self.right_message_Alter.setWindowOpacity(0.9)  # 设置窗口透明度
        self.right_message_Alter.setWindowFlag(QtCore.Qt.FramelessWindowHint)  # 隐藏边框

        self.right_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.right_bar_layout1 = QtWidgets.QGridLayout()  # 右侧顶部搜索框网格布局
        self.right_bar_widget1.setLayout(self.right_bar_layout1)

        # 2.2 个人信息
        self.a = QPushButton(qtawesome.icon('fa.user', color="black"), ":")  # 个人账号
        self.a.setStyleSheet('''QPushButton{border:none;color:black;}''')
        self.a1 = QPushButton(qtawesome.icon('fa.mars', color="black"), ":")  # 个人账号
        self.a1.setStyleSheet('''QPushButton{border:none;color:black;}''')
        self.a2 = QPushButton(qtawesome.icon('fa.university', color="black"), ":")  # 个人账号
        self.a2.setStyleSheet('''QPushButton{border:none;color:black;}''')
        self.a3 = QPushButton(qtawesome.icon('fa.birthday-cake', color="black"), ":")  # 个人账号
        self.a3.setStyleSheet('''QPushButton{border:none;color:black;}''')
        self.a4 = QPushButton(qtawesome.icon('fa.child', color="black"), ":")  # 个人账号
        self.a4.setStyleSheet('''QPushButton{border:none;color:black;}''')
        self.user9 = QtWidgets.QLabel("个人资料")
        self.user9.setFont(qtawesome.font('fa', 31))
        self.right_bar_layout1.addWidget(self.user9, 0, 1, 2, 4)
        # 右边栏美化
        # 右边框整体风格美化
        self.right_widget.setStyleSheet('''
                            QStackedWidget#right_stacked_Widget{
                                color:#232C51;
                                background:white;
                                border-top:1px solid darkGray;
                                border-bottom:1px solid darkGray;
                                border-right:1px solid darkGray;
                                border-top-right-radius:10px;
                                border-bottom-right-radius:10px;
                            }
                            QLabel#right_lable{
                                border:none;
                                font-size:16px;
                                font-weight:700;
                                font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
                            }
                        ''')

        self.right_layout.addWidget(self.right_bar_widget, 0, 0, 1, 9)


        self.left_close.setFixedSize(15, 15)  # 设置关闭按钮的大小
        self.left_visit.setFixedSize(15, 15)  # 设置按钮大小
        self.left_mini.setFixedSize(15, 15)  # 设置最小化按钮大小
        self.left_close.setStyleSheet(
            '''QPushButton{background:#F76677;border-radius:5px;}QPushButton:hover{background:red;}''')
        self.left_visit.setStyleSheet(
            '''QPushButton{background:#F7D674;border-radius:5px;}QPushButton:hover{background:yellow;}''')
        self.left_mini.setStyleSheet(
            '''QPushButton{background:#6DDF6D;border-radius:5px;}QPushButton:hover{background:green;}''')
        self.left_widget.setStyleSheet('''
                           QPushButton{border:none;color:white;}
                           QPushButton#left_label{
                               border:none;
                               border-bottom:1px solid SteelBlue;
                               font-size:18px;
                               font-weight:700;
                               font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
                           }
                           QPushButton#left_button:hover{border-left:4px solid red;font-weight:700;}
                           QWidget#left_widget{
                               background:Black;
                               border-top:1px solid white;
                               border-bottom:1px solid white;
                               border-left:1px solid white;
                               border-top-left-radius:10px;
                               border-bottom-left-radius:10px;
                           }
                       ''')

        self.right_widget.setStyleSheet('''
                  QWidget#right_widget{
                    color:#232C51;
                    background:white;
                    border-top:1px solid darkGray;
                    border-bottom:1px solid darkGray;
                    border-right:1px solid darkGray;
                    border-top-right-radius:10px;
                    border-bottom-right-radius:10px;
                  }
                  QLabel#right_lable{
                    border:none;
                    font-size:16px;
                    font-weight:700;
                    font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
                  }
                ''')
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
        # 遇到问题
        self.form3 = QWidget()
        self.right_widget.addWidget(self.form3)
        self.formLayout2 = QtWidgets.QGridLayout(self.form3)

        # 2.1 信息提示对话框
        self.right_message_Alter = QMessageBox();
        self.right_message_Alter.setObjectName("right_message_Alter");
        self.right_message_Alter.setWindowOpacity(0.9)  # 设置窗口透明度
        self.right_message_Alter.setWindowFlag(QtCore.Qt.FramelessWindowHint)  # 隐藏边框

        self.right_bar_widget1 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.right_bar_layout1 = QtWidgets.QGridLayout()  # 右侧顶部搜索框网格布局
        self.right_bar_widget1.setLayout(self.right_bar_layout1)

        # 2.2 问题
        self.user9 = QtWidgets.QLabel("关于与帮助")
        self.user9.setFont(qtawesome.font('fa', 30))
        self.right_bar_layout1.addWidget(self.user9, 0, 1, 2, 4)
        self.user = QtWidgets.QPushButton(qtawesome.icon('fa.question-circle-o', color="black"), "使用帮助")
        self.user.setFont(qtawesome.font('fa', 22))
        self.right_bar_layout1.addWidget(self.user, 8, 3, 1, 4)
        # self.user.clicked.connect(self.right_folder_button_clicked3)
        self.user.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.user1 = QtWidgets.QPushButton(qtawesome.icon('fa.envelope-open-o', color="black"), "反馈问题")
        self.user1.setFont(qtawesome.font('fa', 22))
        self.right_bar_layout1.addWidget(self.user1, 9, 3, 1, 4)
        # self.user1.clicked.connect(self.right_folder_button_clicked4)
        self.user1.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.user2 = QtWidgets.QPushButton(qtawesome.icon('fa.internet-explorer', color="black"), "学校官网")
        self.user2.setFont(qtawesome.font('fa', 22))
        self.right_bar_layout1.addWidget(self.user2, 10, 3, 1, 4)
        # self.user2.clicked.connect(self.right_folder_button_clicked5)
        self.user2.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.user3 = QtWidgets.QPushButton(qtawesome.icon('fa.users', color="black"), "主创人员")
        self.user3.setFont(qtawesome.font('fa', 22))
        self.right_bar_layout1.addWidget(self.user3, 11, 3, 1, 4)
        # self.user3.clicked.connect(self.right_folder_button_clicked6)
        self.user3.setStyleSheet(
            "QPushButton{color:highlight}"
            "QPushButton:hover{color:white}"
            "QPushButton{background-color:rgb(0,191,255)}"
            "QPushButton{border:2px}"
            "QPushButton{border-radius:10px}"
            "QPushButton{padding:5px 6px}"
            "QPushButton{font-size:14pt}")
        self.formLayout2.addWidget(self.right_bar_widget1, 0, 0, 1, 5)
        self.recommend_button_1 = QtWidgets.QToolButton()
        self.recommend_button_1.setIcon(QtGui.QIcon('./4.jpg'))
        self.recommend_button_1.setIconSize(QtCore.QSize(1000, 1000))
        self.right_bar_layout1.addWidget(self.recommend_button_1, 2, 1, 6, 8)
        self.recommend_button_1.setStyleSheet('''
                                                 QToolButton{border:none;color:black;}
                                                 QToolButton:hover{color:white}
                                                  ''')
        self.right_bar_widget2 = QtWidgets.QWidget()  # 右侧顶部搜索框部件
        self.right_bar_layout2 = QtWidgets.QGridLayout()  # 右侧顶部搜索框网格布局
        self.right_bar_widget2.setLayout(self.right_bar_layout2)
        self.formLayout2.addWidget(self.right_bar_widget2, 1, 0, 1, 9)

        self.show()
if __name__ == '__main__':

    app = QApplication(sys.argv)
    e = MainUi()
    sys.exit(app.exec_())