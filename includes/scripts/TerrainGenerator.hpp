#pragma once

#include <scripting/Script.hpp>

#include <terrain/HeightMap.hpp>

namespace texplr {

class TerrainGenerator : public virtual Script {
public:
    TerrainGenerator(uint32_t segments, float size, const HeightMap& heightMap);

    virtual void OnInit() override;
    virtual void OnAttach() override;
    virtual void OnUpdate(float deltaTime) override;

    const HeightMap& getHeightMap() const;

private:
    float m_size;
    float m_start;
    uint32_t m_segments;
    HeightMap m_heightMap;
    glm::vec2 m_offset;

    glm::vec3 positionAt(uint32_t row, uint32_t column);
};

} // namespace texplr
