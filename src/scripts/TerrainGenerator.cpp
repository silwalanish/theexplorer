#include <scripts/TerrainGenerator.hpp>

#include <ecs/components/Mesh.hpp>
#include <ecs/components/Terrain.hpp>
#include <ecs/components/Transform.hpp>

#include <glm/gtc/noise.hpp>

namespace texplr {

TerrainGenerator::TerrainGenerator(uint32_t segments, float size, const HeightMap& heightMap)
    : m_segments(segments)
    , m_size(size)
    , m_heightMap(heightMap)
{
}

void TerrainGenerator::OnInit()
{
    m_start = -m_size / 2.0f;
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
    const Transform& transform = m_world->getComponent<Transform>(m_entity);

    m_offset = glm::vec2(transform.position.x, transform.position.z);
    uint32_t vertexPerRow = m_segments + 1;

    terrain.meshData = MeshData {};

    for (uint32_t i = 0; i < vertexPerRow; i++) {
        for (uint32_t j = 0; j < vertexPerRow; j++) {
            glm::vec3 position = positionAt(i, j);
            glm::vec3 bPosition = positionAt(i + 1, j);
            glm::vec3 cPosition = positionAt(i + 1, j + 1);

            glm::vec3 vBMinusA = bPosition - position;
            glm::vec3 vCMinusA = cPosition - position;

            glm::vec3 normal = glm::normalize(glm::cross(vBMinusA, vCMinusA));

            terrain.meshData.vertices.push_back(Vertex { position, normal, glm::vec2(j, i) / (float)(m_segments) });

            if (i != m_segments && j != m_segments) {
                terrain.meshData.indices.push_back(i * vertexPerRow + j);
                terrain.meshData.indices.push_back((i + 1) * vertexPerRow + j);
                terrain.meshData.indices.push_back((i + 1) * vertexPerRow + j + 1);

                terrain.meshData.indices.push_back(i * vertexPerRow + j);
                terrain.meshData.indices.push_back((i + 1) * vertexPerRow + j + 1);
                terrain.meshData.indices.push_back(i * vertexPerRow + j + 1);
            }
        }
    }

    terrain.material = Material { glm::vec3(0.7f, 0.3f, 0.2f) };
}

void TerrainGenerator::OnUpdate(float deltaTime)
{
}

glm::vec3 TerrainGenerator::positionAt(uint32_t row, uint32_t column)
{
    float xProgress = (column / (float)m_segments);
    float zProgress = (row / (float)m_segments);

    float x = m_start + xProgress * m_size;
    float z = m_start + zProgress * m_size;
    float y = m_heightMap.heightAt(m_offset + glm::vec2(x, z));

    return glm::vec3(x, y, z);
}

} // namespace texplr
