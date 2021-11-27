#include "../include/argument_parser.h"
#include "../include/utils.h"
#include <iostream>

using std::unordered_map;
using std::make_pair;
using std::string;
using std::pair;

void ArgumentParser::add_argument(const string& flag, DataType data_type, 
                                  bool required, void* var, 
                                  const string& description) {
  if (data_type == INT)
    *static_cast<int*>(var) = 0;
  else if (data_type == BOOL)
    *static_cast<bool*>(var) = false;
  else if (data_type == DOUBLE)
    *static_cast<double*>(var) = 0.0;
  else if (data_type == STRING)
    *static_cast<string*>(var) = "";

  args_[flag] = ArgumentConfig(flag, data_type, required, var, description);
}

void ArgumentParser::parse(int arg_count, char* arg_values[]) {
  // load all of the arguments passed via the command line
  for (int i = 1; i < arg_count; ++i) {
    // skip the executable name (the 0th argument) by starting at 1
    string flag = arg_values[i];
    auto iter = args_.find(flag);

    if (iter == args_.end()) {
      std::cout << BOLDRED << "Unknown flag: " << flag << RESET << std::endl;
    } else {
      args_[flag].filled_ = true;
      void* to_fill = args_[flag].variable_to_fill_;

      if (iter->second.data_type_ == INT)
        *static_cast<int*>(to_fill) = std::stoi(arg_values[++i]);
      else if (iter->second.data_type_ == BOOL)
        *static_cast<bool*>(to_fill) = true;
      else if (iter->second.data_type_ == DOUBLE)
        *static_cast<double*>(to_fill) = std::stod(arg_values[++i]);
      else if (iter->second.data_type_ == STRING)
        *static_cast<string*>(to_fill) = arg_values[++i];
    }
  }

  // check if any required arguments have not been provided
  for (pair<string, ArgumentConfig> p : args_) {
    if (p.second.required_ && !p.second.filled_) {
      std::cout << BOLDRED << "Missing required positional argument " << p.first
                << ": [" << type_as_string(p.second.data_type_) << "] "
                << p.second.description_ << RESET << std::endl;
    }
  }
}

std::string ArgumentParser::type_as_string(DataType t) const {
  if (t == INT)    return "INTEGER";
  if (t == BOOL)   return "BOOLEAN";
  if (t == DOUBLE) return "DOUBLE";
  if (t == STRING) return "STRING";

  return "";
}
