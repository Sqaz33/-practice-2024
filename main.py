import cv2
import numpy as np
from skimage import measure
import matplotlib.pyplot as plt


# Функция для предобработки изображения
def preprocess_image(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    _, binary_image = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY_INV)
    return binary_image


# Функция для сегментации и подсчета колоний
def count_colonies(image_path):
    binary_image = preprocess_image(image_path)
    labeled_image = measure.label(binary_image, connectivity=2)
    colony_count = np.max(labeled_image)
    return colony_count, labeled_image


# Пример использования
image_path = 'pet.jpg'
colony_count, labeled_image = count_colonies(image_path)
print(f'Number of colonies: {colony_count}')

# Визуализация результата
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.imshow(cv2.imread(image_path, cv2.IMREAD_GRAYSCALE), cmap='gray')
plt.title('Original Image')
plt.subplot(1, 2, 2)
plt.imshow(labeled_image, cmap='nipy_spectral')
plt.title('Labeled Image')
plt.show()
