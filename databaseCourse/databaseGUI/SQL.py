import pymysql
import time


class SQLResult():
    def __init__(self, cursor):
        self.data = cursor.fetchall()
        self.desp = self.getTitle(cursor.description)

    def getTitle(self, desp):
        title = []
        for elem in desp:
            title.append(elem[0])
            # print(elem[0])
        return title


class SQLOperator():
    # mysql_conn = pymysql.connect(host='localhost', port=3306, user='root', password='123456',
    # db='book-management_system')
    def __init__(self, user, pwd):
        self.mysql_conn = pymysql.connect(host='localhost', port=3306, user=user, password=pwd,
                                          db='book-management_system')
        self.title = []

    def select(self, sqlCommand):
        try:
            with self.mysql_conn.cursor() as cursor:
                # print("echo1")

                cursor.execute(sqlCommand)
                self.result = SQLResult(cursor)
                # self.description=self.getTitle(cursor.description)
                # self.showResult()
        except Exception as e:
            print("error1")
            self.result.data = None

    def update(self, sqlCommand):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                self.mysql_conn.commit()

        except Exception as e:
            self.mysql_conn.rollback()
            print("error2")

    def insert(self, sqlCommand):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                self.mysql_conn.commit()
        except Exception as e:
            self.mysql_conn.rollback()
            print("error3")

    def deleted(self, sqlCommand):
        try:
            with self.mysql_conn.cursor() as cursor:
                # print("echo1")
                cursor.execute(sqlCommand)
                self.mysql_conn.commit()
        except Exception as e:
            self.mysql_conn.rollback()
            print("error4")

    def call(self, sqlCommand):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                self.mysql_conn.commit()
        except Exception as e:
            print("error5")
            self.mysql_conn.rollback()

    def showResult(self):
        if self.result.data is None:
            return
        # print(self.result.desp)
        string =''
        for res in self.result.data:
            for elem in res:
                string += ("%-15s\t"%str(elem))
            string +='\n'
        return string

    def getComboxList(self, sqlCommand):
        targetList = ["ALL"]
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                data = cursor.fetchall()
                for elem in data:
                    targetList.append(elem[0])
        except Exception as e:
            print("error6")
        return targetList

    def getComboxList_noneAll(self, sqlCommand):
        targetList = []
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                data = cursor.fetchall()
                for elem in data:
                    targetList.append(elem[0])
        except Exception as e:
            print("error7")
        return targetList

    def select_para(self, cmd, paras):
        try:
            with self.mysql_conn.cursor() as cursor:
                # print("echo1")

                cursor.execute(cmd, paras)
                self.result = SQLResult(cursor)
                # self.description=self.getTitle(cursor.description)
                # self.showResult()
        except Exception as e:
            print("error8")
            self.result.data = None

    def insert_para(self, sqlCommand, paras):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand, paras)
                self.mysql_conn.commit()
        except Exception as e:
            self.mysql_conn.rollback()
            print("error9")

    def delete_para(self, sqlCommand, paras):
        try:
            with self.mysql_conn.cursor() as cursor:
                # print("echo1")
                cursor.execute(sqlCommand, paras)
                self.mysql_conn.commit()
        except Exception as e:
            self.mysql_conn.rollback()
            print("error10")

    def update_para(self, sqlCommand, paras):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand, paras)
                self.mysql_conn.commit()
        except Exception as e:
            self.mysql_conn.rollback()
            print("error11")

    def call_para(self, sqlCommand, paras):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                self.mysql_conn.commit()
        except Exception as e:
            print("error12")
            self.mysql_conn.rollback()

    def getSingleValue(self, sqlCommand):
        try:
            with self.mysql_conn.cursor() as cursor:
                cursor.execute(sqlCommand)
                data = cursor.fetchall()
                return data[0][0]
        except Exception as e:
            print("error13")
            # self.mysql_conn.rollback()


class SQLCounter(SQLOperator):
    def __init__(self, user, pwd):
        super(SQLCounter, self).__init__(user, pwd)
