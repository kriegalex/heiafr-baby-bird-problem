//
// Created by mlourenco on 16.10.17.
//

#include <PrintThread.h>
#include "Nest.h"

Nest::Nest(unsigned long chicks_number) {
  m_chicks_in_nest = chicks_number;
}
void Nest::IncreaseFoodStored(const unsigned int &food_amount) {
  m_food_stored += food_amount;
  parents_mutex.unlock();
}
void Nest::DecreaseFoodStored(const unsigned int &food_amount) {
  m_food_stored -= food_amount;
  chicks_mutex.unlock();
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
void Nest::LeaveNest(unsigned int id) {
  m_chicks_in_nest--;
  PrintThread{} << "Chick " << id << " leaves nest. " << m_chicks_in_nest << " remaining." << std::endl;
}
bool Nest::IsNestEmpty() const {
  return m_chicks_in_nest == 0;
}
bool Nest::ChicksCheckIsFoodEmpty(unsigned int id) {
  chicks_mutex.lock();
  PrintThread{} << "Chick " << id << " checks nest has " << m_food_stored << " food." << std::endl;
  if (m_food_stored == 0) // if no food, release lock
    chicks_mutex.unlock();
  return m_food_stored == 0;
}
bool Nest::ParentsCheckIsFoodEmpty(unsigned int id) {
  parents_mutex.lock();
  PrintThread{} << "Parent " << id << " checks nest has " << m_food_stored << " food." << std::endl;
  if (m_food_stored != 0) // if already food, release lock
    parents_mutex.unlock();
  return m_food_stored == 0;
}
