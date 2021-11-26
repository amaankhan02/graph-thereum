#pragma once
#include <string_view>
#include <ctime>

void print_elapsed(clock_t& c1, clock_t& c2, const std::string_view& action);
