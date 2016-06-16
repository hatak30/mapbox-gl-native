#include <mbgl/shader/raster_shader.hpp>
#include <mbgl/shader/raster.vertex.hpp>
#include <mbgl/shader/raster.fragment.hpp>
#include <mbgl/gl/gl.hpp>

#include <cstdio>

using namespace mbgl;

RasterShader::RasterShader(gl::ObjectStore& store)
    : Shader("raster", shaders::raster::vertex, shaders::raster::fragment, store)
    , a_texture_pos(MBGL_CHECK_ERROR(glGetAttribLocation(getID(), "a_texture_pos"))) {
}

void RasterShader::bind(GLbyte* offset) {
    const GLint stride = 8;

    MBGL_CHECK_ERROR(glEnableVertexAttribArray(a_pos));
    MBGL_CHECK_ERROR(glVertexAttribPointer(a_pos, 2, GL_SHORT, false, stride, offset));

    MBGL_CHECK_ERROR(glEnableVertexAttribArray(a_texture_pos));
    MBGL_CHECK_ERROR(glVertexAttribPointer(a_texture_pos, 2, GL_SHORT, false, stride, offset + 4));
}
