#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

class ServerConfig {
private:
  std::string _host;
  int _port;
  std::vector<std::string> _serverNames;
  size_t _clientMaxBodySize;
  std::vector<Location> _Locations;
  std::map<int, std::stirng> _errorPages;

public:
  // Constructors
  // ==============
  ServerConfig();
  ServerConfig(ServerConfig& other);
  ServerConfig& operator=(ServerConfig& other);
  ~ServerConfig();

  // Methods
  // =========

};

#endif // SERVERCONFIG_HPP!
