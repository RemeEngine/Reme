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

class Node : public Asset {
public:
    static RefPtr<Node> create(const std::string& name = "AnonNode")
    {
        return Asset::make<Node>(name);
    }

    Node(const std::string& name = "Something that inherit Node, maybe")
        : m_name(name) {};

    virtual ~Node() {};

    inline virtual const std::string& name() const { return m_name; }
    inline virtual void set_name(const std::string& name) { m_name = name; }

    inline virtual const std::vector<RefPtr<Node>>& children() const { return m_children; }

    template<typename Callback>
    void for_each_child(Callback callback)
    {
        for (auto& child : children()) {
            callback(child);
        }
    }

    virtual void add_child(RefPtr<Node>);
    virtual void remove_child(RefPtr<Node>);
    virtual void remove_all_child();

    inline virtual i32 z_order() const { return m_z_order; }
    inline virtual void set_z_order(i32 z_order) { m_z_order = z_order; }

    inline i32 global_z_order() const { return m_assigned_z_order; }
    inline const glm::vec4& bounding_rect() const { return m_bounding_rect; }

    inline virtual u32 parent_uid() const { return m_parent_uid; }
    inline virtual RefPtr<Node> parent() { return AssetManager::get<Node>(m_parent_uid); }
    inline virtual RefPtr<Node> parent() const { return AssetManager::get<Node>(m_parent_uid); }

    virtual void do_layout();

    virtual void on_render();
    virtual void render() {}

    virtual void on_enter();
    virtual void on_exit();

    inline virtual bool visible() const { return m_visible; }
    inline virtual void set_visible(bool visible) { m_visible = visible; }

    inline virtual float rotation() const { return m_rotation; }
    inline virtual void set_rotation(float rotation) { m_rotation = rotation; }

    inline virtual glm::vec2 scale() const { return m_scale; }
    inline float scale_x() const { return scale().x; }
    inline float scale_y() const { return scale().y; }

    inline virtual void set_scale(glm::vec2 scale) { m_scale = scale; }
    inline void set_scale(float scale) { set_scale({ scale, scale }); }
    inline void set_scale_x(float scale_x) { set_scale({ scale_x, scale().y }); }
    inline void set_scale_y(float scale_y) { set_scale({ scale().y, scale_y }); }

    inline virtual glm::vec2 position() const { return m_position; }
    inline float x() const { return position().x; }
    inline float y() const { return position().y; }

    inline virtual void set_position(glm::vec2 position) { m_position = position; }
    inline void set_x(float x) { set_position({ x, position().y }); }
    inline void set_y(float y) { set_position({ position().x, y }); }

    inline virtual glm::vec2 anchor_point() const { return m_anchor_point; }
    inline float anchor_x() const { return anchor_point().x; }
    inline float anchor_y() const { return anchor_point().y; }

    virtual void set_anchor_point(glm::vec2 anchor_point) { m_anchor_point = anchor_point; }
    inline void set_anchor_x(float x) { set_anchor_point({ x, anchor_point().y }); }
    inline void set_anchor_y(float y) { set_anchor_point({ anchor_point().x, y }); }

    inline virtual glm::vec2 size() const { return m_size; }
    inline float width() const { return size().x; }
    inline float height() const { return size().y; }

    inline virtual void set_size(glm::vec2 size) { m_size = size; }
    inline void set_width(float width) { set_size({ width, size().y }); }
    inline void set_height(float height) { set_size({ size().x, height }); }

    inline virtual const char* class_name() const override { return "GUI::Node"; }

private:
    void sort_children_by_z_order();

    // Note: For event handling
    i32 m_assigned_z_order { 0 };
    glm::vec4 m_bounding_rect { 0, 0, 0, 0 };

    u32 m_peek_child_count { 0 };

    AssetUID m_parent_uid { 0 };
    i32 m_z_order { 0 };
    i32 m_next_z_order { 0 };
    bool m_visible { true };

    float m_rotation { 0.0f };
    glm::vec2 m_scale { 1.0f, 1.0f };
    glm::vec2 m_position { 0.0f, 0.0f };
    glm::vec2 m_anchor_point { 0.5f, 0.5f };
    glm::vec2 m_size { 0.0f, 0.0f };

    std::string m_name;
    std::vector<RefPtr<Node>> m_children;
    bool m_should_reorder_children { false };
};

} // namespace Reme::GUI
