import cv2
import socket
import json
import random
import string
import time

rate = 30  # hz

rate = rate * 3  # 3 messages to send

# rate = 1

boolean = False
passDict = {
    "KEY1": 3,
    "KEY2": 2.1,
    # "KEY3": "afsd",
}

cam = cv2.VideoCapture(0)


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
    try:
        s.send(bytesNEW)
    except (BrokenPipeError, ConnectionResetError):
        return True
    return False


if __name__ == '__main__':
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
            if sendImg(img, 1, 0):
                break
            time.sleep(1 / rate)
            cv2.rectangle(img, (10, 100), (200, 200), (0, 255, 0))
            if sendImg(img, 2, 0):
                break
            time.sleep(1 / rate)

            # JSON
            if random.randint(0, 100) > 85:
                boolean = not boolean
            passDict["KEY1"] = random.randint(0, 100)
            passDict["KEY2"] = random.randint(0, 100) / 10
            passDict["KEY3"] = ''.join(random.choices(string.ascii_uppercase + string.digits, k=8))
            passDict["KEY4"] = boolean
            # passDict["KEY5"] = {'test': '0.909786413025275', 'batteryVoltage': '0.009091915060669975', 'current': '45.63201604385857', 'spinny': 120, 'roll': 120, 'pitch': 10, 'yaw': 120, 'altitude': -8.5, 'groundSpeed': 19.5, 'verticalSpeed': -2.0, 'terrainAlt': 16.0, 'j': 80.5, 'slowSweep': 0.5527777777777778, 'status': 1, 'x_position_global': 0.15821773239705142, 'y_position_global': 0.9454718870797071, 'allowedToArm': True, 'armed': False, 'diagnostics_agg': {'aaa': [['hi', 'aaa'], ['bbb', 0.6750887988733792]], 'bbb': [['aa', '  0.34561301568081393'], ['bbb', 0.11375899812633583], ['c', 0.7906805705515809], ['ddddddddd', 0.5612774742237371]]}, 'annunciator': [['Overall', 0, 'Test'], ['Battery', 1, 'Test2'], ['Lights', 2, 'Test3'], ['aaaaaaaaaaaaaaaaaaaaaaaaaa', 0, 'test4']], 'annunciator_2': [['aaa', 2, 'Test'], ['bbb', 0, 'Test2'], ['ccc', 0, 'Test3'], ['ddddd', 3, 'test4']], 'status_event': [['help', 1], ['aaaaaaaaaaaaaaaa', 2], ['bbbbbbbbbbb', 3], ['qqqqqqqqq', 0]]}         #{"a": 1, "B": "ad"}  # [["poiu", 1, 1.3, True], ["2poiu", 21, 21.3, False]]
            # print(passDict)
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
            try:
                s.send(bytesToSend)
            except (BrokenPipeError, ConnectionResetError):
                break
            time.sleep(1 / rate)
        print("Disconnected")
