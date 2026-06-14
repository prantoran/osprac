import os
import time 

pipe_path = "my_pipe"

with open(pipe_path, "w") as fifo:
	for i in range(5):
		msg = f"Msg {i}"
		print(f"Writer: sending -> {msg}")
		fifo.write(msg + "\n")
		fifo.flush()
		time.sleep(1)

