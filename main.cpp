#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <poll.h> 
#include <unistd.h>     
#include <arpa/inet.h>  
#include <fcntl.h>      

int main() {
    // 1. Create the Socket (The "Phone Line")
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd == -1) { 
        std::cerr << "Socket failed" << std::endl; 
        return 1; 
    }

    // 2. Set to Non-Blocking (Required for 1337)
    fcntl(listenFd, F_SETFL, O_NONBLOCK);

    // 3. Bind to Port 8002 (The "Phone Number")
    struct sockaddr_in addr;
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

    // 5. Setup Poll (The "Manager")
    struct pollfd pfd;
    pfd.fd = listenFd;
    pfd.events = POLLIN; // Only look for incoming data/connections

    while (true) {
        int ret = poll(&pfd, 1, -1); // Wait forever for an event
        if (ret > 0 && (pfd.revents & POLLIN)) {
            
            // 6. Accept the connection (The "Front Door")
            int clientFd = accept(listenFd, NULL, NULL);
            if (clientFd != -1) {
                std::cout << "Client connected! FD: " << clientFd << std::endl;

                // 7. Receive Data (Into our local buffer)
                char buffer[1024];
                int bytesRead = recv(clientFd, buffer, 1024, 0);
                if (bytesRead > 0) {
                    std::string request(buffer, bytesRead);
                    std::cout << "--- Received Request ---" << std::endl;
                    std::cout << request << std::endl;
                }

                // 8. Send a simple Response and Close
                std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
                send(clientFd, response.c_str(), response.size(), 0);
                
                close(clientFd);
                break; // Exit after handling one client
            }
        }
    }

    close(listenFd);
    return 0;
}












