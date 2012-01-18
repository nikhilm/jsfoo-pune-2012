#include <stdio.h>
#include <string.h>
#include <v8.h>
#include <node.h>
using namespace v8;

Handle<Value> Print(const Arguments &args) {
    HandleScope scope;

    for (int i = 0; i < args.Length(); i++) {
        if (!args[i]->IsString())
            continue;

        // also String::AsciiValue
        String::Utf8Value val(args[i]);
        printf("%s ", *val); // <<<<<<
    }
    return Undefined();
}

Handle<Value> Read(const Arguments &args) {
    HandleScope scope;

    char str[1024];
    fgets(str, 1023, stdin);

    Local<String> v8String = String::New(str, strlen(str));
    return scope.Close(v8String);
}

extern "C" {
    static void Init(Handle<Object> target) {
        HandleScope scope;

        Handle<FunctionTemplate> printTpl =
            FunctionTemplate::New(Print);

        Handle<FunctionTemplate> readTpl =
            FunctionTemplate::New(Read);

        target->Set(String::New("print"),
                    printTpl->GetFunction());
        target->Set(String::New("read"),
                    readTpl->GetFunction());
    }
    NODE_MODULE(strings, Init)
}
