import sys
from 双序列比对 import NW_alignment
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QTextEdit, QPushButton, QFileDialog


class InputOutputWindow(QWidget):
    def __init__(self):
        super().__init__()

        # 设置窗口标题和大小
        self.setWindowTitle('输入输出窗口')
        self.resize(400, 400)

        # 创建控件
        file1_label = QLabel('fasta文件1:', self)
        self.fasta_file1_edit = QLineEdit(self)
        file1_button = QPushButton('选择文件', self)
        file2_label = QLabel('fasta文件2:', self)
        self.fasta_file2_edit = QLineEdit(self)
        file2_button = QPushButton('选择文件', self)
        output_label = QLabel('输出:', self)
        self.output_edit = QTextEdit(self)
        self.output_edit.setReadOnly(True)
        submit_button = QPushButton('提交', self)

        # 创建布局
        file1_layout = QHBoxLayout()
        file1_layout.addWidget(file1_label)
        file1_layout.addWidget(self.fasta_file1_edit)
        file1_layout.addWidget(file1_button)

        file2_layout = QHBoxLayout()
        file2_layout.addWidget(file2_label)
        file2_layout.addWidget(self.fasta_file2_edit)
        file2_layout.addWidget(file2_button)

        output_layout = QHBoxLayout()
        output_layout.addWidget(output_label)
        output_layout.addWidget(self.output_edit)

        button_layout = QHBoxLayout()
        button_layout.addStretch(1)
        button_layout.addWidget(submit_button)

        main_layout = QVBoxLayout()
        main_layout.addLayout(file1_layout)
        main_layout.addLayout(file2_layout)
        main_layout.addLayout(output_layout)
        main_layout.addLayout(button_layout)

        # 设置窗口的主布局
        self.setLayout(main_layout)

        # 连接信号和槽
        file1_button.clicked.connect(self.on_file1_button_clicked)
        file2_button.clicked.connect(self.on_file2_button_clicked)
        submit_button.clicked.connect(self.on_submit)

    def on_file1_button_clicked(self):
        # 打开文件对话框并获取选择的文件路径
        file_path, _ = QFileDialog.getOpenFileName(self, '选择文件', '', 'Text Files (*.txt);;All Files (*)')

        # 如果选择了文件，则在文件1编辑框中显示文件路径
        if file_path:
            self.fasta_file1_edit.setText(file_path)

    def on_file2_button_clicked(self):
        # 打开文件对话框并获取选择的文件路径
        file_path, _ = QFileDialog.getOpenFileName(self, '选择文件', '', 'Text Files (*.txt);;All Files (*)')

        # 如果选择了文件，则在文件2编辑框中显示文件路径
        if file_path:
            self.fasta_file2_edit.setText(file_path)

    def on_submit(self):
        # 获取文件路径
        file1_path = self.fasta_file1_edit.text()
        file2_path = self.fasta_file2_edit.text()
        print("ll")
        print(file1_path)
        result = NW_alignment(file1_path,file2_path)
        print(result)
        # 处理文件内容并输出结果
        output_text = f'fasta1_alignment:{result[0]}\nfasta2_alignment:{result[1]}\nscores:{result[2]}'
        self.output_edit.setText(output_text)


if __name__ == '__main__':
    # 创建应用程序对象
    app = QApplication(sys.argv)

    # 创建窗口对象
    window = InputOutputWindow()

    # 显示窗口
    window.show()

    # 运行应用程序
    sys.exit(app.exec_())