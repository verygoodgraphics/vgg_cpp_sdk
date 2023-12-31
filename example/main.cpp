#include "vgg_sdk.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace VggExport;
using namespace emscripten;

// todo, pass event, context parameters
void update() {
  VggSdk vggSdk{"https://s3.vgg.cool/test/js/vgg-sdk.esm.js"};

  // design document
  auto design_doc = vggSdk.getDesignDocument();
  std::cout << "design_doc size: " << design_doc.size() << std::endl;

  // edit design document test
  std::srand(std::time(nullptr));
  auto alpha = static_cast<double>(std::rand()) / RAND_MAX;
  auto path = "/artboard/0/layers/0/childObjects/1/childObjects/1/style/fills/"
              "0/color/alpha";
  vggSdk.designDocumentUpdateAt(path, std::to_string(alpha));

  vggSdk.designDocumentAddAt(path, std::to_string(alpha));
  vggSdk.designDocumentDeleteAt(path);

  // event listeners test
  auto element_path = "/fake/update_background_color";
  auto listenters = vggSdk.getEventListeners(element_path);
  std::cout << "listeners are: " << listenters << std::endl;

  auto type = "click";
  auto code = "console.log('log from code added by sdk');";
  if (alpha > 0.5) {
    std::cout << "add listener" << std::endl;
    vggSdk.addEventListener(element_path, type, code);
  } else {
    std::cout << "remove listener" << std::endl;
    vggSdk.removeEventListener(element_path, type, code);
  }
}

EMSCRIPTEN_BINDINGS(my_module) { function("update", &update); }