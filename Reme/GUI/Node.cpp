#include <Reme/GUI/Node.h>

#include <Reme/Core/Application.h>
#include <Reme/Debug/Instrumentor.h>
#include <Reme/Renderer/Renderer2D.h>
#include <algorithm>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Reme::GUI {

void Node::add_child(RefPtr<Node> child)
{
    PROFILE_FUNCTION();

    ASSERT(!child->parent_uid(), "This node already been added");

    m_should_reorder_children = true;

    if (!child->z_order())
        child->set_z_order(++m_next_z_order);

    m_children.push_back(child);
    if (m_children.size() > m_peek_child_count) {
        m_peek_child_count = m_children.size();
        Application::the().queue_do_layout();
    }

    child->on_enter();
}

void Node::remove_child(RefPtr<Node> child)
{
    PROFILE_FUNCTION();

    auto it = std::find_if(m_children.begin(), m_children.end(), [&child](auto node) {
        return node->uid() == child->uid();
    });

    if (it != m_children.end()) {
        it->get()->on_exit();
        m_should_reorder_children = true;
        m_children.erase(it);
    }
}

void Node::remove_all_child()
{
    for_each_child([](auto& child) {
        child->on_exit();
    });

    m_children.clear();
}

void Node::on_enter()
{
}

void Node::on_exit()
{
    remove_all_child();
}

void Node::sort_children_by_z_order()
{
    PROFILE_FUNCTION();

    if (!m_should_reorder_children)
        return;

    m_should_reorder_children = false;
    std::sort(m_children.begin(), m_children.end(), [](auto a, auto b) {
        return a->z_order() < b->z_order();
    });
}

void Node::on_render()
{
    if (m_should_reorder_children)
        sort_children_by_z_order();

    if (!m_visible)
        return;

    Renderer2D::push_state();

    glm::vec2 relative_anchor_pos = size() * scale() * anchor_point();

    Renderer2D::translate(position());
    Renderer2D::translate(relative_anchor_pos);
    Renderer2D::rotate(rotation());
    Renderer2D::scale(scale());
    Renderer2D::translate(-relative_anchor_pos);

    render();
    for_each_child([](auto& child) {
        child->on_render();
    });

    Renderer2D::pop_state();
}

void Node::do_layout()
{
    static i32 s_global_z_order = 0;

    if (!parent()) { // This is root node
        s_global_z_order = 0;
        m_bounding_rect = glm::vec4(0, 0, size() * scale());
        return;
    }

    Node& parent = *Node::parent();
    auto& parent_rect = parent.bounding_rect();

    auto inherited_scale = glm::vec2(parent_rect.z, parent_rect.w) / parent.size();
    auto effective_size = size() * scale() * inherited_scale;
    auto top_left = glm::vec2(parent_rect.x, parent_rect.y) + position() - effective_size * anchor_point();

    m_bounding_rect = glm::vec4(top_left, effective_size);
    m_assigned_z_order = ++s_global_z_order;

    if (m_should_reorder_children)
        sort_children_by_z_order();

    for_each_child([](auto& child) {
        child->do_layout();
    });
}

} // namespace Reme::GUI
