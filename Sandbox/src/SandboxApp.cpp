#include<ZJY.h>

#include"imgui/imgui.h"

class ExampleLayer : public ZJY::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//Z_CLIENT_INFO("ExampleLayer::Update");
		if (ZJY::Input::IsKeyPressed(ZJY::Key::Tab))
			Z_CLIENT_INFO("Tab is pressed(poll)!");
	}

	void OnEvent(ZJY::Event& event) override
	{
		//Z_CLIENT_TRACE("{0}", event);
		if (event.GetEventType() == ZJY::EventType::KeyPressed)
		{
			ZJY::KeyPressedEvent& e = (ZJY::KeyPressedEvent&)event;
			if (ZJY::Input::IsKeyPressed(ZJY::Key::Tab))
				Z_CLIENT_INFO("Tab is pressed(event)!");
			Z_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
		}
	} 

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("hello");
		ImGui::End();
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
}

Sandbox::~Sandbox()
{

}

ZJY::Application* ZJY::CreatApplication() {
	return new Sandbox();
}