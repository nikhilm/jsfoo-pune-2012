#include <v8.h>
#include <node.h>
using namespace v8;

Handle<Value> Inventory(const Arguments &args) {
    return args.This();
}

extern "C" {
    static void Init(Handle<Object> target) {
        HandleScope scope;

        Handle<FunctionTemplate> inventoryTpl =
            FunctionTemplate::New(Inventory);

        Handle<ObjectTemplate> instance =
            inventoryTpl->InstanceTemplate();

        instance->Set(String::New("items"), Integer::New(257));

        target->Set(String::NewSymbol("Inventory"),
                    inventoryTpl->GetFunction());
    }
    NODE_MODULE(simpleobject, Init)
}
