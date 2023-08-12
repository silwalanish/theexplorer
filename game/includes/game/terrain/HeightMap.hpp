#pragma once

#include <glm/glm.hpp>

namespace texplr {

class HeightMap {
public:
    HeightMap(float frequency, float amplitude, float lacunarity, float gain);
    ~HeightMap();

    float heightAt(const glm::vec2& pos);

private:
    float m_frequency;
    float m_amplitude;
    float m_lacunarity;
    float m_gain;
};

} // namespace texplr
