import cv2
import os
import numpy as np
import tkinter as tk
from tkinter import filedialog
import bicubic
import re
import tempfile
import shutil
def imreadEX(image_path):
    if re.compile('[^ㄱ-ㅣ가-힣]+').sub('', image_path):
            stream = open(image_path, "rb")
            bytes = bytearray(stream.read())
            numpyarray = np.asarray(bytes, dtype=np.uint8)
            img = cv2.imdecode(numpyarray, cv2.IMREAD_UNCHANGED)
            if not img is None:
                return img
            else:
                file_tmp=tempfile.NamedTemporaryFile().name
                shutil.copy(image_path,file_tmp)
                image_path=file_tmp
    img = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)
    return img

def draw_histogram(img):

    h = np.zeros((img.shape[0], 256), dtype=np.uint8)

    hist_item = cv2.calcHist([img],[0],None,[256],[0,256])
    cv2.normalize(hist_item,hist_item,0,255,cv2.NORM_MINMAX)
    hist=np.int32(np.around(hist_item))
    for x,y in enumerate(hist):
        cv2.line(h,(x,0+10),(x,y+10),(255,255,255))

    cv2.line(h, (0, 0 + 10), (0, 5), (255, 255, 255) )
    cv2.line(h, (255, 0 + 10), (255, 5), (255, 255, 255))
    y = np.flipud(h)

    return y

# 파일선택창
root = tk.Tk()
root.withdraw()
filename = filedialog.askopenfilename(title='Choose a original file')
img_hr = imreadEX(filename)
print(filename + ' loaded ')

print('cubic interpolation do:  ' + filename)

img_bi = bicubic.bicubic(img_hr, img_hr.shape[1] * 2, img_hr.shape[0] * 2)
print(img_bi.shape)
cv2.imwrite( filename+'save', img_bi)
print(filename + ' saved as BI/bi-' + filename)

original_histogram = draw_histogram(img_bi.astype('int8'))
cv2.imshow('original', original_histogram)
cv2.waitKey(0)
cv2.destroyAllWindows()