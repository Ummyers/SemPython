print("Curso de Python: Segunda parte")
'''
Python 3 no esta peleado con los acentos
'''
#x = "Cadena de texto"

#Esta conviertiendo la entrada a un valor de tipo integer
# x = input("mensaje que se muestra para cachar la entrada")
x = int(input())

if x>0:
	print("Tu número es positivo")
elif x<0:
	print("Tu número es negativo")
else:
	print("No cumple con ninguna condición")

nombre = input("Ingresa tu nombre")

if nombre == "Andrea":
	print("Hola ama")
else:
	print("¿tu quien eres?")


contador = 10
while contador>0:
	print("Así es un ciclo en python")
	contador = contador -1


for i in range(10):
	print("Un for en python")
#For con dos parametros 
#Primer parametro es desde donde inicia
#el segundo parametro indica el limite de iteraciones
#con el tercer elemento indicas el numero de incremento
