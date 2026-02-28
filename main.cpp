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
  addr.sin_port = htons(8080;
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

  return 0;
}

