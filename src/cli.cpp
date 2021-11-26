#include "../include/cli.h"
#include <iostream>

using std::vector;
using std::string;
using std::pair;

CLI::CLI(int arg_count, char* arg_values[],
         const vector<pair<string, DataType>>& potential_args)
    : arg_count_(arg_count) {
  // internally configure all potential arguments we could see
  for (const pair<string, DataType>& p : potential_args) {
    void* default_val = nullptr;

    if (p.second == INT)         default_val = new int(0);
    else if (p.second == BOOL)   default_val = new bool(false);
    else if (p.second == DOUBLE) default_val = new double(0.0);
    else if (p.second == STRING) default_val = new string("");

    args_.insert(make_pair(p.first, Argument(default_val, p.second)));
  }

  // load all of the arguments passed via the command line
  for (int i = 1; i < arg_count_; ++i) {
    // skip the executable name (the 0th argument) by starting at 1
    string flag = arg_values[i];
    auto iter = args_.find(flag);

    if (iter == args_.end()) {
      std::cerr << "Unknown flag: " << flag << std::endl;
    } else {
      if (iter->second.data_type_ == INT)
        *static_cast<int*>(args_[flag].value_) = std::stoi(arg_values[++i]);
      else if (iter->second.data_type_ == BOOL)
        *static_cast<bool*>(args_[flag].value_) = true;
      else if (iter->second.data_type_ == DOUBLE)
        *static_cast<double*>(args_[flag].value_) = std::stod(arg_values[++i]);
      else if (iter->second.data_type_ == STRING)
        *static_cast<string*>(args_[flag].value_) = arg_values[++i];
    }
  }
}

CLI::~CLI() {
  for (pair<std::string, Argument> p : args_) {
    if (args_[p.first].data_type_ == INT)
      delete static_cast<int*>(p.second.value_);
    else if (args_[p.first].data_type_ == BOOL)
      delete static_cast<bool*>(p.second.value_);
    else if (args_[p.first].data_type_ == DOUBLE)
      delete static_cast<double*>(p.second.value_);
    else if (args_[p.first].data_type_ == STRING)
      delete static_cast<string*>(p.second.value_);
  }
}

void* CLI::get(const std::string& flag) const {
  auto iter = args_.find(flag);
  return iter != args_.end() ? iter->second.value_ : nullptr;
}
