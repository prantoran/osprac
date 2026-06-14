import socket

HOST = "127.0.0.1"
PORT = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print("Server: waiting for a connection...")

    conn, addr = s.accept()
    with conn:
        print(f"Server: connected to {addr}")
        while True:
            data = conn.recv(1024)
            if not data:
                break
            response = data.decode().upper()
            conn.sendall(response.encode())