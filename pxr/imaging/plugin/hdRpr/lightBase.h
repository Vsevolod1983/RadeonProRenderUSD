#ifndef HDRPR_LIGHT_BASE_H
#define HDRPR_LIGHT_BASE_H

#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4f.h"
#include "pxr/imaging/hd/sprim.h"
#include "pxr/imaging/hd/light.h"
#include "pxr/usd/sdf/path.h"

namespace rpr { class Shape; }

PXR_NAMESPACE_OPEN_SCOPE

class HdRprApi;
struct HdRprApiMaterial;

class HdRprLightBase : public HdLight {
public:
    HdRprLightBase(SdfPath const& id)
        : HdLight(id) {

    }

    ~HdRprLightBase() override = default;

    void Sync(HdSceneDelegate* sceneDelegate,
              HdRenderParam* renderParam,
              HdDirtyBits* dirtyBits) override;

    HdDirtyBits GetInitialDirtyBitsMask() const override;

    void Finalize(HdRenderParam* renderParam) override;

protected:
    virtual bool SyncGeomParams(HdSceneDelegate* sceneDelegate, SdfPath const& id) = 0;

    virtual rpr::Shape* CreateLightMesh(HdRprApi* rprApi) = 0;

    // Normalize Light Color with surface area
    virtual GfVec3f NormalizeLightColor(const GfMatrix4f& transform, const GfVec3f& emmisionColor) = 0;

private:
    bool IsDirtyMaterial(const GfVec3f& emmisionColor);

private:
    rpr::Shape* m_lightMesh = nullptr;
    HdRprApiMaterial* m_lightMaterial = nullptr;
    GfVec3f m_emmisionColor = GfVec3f(0.0f);
    GfMatrix4f m_transform;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // HDRPR_LIGHT_BASE_H
