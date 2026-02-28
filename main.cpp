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
  memset(&addr, 0, sizeof(addr));
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
    std::cerr << "Error: epoll_ctl fail" << std::endl;
    return 1;
  }


  while (true) {
    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);

    for (int n = 0; n < nfds; ++n) {
      if (events[n].data.fd == socketfd) {
        int clientfd = accept(socketfd, NULL, NULL);

        fcntl(clientfd, F_SETFL, O_NONBLOCK);
        ev.events = EPOLLIN;
        ev.data.fd = clientfd;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &ev);
        std::cout << "New client added to epoll!" << std::endl;
      } else {
        char buffer[1024];
        int b = recv(events[n].data.fd, buffer, 1024, 0);
        if (b <= 0) {
          epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd, NULL);
          close(events[n].data.fd);
        } else {
          // Send response (In a real Webserv, use EPOLLOUT first!)
          std::string res = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello!";
          send(events[n].data.fd, res.c_str(), res.size(), 0);
        }
      }
    }
  }

  return 0;
}

