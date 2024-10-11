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
  int control{1};
  std::cout << "Elige la heurística a utilizar: " << std::endl;
  std::cout << "1. Distancia de Manhattan" << std::endl;
  std::cout << "2. Distancia de Chebyshev" << std::endl;
  std::cout << "3. Distancia Euclídea P" << std::endl;
  std::cout << "4. Distancia de Canberra" << std::endl;
  std::cin >> control;
  if (control < 1 || control > 4) {
    std::cout << "Opción no válida" << std::endl;
    return 0;
  }
  Maze maze(fichero_de_entrada, control);
  maze.SolveMaze();
  maze.PrintMaze();

  bool running = true;
  while (running) {
    std::cout << "Desea cambiar la entrada/salida del laberinto? (s/n)" << std::endl;
    char respuesta;
    std::cin >> respuesta;
    if (respuesta == 's') {
      std::cout << "Introduzca la nueva entrada y salida del laberinto: " << std::endl;
      int inicio_i, inicio_j, fin_i, fin_j;
      std::cin >> inicio_i >> inicio_j >> fin_i >> fin_j;
      maze.CambiarES(inicio_i, inicio_j, fin_i, fin_j);
      maze.SolveMaze();
      maze.PrintMaze();
    } else {
      running = false;
    }
  }

  return 0;
}