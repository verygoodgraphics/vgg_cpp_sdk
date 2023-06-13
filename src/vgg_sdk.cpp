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