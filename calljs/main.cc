#include <v8.h>
#include <node.h>
using namespace v8;

Handle<Value> Apply(const Arguments &args) {
    HandleScope scope;

    Handle<Function> func = Handle<Function>::Cast(args[0]);
    Handle<Object> receiver = args[1]->ToObject();

    Handle<Value> *argv = new Handle<Value>[args.Length() - 2];
    for (int i = 2; i < args.Length(); i++)
        argv[i-2] = args[i];

    func->Call(receiver, args.Length()-2, argv);

    delete argv;
    return Undefined();
}

extern "C" {
    static void Init(Handle<Object> target) {
        HandleScope scope;

        NODE_SET_METHOD(target, "apply", Apply);
    }
    NODE_MODULE(calljs, Init)
}
