#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location : public ServerConfig {
private;
  std::string _path;
  std::string _root;
  std::string _index;
  bool _autoindex;
  std::vector<std::string> _methodsAllowed;
  std::string _cgiPath;
  std::string _cgiExtension;

public:
  // Constructors
  // ==============
  Location();
  Location(Location& other);
  Location& operator=(Location& other);
  ~Location();

  // Methods
  // =========

};

#endif // LOCATION_HPP!
