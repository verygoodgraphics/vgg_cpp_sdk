mergeInto(LibraryManager.library, {
  jsAdd1: function (x) {
    return x + 1;
  },
  jsAdd2: function (x) {
    return x + 2.0;
  },
  jsAdd11: function (x) {
    return jsBridgeAdd11(x);
  },
});
