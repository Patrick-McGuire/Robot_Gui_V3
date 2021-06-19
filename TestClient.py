import cv2
import socket

s = socket.socket()
s.connect(('127.0.0.1', 1254))
cam = cv2.VideoCapture(0)

while True:
    ret_val, img = cam.read()
    is_success, im_buf_arr = cv2.imencode(".jpg", img)
    bytesIN = im_buf_arr.tobytes()
    bytesNEW = bytearray(bytesIN)
    bytesNEW.insert(0, 4)
    cv2.waitKey(1)
    s.send(bytesNEW)
