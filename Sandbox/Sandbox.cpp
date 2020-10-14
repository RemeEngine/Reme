#include <Reme/Core/EntryPoint.h>
#include <Reme/GUI/Node.h>
#include <Reme/Reme.h>

using namespace Reme;

class Scene : public GUI::Node {
protected:
    virtual void on_enter() override
    {
        auto& window = Application::the().window();
        cam = make<OrthographicCamera>(0, window.width(), window.height(), 0);

        imgs[0] = Texture::create("assets/miku-cutie.jpg");
        imgs[1] = Texture::create("assets/rem-bb.png");
        imgs[2] = Texture::create("assets/rem-sleeping-rose.png");
        imgs[3] = Texture::create("assets/you-waifu-material.jpg");
    }

    virtual void render() override
    {
        auto width = Application::the().window().width();
        auto height = Application::the().window().height();

        Renderer2D::begin(cam);

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

        for (u32 x = 0; x < width; x += rectSize) {
            for (u32 y = 0; y < height; y += rectSize) {
                Renderer2D::fill_rect(
                    Color(x % 255, y % 255, 255),
                    x, y,
                    rectSize - 2.0f, rectSize - 2.0f);
            }
        }

        Renderer2D::fill_rect(Color::GREEN, 0.0f, 100.0f, 50.0f, 50.0f);
        Renderer2D::fill_rect(Color::RED, 100.0f, 100.0f, 50.0f, 50.0f);
        Renderer2D::fill_rect(Color::BLUE, 100.0f, 0.0f, 50.0f, 50.0f);

        Renderer2D::push_state();
        Renderer2D::translate(200.0f, 200.0f);
        Renderer2D::rotate(glm::radians(rot));
        Renderer2D::translate(-200.0f, -200.0f);
        Renderer2D::draw_texture(Texture::DEFAULT, 200.0f, 200.0f, 50.0f, 50.0f);
        Renderer2D::pop_state();

        Renderer2D::end();
    }

    virtual void update(float dt) override
    {
        float speed = 300 * dt;
        glm::vec3 v = { 0.0f, 0.0f, 0.0f };
        if (Input::is_key_pressed(KeyCode::W))
            v.y -= speed;
        if (Input::is_key_pressed(KeyCode::A))
            v.x -= speed;
        if (Input::is_key_pressed(KeyCode::S))
            v.y += speed;
        if (Input::is_key_pressed(KeyCode::D))
            v.x += speed;

        if (v.x != 0.0f || v.y != 0.0f || v.z != 0.0f) {
            cam->set_position(cam->position() + v);
        }

        if (Input::is_key_pressed(KeyCode::Q))
            rot += 10 * dt;
        if (Input::is_key_pressed(KeyCode::E))
            rot -= 10 * dt;

        if (Input::is_key_pressed(KeyCode::R))
            imgWidth += 100 * dt;
        if (Input::is_key_pressed(KeyCode::T))
            imgWidth -= 100 * dt;

        if (Input::is_key_pressed(KeyCode::F))
            rectSize += 100 * dt;
        if (Input::is_key_pressed(KeyCode::G))
            rectSize -= 100 * dt;
    }

private:
    float rot = 45.0f;
    float imgWidth = 50.0f;
    float rectSize = 50.0f;
    RefPtr<OrthographicCamera> cam;
    std::array<RefPtr<Texture>, 4> imgs;
};

class MyApp : public Application {
public:
    MyApp()
        : Application({ "Sandbox", 1280, 720 })
    {
        window().set_current_scene(make<Scene>());
    }
};

REME_APP_ENTRY(MyApp)
