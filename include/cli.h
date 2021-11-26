#pragma once
#include <unordered_map>
#include <string>
#include <vector>

class CLI {
  public:
    enum DataType {
      INT,
      BOOL,
      DOUBLE,
      STRING
    };

    CLI(int arg_count, char* arg_values[],
        const std::vector<std::pair<std::string, DataType>>& potential_args);

    ~CLI();

    void* get(const std::string& flag) const;
  private:
    struct Argument {
      void* value_;
      DataType data_type_;

      Argument() : value_(nullptr), data_type_() {}
      Argument(void* value, DataType data_type)
        : value_(value), data_type_(data_type) {}
    };

    std::unordered_map<std::string, Argument> args_;
    int arg_count_;
};
