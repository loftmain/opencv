#-*- coding:utf-8 -*-
import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('lena.png', cv2.IMREAD_COLOR)
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# 행 : Height, 열:width
height, width = img.shape[:2]
internearest = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_NEAREST)
interlinear = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_LINEAR)
# 배수 Size지정
intercubic = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)

#h = np.zeros((zoom2.shape[0], 256), dtype=np.uint8)
mask = np.zeros(intercubic.shape[:2], np.uint8)
mask[100:101, 100:200] = 255
hist_item = cv2.calcHist([intercubic],[0],mask,[256],[0,256])
masked_img = cv2.bitwise_and(intercubic, intercubic, mask=mask)

mask2 = np.zeros(interlinear.shape[:2], np.uint8)
mask2[100:101, 100:200] = 255
hist_item2 = cv2.calcHist([interlinear],[0],mask2,[256],[0,256])
print(interlinear[100:101, 100:110])
print(intercubic[100:101, 100:110])

masked_img2 = cv2.bitwise_and(interlinear, interlinear, mask=mask2)

plt.subplot(221), plt.imshow(internearest, 'gray')
plt.subplot(222), plt.imshow(interlinear, 'gray')
plt.subplot(223), plt.imshow(intercubic, 'gray')
plt.subplot(224), plt.plot(internearest[100:101, 150:200][0], "g", label="internearest"), plt.plot(intercubic[100:101, 150:200][0], 'b', label="intercubic"), \
plt.plot(interlinear[100:101, 150:200][0],'r',  label="interlinear"), plt.legend(loc='upper right')
plt.xlim([0, 50])

plt.show()

#cv2.imwrite("INTERCUBIC.png", zoom2)
cv2.imshow('Origianl', img)
cv2.imshow('intercubic', intercubic)
cv2.imshow('interlinear', interlinear)

cv2.waitKey(0)
cv2.destroyAllWindows()