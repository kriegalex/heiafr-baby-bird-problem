//
// Created by mlourenco on 16.10.17.
//

#include <thread>
#include <random>
#include <iostream>

#include "Parent.h"

Parent::Parent(unsigned int hunt_success_rate, unsigned int max_food_size, unsigned int id) {
  m_hunt_success_rate = hunt_success_rate;
  m_max_food_size = max_food_size;
  m_id = id;
}
void Parent::Rest() const {
  //std::this_thread::sleep_for(std::chrono::seconds(m_sleep_time_sec));
  std::this_thread::sleep_for(std::chrono::milliseconds(m_sleep_time_millisec));
}
void Parent::Hunt() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<unsigned int> uniform_int_distribution(1, 100);
  unsigned int dice = uniform_int_distribution(engine);
  if (dice <= m_hunt_success_rate) {
    m_food_hunted += m_max_food_size;
    std::cout << "Parent " << m_id << " hunts successfully " << m_max_food_size << " food." << std::endl;
  } else
    std::cout << "Parent " << m_id << " doesn't hunt successfully " << m_max_food_size << " food." << std::endl;

}
void Parent::DepositFood(Nest &nest) {
  unsigned int nest_capacity = nest.get_food_capacity();
  // while we have food from hunt
  while (m_food_hunted > 0) {
    // wait for the nest to be empty
    while (nest.get_food_stored() > 0) Rest();
    if (m_food_hunted > nest_capacity) {
      nest.IncreaseFoodStored(nest_capacity);
      std::cout << "Parent " << m_id << " deposits " << nest_capacity << " food in nest." << std::endl;
      m_food_hunted -= nest_capacity;
    } else {
      nest.IncreaseFoodStored(m_food_hunted);
      std::cout << "Parent " << m_id << " deposits " << m_food_hunted << " food in nest." << std::endl;
      m_food_hunted = 0;
    }
    Rest();
  }
}
