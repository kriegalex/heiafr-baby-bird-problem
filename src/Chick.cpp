//
// Created by mlourenco on 16.10.17.
//

#include <thread>
#include <iostream>

#include "PrintThread.h"
#include "Chick.h"

Chick::Chick(unsigned int id) {
  m_id = id;
}
void Chick::Sleep() const {
  //std::this_thread::sleep_for(std::chrono::seconds(m_sleep_time_sec));
  std::this_thread::sleep_for(std::chrono::milliseconds(m_sleep_time_millisec));
}
void Chick::GetFood(Nest &nest) {
  while (nest.ChicksCheckIsFoodEmpty(m_id)) Sleep();
  nest.DecreaseFoodStored(m_eat_amount);
  PrintThread{} << "Chick " << m_id << " gets " << m_eat_amount << " amount of food from Nest." << std::endl;
  m_food += m_eat_amount;
}
void Chick::EatAndDigest() {
  m_food -= m_eat_amount;
  PrintThread{} << "Chick " << m_id << " eats." << std::endl;
}
