import numpy as np
import matplotlib.pyplot as plt

def Euler(xn, yn, h, MyF):
    return yn + (h*MyF(yn,xn))

def MyFirstODE(y,x):
    return x-y

def ExactSolution(x):
    return x-1+2*np.exp(-x)

EulerSolutions=[]

NumPuntos=10000
x0=0.
xf=5.

xs = np.linspace(x0,xf,NumPuntos)
y0 = 1.0

EulerSolutions.append(y0)

for i in xs[1:]:
    CurrentSolution=Euler(i, EulerSolutions[-1], ((xf-x0)/NumPuntos), MyFirstODE)
    EulerSolutions.append(CurrentSolution)

from scipy.integrate import odeint

ys = odeint(MyFirstODE, y0, xs)
ys = np.array(ys).flatten()

y_exact=ExactSolution(xs)

#plt.plot(xs, ys, "r")
#plt.plot(xs, EulerSolutions, "b")
#plt.plot(xs, y_exact, "g--")

y1_difference = np.abs(ys - y_exact)
yE_difference = np.abs(ys - EulerSolutions)

plt.semilogy(xs, y1_difference,"r")
plt.semilogy(xs, yE_difference,"b")

plt.show()
