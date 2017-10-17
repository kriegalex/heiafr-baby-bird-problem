//
// Created by mlourenco on 16.10.17.
//

#pragma once

#include "Nest.h"

class Parent {
 public:
  Parent(unsigned int hunt_success_rate, unsigned int max_food_size, unsigned int id);
  void Rest() const;
  void Hunt();
  void DepositFood(Nest &nest);
 private:
  unsigned int m_hunt_success_rate = 30; // between 1 and 100
  const unsigned int m_sleep_time_sec = 1; // seconds
  unsigned int m_sleep_time_millisec = 100; // milliseconds
  unsigned int m_max_food_size = 5;
  unsigned int m_food_hunted = 0;
  unsigned int m_id = 0;

  bool HuntIsSuccessfull() const;
};
