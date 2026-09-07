if (typeof window !== "undefined" && typeof HTMLSourceElement !== "undefined") {
  var origSetAttribute = HTMLSourceElement.prototype.setAttribute;
  HTMLSourceElement.prototype.setAttribute = function (name, value) {
    if (
      typeof name === "string" &&
      name.toLowerCase() === "type" &&
      value === "audio/vnd.wave"
    ) {
      value = "audio/wav";
    }
    return origSetAttribute.call(this, name, value);
  };

  var sourceDesc = Object.getOwnPropertyDescriptor(
    HTMLSourceElement.prototype,
    "type",
  );
  if (sourceDesc && sourceDesc.set) {
    var origTypeSet = sourceDesc.set;
    Object.defineProperty(HTMLSourceElement.prototype, "type", {
      set: function (val) {
        if (val === "audio/vnd.wave") {
          val = "audio/wav";
        }
        return origTypeSet.call(this, val);
      },
      get: sourceDesc.get,
      configurable: true,
      enumerable: true,
    });
  }
}

if (typeof window !== "undefined" && typeof HTMLAudioElement !== "undefined") {
  var origPlay = HTMLAudioElement.prototype.play;
  HTMLAudioElement.prototype.play = function () {
    var p = origPlay.call(this);
    if (p && typeof p.catch === "function") {
      p.catch(function (err) {
        // Ignore AbortError caused by rapid play/pause toggling
        if (err && err.name === "AbortError") {
          return;
        }
        console.warn("Audio play exception:", err);
      });
    }
    return p;
  };
}
