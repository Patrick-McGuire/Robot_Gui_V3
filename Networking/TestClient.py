# a = 255
#
# print(a.to_bytes(4, "little"))
# print(a.to_bytes(4, "little")[0])
# print(a.to_bytes(4, "little")[1])
# while True:
#     pass

import cv2
import socket
import json
import random
import string
import time

passDict = {
    "KEY1": 3,
    "KEY2": 2.1,
    # "KEY3": "afsd",
}

s = socket.socket()
while True:
    try:
        s.connect(('localhost', 1254))
        break
    except Exception as e:
        print(e)
        time.sleep(5)

# while True:
#     passDict["KEY1"] = random.randint(0, 100)
#     passDict["KEY2"] = random.randint(0, 100) / 10
#     passDict["KEY3"] = ''.join(random.choices(string.ascii_uppercase + string.digits, k=8))
#     bytesToSend = bytearray(json.dumps(passDict).encode())
#
#     # insert the length
#     # print(len(bytesToSend))
#     bytesNum = len(bytesToSend).to_bytes(4, "little")
#     bytesToSend.insert(0, bytesNum[3])
#     bytesToSend.insert(0, bytesNum[2])
#     bytesToSend.insert(0, bytesNum[1])
#     bytesToSend.insert(0, bytesNum[0])
#
#     bytesToSend.insert(0, 3)
#     # print(bytesToSend)
#     s.send(bytesToSend)
#     time.sleep(0.01)

cam = cv2.VideoCapture(0)
while True:
    ret_val, img = cam.read()
    is_success, im_buf_arr = cv2.imencode(".jpg", img)
    bytesIN = im_buf_arr.tobytes()
    bytesNEW = bytearray(bytesIN)

    bytesNum = len(bytesNEW).to_bytes(4, "little")
    # print(len(bytesNEW))
    bytesNEW.insert(0, 1)           # img id
    bytesNEW.insert(0, bytesNum[3])
    bytesNEW.insert(0, bytesNum[2])
    bytesNEW.insert(0, bytesNum[1])
    bytesNEW.insert(0, bytesNum[0])
    bytesNEW.insert(0, 4)
    cv2.waitKey(5)
    s.send(bytesNEW)

