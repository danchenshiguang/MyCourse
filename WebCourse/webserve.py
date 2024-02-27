import socket
import re
HOST = ""  # ip地址
PORT = 8888  # 端口

html_seg = '''
HTTP/1.1 200 OK
Content-Type:text/html
Connection: close

'''
    # 类型为图片的报文首部
picture_seg = '''
HTTP/1.1 200 OK     
Content-Type:image/jpg

'''
def get_method_src(request):
    """解析请求数据，获取请求报文的方法和源"""
    method = request.split(' ')[0]
    src =request.split(' ')[1]
    return method,src


def get_file_content(filename):
    """获得文件的内容"""
    if filename == 'first.html':
        with open(f"{filename}", mode="r") as fp:
            data = fp.read()
            fp.close()
    elif filename == 'network.jpg':
        with open(f"{filename}", mode="rb") as fp:
            data = fp.read()
            fp.close()
    elif filename == 'second.html':
        with open(f"{filename}", mode="r",encoding="utf-8") as fp:
            data = fp.read()
            fp.close()
    return data


def get_response(method, src):
    data = ""
    #deal wiht GET method
    if method == 'GET':
        if src == '/first.html'or src =='/':
             data = html_seg+get_file_content("first.html")
        elif src == '/network.jpg':
            return picture_seg.encode()+get_file_content("network.jpg")
        elif src == '/second.html':
            data = html_seg+get_file_content("second.html")
        elif re.match('^/\?.*$', src):
            entry = src.split('?')[1]      # main content of the request
            data = html_seg+entry
            data += '<br /><font color="green" size="7">you enter second html!</p>'
    elif method == 'POST':
        data =html_seg+ '<br /><font color="green" size="7">register successs!</p>'

    return data.encode("utf-8")


def main():
    server_socket= socket.socket(socket.AF_INET,socket.SOCK_STREAM)  # AF_INET表示地址是用ipv4协议，SOCK_STREAM表示TCP连接
    # server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))  # 这个socket绑定这个端口
    server_socket.listen(5)  # 监听此端口，参数为5表示接收5个连接，这里会阻塞
    print("Serving Http on port %s..."%PORT)
    while True:
        connection, addr = server_socket.accept()  # 如果接收到连接，获取这个连接对象和它的地址
        print('Connected by', addr)
        resquest = connection.recv(1024) # 接收数据，数据的最大值为1024bit
        print(resquest.decode(('utf-8')))
        mathod,src =get_method_src(resquest.decode('utf-8'))#获取方法和源
        end_data = get_response(mathod, src)  #得到响应数据
        connection.sendall(end_data)  # 发送响应数据
        connection.close()

if __name__ == '__main__':
    main()