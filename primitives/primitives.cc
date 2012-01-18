#include <math.h>
#include <v8.h>
#include <node.h>
#include <node_version.h>
using namespace v8;

extern "C" {
    static void Init(Handle<Object> target) {
        target->Set(String::NewSymbol("pi"),
                    Number::New(M_PI));

        NODE_DEFINE_CONSTANT(target, NODE_MINOR_VERSION);

        target->Set(String::New("name"), String::New("Nikhil"));
    }
    NODE_MODULE(primitives, Init)
}
