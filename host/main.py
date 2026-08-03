import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 8080))

print("Connected to device!")
command = "SET_THRESHOLD 30\n"
client.send(command.encode("utf-8"))
print("Sent command:", command, end="")
while True:
    data = client.recv(1024)
    message = data.decode("utf-8")
    print("Received:", message, end="")
client.close()