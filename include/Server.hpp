#ifndef SERVER_HPP
#define SERVER_HPP

class Server {
private:
  int _listenFd;
  ServerConfig _config;
  struct sockaddr_in _address;

public:
  // Constructors
  // ==============
  Server();
  Server(Server& other);
  Server& operator=(Server& other);
  ~Server();

  // Methods
  // =========
  void setUpSocket();
  void setConfig();
  int acceptConnection();
  int getListenFd();
  ServerConfig& getConfig();

};

#endif // SERVER_HPP!
