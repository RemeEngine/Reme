#include <Reme/GUI/Node.h>

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

void Node::on_event(Badge<Window>, Event& event)
{
    PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyDownEvent>(BIND_EVENT_FN(Node::on_key_down));
    dispatcher.dispatch<KeyUpEvent>(BIND_EVENT_FN(Node::on_key_up));
    dispatcher.dispatch<MouseDownEvent>(BIND_EVENT_FN(Node::on_mouse_down));
    dispatcher.dispatch<MouseUpEvent>(BIND_EVENT_FN(Node::on_mouse_up));
    dispatcher.dispatch<MouseMoveEvent>(BIND_EVENT_FN(Node::on_mouse_move));
    dispatcher.dispatch<AppRenderEvent>(BIND_EVENT_FN(Node::on_render));
    dispatcher.dispatch<AppUpdateEvent>(BIND_EVENT_FN(Node::on_update));
}

bool Node::on_update(AppUpdateEvent event)
{
    update(event.delta_time());
    for_each_child([&event](auto& child) {
        child->on_update(event);
    });

    return false;
}

bool Node::on_render(AppRenderEvent event)
{
    if (m_should_reorder_children)
        sort_children_by_z_order();

    Renderer2D::push_state();

    glm::vec2 relative_anchor_pos = transformed_size() * anchor_point();
    Renderer2D::translate(position());
    Renderer2D::translate(relative_anchor_pos);
    Renderer2D::rotate(rotation());
    Renderer2D::scale(scale());
    Renderer2D::translate(-relative_anchor_pos);

    render();
    for_each_child([&event](auto& child) {
        child->on_render(event);
    });

    Renderer2D::pop_state();
    return false;
}

glm::mat3 Node::transformation_matrix() const
{
    glm::vec2 relative_anchor_pos = transformed_size() * anchor_point();

    glm::mat3 matrix(1.0f);
    matrix = glm::translate(matrix, position());
    matrix = glm::translate(matrix, relative_anchor_pos);
    matrix = glm::rotate(matrix, rotation());
    matrix = glm::scale(matrix, scale());
    matrix = glm::translate(matrix, -relative_anchor_pos);

    return matrix;
}

} // namespace Reme::GUI
