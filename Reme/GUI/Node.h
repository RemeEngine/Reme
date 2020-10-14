#pragma once

#include <Reme/Core/Asset.h>
#include <Reme/Core/Badge.h>
#include <Reme/Core/Core.h>
#include <Reme/Events/ApplicationEvent.h>
#include <Reme/Events/Event.h>
#include <Reme/Events/KeyEvent.h>
#include <Reme/Events/MouseEvent.h>
#include <Reme/Forward.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Reme::GUI {

class Node : Asset {
public:
    Node(const std::string& name = "Node")
        : m_name(name) {};

    virtual ~Node() {};

    inline const std::string& name() const { return m_name; }
    inline const std::vector<RefPtr<Node>>& children() const { return m_children; }

    void add_child(RefPtr<Node>);
    void remove_child(RefPtr<Node>);

    void set_z_order(i32 z_order) { m_z_order = z_order; }
    i32 z_order() const { return m_z_order; }

    u32 parent_uid() const { return m_parent_uid; }
    RefPtr<Node> parent() { return AssetManager::get<Node>(m_parent_uid); }

    virtual void on_event(Badge<Window>, Event&);

    virtual void render() {}
    virtual void update(float) {}

    virtual void on_enter() {}
    virtual void on_exit() {}

protected:
    virtual bool on_mouse_down(MouseDownEvent) { return false; }
    virtual bool on_mouse_up(MouseUpEvent) { return false; }
    virtual bool on_mouse_move(MouseMoveEvent) { return false; }
    virtual bool on_key_down(KeyDownEvent) { return false; }
    virtual bool on_key_up(KeyUpEvent) { return false; }
    virtual bool on_key_press(KeyPressEvent) { return false; }

private:
    void sort_children_by_z_order();

    u32 m_parent_uid { 0 };
    i32 m_z_order { 0 };
    i32 m_next_z_order { 0 };

    std::string m_name;
    std::vector<RefPtr<Node>> m_children;
    bool m_should_reorder_children { false };
};

} // namespace Reme::GUI
