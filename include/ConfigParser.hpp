#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

class ConfigParser {
private:
  std::string _filePath;

public:
  // Constructors
  // ==============
  ConfigParser();
  ConfigParser(std::string filePath);
  ConfigParser(ConfigParser& other);
  ConfigParser& operator=(ConfigParser& other);
  ~ConfigParser();

  // Methods
  // =========

};

#endif // CONFIGPARSER_HPP!
