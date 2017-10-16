//
// Created by mlourenco on 16.10.17.
//

#include "Nest.h"

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
