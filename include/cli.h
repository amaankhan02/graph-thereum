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

    struct ArgumentConfig {
      std::string flag_;
      std::string description_;
      DataType data_type_;
      bool required_;
      bool filled_;
      void* variable_to_fill_;

      ArgumentConfig() : flag_(), description_(), data_type_(), required_(false),
                         filled_(false), variable_to_fill_() {}

      ArgumentConfig(const std::string& flag, DataType data_type, bool required,
                     void* var, const std::string& description="")
        : flag_(flag), description_(description), data_type_(data_type),
          required_(required), filled_(false), variable_to_fill_(var) {}
    };

    static void parse_args(int arg_count, char* arg_values[],
                           std::vector<ArgumentConfig>& arg_configs);
  private:
    static std::string type_as_string(DataType t);
};
