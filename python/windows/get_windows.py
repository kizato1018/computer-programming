from PIL import ImageGrab
import numpy as np
import cv2
import win32gui, win32ui, win32con, win32api
import time
import numba as nb


# fps
prev_frame_t = 0
new_frame_t = 0



traindata = 'C:/Users/蕭瀜/AppData/Local/Programs/Python/Python39/Lib/site-packages/cv2/data/haarcascade_frontalface_default.xml'
# 載入分類器
face_cascade = cv2.CascadeClassifier('./haarcascade_frontalface_default.xml')
# print(face_cascade)


hwnd = win32gui.GetDesktopWindow()
cnt = 0
while True:
    cnt += 1
    left, top, right, bot = win32gui.GetWindowRect(hwnd)
    # try :
        # left, top, right, bot = win32gui.GetWindowRect(hwnd)
    # except :
    #     print("找不到視窗")
    #     break

    img = ImageGrab.grab(bbox = (left, top, right, bot))
    img = img.resize((1280,768))
    img_np = np.array(img)

    new_frame_t = time.time()
    fps = 1 / float(new_frame_t - prev_frame_t)
    prev_frame_t = new_frame_t
    fps = (str(int(fps)))
    print(fps)
    if(cnt % 5):
        cnt = 0
        gray = cv2.cvtColor(img_np, cv2.COLOR_BGR2GRAY)
        # 偵測臉部
        faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.08,
        minNeighbors=3,
        minSize=(16, 16))
        # 繪製人臉部份的方框
        for (x, y, w, h) in faces:
            cv2.rectangle(img_np, (x, y), (x + w, y + h), (0, 255, 0), 2)

    img_np = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)
#     cv2.namedWindow('screen box', cv2.WINDOW_NORMAL)  #正常視窗大小
    cv2.putText(img_np, fps, (7, 70), cv2.FONT_HERSHEY_SIMPLEX, 3, (100, 255, 0), 3, cv2.LINE_AA) 
    cv2.imshow("screen box", img_np)
    k = cv2.waitKey(30)&0xFF #64bits! need a mask
    if k ==27:
        cv2.destroyAllWindows()
        break