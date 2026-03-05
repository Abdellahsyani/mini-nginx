#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

class HttpRequest {
private:
  std::string _method;
  std::string _uri;
  std::map<std::string, std::string> _headers;
  std::string _body;
  bool _isHeaderParsed;
public:
  // Constructors
  // ==============
  HttpRequest();
  HttpRequest(HttpRequest& other);
  HttpRequest& operator=(HttpRequest& other);
  ~HttpRequest();

  // Methods
  // =========
  void parse(std::string data);
  std::string getMethod();
  std::string getHeader(std::string key);

};

#endif // HTTPREQUEST_HPP!
