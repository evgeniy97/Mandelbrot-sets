import numpy as np
import matplotlib.pyplot as plt

# https://github.com/kyle90/mandelbort

screensize = (600,600) # so we will have array 600*600
scale = 250
center = (-0.7,0)
iterations = 767 # 767 to large
colour = (0.2,0.6,1)

mode_cool = False

def vector_square(i):
	return (i[0]*i[0]-i[1]*i[1],2*i[0]*i[1])
	
def vector_add(i,j):
	return (i[0]+j[0],i[1]+j[1])

def cool(intensity):
    return [colour[0]*intensity,colour[1]*intensity,colour[2]*intensity]

def not_so_cool(n):
    if n < 256:
        return [float(n),.0,.0]
    elif n < 511:
        return [256.,float(n),.0]
    else: 
        return [256.,256.,float(n)]

pic = []
inten = []
for y in range(screensize[1]):
    row = []
    row_int = []
    for x in range(screensize[0]):
        constant = ((x-screensize[0]/2)/scale+center[0],(y-screensize[1]/2)/scale-center[1])
        pos_ = [0,0]
        pos_new = [0,0]
        intensity = 0
        for n in range(iterations):
            if pos_[0]*pos_[0]+pos_[1]*pos_[1] > 4:
                
                if mode_cool:
                    intensity = 1000/n
                else:
                    intensity = n
                break

            pos_new = vector_add(vector_square(pos_),constant)

            pos_[0] = pos_new[0]
            pos_[1] = pos_new[1]
        if intensity > 255:
            intensity = 255

        if mode_cool:
            f = cool
        else:
            f = not_so_cool

        row.append(f(intensity))
        row_int.append(intensity)
    pic.append(row)
    inten.append(row_int)

plt.axis('off')
plt.imshow(pic)
plt.savefig('new_out.jpg', bbox_inches='tight')  