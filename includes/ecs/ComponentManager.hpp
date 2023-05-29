#pragma once

#include <map>

#include <ecs/EntityHandle.hpp>

namespace texplr {

class BaseComponentManager { };

template <typename T>
class ComponentManager : public BaseComponentManager {
public:
    ComponentManager() { }

    ~ComponentManager()
    {
        m_components.clear();
    }

    T& get(EntityHandle entity)
    {
        return m_components.at(entity);
    }

    void add(EntityHandle entity, const T& component)
    {
        m_components[entity] = component;
    }

    void remove(EntityHandle entity)
    {
        if (has(entity)) {
            m_components.erase(m_components.find(entity));
        }
    }

    bool has(EntityHandle entity)
    {
        return m_components.find(entity) != m_components.end();
    }

private:
    std::map<EntityHandle, T> m_components;
};

} // namespace texplr
