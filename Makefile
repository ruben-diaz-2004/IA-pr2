# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Asignatura: Inteligencia Artificial
# 
# @author Rubén Díaz Marrero
# @date 25/09/2023
# 

CXX = g++
CXXFLAGS = -Wall -std=c++17 -g 



all: Informadas

Informadas: main.cc maze.cc
		$(CXX) $(CXXFLAGS) -o $@ $^
	

	
.PHONY: all clean
clean:
		rm -f Informadas