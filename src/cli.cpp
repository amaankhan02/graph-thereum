#include "../include/cli.h"
#include <iostream>

using std::make_pair;
using std::vector;
using std::string;
using std::pair;

CLI::CLI(int arg_count, char* arg_values[],
         const vector<pair<string, DataType>>& flags)
    : arg_count_(arg_count) {
  for (const pair<string, DataType>& p : flags) {
    args_.insert(make_pair(p.first, ArgumentValue("", p.second)));
    void* default_val = nullptr;

    switch (p.second) {
      case DataType::INT: {
        default_val = new int(0);
        break;
      }
      case DataType::BOOL: {
        default_val = new bool(false);
        break;
      }
      case DataType::DOUBLE: {
        default_val = new double(0.0);
        break;
      }
      case DataType::STRING: {
        default_val = new string("");
        break;
      }
    }

    parsed_values_.insert(make_pair(p.first, default_val));
  }

  // skip the executable name (the 0th argument) by starting at 1
  for (int i = 1; i < arg_count_; ++i) {
    string flag = arg_values[i];
    auto iter = args_.find(flag);

    if (iter == args_.end()) {
      std::cerr << "Unknown flag: " << flag << std::endl;
    } else {
      switch (iter->second.data_type_) {
        case DataType::INT: {
          ++i;
          iter->second.value_ = arg_values[i];
          *static_cast<int*>(parsed_values_[flag]) = std::stoi(arg_values[i]);
          break;
        }
        case DataType::BOOL: {
          iter->second.value_ = "true";
          *static_cast<bool*>(parsed_values_[flag]) = true;
          break;
        }
        case DataType::DOUBLE: {
          ++i;
          iter->second.value_ = arg_values[i];
          *static_cast<double*>(parsed_values_[flag]) = std::stod(arg_values[i]);
          break;
        }
        case DataType::STRING: {
          ++i;
          iter->second.value_ = arg_values[i];
          *static_cast<string*>(parsed_values_[flag]) = arg_values[i];
          break;
        }
      }
    }
  }
}

CLI::~CLI() {
  for (pair<std::string, void*> p : parsed_values_) {
    DataType t = args_[p.first].data_type_;
    switch (t) {
      case INT: {
        int* ptr = static_cast<int*>(p.second);
        delete ptr;
        break;
      }
      case BOOL: {
        bool* ptr = static_cast<bool*>(p.second);
        delete ptr;
        break;
      }
      case DOUBLE: {
        double* ptr = static_cast<double*>(p.second);
        delete ptr;
        break;
      }
      case STRING: {
        string* ptr = static_cast<string*>(p.second);
        delete ptr;
        break;
      }
    }
  }
}

void* CLI::get(const std::string& flag) const {
  auto iter = parsed_values_.find(flag);
  return iter != parsed_values_.end() ? iter->second : nullptr;
}

