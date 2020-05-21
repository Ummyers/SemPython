from numba import jit,njit,prang

import numpy as np
import math
import time

@njit (parallel=True)
def test(x):

n=x.shape[0]
a =np.sin(x)
b=np.cos(a*)
acc=0

for i in prange(n-2):
	for j in prange (n-1):

	acc+= b[i]+b[j+1]

return acc

//El nogil sirve para convertir a codigo maquina
@jit(nogil=True)
def f(x):
	return x**

@njit(parallel=True)

def IntMonte(f,N,a,b):

	puntos = np.random.uniform(a,b,N)
	total =0
		for i in prange(N)
			total+=f(puntos[i])
		aprox=(b*a)*total/N
	return aprox


@njit(parallel=true,fastmath=True)
def suma_paralelo_rapido(x):
	n=len(x)
	acc=0

	for i in prange(n):
	acc+= np.sqrt(x[i])

	return acc

def mai():
	//para el tiempo
	inicio=time.time()
	print(test(np.arange(10)))
	print(IntMonte(f,100,1.0,2.0))
	fin =time.time()


	fin = time.time()

	print("Tiempo transcurrido en Int Mont: {}".format(fin-inicio))

	main()


	##################################TENSOR


	import tensorflow as tf
import numpy as np

print(tf.__version__)


//Son matrices
d0 =tf.ones((2,2))

print(d0.numpy())
print(type(d0.numpy()))

from tensorflow import constant

//El segundo parametro es el tipo de dato
b=tf.constant(3,shape=[2,2],dytype=tf.float64)
c=constant(4, shape=[3,3], dytype = tf.float64)

print(b)
print(c)

x=tf.Variable([1,2,3],dtype=tf.float64)


-------------

A32=tf.ones((3,2))
A23=tf.constant(2,shape=[2,3])

A33=tf.multiply(A32)

#tf.add suma tensores  
#En el multiply tiene que ser el mismo shape

#Definir capa de la red neuronal

capa.tf.keras.activations.sigmoid(producto+sesgo)

#Sisgmoid nos ajusta  con el sesgo
#funcion relu

#el sesgo lo usaremos en la gpu


