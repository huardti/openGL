project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
	objdir ("./bin/obj/" .. outputdir .. "/%{prj.name}")

    includedirs
    {
        "include"
    }

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"