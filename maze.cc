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
#include <fstream>
#include "maze.h"
#include <cmath>

Maze::Maze(std::fstream& fichero_entrada, const int& control) : control_{control}, generados_{0}, inspeccionados_{0}, coste_final_{0} {
  fichero_entrada >> n_filas_;
  fichero_entrada >> n_columnas_;
  std::cout << "Filas: " << n_filas_ << " Columnas: " << n_columnas_ << std::endl;
  std::string linea;
  std::vector<int> fila;
  std::getline(fichero_entrada, linea);
  while (std::getline(fichero_entrada, linea)) {
    for (int i = 0; i < n_columnas_*2; i++) {
      if (linea[i] != ' ') {
        fila.push_back(linea[i] - '0');
      }
    }
    maze_.push_back(fila);
    fila.clear();
  }

  for (int i = 0; i < n_filas_; i++) {
    for (int j = 0; j < n_columnas_; j++) {
      if (maze_[i][j] == 3) {
        inicio_ = std::make_pair(i, j);
      }
      if (maze_[i][j] == 4) {
        fin_ = std::make_pair(i, j);
      }
    }
  }
  std::cout << "S: (" << inicio_.first << ", " << inicio_.second << ")\n";
  std::cout << "E: (" << fin_.first << ", " << fin_.second << ")\n";
}


bool Maze::SolveMaze() {
  Nodo* nodo_inicial = new Nodo(inicio_);
  nodos_abiertos_.push_back(nodo_inicial);
  FuncionCoste(nodo_inicial);
  while(!nodos_abiertos_.empty()) {
    Nodo* nodo_actual = BuscarNodoMenorCoste();
    nodos_cerrados_.push_back(nodo_actual);
    std::cout << "Nodo actual: (" << nodo_actual->GetIdentificador().first << ", " << nodo_actual->GetIdentificador().second << ")" << std::endl;
    inspeccionados_++;
    if (nodo_actual->GetIdentificador() == fin_) {
      std::cout << "Camino encontrado" << std::endl;
      coste_final_ = nodo_actual->GetCoste();
      ReconstruirCamino(nodo_actual);
      EliminaNodos();
      return true;
    }
    for (int i{-1}; i <= 1; ++i) {
      for (int j{-1}; j <= 1; ++j) {
        if (i == 0 && j == 0) {
          continue;
        }
        if (nodo_actual->GetIdentificador().first + i < 0 || nodo_actual->GetIdentificador().first + i >= n_filas_ || nodo_actual->GetIdentificador().second + j < 0 || nodo_actual->GetIdentificador().second + j >= n_columnas_) {
          continue;
        }
        if (maze_[nodo_actual->GetIdentificador().first + i][nodo_actual->GetIdentificador().second + j] == 1) {
          continue;
        }
        Nodo* nodo_vecino = NodoAbierto(nodo_actual->GetIdentificador().first + i, nodo_actual->GetIdentificador().second + j);
        if (nodo_vecino == nullptr) { // Si no está en nodos_abiertos
          nodo_vecino = NodoCerrado(nodo_actual->GetIdentificador().first + i, nodo_actual->GetIdentificador().second + j);
          if (nodo_vecino == nullptr) { // Si no está en nodos_cerrados
            nodo_vecino = new Nodo(std::make_pair(nodo_actual->GetIdentificador().first + i, nodo_actual->GetIdentificador().second + j), nodo_actual);
            nodos_abiertos_.push_back(nodo_vecino);
            generados_++;
            FuncionCoste(nodo_vecino);
          }
        } else { // Si está en nodos_abiertos
          if (nodo_vecino->GetCosteMovimiento() > CalculaCoste(nodo_actual, nodo_vecino)) {
            nodo_vecino->SetPadre(nodo_actual);
            FuncionCoste(nodo_vecino);
          }
        }
      }
    }
  }
  std::cout << "No se ha encontrado camino" << std::endl;
  EliminaNodos();
  return false;
}


int Maze::CalculaCoste(Nodo* nodo, Nodo* nodo_vecino) {
  if (MismaFilaColumna(nodo, nodo_vecino)) {
    return nodo->GetCosteMovimiento() + 5;
  }
  return nodo->GetCosteMovimiento() + 7;

}


void Maze::ReconstruirCamino(Nodo* nodo) {
  Nodo* nodo_actual = nodo;
  while (nodo_actual->GetPadre() != nullptr) {
    maze_[nodo_actual->GetIdentificador().first][nodo_actual->GetIdentificador().second] = 2;
    nodo_actual = nodo_actual->GetPadre();
  }
  maze_[nodo_actual->GetIdentificador().first][nodo_actual->GetIdentificador().second] = 2;
}




Nodo* Maze::BuscarNodoMenorCoste() {
  Nodo* nodo_menor_coste = nodos_abiertos_[0];
  int index{0};
  for (int i = 1; i < nodos_abiertos_.size(); i++) {
    if (nodos_abiertos_[i]->GetCoste() < nodo_menor_coste->GetCoste()) {
      nodo_menor_coste = nodos_abiertos_[i];
      index = i;
    }
  }
  nodos_abiertos_.erase(nodos_abiertos_.begin() + index);
  return nodo_menor_coste;
}
// void Maze::PrintMaze() {
//   for (int i = 0; i < n_filas_; i++) {
//     for (int j = 0; j < n_columnas_; j++) {
//       std::cout << maze_[i][j];
//     }
//     std::cout << std::endl;
//   }
// }



