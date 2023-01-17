workspace "ZJY"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{}cfg.architecture" 

project "ZJY"
	location "ZJY"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"Z_BUILD_DLL",
			"Z_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "HZ_DEUBG"
			symbols "On"

		filter "configurations:Release"
			defines "HZ_Release"
			optimize "On"

		filter "configurations:Dist"
			defines "HZ_Dist"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ZJY/vendor/spdlog/include",
		"ZJY/src"
	}

	links
	{
		"ZJY"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"Z_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "HZ_DEUBG"
			symbols "On"

		filter "configurations:Release"
			defines "HZ_Release"
			optimize "On"

		filter "configurations:Dist"
			defines "HZ_Dist"
			optimize "On"