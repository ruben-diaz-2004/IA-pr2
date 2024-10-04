/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2024-2025
  * Práctica 1: Búsquedas no informadas
  * 
  * @author Rubén Díaz Marrero 
  * @date 01/10/2024
  */

#ifndef _MAZE_H
#define _MAZE_H

#include <vector>
#include <fstream>
#include "nodo.h"

class Maze {
public:
  Maze(std::fstream& fichero_entrada);
  bool SolveMaze();
  void FuncionCoste(Nodo* nodo);
  int CosteAcumulado(Nodo* nodo);
  int FuncionHeuristica(Nodo* nodo);
  Nodo* NodoAbierto(int i, int j); // for each nodo in nodos_abiertos: if nodo.pos_i == i && nodo.pos_j == j return nodo;
  Nodo* NodoCerrado(int i, int j);
  void PrintMaze();
private:
  std::pair<int,int> inicio_;
  std::pair<int,int> fin_;
  // Imprimimos la salida por un fichero
  // std::ofstream fichero_salida{"salida.txt"};
  int n_filas_;
  int n_columnas_;
  std::vector<std::vector<int>> maze_;
  std::vector<Nodo*> nodos_abiertos_;
  std::vector<Nodo*> nodos_cerrados_;

};




#endif