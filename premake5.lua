workspace "PhysicsSim"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PhysicsSim"
    location "PhysicsSim"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.location}/src/**.h", 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.fs",
        "%{prj.location}/src/**.vs"
    }

    excludes {
        "%{prj.location}/src/NewClass/**.*"
    }

    includedirs {
        "%{prj.location}/src",
        "%{prj.location}/vendor/glfw_build/glad/include",
        "%{prj.location}/vendor/glfw_build/glm",
        "%{prj.location}/vendor/glfw_build/glfw/include",
        "%{prj.location}/vendor/imgui_build/build_src",
        "%{prj.location}/vendor/imgui_build/build_src/backends"
    }

    links {
        "opengl32.lib",
        "imgui_build",
        "glfw_build",
        "spdlog"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

project "imgui_build"
    location "PhysicsSim"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.location}/vendor/imgui_build/build_src/*.h",
        "%{prj.location}/vendor/imgui_build/build_src/*.cpp",
        "%{prj.location}/vendor/imgui_build/build_src/backends/imgui_impl_opengl3.h",
        "%{prj.location}/vendor/imgui_build/build_src/backends/imgui_impl_opengl3.cpp",
        "%{prj.location}/vendor/imgui_build/build_src/backends/imgui_impl_opengl3_loader.h",
        "%{prj.location}/vendor/imgui_build/build_src/backends/imgui_impl_glfw.h",
        "%{prj.location}/vendor/imgui_build/build_src/backends/imgui_impl_glfw.cpp"
    }

    includedirs {
        "%{prj.location}/vendor/imgui_build/build_src",
        "%{prj.location}/vendor/imgui_build/build_src/backends",
        "%{prj.location}/vendor/glfw_build/glfw/include"
    }

    links {
        "opengl32.lib",
        "glfw_build"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

project "glfw_build"
    location "PhysicsSim"
    kind "StaticLib"
    language "C"
    staticruntime "off"
    warnings "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.location}/vendor/glfw_build/glfw/include/GLFW/glfw3.h",
        "%{prj.location}/vendor/glfw_build/glfw/include/GLFW/glfw3native.h",
        "%{prj.location}/vendor/glfw_build/glfw/src/glfw_config.h",
        "%{prj.location}/vendor/glfw_build/glfw/src/context.c",
        "%{prj.location}/vendor/glfw_build/glfw/src/init.c",
        "%{prj.location}/vendor/glfw_build/glfw/src/input.c",
        "%{prj.location}/vendor/glfw_build/glfw/src/monitor.c",
        "%{prj.location}/vendor/glfw_build/glfw/src/vulkan.c",
        "%{prj.location}/vendor/glfw_build/glfw/src/window.c",
        "%{prj.location}/vendor/glfw_build/glad/include/glad/glad.h",
        "%{prj.location}/vendor/glfw_build/glad/include/KHR/khrplatform.h",
        "%{prj.location}/vendor/glfw_build/glad/src/glad.c",
        "%{prj.location}/vendor/glfw_build/glm/glm/**.hpp",
        "%{prj.location}/vendor/glfw_build/glm/glm/**.inl"
    }

    includedirs {
        "%{prj.location}/vendor/glfw_build/glfw/include",
        "%{prj.location}/vendor/glfw_build/glad/include",
        "%{prj.location}/vendor/glfw_build/glm"
    }

    links {
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines { 
            --"GLFW_INCLUDE_NONE",
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files {
            "%{prj.location}/vendor/glfw_build/glfw/src/win32_init.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/win32_joystick.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/win32_monitor.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/win32_time.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/win32_thread.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/win32_window.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/wgl_context.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/egl_context.c",
            "%{prj.location}/vendor/glfw_build/glfw/src/osmesa_context.c"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

project "spdlog"
    location "PhysicsSim"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    defines {
        "SPDLOG_COMPILED_LIB"
    }

    files { 
        "%{prj.location}/vendor/spdlog_build/include/**.h",
        "%{prj.location}/vendor/spdlog_build/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/vendor/spdlog_build/include"
    }

    links {
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"