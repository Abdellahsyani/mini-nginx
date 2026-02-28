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
  // 1. Create the Socket (The "Phone Line")
  int listenFd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenFd == -1) { 
    std::cerr << "Socket failed" << std::endl; 
    return 1; 
  }

  //None blocking
  fcntl(listenFd, F_SETFL, O_NONBLOCK);

  // Bind to Port 8002
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
  addr.sin_port = htons(8002);       // Port 8002 in Network Byte Order

  if (bind(listenFd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    std::cerr << "Bind failed. Is port 8002 busy?" << std::endl;
    return 1;
  }

  // 4. Start Listening (The "Waiting Line")
  listen(listenFd, 10);
  std::cout << "Server started on port 8002. Waiting for one client..." << std::endl;

  std::vector<struct pollfd> fds;
  // 5. Setup Poll (The "Manager")
  struct pollfd pfd;
  pfd.fd = listenFd;
  pfd.events = POLLIN; // Only look for incoming data/connections

  fds.push_back(pfd);

  socklen_t clientLen = sizeof(addr);
  int clientFd = -1;
  while (true) {
    // 3. Pass the vector to poll (fds.data() gives the raw array pointer)
    int ret = poll(&fds[0], fds.size(), -1);

    if (ret > 0) {
      // 4. Loop through the vector to see who is ready
      for (size_t i = 0; i < fds.size(); ++i) {

        if (fds[i].revents & POLLIN) {

          if (fds[i].fd == listenFd) {
            // SOMEONE IS KNOCKING AT THE FRONT DOOR
            clientFd = accept(listenFd, NULL, NULL);
            if (clientFd != -1) {
              fcntl(clientFd, F_SETFL, O_NONBLOCK);
              struct pollfd newClient;
              newClient.fd = clientFd;
              newClient.events = POLLIN; // "Watch for data from this user"
              fds.push_back(newClient);  // ADD TO VECTOR
            }
          } else {
            // AN EXISTING CLIENT SENT DATA
            char buffer[1024];
            int bytesRead = recv(fds[i].fd, buffer, 1024, 0);
            if (bytesRead <= 0) {
              // Client disconnected
              close(fds[i].fd);
              fds.erase(fds.begin() + i); // REMOVE FROM VECTOR
              --i; // Adjust index because we deleted an element
            } else {
              // 8. Send a simple Response and Close
              std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
              send(fds[i].fd, response.c_str(), response.size(), 0);

              close(clientFd);
              // Process the request...
            }
          }
        }
      }
    }
  }

  return 0;
}

