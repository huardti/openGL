workspace "openGL"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

	flags
	{
		"MultiProcessorCompile"
	}


    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Dependencies"
        include "libs/GLFW"
        include "libs/GLAD"
    group ""


-----------------------------------------


project "openGL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
    objdir ("./bin/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.hpp",
        "src/**.cpp",
    }

    defines
    {
    }

    includedirs
    {
        "src",
        "libs/GLFW/include",
        "libs/GLAD/include",
    }

    links
    {
        "GLFW",
        "GLAD",
        "Xrandr",
        "Xi",
        "GLU",
        "GL",
        "X11",
        "dl",
        "pthread"
    }


    filter "system:windows"
        systemversion "latest"

        defines
        {
        }

    filter "system:linux"
        systemversion "latest"

        defines
        {
        }

    filter "configurations:Debug"
        defines "_DEBUG"
        runtime "Debug"
        symbols "on"

        links
        {
        }

    filter "configurations:Release"
        defines "_RELEASE"
        runtime "Release"
        optimize "on"

        links
        {
        }

    filter "configurations:Dist"
        defines "_DIST"
        runtime "Release"
        optimize "on"

        links
        {
        }
