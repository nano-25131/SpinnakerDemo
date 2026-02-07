import os
import mmap
import struct
import time
import numpy as np
import cv2

SHM_NAME = "/spinnaker_img"
SHM_WIDTH = 64
SHM_HEIGHT =  64
SHM_CHANNELS = 1
IMG_SIZE = SHM_WIDTH * SHM_HEIGHT * SHM_CHANNELS

shm_path = "/dev/shm" + SHM_NAME

fd = os.open(shm_path, os.O_RDONLY)

mm = mmap.mmap(
    fd,
    length=16 + IMG_SIZE,
    access=mmap.ACCESS_READ
)

print("Shared memory opened.")

last_time = time.time()
fps = 0.0

try:
    while True:
        mm.seek(0)
        header = mm.read(16)
        ready, width, height, channels = struct.unpack("4i", header)

        if ready != 1:
            time.sleep(0.001)
            continue

        img_bytes = mm.read(IMG_SIZE)

        img = np.frombuffer(img_bytes, dtype=np.uint8)
        img = img.reshape((height, width))

        # ========= FPS 计算 =========
        now = time.time()
        dt = now - last_time
        last_time = now

        if dt > 0:
            inst_fps = 1.0 / dt
            fps = fps * 0.9 + inst_fps * 0.1
        # ============================

        # 显示 FPS
        vis = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
       # cv2.putText(
        #    vis,
       #     f"FPS: {fps:.1f}",
      #      (10, 30),
     #       cv2.FONT_HERSHEY_SIMPLEX,
    #        0.8,
   #         (0, 255, 0),
  #          2,
 #           cv2.LINE_AA
#        )

        cv2.imshow("Shared Memory Image", vis)

        if cv2.waitKey(1) == 27:
            break

finally:
    mm.close()
    os.close(fd)
    cv2.destroyAllWindows()
