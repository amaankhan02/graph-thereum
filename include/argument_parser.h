#pragma once
#include <unordered_map>
#include <string>

/**
 * @brief 
 * 
 */
class ArgumentParser {
  public:
    /**
     * @brief Construct a new Argument Parser object.
     */
    ArgumentParser() : args_() { }

    /**
     * @brief 
     * 
     * @param flag 
     * @param required 
     * @param var 
     * @param description 
     */
    void add_argument(const std::string& flag, bool required, int* var, 
                      const std::string& description="");

    /**
     * @brief 
     * 
     * @param flag 
     * @param required 
     * @param var 
     * @param description 
     */
    void add_argument(const std::string& flag, bool required, bool* var, 
                      const std::string& description="");

    /**
     * @brief 
     * 
     * @param flag 
     * @param required 
     * @param var 
     * @param description 
     */
    void add_argument(const std::string& flag, bool required, std::string* var, 
                      const std::string& description="");

    /**
     * @brief 
     * 
     * @param flag 
     * @param required 
     * @param var 
     * @param description 
     */
    void add_argument(const std::string& flag, bool required, double* var, 
                      const std::string& description="");
    
    /**
     * @brief 
     * 
     * @param arg_count 
     * @param arg_values 
     */
    void parse(int arg_count, char* arg_values[]);
  private:
    /**
     * @brief 
     * 
     */
    enum DataType {
      INT,
      BOOL,
      DOUBLE,
      STRING
    };
    
    /**
     * @brief This struct is used to model the command line arguments that a 
     * program can expect to see when its associated executable is run on a 
     * command line interface. Boolean command line arguments are set to true or
     * false by simply adding/omitting the flag alone. All other types of 
     * command line arguments must follow the flag with the value to pass in as 
     * an argument. If the flag is not specified, the default value is assumed.
     */
    struct ArgumentConfig {
      /**
       * @brief A string indicating the flag used to declare the command line 
       * argument. 
       */
      std::string flag_;

      /**
       * @brief A string containing the description of the use of this command 
       * line argument in the context of the executable. 
       */
      std::string description_;

      /**
       * @brief A DataType enum indicating the type this argument must take. 
       */
      DataType data_type_;

      /**
       * @brief A bool indicating whether this command line argument is required
       * in the context of the executable. The parser will produce a warning if 
       * there is a required variable that has not been provided in the command
       * line. 
       */
      bool required_;

      /**
       * @brief A bool indicating whether this argument was defined in the 
       * arguments passed in the command line. Unfilled required arguments will
       * trigger a warning displayed in the command line.
       */
      bool filled_;

      /**
       * @brief A void* that points to the variable to populate with the value
       * passed in via the command line. If an argument is not provided in the 
       * command line, this variable takes on the default value of the type. 
       * This void* must be cast to the type of the variable pointed to in order
       * to write the appropriate value. The proper typecasting is completed by 
       * referring to the data_type_ field and casting as appropriate.
       */
      void* variable_to_fill_;

      /**
       * @brief Construct a default ArgumentConfig object.
       */
      ArgumentConfig() : flag_(), description_(), data_type_(), required_(false),
                          filled_(false), variable_to_fill_() {}

      /**
       * @brief Construct a new Argument Config object.
       * 
       * @param flag 
       * @param data_type 
       * @param required 
       * @param var 
       * @param description 
       */
      ArgumentConfig(const std::string& flag, DataType data_type, bool required,
                     void* var, const std::string& description)
        : flag_(flag), description_(description), data_type_(data_type),
          required_(required), filled_(false), variable_to_fill_(var) {}
    };

    /**
     * @brief 
     * 
     */
    std::unordered_map<std::string, ArgumentConfig> args_;

    /**
     * @brief Map a DataType enum variant to its typed string representation.
     * 
     * @param t a DataType enum to convert to a string.
     * @return a std::string representing the text form of the passed enum.
     */
    std::string type_as_string(DataType t) const;
};
