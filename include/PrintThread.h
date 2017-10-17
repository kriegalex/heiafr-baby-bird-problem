//
// Created by mlourenco on 17.10.17.
//

#pragma once

#include <mutex>
#include <sstream>
#include <iostream>

/** Thread safe cout class
  * Exemple of use:
  *    PrintThread{} << "Hello world!" << std::endl;
  */
class PrintThread : public std::ostringstream {
 public:
  PrintThread() = default;

  ~PrintThread() override {
    std::lock_guard<std::mutex> guard(_mutexPrint);
    std::cout << this->str();
  }

 private:
  static std::mutex _mutexPrint;
};
