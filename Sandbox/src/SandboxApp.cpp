#include<ZJY.h>

class Sandbox:public ZJY::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{

}

ZJY::Application* ZJY::CreatApplication() {
	return new Sandbox();
}