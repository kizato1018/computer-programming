import d3dshot
import numpy as np
import cv2
import time

d = d3dshot.create(capture_output="numpy", frame_buffer_size=100)
d.capture()
time.sleep(3)  # Capture is non-blocking so we wait explicitely
d.stop()
for n in range(0, len(d.frame_buffer)):
    cv2.imshow('screen',d.get_frame(n))
# print(d.displays)
# time.sleep(5)
cv2.destroyAllWindows()
