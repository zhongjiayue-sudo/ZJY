#pragma once
//Èë¿Úµã

#ifdef Z_PLATFORM_WINDOWS
extern ZJY::Application* ZJY::CreatApplication();

int main(int argc, char** argv)
{
	auto app = ZJY::CreatApplication();
	app->Run();
	delete app;
	return 0;
}

#endif