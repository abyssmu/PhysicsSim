// Most of the ImGui portion is copied from ImGui opengl3+glfw example
// It has been reorginized a bit for better reading

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

#include <stdio.h>

namespace App
{
	class Application
	{
	public:
		Application() = delete;
		Application(const Application& other) = delete;
		~Application();
		Application(const int& width, const int height, const string name);

		void Run(bool demo);

	private:
		void SetupImGuiIO();
		void DrawImGui();

		void LoopImGui(const bool& demo);

		void SetupDemoWindow();
		void SetupSimWindow();

		void CreateBaseWindow(
			const string& name,
			const string& top_left,
			const string& top_right,
			const string& bot_left,
			const string& bot_right,
			ImGuiWindowFlags window_flags);
		void CreateSelectionWindow(const string& name, ImGuiWindowFlags window_flags);
		void CreateRenderWindow(const string& name, ImGuiWindowFlags window_flags);
		void CreateStatsWindow(const string& name, ImGuiWindowFlags window_flags);
		void CreateGraphWindow(const string& name, ImGuiWindowFlags window_flags);
		void CreateDockspace(
			const string& dockspace,
			const string& top_left,
			const string& top_right,
			const string& bot_left,
			const string& bot_right,
			const ImGuiWindowFlags window_flags);

	private:
		ImVec4 _clear_color;
		bool _show_demo_window;
		bool _show_another_window;
		unique_ptr<Scene::Scene> _scene;
		ImVec2 _render_size;
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