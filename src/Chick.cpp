//
// Created by mlourenco on 16.10.17.
//

#include <thread>

#include "Chick.h"
#include "PrintThread.h"

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
#ifdef DEBUG
  PrintThread{} << "Chick " << m_id << " gets " << m_eat_amount << " amount of food from Nest." << std::endl;
#endif
  m_food += m_eat_amount;
}
void Chick::EatAndDigest() {
  m_food -= m_eat_amount;
#ifdef DEBUG // this comes from CMake (CMakeLists.txt)
  PrintThread{} << "Chick " << m_id << " eats." << std::endl;
#endif
}
