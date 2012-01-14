#include <v8.h>
#include <node.h>
using namespace v8;

Handle<Value> Square(const Arguments &args) {
    HandleScope scope;

    int a = args[0]->Int32Value();
    int sq = a * a;

    return scope.Close(Integer::New(sq));
}

extern "C" {
    static void Init(Handle<Object> target) {
        HandleScope scope;

        Handle<FunctionTemplate> squareTpl =
            FunctionTemplate::New(Square);

        target->Set(String::New("square"),
                    squareTpl->GetFunction());
    }
    NODE_MODULE(simplefunctions, Init)
}
