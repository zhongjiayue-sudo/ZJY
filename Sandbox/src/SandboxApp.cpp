#include<ZJY.h>

class ExampleLayer : public ZJY::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}

	void OnUpdate() override
	{
		Z_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(ZJY::Event& event) override
	{
		Z_CLIENT_TRACE("{0}", event);
	}

private:

};


class Sandbox:public ZJY::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
	PushLayer(new ExampleLayer());
	PushOverlay(new ZJY::ImGuiLayer());
}

Sandbox::~Sandbox()
{

}

ZJY::Application* ZJY::CreatApplication() {
	return new Sandbox();
}