#include <v8.h>
#include <node.h>
using namespace v8;

Handle<Value> Inventory(const Arguments &args) {
    return args.This();
}

Handle<Value> AddStock(const Arguments &args) {
    HandleScope scope;

    Handle<Object> This = args.This();

    int items = This->Get(String::New("items"))->Uint32Value();

    items += args[0]->Uint32Value();

    This->Set(String::New("items"), Integer::New(items));

    return Undefined();
}

Handle<Value> Ship(const Arguments &args) {
    HandleScope scope;

    Handle<Object> This = args.This();
    int items = This->Get(String::New("items"))->Uint32Value();

    int orders = args[0]->Uint32Value();

    if (items < orders)
        return ThrowException(String::New("Not enough items"));

    This->Set(String::New("items"), Integer::New(items - orders));

    return Undefined();
}

extern "C" {
    static void Init(Handle<Object> target) {
        HandleScope scope;

        Handle<FunctionTemplate> inventoryTpl =
            FunctionTemplate::New(Inventory);

        Handle<ObjectTemplate> instance =
            inventoryTpl->InstanceTemplate();

        instance->Set(String::New("items"), Integer::New(257));

        // operating on inventoryTpl->PrototypeTemplate()
        NODE_SET_PROTOTYPE_METHOD(inventoryTpl,
                                  "addStock",
                                  AddStock);
        NODE_SET_PROTOTYPE_METHOD(inventoryTpl,
                                  "ship",
                                  Ship);

        target->Set(String::NewSymbol("Inventory"),
                    inventoryTpl->GetFunction());
    }
    NODE_MODULE(methods, Init)
}
