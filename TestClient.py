import cv2
import socket
import json
import random
import string
import time

passDict = {
    "KEY1": 3,
    "KEY2": 2.1,
    "KEY3": "afsd",
}

s = socket.socket()
s.connect(('127.0.0.1', 1254))

while True:
    passDict["KEY1"] = random.randint(0, 100)
    passDict["KEY2"] = random.randint(0, 100) / 10
    passDict["KEY3"] = ''.join(random.choices(string.ascii_uppercase + string.digits, k=8))
    bytesToSend = bytearray(json.dumps(passDict).encode())
    bytesToSend.insert(0, 3)
    print(bytesToSend)
    s.send(bytesToSend)
    time.sleep(.01)

# s = socket.socket()
# s.connect(('127.0.0.1', 1254))
# cam = cv2.VideoCapture(0)
#
# while True:
#     ret_val, img = cam.read()
#     is_success, im_buf_arr = cv2.imencode(".jpg", img)
#     bytesIN = im_buf_arr.tobytes()
#     bytesNEW = bytearray(bytesIN)
#     bytesNEW.insert(0, 4)
#     cv2.waitKey(1)
#     s.send(bytesNEW)
