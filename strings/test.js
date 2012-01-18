var strings = require('./build/Release/strings')
strings.print("this", "is", 5, 6, "strings\n");
strings.print("Enter name:");
var name = strings.read();
strings.print("Hi", name);
