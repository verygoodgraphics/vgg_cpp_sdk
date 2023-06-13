#pragma once

#include <emscripten.h>
#include <emscripten/val.h>

#include <string>
#include <vector>

namespace VggExport {
class VggSdk {
  emscripten::val m_sdk_url;

public:
  using ListenersType =
      std::unordered_map<std::string, std::vector<std::string>>;

  VggSdk(const char *sdkUrl) : m_sdk_url{sdkUrl} {}

  emscripten::val getDesignDocument();

  void designDocumentAddAt(const std::string &json_pointer,
                           const std::string &value);
  void designDocumentUpdateAt(const std::string &json_pointer,
                              const std::string &value);
  void designDocumentDeleteAt(const std::string &json_pointer);

  // event listener
  // event types:
  // https://developer.mozilla.org/en-US/docs/Web/API/Element#events
  void addEventListener(const std::string &element_path,
                        const std::string &event_type,
                        const std::string &listener_code);
  void removeEventListener(const std::string &element_path,
                           const std::string &event_type,
                           const std::string &listener_code);
  auto getEventListeners(const std::string &element_path) -> ListenersType;
};

} // namespace VggExport