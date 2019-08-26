#ifndef CSOAP_MESSAGE_H_
#define CSOAP_MESSAGE_H_

#include <string>

#include "pugixml/pugixml.hpp"

#include "csoap/globals.h"

namespace csoap {

// Base class for SOAP request and response.
class Message {
public:
  virtual ~Message() = default;

  // E.g., set as kSoapEnvNamespace.
  void set_soapenv_ns(const SoapNamespace& soapenv_ns) {
    soapenv_ns_ = soapenv_ns;
  }

  void set_service_ns(const SoapNamespace& service_ns) {
    service_ns_ = service_ns;
  }

  const std::string& operation() const {
    return operation_;
  }

  void set_operation(const std::string& operation) {
    operation_ = operation;
  }

  // Convert to SOAP XML.
  void ToXml(bool format_raw, const std::string& indent,
             std::string* xml_string);

  // Parse from SOAP XML.
  bool FromXml(const std::string& xml_string);

protected:
  // Convert to SOAP body XML.
  virtual void ToXmlBody(pugi::xml_node xbody) = 0;

  // Parse from SOAP body XML.
  virtual bool FromXmlBody(pugi::xml_node xbody) = 0;

  SoapNamespace soapenv_ns_;  // SOAP envelope namespace.
  SoapNamespace service_ns_;  // Namespace for your web service.

  std::string operation_;
};

}  // namespace csoap

#endif  // CSOAP_MESSAGE_H_
