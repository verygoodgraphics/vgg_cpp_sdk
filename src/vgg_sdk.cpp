#include "vgg_sdk.hpp"

#include <emscripten.h>
#include <emscripten/val.h>

#include <iostream>

using namespace VggExport;
using namespace emscripten;

// https://web.dev/emscripten-embedding-js-snippets/
EM_ASYNC_JS(EM_VAL, get_doc, (), {
  const {getVggSdk, DesignDocument} =
      await import("https://s3.vgg.cool/test/js/vgg-sdk.esm.js");
  const vggSdk = await getVggSdk();

  out("got the vggSdk: ", vggSdk);

  let doc = await DesignDocument.getDesignDocument();

  // doc = JSON.stringify(doc);

  return Emval.toHandle(doc);
});

EM_ASYNC_JS(void, design_doc_add_at, (EM_VAL path_val, EM_VAL value_val), {
  const path = Emval.toValue(path_val);
  const value = Emval.toValue(value_val);

  const {getVggSdk} =
      await import("https://s3.vgg.cool/test/js/vgg-sdk.esm.js");
  const vggSdk = await getVggSdk();

  try {
    vggSdk.addAt(path, value);
  } catch (err) {
    console.error(err);
  }
});

EM_ASYNC_JS(void, design_doc_update_at, (EM_VAL path_val, EM_VAL value_val), {
  const path = Emval.toValue(path_val);
  const value = Emval.toValue(value_val);

  const {getVggSdk} =
      await import("https://s3.vgg.cool/test/js/vgg-sdk.esm.js");
  const vggSdk = await getVggSdk();

  try {
    vggSdk.updateAt(path, value);
  } catch (err) {
    console.error(err);
  }
});

EM_ASYNC_JS(void, design_doc_delete_at, (EM_VAL path_val), {
  const path = Emval.toValue(path_val);

  const {getVggSdk} =
      await import("https://s3.vgg.cool/test/js/vgg-sdk.esm.js");
  const vggSdk = await getVggSdk();

  try {
    vggSdk.deleteAt(path);
  } catch (err) {
    console.error(err);
  }
});

emscripten::val VggSdk::getDesignDocument() {
  auto doc = val::take_ownership(get_doc());
  return doc;
}

void VggSdk::designDocumentAddAt(const std::string &json_pointer,
                                 const std::string &value) {
  val path_val{json_pointer};
  val value_val{value};
  design_doc_add_at(path_val.as_handle(), value_val.as_handle());
}

void VggSdk::designDocumentUpdateAt(const std::string &json_pointer,
                                    const std::string &value) {
  val path_val{json_pointer};
  val value_val{value};
  design_doc_update_at(path_val.as_handle(), value_val.as_handle());
}

void VggSdk::designDocumentDeleteAt(const std::string &json_pointer) {
  val path_val{json_pointer};
  design_doc_delete_at(path_val.as_handle());
}