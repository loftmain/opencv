import cv2
import numpy as np
import tkinter as tk
from tkinter import filedialog


def find_nearest_above(my_array, target):
    diff = my_array - target
    mask = np.ma.less_equal(diff, -1)
    # We need to mask the negative differences
    # since we are looking for values above
    if np.all(mask):
        c = np.abs(diff).argmin()
        return c # returns min index of the nearest if target is greater than any value
    masked_diff = np.ma.masked_array(diff, mask)
    return masked_diff.argmin()

def hist_match(original, specified):
    oldshape = original.shape
    original = original.ravel()
    specified = specified.ravel()

    # get the set of unique pixel values and their corresponding indices and counts
    s_values, bin_idx, s_counts = np.unique(original, return_inverse=True, return_counts=True)
    t_values, t_counts = np.unique(specified, return_counts=True)

    # Calculate s_k for original image
    s_quantiles = np.cumsum(s_counts).astype(np.float64)
    s_quantiles /= s_quantiles[-1]

    # Calculate s_k for specified image
    t_quantiles = np.cumsum(t_counts).astype(np.float64)
    t_quantiles /= t_quantiles[-1]

    # Round the values
    sour = np.around(s_quantiles * 255)
    temp = np.around(t_quantiles * 255)

    # Map the rounded values
    b = []
    for data in sour[:]:
        b.append(find_nearest_above(temp, data))
    b = np.array(b, dtype='uint8')

    return b[bin_idx].reshape(oldshape)

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

def hangulFilePathImageRead ( filePath ) :

    stream = open( filePath.encode("utf-8") , "rb")
    bytes = bytearray(stream.read())
    numpyArray = np.asarray(bytes, dtype=np.uint8)

    return cv2.imdecode(numpyArray , cv2.IMREAD_UNCHANGED)

# 파일선택창
root = tk.Tk()
root.withdraw()
file_path1 = filedialog.askopenfilename(title='Choose a original file')
file_path2 = filedialog.askopenfilename(title='Choose a specified file')

# 이미지 로드
original = cv2.imdecode(np.fromfile(file_path1, np.uint8), 0)
specified = cv2.imdecode(np.fromfile(file_path2, np.uint8), 0)

# 히스토그램이 안나와서 사이즈 키움
specified = cv2.resize(specified,(360,360))

# 히스토그램 그리기
original_histogram = draw_histogram(original)
specified_histogram = draw_histogram(specified)

# 히스토그램 명세화
equalization = hist_match(original, specified)

# equalization 히스토그램 그리기
equalization_histogram =  draw_histogram(equalization)

# 원래 이미지와 히스토그램 붙이기
result0 = np.hstack((original, original_histogram))
result1 = np.hstack((specified, specified_histogram))
result2 = np.hstack((equalization, equalization_histogram))

# 화면에 이미지 출력
cv2.imshow('original', result0)
cv2.imshow('specified', result1)
cv2.imshow('equalization',np.array(result2,dtype='uint8'))
cv2.waitKey(0)
cv2.destroyAllWindows()