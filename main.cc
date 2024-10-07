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


#include <iostream>
#include "fstream"
#include "maze.h"

int main(int argc, char* argv[]) {
  std::fstream fichero_de_entrada{argv[1]};
  std::fstream fichero_de_entrada_2{argv[1]};

  Maze maze(fichero_de_entrada);
  maze.SolveMaze();
  maze.PrintMaze();

  std::cout << "Desea cambiar la entrada/salida del laberinto? (s/n)" << std::endl;
  char respuesta;
  std::cin >> respuesta;
  if (respuesta == 's') {
    std::cout << "Introduzca la nueva entrada y salida del laberinto: " << std::endl;
    int inicio_i, inicio_j, fin_i, fin_j;
    std::cin >> inicio_i >> inicio_j >> fin_i >> fin_j;
    Maze new_maze(fichero_de_entrada_2);
    new_maze.CambiarES(inicio_i, inicio_j, fin_i, fin_j);
    new_maze.SolveMaze();
    new_maze.PrintMaze();
  }

  return 0;
}