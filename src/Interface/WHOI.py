import cv2
import socket
import json
import random
import string
import time
import serial
import threading

rate = 60  # hz
rate = rate * 3  # 3 messages to send

passDict = {

}

data = {}

serial = serial.Serial("/dev/ttyUSB0", 115200)

velDict = {}
posDict = {}


def merge_two_dicts(x, y):
    """Given two dictionaries, merge them into a new dict as a shallow copy."""
    z = x.copy()
    z.update(y)
    return z


def resetPos():
    serial.read_all()
    serial.write("wcr\n".encode("utf-8"))


def read():
    report = serial.readline().decode("utf-8")
    if report.find("wrz") >= 0:
        report = report[report.find("wrz") + 4:]  # Clip the string
        report = report.split(",")
        velDict["vx"] = float(report[0])
        velDict["vy"] = float(report[1])
        velDict["vz"] = float(report[2])
        velDict["valid"] = report[3] == 'y'
        velDict["altitude"] = float(report[4])
        velDict["time"] = int(report[7])
        return True
    elif report.find("wrp") >= 0:
        report = report[report.find("wrp") + 4:]  # Clip the string
        report = report.split(",")
        posDict["time"] = float(report[0])
        posDict["x"] = float(report[1])
        posDict["y"] = float(report[2])
        posDict["z"] = float(report[3])
        posDict["roll"] = float(report[5])
        posDict["pitch"] = float(report[6])
        posDict["yaw"] = float(report[7])
        return True


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
        try:
            data = s.recv(1024).decode('utf-8')
            data = json.loads(data)
            # if(data.has_key)
            # print(data)
        except Exception as e:
            pass
    #         if data != "":
    #             break
    except (BrokenPipeError, ConnectionResetError):
        return False
    time.sleep(1 / rate)
    return True


if __name__ == '__main__':
    i = 0
    j = 0

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
            read()
            passDict = merge_two_dicts(velDict, posDict)

            if "Values" in data:
                if "button1" in data["Values"]:
                    if data["Values"]["button1"]:
                        resetPos()

            # print(posDict)
            # passDict["pitch"] = 10
            # passDict["yaw"] = i
            # passDict["altitude"] = float(i) / 80.0 - 10
            # passDict["groundSpeed"] = 19.5
            # passDict["verticalSpeed"] = (i / 15) - 10
            # passDict["terrainAlt"] = (-i / 5) + 40
            # passDict["j"] = j
            # passDict["slowSweep"] = 1 - float(j) / 180.0

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
