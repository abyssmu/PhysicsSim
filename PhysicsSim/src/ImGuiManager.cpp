#include "Application.h"

namespace App
{
	ImGuiManager::ImGuiManager(ImVec4 clear_color, GLFWwindow* window, const char* glsl_version) :
		_show_demo_window(false),
		_show_another_window(false),
		_clear_color(clear_color),
		_debug_msg(""),
		_render_size(0.0f, 0.0f),
		_window_flags(0)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		_window_flags |= ImGuiWindowFlags_NoCollapse;
		_window_flags |= ImGuiWindowFlags_NoResize;
		_window_flags |= ImGuiWindowFlags_NoMove;
		_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		_window_flags |= ImGuiWindowFlags_NoNavFocus;
	}

	void ImGuiManager::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::AddDebugMessage(const string& msg)
	{
		_debug_msg += msg + '\n';
	}

	void ImGuiManager::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiManager::SetupDemoWindow()
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");

		ImGui::Text("This is some useful text.");
		ImGui::Checkbox("Demo Window", &_show_demo_window);
		ImGui::Checkbox("Another Window", &_show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&_clear_color);

		if (ImGui::Button("Button")) counter++;

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		if (_show_another_window)
		{
			ImGui::Begin("Another Window", &_show_another_window);
			ImGui::Text("Hello from another window!");

			if (ImGui::Button("Close Me")) _show_another_window = false;

			ImGui::End();
		}

		if (_show_demo_window) ImGui::ShowDemoWindow(&_show_demo_window);
	}

	void ImGuiManager::SetupSimWindow(bool& resize, GLuint& texture_id, float aspect_ratio)
	{
		CreateBaseWindow();
		CreateSelectionWindow();
		CreateRenderWindow(resize, texture_id, aspect_ratio);
		CreateGraphWindow();
		CreateDebugWindow();
		CreateStatsWindow();
	}

	ImVec4& ImGuiManager::GetClearColor()
	{
		return _clear_color;
	}

	ImVec2& ImGuiManager::GetRenderSize()
	{
		return _render_size;
	}

	void ImGuiManager::CreateBaseWindow()
	{
		ImGuiWindowFlags flags = _window_flags | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::Begin(simulation.c_str(), nullptr, flags);
		CreateDockspace();
		ImGui::End();
	}

	void ImGuiManager::CreateSelectionWindow()
	{
		ImGui::Begin(selection.c_str(), nullptr, _window_flags);
		ImGui::End();
	}

	void ImGuiManager::CreateRenderWindow(bool& resize, GLuint& texture_id, float aspect_ratio)
	{
		ImGui::Begin(render.c_str(), nullptr, _window_flags);

		ImVec2 size = ImGui::GetContentRegionAvail();
		if (size.x != _render_size.x || size.y != _render_size.y)
		{
			_render_size = size;
			resize = true;
			//
		}

		ImVec2 display_size = ImVec2(size.x, size.x / aspect_ratio);
		if (display_size.y > size.y) display_size = ImVec2(size.y, size.y / aspect_ratio);

		if (glIsTexture(texture_id)) ImGui::Image((void*)(intptr_t)texture_id, display_size);
		else std::cout << "Invalid texture ID!" << std::endl;

		ImGui::End();
	}

	void ImGuiManager::CreateStatsWindow()
	{
		ImGui::Begin(stats.c_str(), nullptr, _window_flags);
		ImGui::End();
	}

	void ImGuiManager::CreateGraphWindow()
	{
		ImGui::Begin(graph.c_str(), nullptr, _window_flags);
		ImGui::End();
	}

	void ImGuiManager::CreateDebugWindow()
	{
		ImGui::Begin(debug.c_str(), nullptr, _window_flags);
		ImGui::TextWrapped(_debug_msg.c_str());
		ImGui::End();
	}

	void ImGuiManager::CreateDockspace()
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			auto dockspace_id = ImGui::GetID(dockspace.c_str());
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

			static auto first_time = true;
			if (first_time)
			{
				first_time = false;
				ImGui::DockBuilderRemoveNode(dockspace_id);
				ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetWindowSize());
				auto dockspace_main_id = dockspace_id;
				auto top_right_id = ImGui::DockBuilderSplitNode(dockspace_main_id, ImGuiDir_Right, 0.75f, nullptr, &dockspace_main_id);
				auto bot_left_id = ImGui::DockBuilderSplitNode(dockspace_main_id, ImGuiDir_Down, 0.5f, nullptr, &dockspace_main_id);

				ImGui::DockBuilderDockWindow(selection.c_str(), dockspace_main_id);
				ImGui::DockBuilderDockWindow(render.c_str(), top_right_id);
				ImGui::DockBuilderDockWindow(stats.c_str(), bot_left_id);

				auto right_sub_id = ImGui::DockBuilderSplitNode(top_right_id, ImGuiDir_Down, 0.25f, nullptr, &top_right_id);
				ImGui::DockBuilderDockWindow(graph.c_str(), right_sub_id);
				ImGui::DockBuilderDockWindow(debug.c_str(), right_sub_id);

				ImGui::DockBuilderFinish(dockspace_id);
			}
		}
	}
}