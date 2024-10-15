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
  Maze(std::fstream& fichero_entrada, const int& control);
  bool SolveMaze();
  void FuncionCoste(Nodo* nodo);
  int CosteAcumulado(Nodo* nodo);
  double FuncionHeuristica(Nodo* nodo, const int& control);
  Nodo* NodoAbierto(int i, int j); // for each nodo in nodos_abiertos: if nodo.pos_i == i && nodo.pos_j == j return nodo;
  Nodo* NodoCerrado(int i, int j);
  void PrintMaze();
  Nodo* BuscarNodoMenorCoste();
  void ReconstruirCamino(Nodo* nodo);
  void CambiarES(const int& inicio_i, const int& inicio_j, const int& fin_i, const int& fin_j);
  void EliminaNodos();
  bool MismaFilaColumna(Nodo* nodo_actual, Nodo* nodo_vecino);
  int CalculaCoste(Nodo* nodo, Nodo* nodo_vecino);
  void ImprimeNodos();
private:
  std::pair<int,int> inicio_;
  std::pair<int,int> fin_;
  int control_;
  // Imprimimos la salida por un fichero
  std::ofstream fichero_salida{"salida.txt"};
  int n_filas_;
  int n_columnas_;
  std::vector<std::vector<int>> maze_;
  std::vector<Nodo*> nodos_abiertos_;
  std::vector<Nodo*> nodos_cerrados_;
  double coste_final_;
  int iteraciones_;
};




#endif