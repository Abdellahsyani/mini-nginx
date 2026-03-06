#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

class HttpResponse {
private:
  int _statusCode;
  std::string _content;
  std::string _fullResponse;

public:
  // Constructors
  // ==============
  HttpResponse();
  HttpResponse(HttpResponse& other);
  HttpResponse& operator=(HttpResponse& other);
  ~HttpResponse();

  // Methods
  // =========
  void buildHeader();
  void setBody(std::string body);
  std::string getFullResponse();

};

#endif // HTTPRESPONSE_HPP!

