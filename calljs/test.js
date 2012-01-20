var calljs = require("./build/Release/calljs")

var f = function() {
    console.log("This", this);
    console.log(arguments);
}

calljs.apply(f, { cool: "dude" }, "one", 2, 3.14);
