#ifndef CLUSTER_HPP
#define CLUSTER_HPP

class Cluster {
private:
  std::vector<Server*> _servers;
  std::map<int, Client*> _clients;
  int _epollFd;
  struct epoll_event _ev;
  struct epoll_event _events;
  std::map<int, ServerConfig> _serv_config

  void _handleEvents();
  void acceptNewConnection(int listenFd);


public:
  // Constructors
  // ==============
  Cluster();
  Cluster(Cluster& other);
  Cluster& operator=(Cluster& other);
  ~Cluster();

  // Methods
  // =========
  void run();
  void init(std::vector<ServerConfig&> Configs);

};

#endif // CLUSTER_HPP!

