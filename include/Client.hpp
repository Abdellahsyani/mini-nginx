#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {
private:
  int _fd;
  std::string _rawRequest;
  HttpRequest _request;
  HttpResponse _response;
  enum _stat; // this for client stat reading writing etc ..

public:
  // Constructors
  // ==============
  Client();
  Client(Client& other);
  Client& operator=(Client& other);
  ~Client();

  // Methods
  // =========
  int readData();
  int sendData();
  int getFd();

};

#endif // CLIENT_HPP!
