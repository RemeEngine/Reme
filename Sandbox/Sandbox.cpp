#include <Reme/Core/EntryPoint.h>
#include <Reme/GUI/Node.h>
#include <Reme/Reme.h>

using namespace Reme;

class TestNode : public GUI::Node {
public:
    TestNode()
    {
        auto miku = GUI::Sprite::create("assets/miku-cutie.jpg");
        miku->set_scale(0.5);

        add_child(miku);

        auto sprite = GUI::Sprite::create("assets/gray.jpeg");
        sprite->set_position({ 500, 500 });
        sprite->set_scale(0.1);
        sprite->set_rotation(3);
        add_child(sprite);
    }
};

class BenchmarkNode : public GUI::Node {
public:
    BenchmarkNode()
    {
        imgs[0] = Texture::create("assets/miku-cutie.jpg");
        imgs[1] = Texture::create("assets/aqua-nyan.jpg");
        imgs[2] = Texture::create("assets/rem-sleeping-rose.png");
        imgs[3] = Texture::create("assets/you-waifu-material.jpg");
    }

    virtual void render() override
    {
        auto width = Application::the().window().width();
        auto height = Application::the().window().height();

        float y = 0.0f;
        do {
            for (u32 i = 0; i < imgs.size(); i++) {
                float ratio = (float)imgs[i]->width() / (float)imgs[i]->height();
                float dHeight = imgWidth / ratio;

                for (u32 j = 0; j < width / imgWidth; j++) {
                    Renderer2D::draw_texture(imgs[i], imgWidth * j, y, imgWidth, dHeight);
                }

                y += dHeight;
            }
        } while (y < height);

        // for (u32 x = 0; x < width; x += rectSize) {
        //     for (u32 y = 0; y < height; y += rectSize) {
        //         Renderer2D::fill_rect(
        //             Color(x % 255, y % 255, 255),
        //             x, y,
        //             rectSize - 2.0f, rectSize - 2.0f);
        //     }
        // }

        Renderer2D::fill_rect(Color::GREEN, 0.0f, 100.0f, 50.0f, 50.0f);
        Renderer2D::fill_rect(Color::RED, 100.0f, 100.0f, 50.0f, 50.0f);
        Renderer2D::fill_rect(Color::BLUE, 100.0f, 0.0f, 50.0f, 50.0f);

        Renderer2D::push_state();
        Renderer2D::translate(200.0f, 200.0f);
        Renderer2D::rotate(glm::radians(rot));
        Renderer2D::translate(-200.0f, -200.0f);
        Renderer2D::draw_texture(Texture::DEFAULT, 200.0f, 200.0f, 50.0f, 50.0f);
        Renderer2D::pop_state();
    }

    void update(float dt)
    {
        float speed = 300 * dt;
        glm::vec2 v = { 0.0f, 0.0f };
        if (Input::is_key_pressed(KeyCode::W))
            v.y -= speed;
        if (Input::is_key_pressed(KeyCode::A))
            v.x -= speed;
        if (Input::is_key_pressed(KeyCode::S))
            v.y += speed;
        if (Input::is_key_pressed(KeyCode::D))
            v.x += speed;

        if (v.x != 0.0f || v.y != 0.0f) {
            set_position(position() + v);
        }

        if (Input::is_key_pressed(KeyCode::Q))
            rot += 50 * dt;
        if (Input::is_key_pressed(KeyCode::E))
            rot -= 50 * dt;

        if (Input::is_key_pressed(KeyCode::R))
            imgWidth += 100 * dt;
        if (Input::is_key_pressed(KeyCode::T))
            imgWidth -= 100 * dt;

        if (Input::is_key_pressed(KeyCode::F))
            rectSize += 100 * dt;
        if (Input::is_key_pressed(KeyCode::G))
            rectSize -= 100 * dt;

        if (Input::is_key_pressed(KeyCode::P))
            ASSERT(false, "P key pressed");
    }

private:
    float rot = 45.0f;
    float imgWidth = 50.0f;
    float rectSize = 50.0f;
    std::array<RefPtr<Texture>, 4> imgs;
};

class Scene : public GUI::Node {
public:
    Scene()
    {
        add_child(make_asset<BenchmarkNode>());
        add_child(make_asset<TestNode>());
    }
};

class MyApp : public Application {
public:
    MyApp()
        : Application({ "Sandbox", 1280, 720 })
    {
        window().set_current_scene(make_asset<Scene>());
    }
};

REME_APP_ENTRY(MyApp)
