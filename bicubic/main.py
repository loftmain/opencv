import cv2
import os
import numpy as np
import tkinter as tk
from tkinter import filedialog
import bicubic
import re
import tempfile
import shutil
from matplotlib import pyplot as plt

def imreadEX(image_path):
    if re.compile('[^ㄱ-ㅣ가-힣]+').sub('', image_path):
            stream = open(image_path, "rb")
            bytes = bytearray(stream.read())
            numpyarray = np.asarray(bytes, dtype=np.uint8)
            img = cv2.imdecode(numpyarray, cv2.COLOR_BGR2GRAY)

            if not img is None:
                return img
            else:
                file_tmp=tempfile.NamedTemporaryFile().name
                shutil.copy(image_path,file_tmp)
                image_path=file_tmp
    img = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)
    return img


# 파일선택창
root = tk.Tk()
root.withdraw()
filename = filedialog.askopenfilename(title='Choose a original file')
img_hr = imreadEX(filename)
print(filename + ' loaded ')

print('cubic interpolation do:  ' + filename)

bicubic = bicubic.bicubic(img_hr, img_hr.shape[1] * 2, img_hr.shape[0] * 2) # 로직 biccubic.py

cv2.imwrite('saved_bicubic.png', bicubic)
print(filename + ' saved as ' + filename)
bicubic_img = cv2.imread('saved_bicubic.png', cv2.IMREAD_COLOR)
bicubic_img = cv2.cvtColor(bicubic_img, cv2.COLOR_BGR2GRAY)

img_hr = cv2.cvtColor(img_hr, cv2.COLOR_BGR2GRAY)
internearest = cv2.resize(img_hr, None, fx=2, fy=2, interpolation=cv2.INTER_NEAREST)
interlinear = cv2.resize(img_hr, None, fx=2, fy=2, interpolation=cv2.INTER_LINEAR)

plt.subplot(221), plt.imshow(internearest, 'gray')
plt.subplot(222), plt.imshow(interlinear, 'gray')
plt.subplot(223), plt.imshow(bicubic_img, 'gray')
plt.subplot(224), plt.plot(internearest[100:101, 150:200][0], "g", label="internearest"), plt.plot(bicubic_img[100:101, 150:200][0], 'b', label="bicubic"), \
plt.plot(interlinear[100:101, 150:200][0],'r',  label="interlinear"), plt.legend(loc='upper right')
plt.xlim([0, 50])

plt.show()

#original_histogram = draw_histogram(img_bi.astype('int8'))
#cv2.imshow('original', original_histogram)
cv2.waitKey(0)
cv2.destroyAllWindows()