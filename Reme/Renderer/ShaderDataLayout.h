#pragma once

#include <Reme/Core/Core.h>

namespace Reme {

enum class ShaderDataType {
    Float,
    Float2,
    Float3,
    Float4,
    Mat2,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    IntArray,
};

static u32 shader_data_type_size(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;

    // Matrix type get handle specially in VertexArray impl
    // Under the hood Matrix type in attribute
    // is the same as Float2[2] for Mat2, Float3[3] for Mat3, ...
    // the fn ExpandDataType will duplicate those as needed
    // we just need to trick it the same as Float2, Float3, ... in this function
    case ShaderDataType::Mat2:
        return 4 * 2;
    case ShaderDataType::Mat3:
        return 4 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4;
    case ShaderDataType::IntArray:
    default:
        CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
}

struct BufferElement {
    ShaderDataType type;
    std::string name;
    u32 size;
    u32 offset;
    bool normalized;
    u32 divisor;

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false, u32 divisor = 0)
        : type(type)
        , name(name)
        , size(shader_data_type_size(type))
        , offset(0)
        , normalized(normalized)
        , divisor(divisor)
    {
    }

    u32 component_count() const
    {
        switch (type) {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Mat2:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
        default:
            CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    }
};

class BufferLayout {
public:
    BufferLayout() {}

    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_elements(elements)
    {
        expand_data_type();
        calculate_offsets_and_stride();
    }

    inline u32 stride() const { return m_stride; }
    inline const std::vector<BufferElement>& elements() const { return m_elements; }

    std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

private:
    void expand_data_type()
    {
        std::vector<BufferElement> new_elements;
        ShaderDataType type;

        u8 loop, i;
        for (auto& element : m_elements) {
            switch (element.type) {
            case ShaderDataType::Mat2:
                loop = 2;
                type = ShaderDataType::Float2;
                break;
            case ShaderDataType::Mat3:
                loop = 3;
                type = ShaderDataType::Float3;
                break;
            case ShaderDataType::Mat4:
                loop = 4;
                type = ShaderDataType::Float4;
                break;
            default:
                new_elements.push_back(element);
                continue;
            }

            for (i = 0; i < loop; i++) {
                new_elements.push_back({ type, element.name, element.normalized, element.divisor });
            }
        }

        m_elements = new_elements;
    }

    void calculate_offsets_and_stride()
    {
        u32 offset = 0;
        m_stride = 0;
        for (auto& element : m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

private:
    std::vector<BufferElement> m_elements;
    u32 m_stride = 0;
};

} // namespace Reme
