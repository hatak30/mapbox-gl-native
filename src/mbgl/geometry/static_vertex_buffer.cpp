#include <mbgl/geometry/static_vertex_buffer.hpp>
#include <mbgl/gl/gl.hpp>

namespace mbgl {

StaticVertexBuffer::StaticVertexBuffer(std::initializer_list<std::pair<VertexType, VertexType>> init) {
    for (const auto& vertex : init) {
        VertexType* vertices = static_cast<VertexType*>(addElement());
        vertices[0] = vertex.first;
        vertices[1] = vertex.second;
    }
}

StaticRasterVertexBuffer::StaticRasterVertexBuffer(std::initializer_list<std::tuple<VertexType, VertexType, VertexType, VertexType>> init) {
    for (const auto& vertex : init) {
        VertexType* vertices = static_cast<VertexType*>(addElement());
        vertices[0] = std::get<0>(vertex);
        vertices[1] = std::get<1>(vertex);
        vertices[2] = std::get<2>(vertex);
        vertices[3] = std::get<3>(vertex);
    }
}

} // namespace mbgl
