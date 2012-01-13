#include <v8.h>
#include <node.h>
#include <node_version.h>
using namespace v8;

extern "C" {
    static void Init(Handle<Object> target) {
        target->Set(String::New("answer"),
                    Integer::New(42));

        target->Set(String::New("node_version"),
                    String::New(NODE_VERSION_STRING));
    }
    NODE_MODULE(primitives, Init)
}
