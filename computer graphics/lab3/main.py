import cv2 as cv
import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk, ImageOps
import numpy as np
import matplotlib.pyplot as plt

class ImageProcessor:
    def __init__(self, root):
        self.root = root

        # Основной фрейм
        self.main_frame = tk.Frame(self.root)
        self.main_frame.pack(side="top", fill="both", expand=True)

        button_font = ('Arial', 11, 'bold')

        # Левый столбец кнопок
        self.left_frame = tk.Frame(self.main_frame)
        self.left_frame.pack(side="left", fill="both", expand=True)

        self.btn_open = tk.Button(self.left_frame, text="Open Image", command=self.open_image, width=20, height=2, font=button_font, bd=3)
        self.btn_open.pack(side="top", pady=5, padx=10)

        self.btn_histogram = tk.Button(self.left_frame, text="Histograms", command=self.histogram, width=20, height=2, font=button_font, bd=3)
        self.btn_histogram.pack(side="top", pady=5, padx=10)

        self.btn_linear = tk.Button(self.left_frame, text="Linear Contrast", command=self.linear, width=20, height=2, font=button_font, bd=3)
        self.btn_linear.pack(side="top", pady=5, padx=10)

        # Правый столбец кнопок
        self.right_frame = tk.Frame(self.main_frame)
        self.right_frame.pack(side="right", fill="both", expand=True)

        self.btn_median = tk.Button(self.right_frame, text="Median Filter", command=self.median, width=20, height=2, font=button_font, bd=3)
        self.btn_median.pack(side="top", pady=5, padx=10)

        self.btn_min = tk.Button(self.right_frame, text="Minimum Filter", command=self.min, width=20, height=2, font=button_font, bd=3)
        self.btn_min.pack(side="top", pady=5, padx=10)

        self.btn_max = tk.Button(self.right_frame, text="Maximum Filter", command=self.max, width=20, height=2, font=button_font, bd=3)
        self.btn_max.pack(side="top", pady=5, padx=10)

        # Области для изображений
        self.original_image_label = tk.Label(self.left_frame, height=300, width=300)
        self.original_image_label.pack(side="bottom", padx=10, pady=10)

        self.processed_image_label = tk.Label(self.right_frame, height=300, width=300)
        self.processed_image_label.pack(side="bottom", padx=10, pady=10)

        self.filename = "D://program etc//projects3//cgcgcg//lab3//photos//cham.jpg"
        self.image = Image.open(self.filename)
        self.original_photo = ImageTk.PhotoImage(self.image)
        self.original_image_label.config(image=self.original_photo)

        self.processed_image = Image.open("D://program etc//projects3//cgcgcg//lab3//photos//bob.jpg")
        self.processed_photo = ImageTk.PhotoImage(self.processed_image)
        self.processed_image_label.config(image=self.processed_photo)

    def update_original_image(self, image):
        photo = ImageTk.PhotoImage(image)
        self.original_image_label.configure(image=photo)
        self.original_image_label.image = photo

    def update_processed_image(self, image):
        photo = ImageTk.PhotoImage(image)
        self.processed_image_label.configure(image=photo)
        self.processed_image_label.image = photo
        
    def open_image(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select Image", filetypes=(("JPEG files", "*.jpg"), ("PNG files", "*.png"), ("All files", "*.*")))        
        
        if self.filename:
            self.image = Image.open(self.filename)
            self.update_original_image(self.image)
    
    def plot_histogram(self, image, title):
        plt.figure()
        plt.title(title)
        plt.xlabel("brightness")
        plt.ylabel("amount")
        plt.hist(image.ravel(), 256, [0, 256])
        plt.show()
    

    def linear(self):
        img = cv.cvtColor(cv.imread(self.filename), cv.COLOR_BGR2GRAY)
        min_val, max_val, _, _ = cv.minMaxLoc(img)
        c_img = (img - min_val) * (255 / (max_val - min_val))
        c_img = np.uint8(c_img)
        c_img = cv.cvtColor(c_img, cv.COLOR_BGR2RGB)
        c_img = Image.fromarray(c_img)
        self.update_processed_image(c_img)


    def histogram(self):
        self.linear()
        img = cv.imread(self.filename)
        r, g, b= cv.split(img)
        b_eq = cv.equalizeHist(b)
        g_eq = cv.equalizeHist(g)
        r_eq = cv.equalizeHist(r)
        
        equalized_image = cv.merge((r_eq, g_eq, b_eq))
        hist = cv.calcHist([equalized_image], [0], None, [256], [0, 256])
        plt.plot(hist)
        plt.show()
        # self.plot_histogram(b, "Исходная гистограмма (синий)")
        # self.plot_histogram(g, "Исходная гистограмма (зеленый)")
        # self.plot_histogram(r, "Исходная гистограмма (красный)")
        # self.plot_histogram(cv.cvtColor(img, cv.COLOR_BGR2GRAY), "Исходная гистограмма (серый)")
        
        # self.plot_histogram(b_eq, "Выравненная гистограмма (синий)")
        # self.plot_histogram(g_eq, "Выравненная гистограмма (зеленый)")
        # self.plot_histogram(r_eq, "Выравненная гистограмма (красный)")
        # self.plot_histogram(cv.cvtColor(equalized_image, cv.COLOR_BGR2GRAY), "Выравненная гистограмма (серый)")
        resized_image = cv.resize(equalized_image, (300, 300))        
        cv.imshow("RGB", resized_image)
    

        image = cv.cvtColor(cv.imread(self.filename), cv.COLOR_BGR2HSV)
        h, s, v = cv.split(image)
        v_eq = cv.equalizeHist(v)
        equalized_hsv = cv.merge((h, s, v_eq))
        equalized_image = cv.cvtColor(equalized_hsv, cv.COLOR_HSV2RGB)
        hist = cv.calcHist([equalized_image], [0], None, [256], [0, 256])
        plt.plot(hist)
        plt.show()
        # self.plot_histogram(v, "start hist (v)")
        # self.plot_histogram(cv.cvtColor(image, cv.COLOR_BGR2GRAY), "Исходная гистограмма (серый)")
        # self.plot_histogram(v_eq, "end hist (v)")
        # self.plot_histogram(cv.cvtColor(equalized_image, cv.COLOR_BGR2GRAY), "Выравненная гистограмма (серый)")
        resized_image = cv.resize(equalized_image, (300, 300))
        cv.imshow("HSV", resized_image)
        

    def median(self):
        img = cv.imread(self.filename)
        c_img = cv.medianBlur(img, 5)
        c_img = cv.cvtColor(c_img, cv.COLOR_BGR2RGB)
        c_img = Image.fromarray(c_img)
        self.update_processed_image(c_img)

    def min(self):
        img = cv.imread(self.filename)
        kernel_size = 3
        kernel = cv.getStructuringElement(cv.MORPH_RECT, (kernel_size, kernel_size))
        c_img = cv.erode(img, kernel)
        c_img = cv.cvtColor(c_img, cv.COLOR_BGR2RGB)
        c_img = Image.fromarray(c_img)
        self.update_processed_image(c_img)

    def max(self):
        img = cv.imread(self.filename)
        kernel_size = 3
        kernel = cv.getStructuringElement(cv.MORPH_RECT, (kernel_size, kernel_size))
        c_img = cv.dilate(img, kernel)
        c_img = cv.cvtColor(c_img, cv.COLOR_BGR2RGB)
        c_img = Image.fromarray(c_img)
        self.update_processed_image(c_img)


def main():
    root = tk.Tk()
    root.geometry("800x600")
    root.title("hee hee")
    app = ImageProcessor(root)
    root.mainloop()


if __name__ == '__main__':
    main()
