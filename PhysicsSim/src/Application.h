#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _APPLICATION_
#define _APPLICATION_

#include "Scene.h"
#include "Simulation.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace App
{
	class ImGuiManager
	{
	public:
		ImGuiManager() = delete;
		ImGuiManager(const ImGuiManager& other) = delete;
		ImGuiManager& operator=(const ImGuiManager& other) = delete;
		ImGuiManager(const ImGuiManager&& other) = delete;
		ImGuiManager& operator=(const ImGuiManager&& other) = delete;

		ImGuiManager(ImVec4 clear_color, GLFWwindow* window, const char* glsl_version);

		~ImGuiManager() = default;

		void Terminate();
		void AddDebugMessage(const string& msg);
		void NewFrame();
		void SetupDemoWindow();
		void SetupSimWindow(bool& resize, GLuint& texture_id, float aspect_ratio);
		ImVec4& GetClearColor();
		ImVec2& GetRenderSize();

	private:
		void CreateBaseWindow();
		void CreateSelectionWindow();
		void CreateRenderWindow(bool& resize, GLuint& texture_id, float aspect_ratio);
		void CreateStatsWindow();
		void CreateGraphWindow();
		void CreateDebugWindow();
		void CreateDockspace();

	private:
		ImVec4 _clear_color;
		bool _show_demo_window;
		bool _show_another_window;
		string _debug_msg;
		ImVec2 _render_size;
		ImGuiWindowFlags _window_flags;

		const string dockspace = "Dockspace";
		const string simulation = "Simulation";
		const string selection = "Selection";
		const string render = "Render";
		const string stats = "Stats";
		const string graph = "Graph";
		const string debug = "Debug";
	};

	class Application
	{
	public:
		Application(const Application& other) = delete;
		Application& operator=(const Application& other) = delete;
		Application(const Application&& other) = delete;
		Application& operator=(const Application&& other) = delete;

		~Application();

		Application() = default;

		bool Init(const int& width, const int& height, const string& name);
		void Run(bool demo);

	private:
		unique_ptr<ImGuiManager> _imgui;
		unique_ptr<Scene::Scene> _scene;
	};

	static void HelpMarker(const char* desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::BeginItemTooltip())
		{
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}

#endif