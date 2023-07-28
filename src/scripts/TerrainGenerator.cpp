#include <scripts/TerrainGenerator.hpp>

#include <components/Mesh.hpp>
#include <components/Terrain.hpp>

#include <glm/gtc/noise.hpp>

namespace texplr {

static float heightMap(const glm::vec2& position, uint32_t octaves, float frequency, float amplitude, float lacunarity, float gain)
{
    float noiseValue = 0.0f;

    for (uint32_t i = 0; i < octaves; i++) {
        noiseValue += amplitude * glm::perlin(position * frequency);
        frequency *= lacunarity;
        amplitude *= gain;
    }

    return noiseValue;
}

TerrainGenerator::TerrainGenerator(uint32_t segments, float size)
    : m_segments(segments)
    , m_size(size)
{
}

void TerrainGenerator::OnInit()
{
}

void TerrainGenerator::OnAttach()
{
    if (!m_world->hasComponent<Terrain>(m_entity)) {
        m_world->addComponent<Terrain>(m_entity, Terrain {});
    }

    if (!m_world->hasComponent<Mesh>(m_entity)) {
        m_world->addComponent<Mesh>(m_entity, Mesh {});
    }

    Mesh& terrain = m_world->getComponent<Mesh>(m_entity);

    terrain.meshData = MeshData {};

    float start = -m_size / 2.0f;

    for (uint32_t i = 0; i < m_segments; i++) {
        for (uint32_t j = 0; j < m_segments; j++) {
            float xProgress = (j / (float)m_segments);
            float zProgress = (i / (float)m_segments);

            float x = start + xProgress * m_size;
            float z = start + zProgress * m_size;
            float y = heightMap(glm::vec2(xProgress, zProgress), 4, 0.2f, 10.0f, 2.488f, 0.5f);

            terrain.meshData.vertices.push_back(Vertex { glm::vec3(x, y, z), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(xProgress, zProgress) });

            if (i != (m_segments - 1) && j != (m_segments - 1)) {
                terrain.meshData.indices.push_back(i * m_segments + j);
                terrain.meshData.indices.push_back((i + 1) * m_segments + j);
                terrain.meshData.indices.push_back((i + 1) * m_segments + j + 1);

                terrain.meshData.indices.push_back(i * m_segments + j);
                terrain.meshData.indices.push_back((i + 1) * m_segments + j + 1);
                terrain.meshData.indices.push_back(i * m_segments + j + 1);
            }
        }
    }

    terrain.meshData.recalculateNormals();

    terrain.material = Material { glm::vec3(0.1f, 0.7f, 0.2f) };
}

void TerrainGenerator::OnUpdate(float deltaTime)
{
}

} // namespace texplr
