#pragma once

#include <mbgl/renderer/bucket.hpp>
#include <mbgl/util/raster.hpp>
#include <mbgl/gl/gl_config.hpp>

namespace mbgl {

class RasterShader;
class StaticRasterVertexBuffer;
class VertexArrayObject;

class RasterBucket : public Bucket {
public:
    RasterBucket(gl::TexturePool&);

    void upload(gl::ObjectStore&) override;
    void render(Painter&, const style::Layer&, const UnwrappedTileID&, const mat4&) override;
    bool hasData() const override;
    bool needsClipping() const override;

    void setImage(PremultipliedImage);

    void bindTextures(gl::Config&, gl::ObjectStore&);
    void drawRaster(RasterShader&, StaticRasterVertexBuffer&, VertexArrayObject&, gl::ObjectStore&);

    Raster raster;
};

} // namespace mbgl
