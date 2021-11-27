#include "../include/utils.h"
#include <iostream>

void print_elapsed(clock_t& c1, clock_t& c2, const std::string_view& action) {
  double elapsed = ((double) (c2 - c1)) / CLOCKS_PER_SEC;
  std::cout << YELLOW << "Elapsed CPU time for " << action << " is " << elapsed
            << " seconds." << RESET << std::endl;
}
