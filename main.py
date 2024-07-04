import cv2
import matplotlib.pyplot as plt

import sys
from PyQt6 import QtCore, QtGui, QtWidgets

from form import Ui_MainWindow

class Petri:
    #TODO: написать определение формы контуров
    def get_thresh(self, image: cv2.typing.MatLike, thres: int) -> cv2.typing.MatLike:
        blurred = cv2.GaussianBlur(image, (3, 3), 0)
        T, thresh_img = cv2.threshold(blurred, thres, 255, 
                            cv2.THRESH_BINARY)
        return thresh_img

    def get_cnts(self, image: cv2.typing.MatLike, thres: int):
        thresh_img = self.get_thresh(image, thres)
        thresh_img = cv2.cvtColor(thresh_img, cv2.COLOR_BGR2GRAY)
        contours, hierarchy = cv2.findContours(thresh_img, 
                                    cv2.RETR_TREE,
                                    cv2.CHAIN_APPROX_SIMPLE)
        return contours, hierarchy
    

class App:
    def __init__(self):  
        self.app = QtWidgets.QApplication(sys.argv)
        self.MainWindow = QtWidgets.QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.MainWindow)
        self.p = Petri()

        #------------------------------
        self.img = plt.imread('M.jpg')
        #------------------------------

        self.ui.label_3.setText('0')


        self.ui.horizontalSlider.valueChanged.connect(self.horizontalSliderValueChange)

    def horizontalSliderValueChange(self):
        self.petri()
        self.ui.label_3.setText(
            str(self.ui.horizontalSlider.value())
        )

    def petri(self):
        thres = int(self.ui.horizontalSlider.value())
        (contours, cnts) = self.p.get_cnts(self.img, thres)


        image_with_contours = self.img.copy()
        cv2.drawContours(image_with_contours, contours, -1, (0, 255, 0), 2)

        image_with_contours = cv2.cvtColor(image_with_contours, cv2.COLOR_BGR2RGB)
    
    def run(self):
        self.MainWindow.show()
        sys.exit(self.app.exec())




    # plt.imshow()
    # plt.imshow(cv2.cvtColor(p.get_thresh(img, thres), cv2.COLOR_BGR2GRAY))
    # plt.title('Image with Contours')
    # print(cnts)
    # plt.axis('off')  # Отключаем оси координат
    # plt.show()

if __name__ == '__main__':
    app = App()
    app.run()




