#include <core/SceneGraph.hpp>

#include <cassert>

namespace texplr {

SceneGraph::SceneGraph(const EntityHandle& root)
    : m_root(root)
{
    m_parentChildMap[root] = std::set<EntityHandle>();
}

SceneGraph::~SceneGraph()
{
}

bool SceneGraph::isRoot(const EntityHandle& entity) const
{
    return m_root == entity;
}

bool SceneGraph::hasChildren(const EntityHandle& parent) const
{
    return getChildren(parent).size() > 0;
}

bool SceneGraph::isParentOf(const EntityHandle& parent, const EntityHandle& child) const
{
    return getParent(child) == parent;
}

void SceneGraph::addChild(const EntityHandle& parent, const EntityHandle& child)
{
    assert(!isRoot(child) && "Can't add root as a child of other entity.");

    removeChild(getParent(child), child);

    if (!m_parentChildMap.contains(parent)) {
        m_parentChildMap[parent] = std::set<EntityHandle>();
    }

    m_parentChildMap[parent].emplace(child);
    m_childParentMap[child] = parent;
}

void SceneGraph::removeChild(const EntityHandle& parent, const EntityHandle& child)
{
    assert(isParentOf(parent, child) && "child isn't a child of parent");

    m_childParentMap.erase(child);
    m_parentChildMap[parent].erase(child);
}

const std::set<EntityHandle>& SceneGraph::getChildren(const EntityHandle& parent) const
{
    static std::set<EntityHandle> empty = std::set<EntityHandle>();

    if (m_parentChildMap.contains(parent)) {
        return m_parentChildMap.at(parent);
    }

    return empty;
}

EntityHandle SceneGraph::getParent(const EntityHandle& child) const
{
    if (m_childParentMap.contains(child)) {
        return m_childParentMap.at(child);
    }

    return m_root;
}

EntityHandle SceneGraph::getRoot() const
{
    return m_root;
}

} // namespace texplr
