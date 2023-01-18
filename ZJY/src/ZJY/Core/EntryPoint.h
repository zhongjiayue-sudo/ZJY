#pragma once
//Èë¿Úµã

#ifdef Z_PLATFORM_WINDOWS
extern ZJY::Application* ZJY::CreatApplication();

int main(int argc, char** argv)
{
	ZJY::Log::Init();
	Z_CORE_ERROR("Init Log!");
	int a = 10;
	Z_CLIENT_INFO("hello Var={0}",a);

	auto app = ZJY::CreatApplication();
	app->Run();
	delete app;
	return 0;
}

#endif