#pragma once

#include <map>
#include <set>

#include <core/EntityHandle.hpp>

namespace texplr {

class SceneGraph {
public:
    SceneGraph(const EntityHandle& root);
    ~SceneGraph();

    bool isRoot(const EntityHandle& entity) const;
    bool hasChildren(const EntityHandle& parent) const;
    bool isParentOf(const EntityHandle& parent, const EntityHandle& child) const;

    void addChild(const EntityHandle& parent, const EntityHandle& child);
    void removeChild(const EntityHandle& parent, const EntityHandle& child);

    const std::set<EntityHandle>& getChildren(const EntityHandle& parent) const;
    EntityHandle getParent(const EntityHandle& child) const;
    EntityHandle getRoot() const;

private:
    EntityHandle m_root;

    std::map<EntityHandle, std::set<EntityHandle>> m_parentChildMap;
    std::map<EntityHandle, EntityHandle> m_childParentMap;
};

} // namespace texplr
