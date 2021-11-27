#include "../include/cli.h"
#include "../include/utils.h"
#include <iostream>

using std::unordered_map;
using std::make_pair;
using std::vector;
using std::string;
using std::pair;

void CLI::parse_args(int arg_count, char* arg_values[],
                     std::vector<ArgumentConfig>& arg_configs) {
  unordered_map<std::string, ArgumentConfig*> args;

  // internally configure all potential arguments we could see
  for (ArgumentConfig& ac : arg_configs) {
    if (ac.data_type_ == INT)
      *static_cast<int*>(ac.variable_to_fill_) = 0;
    else if (ac.data_type_ == BOOL)
      *static_cast<bool*>(ac.variable_to_fill_) = false;
    else if (ac.data_type_ == DOUBLE)
      *static_cast<double*>(ac.variable_to_fill_) = 0.0;
    else if (ac.data_type_ == STRING)
      *static_cast<string*>(ac.variable_to_fill_) = "";

    args.insert(make_pair(ac.flag_, &ac));
  }

  // load all of the arguments passed via the command line
  for (int i = 1; i < arg_count; ++i) {
    // skip the executable name (the 0th argument) by starting at 1
    string flag = arg_values[i];
    auto iter = args.find(flag);

    if (iter == args.end()) {
      std::cerr << BOLDRED << "Unknown flag: " << flag << RESET << std::endl;
    } else {
      args[flag]->filled_ = true;
      void* to_fill = args[flag]->variable_to_fill_;

      if (iter->second->data_type_ == INT)
        *static_cast<int*>(to_fill) = std::stoi(arg_values[++i]);
      else if (iter->second->data_type_ == BOOL)
        *static_cast<bool*>(to_fill) = true;
      else if (iter->second->data_type_ == DOUBLE)
        *static_cast<double*>(to_fill) = std::stod(arg_values[++i]);
      else if (iter->second->data_type_ == STRING)
        *static_cast<string*>(to_fill) = arg_values[++i];
    }
  }

  // check if any required arguments have not been provided
  for (pair<string, ArgumentConfig*> p : args) {
    if (p.second->required_ && !p.second->filled_) {
      std::cerr << BOLDRED << "Missing required positional argument " << p.first
                << ": [" << type_as_string(p.second->data_type_) << "] "
                << p.second->description_ << RESET << std::endl;
    }
  }
}

std::string CLI::type_as_string(DataType t) {
  if (t == INT)    return "INTEGER";
  if (t == BOOL)   return "BOOLEAN";
  if (t == DOUBLE) return "DOUBLE";
  if (t == STRING) return "STRING";

  return "";
}
