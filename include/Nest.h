//
// Created by mlourenco on 16.10.17.
//

#include <mutex>

#pragma once

class Nest {
 private:
  unsigned int m_food_capacity = 5;
  unsigned int m_food_stored = 0;
  unsigned long m_chicks_in_nest = 0;
  std::mutex parents_mutex;
  std::mutex chicks_mutex;

 public:
  explicit Nest(unsigned long chicks_number);
  void IncreaseFoodStored(const unsigned int &food_amount);
  void DecreaseFoodStored(const unsigned int &food_amount);
  void LeaveNest(unsigned int id);
  bool IsNestEmpty() const;
  bool ChicksCheckIsFoodEmpty(unsigned int id);
  bool ParentsCheckIsFoodEmpty(unsigned int id);
  unsigned int get_food_capacity() const;

};
