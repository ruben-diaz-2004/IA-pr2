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

  Maze maze(fichero_de_entrada);
  maze.PrintMaze();

  return 0;
}