//
// Created by mlourenco on 16.10.17.
//

#include "Nest.h"

Nest::Nest(unsigned long chicks_number) {
  m_chicks_in_nest = chicks_number;
}
void Nest::IncreaseFoodStored(const unsigned int &food_amount) {
  m_food_stored += food_amount;
}
void Nest::DecreaseFoodStored(const unsigned int &food_amount) {
  m_food_stored -= food_amount;
}
unsigned int Nest::get_food_stored() const {
  return m_food_stored;
}
void Nest::set_food_stored(const unsigned int &food_amount) {
  m_food_stored = food_amount;
}
unsigned int Nest::get_food_capacity() const {
  return m_food_capacity;
}
void Nest::set_food_capacity(const unsigned int &food_amount) {
  m_food_capacity = food_amount;
}
void Nest::LeaveNest() {
  m_chicks_in_nest--;
}
bool Nest::IsNestEmpty() const {
  return m_chicks_in_nest == 0;
}
