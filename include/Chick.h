//
// Created by mlourenco on 16.10.17.
//

#pragma once

#include "Nest.h"

class Chick {
 public:
  Chick(unsigned int id);
  void Sleep() const;
  void GetFood(Nest &nest);
  void EatAndDigest();
 private:
  unsigned int m_food = 0;
  unsigned int m_sleep_time_sec = 1; // seconds
  unsigned int m_sleep_time_millisec = 100; // milliseconds
  unsigned int m_eat_amount = 1; // the amount a chick eats
  unsigned int m_id = 0;
};
