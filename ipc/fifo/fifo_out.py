pipe_path = "my_pipe"

with open(pipe_path, "r") as fifo:
    for line in fifo:
        print("Reader: received ->", line.strip())