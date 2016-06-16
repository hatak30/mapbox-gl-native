#pragma once

#include <mbgl/geometry/buffer.hpp>

#include <array>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cmath>

namespace mbgl {

class StaticVertexBuffer : public Buffer<
    4, // bytes per vertex (2 * signed short == 4 bytes)
    GL_ARRAY_BUFFER,
    32 // default length
> {
public:
    using VertexType = int16_t;
    StaticVertexBuffer(std::initializer_list<std::pair<VertexType, VertexType>>);
};

class StaticRasterVertexBuffer : public Buffer<
    8, // bytes per vertex (4 * signed short == 8 bytes)
    GL_ARRAY_BUFFER,
    32 // default length
> {
public:
    using VertexType = int16_t;
    StaticRasterVertexBuffer(std::initializer_list<std::array<VertexType, 4>>);
};

} // namespace mbgl
