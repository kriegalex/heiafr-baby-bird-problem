//
// Created by mlourenco on 16.10.17.
//

#pragma once

class Nest {
 private:
  unsigned int m_food_capacity = 5;
  unsigned int m_food_stored = 0;
  unsigned long m_chicks_in_nest = 0;

 public:
  explicit Nest(unsigned long chicks_number);
  void IncreaseFoodStored(const unsigned int &food_amount);
  void DecreaseFoodStored(const unsigned int &food_amount);
  void LeaveNest();
  bool IsNestEmpty() const;
  unsigned int get_food_stored() const;
  void set_food_stored(const unsigned int &food_amount);
  unsigned int get_food_capacity() const;
  void set_food_capacity(const unsigned int &food_amount);

};
