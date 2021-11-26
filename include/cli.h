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
        const std::vector<std::pair<std::string, DataType>>& flag);

    ~CLI();

    void* get(const std::string& flag) const;
  private:
    struct ArgumentValue {
      std::string value_;
      DataType data_type_;

      ArgumentValue() : value_(""), data_type_() {}
      ArgumentValue(const std::string& value, DataType data_type)
        : value_(value), data_type_(data_type) {}
    };

    std::unordered_map<std::string, ArgumentValue> args_;
    std::unordered_map<std::string, void*> parsed_values_;
    int arg_count_;
};
