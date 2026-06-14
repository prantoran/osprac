import socket

HOST = "127.0.0.1"
PORT = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    message = input("Enter message: ")
    s.sendall(message.encode())
    data = s.recv(1024)

print("Client received:", data.decode())