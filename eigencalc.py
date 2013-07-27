import numpy
import numpy.linalg as linalg
P = numpy.array([[0.616556 ,0.615444], [0.615444  ,0.716556]])
D, V = linalg.eig(P)
print V
print V[1][1]
file = open("result.txt", "w")
file.write(str(V[0][0]))
file.write(" ")
file.write(str(V[0][1]))
file.write(" ")
file.write(str(V[1][0]))
file.write(" ")
file.write(str(V[1][1]))
file.write(" ")
file.close()
