#include <iostream>
#include <thread>

#include<boost/program_options.hpp>

#include "Chick.h"
#include "Parent.h"
#include "PrintThread.h"

namespace po = boost::program_options;

/**
 * Read options from command line
 *
 * @param chicks_number
 * @param baby_chick_iters
 * @param parents_number
 * @param portion_size
 * @param hunting_success_rate
 * @param ac arguments count
 * @param av arguments values
 * @return 1 if failure, 0 otherwise
 */
int InitProgramOptions(unsigned long &chicks_number,
                       unsigned int &baby_chick_iters,
                       unsigned long &parents_number,
                       unsigned int &portion_size,
                       unsigned int &hunting_success_rate,
                       const int ac, const char **av) {
  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("chicks", po::value<unsigned long>(), "number of chick processes")
      ("iters", po::value<unsigned int>(), "the number of iterations a baby chick "
          "does before it reaches adulthood and leaves the nest")
      ("parents", po::value<unsigned long>(), "the number of parents")
      ("portion", po::value<unsigned int>(), "the maximum portion size a parent"
          "brings back from a hunt")
      ("hunting", po::value<unsigned int>(), "the success rate a parent has when hunting");

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  if (vm.count("chicks")) {
    std::cout << "Chicks number was set to "
        << vm["chicks"].as<unsigned long>() << ".\n";
    chicks_number = vm["chicks"].as<unsigned long>();
  } else {
    std::cout << "Chicks number was defaulted to " << chicks_number << ".\n";
  }

  if (vm.count("iters")) {
    std::cout << "Baby chicks iterations was set to "
        << vm["iters"].as<unsigned int>() << ".\n";
    baby_chick_iters = vm["iters"].as<unsigned int>();
  } else {
    std::cout << "Baby chicks iterations was defaulted to " << baby_chick_iters << ".\n";
  }

  if (vm.count("parents")) {
    std::cout << "Parents number was set to "
        << vm["parents"].as<unsigned long>() << ".\n";
    parents_number = vm["parents"].as<unsigned long>();
  } else {
    std::cout << "Parents number was defaulted to " << parents_number << ".\n";
  }

  if (vm.count("portion")) {
    std::cout << "Portion size was set to "
        << vm["portion"].as<unsigned int>() << ".\n";
    portion_size = vm["portion"].as<unsigned int>();
  } else {
    std::cout << "Portion size was defaulted to " << portion_size << ".\n";
  }

  if (vm.count("hunting")) {
    std::cout << "Hunting success rate was set to "
              << vm["hunting"].as<unsigned int>() << ".\n";
    hunting_success_rate = vm["hunting"].as<unsigned int>();
  } else {
    std::cout << "Hunting success rate was defaulted to " << hunting_success_rate << "%.\n";
  }
  return 0;
}

void ParentProcess(unsigned int id, unsigned int max_food_size,
                   unsigned int hunting_success_rate, Nest &n) {
  Parent p(hunting_success_rate, max_food_size, id);
  PrintThread{} << "Hello world, I'm parent " << id << std::endl;
  while (!n.IsNestEmpty()) {
    p.Hunt();
    p.DepositFood(n);
    p.Rest();
  }
}

void ChickProcess(unsigned int id, unsigned int max_iter, Nest &nest) {
  Chick c(id);
  PrintThread{} << "Hello world, I'm chick " << id << std::endl;
  for (unsigned int i = 0; i < max_iter; ++i) {
    c.Sleep();
    c.GetFood(nest);
    c.EatAndDigest();
  }
  PrintThread{} << "Chick " << id << " has grown up." << std::endl;
  nest.LeaveNest(id);
}

void CreateChicksProcesses(std::vector<std::thread> &thread_ptrs,
                           unsigned int max_iter, Nest &nest) {
  unsigned int id = 0;
  for (auto &thread : thread_ptrs) {
    thread = std::thread(ChickProcess, id++, max_iter, std::ref(nest));
  }
}

void CreateParentsProcesses(std::vector<std::thread> &thread_ptrs,
                            unsigned int max_food_size,
                            unsigned int hunting_success_rate,
                            Nest &n) {
  unsigned int id = 0;
  for (auto &thread : thread_ptrs) {
    thread = std::thread(ParentProcess, id++, max_food_size,
                         hunting_success_rate, std::ref(n));
  }
}

/**
 * Wait for all processes to finish
 *
 * @param thread_ptrs the array of threads
 */
void JoinAllProcesses(std::vector<std::thread> &thread_ptrs) {
  for (auto &thread : thread_ptrs) {
    thread.join();
  }
}

int main(const int ac, const char **av) {

  unsigned long chicks_number = 7;
  unsigned int baby_chick_iters = 53;
  unsigned long parents_number = 3;
  unsigned int max_food_size = 5;
  unsigned int hunting_success_rate = 30;

  int fail = InitProgramOptions(chicks_number, baby_chick_iters, parents_number,
                                max_food_size, hunting_success_rate, ac, av);
  if (fail) return 1;

  // vectors of threads
  std::vector<std::thread> parents_threads(parents_number);
  std::vector<std::thread> chicks_threads(chicks_number);

  Nest n(chicks_number); // the shared nest

  CreateChicksProcesses(chicks_threads, baby_chick_iters, n);
  CreateParentsProcesses(parents_threads, max_food_size, hunting_success_rate, n);

  JoinAllProcesses(chicks_threads);
  JoinAllProcesses(parents_threads);

  std::cout << "Simulation has ended, all processes have terminated normally" << std::endl;

  return 0;
}
