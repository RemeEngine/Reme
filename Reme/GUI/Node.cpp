#include <Reme/GUI/Node.h>

#include <Reme/Debug/Instrumentor.h>
#include <algorithm>

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

    dispatcher.dispatch<AppRenderEvent>([this](auto) {
        this->render();
        return true;
    });

    dispatcher.dispatch<AppUpdateEvent>([this](AppUpdateEvent e) {
        this->update(e.delta_time());
        return true;
    });
}

} // namespace Reme::GUI
