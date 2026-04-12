#include "ds/external_codec_adapter.hpp"
#include "simple_codec/simple_codec.hpp"

namespace ds {
int external_simple_sum(int a, int b) { return simple_codec::simple_sum(a, b); }
}
