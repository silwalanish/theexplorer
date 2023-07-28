#pragma once

#include <core/Script.hpp>

namespace texplr {

class TerrainGenerator : public virtual Script {
public:
    TerrainGenerator(uint32_t segments, float size);

    virtual void OnInit() override;
    virtual void OnAttach() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    float m_size;
    uint32_t m_segments;
};

} // namespace texplr
