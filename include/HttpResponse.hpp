#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

class HttpResponse {
private:
  std::string _method;
  std::string _uri;
  std::map<std::string, std::string> _headers;
  std::string _body;
  bool _isHeaderParsed;

public:
  // Constructors
  // ==============
  HttpResponse();
  HttpResponse(HttpResponse& other);
  HttpResponse& operator=(HttpResponse& other);
  ~HttpResponse();

  // Methods
  // =========
  void parse(std::string data);
  std::string getMethod();
  std::string getHeader(std::string key);

};

#endif // HTTPRESPONSE_HPP!

