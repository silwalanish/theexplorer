#include <terrain/HeightMap.hpp>

#include <glm/gtc/noise.hpp>

namespace texplr {

static const uint32_t OCTAVES = 6;

HeightMap::HeightMap(float frequency, float amplitude, float lacunarity, float gain)
    : m_frequency(frequency)
    , m_amplitude(amplitude)
    , m_lacunarity(lacunarity)
    , m_gain(gain)
{
}

HeightMap::~HeightMap() { }

float HeightMap::heightAt(const glm::vec2& pos)
{
    float noiseValue = 0.0f;
    float frequency = m_frequency;
    float amplitude = m_amplitude;

    for (uint32_t i = 0; i < OCTAVES; i++) {
        noiseValue += amplitude * glm::perlin(pos * frequency);
        frequency *= m_lacunarity;
        amplitude *= m_gain;
    }

    return noiseValue;
}

} // namespace texplr
