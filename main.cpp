#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <poll.h> 
#include <unistd.h>     
#include <arpa/inet.h>  
#include <fcntl.h>      
#include <cstring>
#include <sys/epoll.h>

#define MAX_EVENTS 100

int main() {
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1)
  {
    std::cerr << "Error: can't open socket" << std::endl;
    return 1;
  }

  fcntl(socketfd, F_SETFL, O_NONBLOCK);

  struct sockaddr_in addr;
  memset(addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    std::cerr << "Error: can't bind" << std::endl;
    close(socketfd);
    return 1;
  }

  if (listen(socketfd, 10) < 0) {
    std::cerr << "Error: something wrong" << std::endl;
    return 1;
  };

  std::cout << "Server waiting for incoming requests ................." << std::endl;

  int epollfd = epoll_create1(0);
  if (epollfd == -1)
  {
    std::cerr << "Error: fail to create epoll" << std::endl;
    return 1;
  }
  struct epoll_event ev, events[MAX_EVENTS];
  ev.data.fd = socketfd;
  ev.events = EPOLLIN;


  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, socketfd, &ev) == -1)
  {
    std::cerr << "Error: epoll_ctl fail" << std::end;
    return 1;
  }


  while (true) {

  }

  return 0;
}

