#include <shapes/Cube.hpp>

namespace texplr {

MeshData Cube::Generate(float size)
{
    MeshData data;
    data.vertices.reserve(24);
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, -0.5f, 0.5f) * size, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, -0.5f, 0.5f) * size, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, 0.5f, 0.5f) * size, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, 0.5f, 0.5f) * size, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f) });

    data.vertices.push_back(Vertex { glm::vec3(-0.5f, -0.5f, -0.5f) * size, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, -0.5f, -0.5f) * size, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, 0.5f, -0.5f) * size, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, 0.5f, -0.5f) * size, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f) });

    data.vertices.push_back(Vertex { glm::vec3(-0.5f, -0.5f, -0.5f) * size, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, -0.5f, 0.5f) * size, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, 0.5f, 0.5f) * size, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, 0.5f, -0.5f) * size, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });

    data.vertices.push_back(Vertex { glm::vec3(0.5f, -0.5f, -0.5f) * size, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, -0.5f, 0.5f) * size, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, 0.5f, 0.5f) * size, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, 0.5f, -0.5f) * size, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f) });

    data.vertices.push_back(Vertex { glm::vec3(-0.5f, 0.5f, 0.5f) * size, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, 0.5f, 0.5f) * size, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, 0.5f, -0.5f) * size, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, 0.5f, -0.5f) * size, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) });

    data.vertices.push_back(Vertex { glm::vec3(-0.5f, -0.5f, 0.5f) * size, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, -0.5f, 0.5f) * size, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(0.5f, -0.5f, -0.5f) * size, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f) });
    data.vertices.push_back(Vertex { glm::vec3(-0.5f, -0.5f, -0.5f) * size, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f) });

    data.indices.reserve(36);
    data.indices.assign({
        // Front
        0,
        3,
        2,
        0,
        2,
        1,

        // Back
        4,
        6,
        7,
        4,
        5,
        6,

        // Left
        8,
        11,
        10,
        8,
        10,
        9,

        // Right
        12,
        13,
        14,
        12,
        14,
        15,

        // Top
        16,
        19,
        18,
        16,
        18,
        17,

        // Bottom
        20,
        22,
        23,
        20,
        21,
        22,
    });

    return data;
}

} // namespace texplr
