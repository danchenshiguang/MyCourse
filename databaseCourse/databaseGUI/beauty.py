from PyQt5 import QtGui, QtCore, QtWidgets, QtSql,Qt
from PyQt5.QtWidgets import *
import sys
import qtawesome
def right_style_beauty(ui):
    ui.right_widget.setStyleSheet('''
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
    ui.right_widget.setStyleSheet('''
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


def left_style_beauty(ui):
    ui.left_close.setFixedSize(15, 15)  # 设置关闭按钮的大小
    ui.left_visit.setFixedSize(15, 15)  # 设置按钮大小
    ui.left_mini.setFixedSize(15, 15)  # 设置最小化按钮大小
    ui.left_close.setStyleSheet(
        '''QPushButton{background:#F76677;border-radius:5px;}QPushButton:hover{background:red;}''')
    ui.left_visit.setStyleSheet(
        '''QPushButton{background:#F7D674;border-radius:5px;}QPushButton:hover{background:yellow;}''')
    ui.left_mini.setStyleSheet(
        '''QPushButton{background:#6DDF6D;border-radius:5px;}QPushButton:hover{background:green;}''')
    ui.left_widget.setStyleSheet('''
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
def button_style():
    style = \
"QPushButton{color:highlight}\
QPushButton:hover{color:white}\
QPushButton{background-color:rgb(0,191,255)}\
QPushButton{border:2px}\
QPushButton{border-radius:10px}\
QPushButton{padding:5px 6px}\
QPushButton{font-size:14pt}"
    return style