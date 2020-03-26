import numpy as np

def integralMonteCarlo(f,N):
	puntos = np.random.uniform(size = N)
	#N valores entre 1 y 0 
	total = 0
	for i in range(N):
		total += f(puntos[i])
	aprox = total/N
	return aprox #Esto es por que se divide entre 1
def f(x):
	retunr x**2

def main 