﻿#ifndef HDRPR_MATERIAL_H
#define HDRPR_MATERIAL_H

#include "pxr/imaging/hd/material.h"

PXR_NAMESPACE_OPEN_SCOPE

struct HdRprApiMaterial;

class HdRprMaterial final : public HdMaterial {
public:
    HdRprMaterial(SdfPath const& id);

    ~HdRprMaterial() override = default;

    void Sync(HdSceneDelegate* sceneDelegate,
              HdRenderParam* renderParam,
              HdDirtyBits* dirtyBits) override;

    HdDirtyBits GetInitialDirtyBitsMask() const override;

    void Reload() override;
    void Finalize(HdRenderParam* renderParam) override;

    /// Get pointer to RPR material
    /// In case material сreation failure return nullptr
    HdRprApiMaterial const* GetRprMaterialObject() const;

private:
    HdRprApiMaterial* m_rprMaterial = nullptr;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // HDRPR_MATERIAL_H
