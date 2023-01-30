workspace "ZJY"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{}cfg.architecture" 

-- Include directories relative to root folder (solution directory)添加外部头文件的时候，要修改参数
IncludeDir = {}
IncludeDir["GLFW"] = "ZJY/vendor/GLFW/include"
IncludeDir["Glad"] = "ZJY/vendor/Glad/include"
IncludeDir["ImGui"] = "ZJY/vendor/imgui"
IncludeDir["glm"] = "ZJY/vendor/glm"

include "ZJY/vendor/GLFW"
include "ZJY/vendor/Glad"
include "ZJY/vendor/imgui"


project "ZJY"
	location "ZJY"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "ZJY/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"Z_BUILD_DLL",
			"Z_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"

		}

		filter "configurations:Debug"
			defines "HZ_DEBUG"
			runtime "Debug"
			--buildoptions "/Mtd"
			symbols "on"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			--buildoptions "/MD"
			optimize "on"

		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			--buildoptions "/MD"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"ZJY/vendor/spdlog/include",
		"ZJY/src",
		"ZJY/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ZJY"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"Z_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "HZ_DEBUG"
			runtime "Debug"
			--buildoptions "/Mtd"
			symbols "on"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			--buildoptions "/MD"
			optimize "on"

		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			--buildoptions "/MD"
			optimize "on"