Nodo* Maze::NodoAbierto(int i, int j) {
  for (int k = 0; k < nodos_abiertos_.size(); k++) {
    if (nodos_abiertos_[k]->GetIdentificador().first == i && nodos_abiertos_[k]->GetIdentificador().second == j) {
      return nodos_abiertos_[k];
    }
  }
  return nullptr;
}



Nodo* Maze::NodoCerrado(int i, int j) {
  for (int k = 0; k < nodos_cerrados_.size(); k++) {
    if (nodos_cerrados_[k]->GetIdentificador().first == i && nodos_cerrados_[k]->GetIdentificador().second == j) {
      return nodos_cerrados_[k];
    }
  }
  return nullptr;
}



void Maze::PrintMaze() {
  for (int i = 0; i < n_filas_; i++) {
    for (int j = 0; j < n_columnas_; j++) {
      switch (maze_[i][j]) {
        case 0:
          std::cout << "-";
          break;
        case 1:
          std::cout << "#";
          break;
        case 2:
          std::cout << "*";
          maze_[i][j] = 0;
          break;
        case 3:
          std::cout << "S";
          break;
        case 4:
          std::cout << "F";
          break;
        default:
          std::cout << " ";
          break;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "Coste: " << coste_final_ << std::endl;
  std::cout << "Nodos generados: " << generados_ << std::endl;
  std::cout << "Nodos inspeccionados: " << inspeccionados_ << std::endl;
}


void Maze::FuncionCoste(Nodo* nodo) {
  nodo->SetCoste(CosteAcumulado(nodo) + FuncionHeuristica(nodo, control_));
}


int Maze::CosteAcumulado(Nodo* nodo) {
  if (nodo->GetPadre() == nullptr) {
    return 0;
  }
  int coste_movimiento{0};
  Nodo* padre = nodo->GetPadre();
  if (padre->GetIdentificador().first == nodo->GetIdentificador().first || padre->GetIdentificador().second == nodo->GetIdentificador().second) {
    coste_movimiento = padre->GetCosteMovimiento() + 5;
  } else {
    coste_movimiento = padre->GetCosteMovimiento() + 7;
  }
  nodo->SetCosteMovimiento(coste_movimiento);
  // std::cout << "Coste acumulado: " << coste_movimiento << std::endl;
  return coste_movimiento;
}


double Maze::FuncionHeuristica(Nodo* nodo, const int& control) {
  double coste{0};
  switch (control) {
    case 1:
    // Distancia de Manhattan
    coste = (abs(nodo->GetIdentificador().first - fin_.first) + abs(nodo->GetIdentificador().second - fin_.second)) * 3;
    break;
    case 2:
    // Distancia de Chebyshev o distancia del rey
    coste = std::max(abs(nodo->GetIdentificador().first - fin_.first), abs(nodo->GetIdentificador().second - fin_.second)) * 5;
    break;
    coste = ((abs(nodo->GetIdentificador().first - fin_.first) / (abs(nodo->GetIdentificador().first) + abs(fin_.first))) + (abs(nodo->GetIdentificador().second - fin_.second) / (abs(nodo->GetIdentificador().second) + abs(fin_.second)))) * 3;
    case 3:
    // Distancia euclidea p, p = 5
    coste = pow(pow(nodo->GetIdentificador().first - fin_.first, 5) + pow(nodo->GetIdentificador().second - fin_.second, 5), 0.2) * 4; // Comprobar si es admisible
    break;
    case 4:
    // Distancia de Canberra
    coste = ((abs(nodo->GetIdentificador().first - fin_.first) / (abs(nodo->GetIdentificador().first) + abs(fin_.first))) + (abs(nodo->GetIdentificador().second - fin_.second) / (abs(nodo->GetIdentificador().second) + abs(fin_.second)))) * 3;
    break;
  }
  nodo->SetHeuristica(coste);
  return coste;
}


void Maze::CambiarES(const int& inicio_i, const int& inicio_j, const int& fin_i, const int& fin_j) {
  maze_[inicio_.first][inicio_.second] = 0;
  maze_[fin_.first][fin_.second] = 0;
  inicio_ = std::make_pair(inicio_i, inicio_j);
  fin_ = std::make_pair(fin_i, fin_j);
  maze_[inicio_i][inicio_j] = 3;
  maze_[fin_i][fin_j] = 4;
}


void Maze::EliminaNodos() {
  for (int i = 0; i < nodos_abiertos_.size(); i++) {
    // std::cout << "Borrando nodo abierto: (" << nodos_abiertos_[i]->GetIdentificador().first << ", " << nodos_abiertos_[i]->GetIdentificador().second << ")\n";
    nodos_abiertos_[i]->SetPadre(nullptr);
    delete nodos_abiertos_[i];
  }
  nodos_abiertos_.clear();
  for (int i = 0; i < nodos_cerrados_.size(); i++) {
    // std::cout << "Borrando nodo cerrado: (" << nodos_cerrados_[i]->GetIdentificador().first << ", " << nodos_cerrados_[i]->GetIdentificador().second << ")\n";
    nodos_cerrados_[i]->SetPadre(nullptr);
    delete nodos_cerrados_[i];
  }
  nodos_cerrados_.clear();
}


bool Maze::MismaFilaColumna(Nodo* nodo_actual, Nodo* nodo_vecino) {
  if (nodo_actual->GetIdentificador().first == nodo_vecino->GetIdentificador().first || nodo_actual->GetIdentificador().second == nodo_vecino->GetIdentificador().second) {
    return true;
  }
  return false;
}