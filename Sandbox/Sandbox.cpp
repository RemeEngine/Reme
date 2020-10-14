#include <Reme/Core/EntryPoint.h>
#include <Reme/GUI/Node.h>
#include <Reme/Reme.h>

class Scene : public Reme::GUI::Node {
public:
    Scene()
    {
        auto& window = Application::the().window();
        cam = Reme::make<OrthographicCamera>(0, window.width(), 0, window.height());
    }

protected:
    virtual void render() override
    {
        Renderer2D::begin(cam);
        Renderer2D::fill_rect(Color::RED, 0, 0, 200, 200);
        Renderer2D::end();
    }

    virtual void update(MAYBE_UNUSED float dt) override
    {
    }

private:
    RefPtr<OrthographicCamera> cam;
};

class MyApp : public Application {
public:
    MyApp()
        : Reme::Application({ "Sandbox", 1280, 720 })
    {
        window().set_current_scene(Reme::make<Scene>());
    }
};

REME_APP_ENTRY(MyApp)
