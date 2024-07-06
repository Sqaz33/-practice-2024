import cv2
import matplotlib.pyplot as plt

import sys
from PyQt6 import QtCore, QtGui, QtWidgets
from PyQt6.QtGui import QPixmap, QImage
from PyQt6.QtCore import Qt
import numpy as np

from PIL import Image 

from form import Ui_MainWindow

class Petri:
    #TODO: написать определение формы контуров
    def get_thresh(self, image: cv2.Mat, thres: int) -> cv2.Mat:
        blurred = cv2.GaussianBlur(image, (3, 3), 0)
        _, thresh_img = cv2.threshold(blurred, thres, 255, cv2.THRESH_BINARY)
        return cv2.cvtColor(thresh_img, cv2.COLOR_BGR2GRAY)
    
    def is_circle(self, contour, threshold=0.3) -> bool:
        # Вычисляем периметр
        perimeter = cv2.arcLength(contour, True)
        # Аппроксимируем контур
        approx = cv2.approxPolyDP(contour, 0.02 * perimeter, True)
        # Вычисляем площадь
        area = cv2.contourArea(contour)
        
        # Если контур имеет менее 5 вершин, то это не круг
        if len(approx) < 5:
            return False
        
        # Вычисляем радиус предполагаемого круга
        (x, y), radius = cv2.minEnclosingCircle(contour)
        circle_area = np.pi * (radius ** 2)

        # Сравниваем площадь контура с площадью круга
        if abs(1 - (area / circle_area)) < threshold:
            return True
        else:
            return False

    def get_cnts(self, image: cv2.Mat, thres: int):
        thresh_img = self.get_thresh(image, thres)
        
        # if len(thresh_img.shape) == 3 and thresh_img.shape[2] == 3:
        #     thresh_img = cv2.cvtColor(thresh_img, cv2.COLOR_BGR2GRAY)
        # thresh_img =  thresh_img.astype(np.uint8)

        # print(thresh_img.type())
        contours, _ = cv2.findContours(thresh_img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        return contours

    def get_colonies(self, image: cv2.Mat, thres: int):
        contours = self.get_cnts(image, thres)
        circle_contours = []

        for contour in contours:
            if self.is_circle(contour):
                circle_contours.append(contour)

        return circle_contours


class App:
    def __init__(self, img_path):  
        self.app = QtWidgets.QApplication(sys.argv)
        self.MainWindow = QtWidgets.QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.MainWindow)
        self.p = Petri()

        self.img = plt.imread(img_path)

        self.ui.label_3.setText('0')
        self.petri()

        self.ui.horizontalSlider.valueChanged.connect(self.horizontalSliderValueChange)
        self.ui.horizontalSlider.valueChanged.connect(self.petri)


    def horizontalSliderValueChange(self):
        self.petri()
        self.ui.label_3.setText(
            str(self.ui.horizontalSlider.value())
        )

    def petri(self):
        thres = int(self.ui.horizontalSlider.value())
        contours = self.p.get_colonies(self.img, thres)


        image_with_contours = self.img.copy()
        cv2.drawContours(image_with_contours, contours, -1, (0, 255, 0), 2)

        image_with_contours = cv2.cvtColor(image_with_contours, cv2.COLOR_BGR2RGB)

        height, width, channel = image_with_contours.shape
        bytes_per_line = channel * width
        q_image = QImage(image_with_contours.data, width, height, bytes_per_line, QImage.Format.Format_RGB888)
        mp = QPixmap.fromImage(q_image)

        self.ui.label_2.setPixmap(mp)
        self.ui.label.setText(str(len(contours)))
    
    def run(self):
        self.MainWindow.show()
        sys.exit(self.app.exec())



if __name__ == '__main__':
    app = App('q120404-01.jpg')
    app.run()




