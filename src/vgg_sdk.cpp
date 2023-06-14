#include "vgg_sdk.hpp"

#include <emscripten.h>
#include <emscripten/val.h>

#include <iostream>

using namespace VggExport;
using namespace emscripten;

// https://web.dev/emscripten-embedding-js-snippets/
EM_ASYNC_JS(EM_VAL, get_design_doc, (EM_VAL sdk_url_val), {
  const sdkUrl = Emval.toValue(sdk_url_val);
  const {DesignDocument} = await import(sdkUrl);

  let doc = await DesignDocument.getDesignDocument();

  // doc = JSON.stringify(doc);

  return Emval.toHandle(doc);
});

EM_ASYNC_JS(void, design_doc_add_at,
            (EM_VAL sdk_url_val, EM_VAL path_val, EM_VAL value_val), {
              const sdkUrl = Emval.toValue(sdk_url_val);
              const {getVggSdk} = await import(sdkUrl);
              const vggSdk = await getVggSdk();

              const path = Emval.toValue(path_val);
              const value = Emval.toValue(value_val);
              try {
                vggSdk.addAt(path, value);
              } catch (err) {
                console.error(err);
              }
            });

EM_ASYNC_JS(void, design_doc_update_at,
            (EM_VAL sdk_url_val, EM_VAL path_val, EM_VAL value_val), {
              const sdkUrl = Emval.toValue(sdk_url_val);
              const {getVggSdk} = await import(sdkUrl);
              const vggSdk = await getVggSdk();

              const path = Emval.toValue(path_val);
              const value = Emval.toValue(value_val);
              try {
                vggSdk.updateAt(path, value);
              } catch (err) {
                console.error(err);
              }
            });

EM_ASYNC_JS(void, design_doc_delete_at, (EM_VAL sdk_url_val, EM_VAL path_val), {
  const sdkUrl = Emval.toValue(sdk_url_val);
  const {getVggSdk} = await import(sdkUrl);
  const vggSdk = await getVggSdk();

  const path = Emval.toValue(path_val);
  try {
    vggSdk.deleteAt(path);
  } catch (err) {
    console.error(err);
  }
});

EM_ASYNC_JS(void, add_event_listener,
            (EM_VAL sdk_url_val, EM_VAL path_val, EM_VAL type_val,
             EM_VAL code_val),
            {
              const sdkUrl = Emval.toValue(sdk_url_val);
              const {getVggSdk} = await import(sdkUrl);
              const vggSdk = await getVggSdk();

              const path = Emval.toValue(path_val);
              const type = Emval.toValue(type_val);
              const code = Emval.toValue(code_val);
              try {
                vggSdk.addEventListener(path, type, code);
              } catch (err) {
                console.error(err);
              }
            });

EM_ASYNC_JS(void, remove_event_listener,
            (EM_VAL sdk_url_val, EM_VAL path_val, EM_VAL type_val,
             EM_VAL code_val),
            {
              const sdkUrl = Emval.toValue(sdk_url_val);
              const {getVggSdk} = await import(sdkUrl);
              const vggSdk = await getVggSdk();

              const path = Emval.toValue(path_val);
              const type = Emval.toValue(type_val);
              const code = Emval.toValue(code_val);
              try {
                vggSdk.removeEventListener(path, type, code);
              } catch (err) {
                console.error(err);
              }
            });

EM_ASYNC_JS(EM_VAL, get_event_listeners, (EM_VAL sdk_url_val, EM_VAL path_val),
            {
              const sdkUrl = Emval.toValue(sdk_url_val);
              const {getVggSdk} = await import(sdkUrl);
              const vggSdk = await getVggSdk();

              const path = Emval.toValue(path_val);
              try {
                const codes = vggSdk.getEventListeners(path);
                const codesJson = JSON.stringify(codes);
                return Emval.toHandle(codesJson);

              } catch (err) {
                console.error('vggSdk.getEventListenrs exception: ', err);
                return Emval.toHandle(null);
              }
            });

emscripten::val VggSdk::getDesignDocument() {
  auto doc = val::take_ownership(get_design_doc(m_sdk_url.as_handle()));
  return doc;
}

void VggSdk::designDocumentAddAt(const std::string &json_pointer,
                                 const std::string &value) {
  val path_val{json_pointer};
  val value_val{value};
  design_doc_add_at(m_sdk_url.as_handle(), path_val.as_handle(),
                    value_val.as_handle());
}

void VggSdk::designDocumentUpdateAt(const std::string &json_pointer,
                                    const std::string &value) {
  val path_val{json_pointer};
  val value_val{value};
  design_doc_update_at(m_sdk_url.as_handle(), path_val.as_handle(),
                       value_val.as_handle());
}

void VggSdk::designDocumentDeleteAt(const std::string &json_pointer) {
  val path_val{json_pointer};
  design_doc_delete_at(m_sdk_url.as_handle(), path_val.as_handle());
}

void VggSdk::addEventListener(const std::string &element_path,
                              const std::string &event_type,
                              const std::string &listener_code) {

  val path_val{element_path};
  val type_val{event_type};
  val code_val{listener_code};

  add_event_listener(m_sdk_url.as_handle(), path_val.as_handle(),
                     type_val.as_handle(), code_val.as_handle());
}

void VggSdk::removeEventListener(const std::string &element_path,
                                 const std::string &event_type,
                                 const std::string &listener_code) {
  val path_val{element_path};
  val type_val{event_type};
  val code_val{listener_code};

  remove_event_listener(m_sdk_url.as_handle(), path_val.as_handle(),
                        type_val.as_handle(), code_val.as_handle());
}

std::string VggSdk::getEventListeners(const std::string &element_path) {
  val path_val{element_path};

  auto codes_json_string_val = val::take_ownership(
      get_event_listeners(m_sdk_url.as_handle(), path_val.as_handle()));
  return codes_json_string_val.as<std::string>();
}