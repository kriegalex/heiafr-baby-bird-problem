#include <iostream>
#include <thread>

#include<boost/program_options.hpp>

namespace po = boost::program_options;

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
      ("chicks", po::value<int>(), "number of chick processes")
      ("iters", po::value<int>(), "the number of iterations a baby chick "
          "does before it reaches adulthood and leaves the nest")
      ("parents", po::value<int>(), "the number of parents")
      ("portion", po::value<int>(), "the maximum portion size a parent"
          "brings back from a hunt")
      ("hunting", po::value<int>(), "the success rate a parent has when hunting");

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

void Parents() {
  std::cout << "Hello world, I'm a parent" << std::endl;
}

void Chicks() {
  std::cout << "Hello world, I'm a chick" << std::endl;
}

void CreateChicksProcesses(std::vector<std::thread> &thread_ptrs) {
  for (auto &thread : thread_ptrs) {
    thread = std::thread(Chicks);
  }
}

void CreateParentsProcesses(std::vector<std::thread> &thread_ptrs) {
  for (auto &thread : thread_ptrs) {
    thread = std::thread(Parents);
  }
}

/**
 * Better than creating two methods for Parents and Chicks,
 * but same effect !
 *
 * @tparam F the function to use
 * @param thread_ptrs the array of threads
 * @param func_ptr the function the thread will use
 */
template<typename F>
void CreateProcesses(std::vector<std::thread> &thread_ptrs, F func_ptr) {
  for (auto &thread : thread_ptrs) {
    thread = std::thread(func_ptr);
  }
}

void JoinAllProcesses(std::vector<std::thread> &thread_ptrs) {
  for (auto &thread : thread_ptrs) {
    thread.join();
  }
}

int main(const int ac, const char **av) {

  unsigned long chicks_number = 7;
  unsigned int baby_chick_iters = 53;
  unsigned long parents_number = 3;
  unsigned int portion_size = 5;
  unsigned int hunting_success_rate = 30;

  int fail = InitProgramOptions(chicks_number, baby_chick_iters, parents_number,
                                portion_size, hunting_success_rate, ac, av);
  if (fail) return 1;

  std::vector<std::thread> parents_threads(parents_number);
  std::vector<std::thread> chicks_threads(chicks_number);

  /*
   * Same as :
   * CreateChicksProcesses(chicks_threads);
   * CreateParentsProcesses(parents_threads);
   */
  CreateProcesses(chicks_threads, Chicks);
  CreateProcesses(parents_threads, Parents);

  JoinAllProcesses(chicks_threads);
  JoinAllProcesses(parents_threads);

  std::cout << "Simulation has ended, all processes have terminated normally" << std::endl;

  return 0;
}
