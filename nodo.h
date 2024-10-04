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

#ifndef _NODO_H
#define _NODO_H


class Nodo {
public:
  using position = std::pair<int, int>;

  Nodo(const position& identificador, Nodo* padre) : identificador_{identificador}, padre_{padre} {}
  Nodo(const position& identificador) : identificador_{identificador}, padre_{nullptr}, coste_movimiento_{0} {}
  position GetIdentificador() const { return identificador_; }
  double GetCoste() const { return coste_; }
  Nodo* GetPadre() const { return padre_; }
  int GetCosteMovimiento() const { return coste_movimiento_; }
  void SetPadre(Nodo* padre) { padre_ = padre; }
  void SetCoste(const double& coste) { coste_ = coste; }
  void SetCosteMovimiento(const int& coste_movimiento) { coste_movimiento_ = coste_movimiento; }
  void SetHeuristica(const int& heuristica) { heuristica_ = heuristica; }

private:
  position identificador_;
  double coste_;
  int coste_movimiento_;
  int heuristica_;
  Nodo* padre_;
};


#endif