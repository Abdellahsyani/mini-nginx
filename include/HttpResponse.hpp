#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

class HttpResponse {
private:
  std::string _method;
  std::string _uri;
  std::map<std::string, std::string> _headers;
public:
  // Constructors
  // ==============
  HttpResponse();
  HttpResponse(HttpResponse& other);
  HttpResponse& operator=(HttpResponse& other);
  ~HttpResponse();

  // Methods
  // =========

};

#endif // HTTPRESPONSE_HPP!

