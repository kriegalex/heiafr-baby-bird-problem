//
// Created by mlourenco on 16.10.17.
//

#pragma once

class Nest {
 private:
  unsigned int m_food_capacity = 5;
  unsigned int m_food_stored = 0;

 public:
  void IncreaseFoodStored(const unsigned int &food_amount);
  void DecreaseFoodStored(const unsigned int &food_amount);
  unsigned int get_food_stored() const;
  void set_food_stored(const unsigned int &food_amount);
  unsigned int get_food_capacity() const;
  void set_food_capacity(const unsigned int &food_amount);

};
