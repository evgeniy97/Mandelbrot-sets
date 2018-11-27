import numpy as np
import matplotlib.pyplot as plt
import glob # Go throw all files in directory
import re
import shutil

colour = (0.2,0.6,1)

def dye(n):
    if n < 256:
        return [float(n),.0,.0]
    elif n < 511:
        return [256.,float(n),.0]
    else: 
        return [256.,256.,float(n)]

def main():
    pic = []
    for file in sorted(glob.glob('result/*.txt'),key=lambda x: int(re.findall(r'\w+',x)[1])):
        pic.append(np.loadtxt(file))
    #func = lambda intensity: [colour[0]*intensity,colour[1]*intensity,colour[2]*intensity]
    func = dye

    picture = []
    for i in range(len(pic)):
        picture.append([]);
        for j in range(len(pic[i])):
            picture[-1].append(func(pic[i][j]))

    picture = np.array(picture)
    plt.axis('off')
    plt.imshow(picture)
    plt.savefig('out.jpg', bbox_inches='tight')   # Переопределить имя файла
    shutil.rmtree('result/')
if __name__ == "__main__":
    main() # sys.argv[0] is a name of the script
