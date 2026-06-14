import threading
import time
import random

BUFFER_SIZE = 5
buffer = []

empty = threading.Semaphore(BUFFER_SIZE)   # counts empty slots
full = threading.Semaphore(0)              # counts filled slots
mutex = threading.Lock()                   # protects buffer


def producer(pid):
    while True:
        item = random.randint(1, 100)
        empty.acquire()
        with mutex:
            buffer.append(item)
            print(f"Producer {pid}: added {item} | Buffer: {buffer}")
        full.release()
        time.sleep(random.uniform(0.5, 1.5))


def consumer(cid):
    while True:
        full.acquire()
        with mutex:
            item = buffer.pop(0)
            print(f"Consumer {cid}: removed {item} | Buffer: {buffer}")
        empty.release()
        time.sleep(random.uniform(0.5, 1.5))


producers = [threading.Thread(target=producer, args=(1,))]
consumers = [threading.Thread(target=consumer, args=(1,))]

for p in producers:
    p.start()

for c in consumers:
    c.start()