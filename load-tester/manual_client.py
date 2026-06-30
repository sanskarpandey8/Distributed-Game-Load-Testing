import socket

HOST = "127.0.0.1"
PORT = 8080

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

commands = [
    "LOGIN Player1",
    "MOVE UP",
    "MOVE LEFT",
    "ATTACK Enemy",
    "STATUS"
]

for command in commands:

    sock.sendall((command + "\n").encode())

    response = sock.recv(1024).decode()

    print(command)
    print("->", response)
    print()

sock.close()