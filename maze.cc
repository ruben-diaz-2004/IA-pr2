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


#include "iostream"
#include <fstream>
#include "maze.h"

Maze::Maze(std::fstream& fichero_entrada) {
  fichero_entrada >> n_filas_;
  fichero_entrada >> n_columnas_;
  std::string linea;
  std::vector<int> fila;
  fichero_entrada >> linea;
  while (std::getline(fichero_entrada, linea)) {
    for (int i = 0; i < n_columnas_; i++) {
      fila.push_back(linea[i]);
    }
    maze_.push_back(fila);
    fila.clear();
  }
}

void Maze::PrintMaze() {
  for (int i = 0; i < n_filas_; i++) {
    for (int j = 0; j < n_columnas_; j++) {
      std::cout << maze_[i][j];
    }
    std::cout << std::endl;
  }
}

// void Maze::PrintMaze() {
//   for (int i = 0; i < n_filas_; i++) {
//     for (int j = 0; j < n_columnas_; j++) {
//       switch (maze_[i][j]) {
//         case 0:
//           std::cout << " ";
//           break;
//         case 1:
//           std::cout << "#";
//           break;
//         case 2:
//           std::cout << "·";
//           break;
//         case 3:
//           std::cout << "S";
//           break;
//         case 4:
//           std::cout << "F";
//           break;
//         default:
//           std::cout << " ";
//           break;
//       }
//     }
//     std::cout << std::endl;
//   }
// }