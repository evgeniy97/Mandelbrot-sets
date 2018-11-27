import numpy as np
import matplotlib.pyplot as plt
import glob # Go throw all files in directory
import re

def main():
    pic = [] # ? Тут проблема?
    for file in sorted(glob.glob('result/*.txt'),key=lambda x: int(re.findall(r'\w+',x)[1])):
        pic.append(np.reshape(np.loadtxt(file) ,(2,3))) # поменять reshape первое число - это width
    
    
    plt.axis('off')
    plt.imshow(pic)
    plt.savefig('out.jpg')   # Переопределить имя файла


def main_old():
    arr = np.loadtxt('in.TXT') # Переопределить имя файла
    arr = arr.reshape((2,2,3)) # понять нужные размеры: количество строк, количество столбцов, всегда 3
    # Здесь надо нормировать на 255
    plt.axis('off')
    plt.imshow(arr)
    plt.savefig('out.jpg')   # Переопределить имя файла

if __name__ == "__main__":
    main()