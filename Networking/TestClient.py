import cv2
import socket
import json
import random
import string
import time

boolean = False
passDict = {
    "KEY1": 3,
    "KEY2": 2.1,
    # "KEY3": "afsd",
}

cam = cv2.VideoCapture(0)


def sendImg(imgToSend, idThing):
    is_success, im_buf_arr = cv2.imencode(".jpg", img)
    bytesIN = im_buf_arr.tobytes()
    bytesNEW = bytearray(bytesIN)

    bytesNum2 = len(bytesNEW).to_bytes(4, "little")
    # print(len(bytesNEW))
    bytesNEW.insert(0, idThing)           # img id
    bytesNEW.insert(0, bytesNum2[3])
    bytesNEW.insert(0, bytesNum2[2])
    bytesNEW.insert(0, bytesNum2[1])
    bytesNEW.insert(0, bytesNum2[0])
    bytesNEW.insert(0, 4)
    # cv2.waitKey(1)
    try:
        s.send(bytesNEW)
    except (BrokenPipeError, ConnectionResetError):
        return True
    return False


while True:
    s = socket.socket()
    while True:
        try:
            s.connect(('localhost', 1254))
            break
        except ConnectionRefusedError:
            time.sleep(1)
    print("Connected")

    while True:
        ret_val, img = cam.read()
        if sendImg(img, 1):
            break
        cv2.rectangle(img, (10, 100), (200, 200), (0, 255, 0))
        if sendImg(img, 2):
            break

        # JSON
        if random.randint(0, 100) > 85:
            boolean = not boolean
        passDict["KEY1"] = random.randint(0, 100)
        passDict["KEY2"] = random.randint(0, 100) / 10
        passDict["KEY3"] = ''.join(random.choices(string.ascii_uppercase + string.digits, k=8))
        passDict["KEY4"] = boolean
        bytesToSend = bytearray(json.dumps(passDict).encode())

        # insert the length
        # print(len(bytesToSend))
        bytesNum = len(bytesToSend).to_bytes(4, "little")
        bytesToSend.insert(0, bytesNum[3])
        bytesToSend.insert(0, bytesNum[2])
        bytesToSend.insert(0, bytesNum[1])
        bytesToSend.insert(0, bytesNum[0])

        bytesToSend.insert(0, 3)
        try:
            s.send(bytesToSend)
        except (BrokenPipeError, ConnectionResetError):
            break
        # time.sleep(1/20)
    print("Disconnected")

