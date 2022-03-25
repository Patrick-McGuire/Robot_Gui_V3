
from networktables import NetworkTables
import cv2
import socket
import json
import random
import string
import time

rate = 60  # hz
rate = rate * 3  # 3 messages to send

boolean = False
passDict = {
    # "KEY1": 3,
    "KEY2": 2.1,
    # "KEY3": "afsd",
}

cam = cv2.VideoCapture(0)
s = socket.socket()

data = ""


def sendData(dataToSend):
    global s, data, rate
    # Attempt to send the data
    try:
        s.send(dataToSend)
    except (BrokenPipeError, ConnectionResetError):
        return False
    startTime = time.time()
    # while startTime > time.time() - .1:
    try:
        data = s.recv(1024).decode('utf-8')
        # print(data)
    #         if data != "":
    #             break
    except (BrokenPipeError, ConnectionResetError):
        return False
    time.sleep(1 / rate)
    return True


def sendImg(imgToSend, idThing, rtnCode):
    is_success, im_buf_arr = cv2.imencode(".jpg", img)
    bytesIN = im_buf_arr.tobytes()
    bytesNEW = bytearray(bytesIN)

    bytesNum2 = len(bytesNEW).to_bytes(4, "little")
    # print(len(bytesNEW))
    bytesNEW.insert(0, idThing)
    bytesNEW.insert(0, rtnCode)  # img id
    bytesNEW.insert(0, bytesNum2[3])
    bytesNEW.insert(0, bytesNum2[2])
    bytesNEW.insert(0, bytesNum2[1])
    bytesNEW.insert(0, bytesNum2[0])
    bytesNEW.insert(0, 4)
    # cv2.waitKey(1)
    return sendData(bytesNEW)


if __name__ == '__main__':
    i = 0
    j = 0

    NetworkTables.initialize("10.1.25.2")
    print("Connecting...")
    while not NetworkTables.isConnected():
        NetworkTables.initialize("10.1.25.2")
        time.sleep(1)

# while True:
#     print(NetworkTables.getTable("SmartDashboard").getEntry("Alliance").value)
#     time.sleep(1)

    while True:
        s = socket.socket()
        while True:
            try:
                s.connect(('localhost', 1254))
                # s.setblocking(False)
                break
            except ConnectionRefusedError:
                time.sleep(1)
        print("Connected")

        while True:
            # ret_val, img = cam.read()
            # if not sendImg(img, 1, 0):
            #     break
            # time.sleep(1 / rate)
            # cv2.rectangle(img, (10, 100), (200, 200), (0, 255, 0))
            # if not sendImg(img, 2, 0):
            #     break
            # time.sleep(1 / rate)

            # JSON
            if random.randint(0, 100) > 85:
                boolean = not boolean
            passDict["RED"] = NetworkTables.getTable("Shuffleboard").getSubTable("Feeder").getEntry("Red").value
            passDict["BLUE"] = NetworkTables.getTable("Shuffleboard").getSubTable("Feeder").getEntry("Blue").value
            passDict["SIDE"] = (not NetworkTables.getTable("Shuffleboard").getSubTable("Feeder").getEntry("Sensor 1").value) * 200
            passDict["THREE"] = (not NetworkTables.getTable("Shuffleboard").getSubTable("Feeder").getEntry("Sensor 3").value) * 400.0 + 5
            passDict["BOTTOM"] = (not NetworkTables.getTable("Shuffleboard").getSubTable("Feeder").getEntry("Color Prox").value) * 300
            # passDict["QU"] = 4#len(NetworkTables.getTable("SmartDashboard").getEntry("balls (queue)").getString("123"))
            # passDict["ballLeftPoopEn  trance"] = NetworkTables.getTable("SmartDashboard").getEntry("ballLeftPoopEntrance").value
            # passDict["Color Prox"] = NetworkTables.getTable("SmartDashboard").getEntry("Color Prox").value

            bytesToSend = bytearray(json.dumps(passDict).encode())

            # insert the length
            # print(len(bytesToSend))
            bytesNum = len(bytesToSend).to_bytes(4, "little")
            bytesToSend.insert(0, 0)
            bytesToSend.insert(0, bytesNum[3])
            bytesToSend.insert(0, bytesNum[2])
            bytesToSend.insert(0, bytesNum[1])
            bytesToSend.insert(0, bytesNum[0])

            bytesToSend.insert(0, 3)
            if not sendData(bytesToSend):
                break
            # print(1)

            i += 3
            if i > 360:
                i = 0

            j += 0.5
            if j > 360:
                j = 0

        print("Disconnected")
