#include <v8.h>
#include <node.h>

using namespace v8;

extern "C" {
    static void Init(Handle<Object> target) {
    }
    NODE_MODULE(firststep, Init)
}
