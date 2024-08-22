#include "Application.h"

namespace App
{
	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	Application::Application(const int& width, const int height, const string name) :
		_show_demo_window(false),
		_show_another_window(false),
		_clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
	{
		_scene = make_unique<Scene::Scene>(width, height, name);
		if (_scene->GetWindow() == nullptr) return;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		SetupImGuiIO();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(_scene->GetWindow(), true);
		ImGui_ImplOpenGL3_Init(_scene->GetGlslVersion());
	}

	void Application::Run(bool demo)
	{
		if (_scene->GetWindow() == nullptr) return;

		if (demo) LoopImGuiDemo();
		else LoopImGuiSim();
	}

	void Application::SetupImGuiIO()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	void Application::DrawImGui()
	{
		ImGui::Render();
		_scene->DrawScene(
			_clear_color.x * _clear_color.w,
			_clear_color.y * _clear_color.w,
			_clear_color.z * _clear_color.w,
			_clear_color.w
		);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Application::LoopImGuiDemo()
	{
		while (!glfwWindowShouldClose(_scene->GetWindow()))
		{
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			glfwPollEvents();
			if (glfwGetWindowAttrib(_scene->GetWindow(), GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			SetupDemoWindow();
			DrawImGui();

			ImGuiIO& io = ImGui::GetIO();

			// Update and Render additional Platform Windows
			// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(_scene->GetWindow());
		}
	}

	void Application::LoopImGuiSim()
	{
		while (!glfwWindowShouldClose(_scene->GetWindow()))
		{
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			glfwPollEvents();
			if (glfwGetWindowAttrib(_scene->GetWindow(), GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}

			_scene->RenderTexture(_render_size.x, _render_size.y);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			SetupSimWindow();
			DrawImGui();

			ImGuiIO& io = ImGui::GetIO();

			// Update and Render additional Platform Windows
			// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(_scene->GetWindow());
		}
	}

	void Application::SetupDemoWindow()
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

	void Application::SetupSimWindow()
	{
		string dock_name = "Simulation";
		string top_left = "Selection";
		string top_right = "Render";
		string bot_left = "Stats";
		string bot_right = "Graph";

		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		window_flags |= ImGuiWindowFlags_NoNavFocus;

		_scene->CheckForWindowResize();
		CreateBaseWindow(dock_name, top_left, top_right, bot_left, bot_right, window_flags);
		CreateSelectionWindow(top_left, window_flags);
		CreateRenderWindow(top_right, window_flags);
		CreateGraphWindow(bot_right, window_flags);
		CreateStatsWindow(bot_left, window_flags);
	}

	void Application::CreateBaseWindow(
		const string& name,
		const string& top_left,
		const string& top_right,
		const string& bot_left,
		const string& bot_right,
		ImGuiWindowFlags window_flags)
	{
		window_flags |= ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::Begin(name.c_str(), nullptr, window_flags);
		CreateDockspace("Dockspace", top_left, top_right, bot_left, bot_right, window_flags);
		ImGui::End();
	}

	void Application::CreateSelectionWindow(const string& name, ImGuiWindowFlags window_flags)
	{
		ImGui::Begin(name.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	void Application::CreateRenderWindow(const string& name, ImGuiWindowFlags window_flags)
	{
		ImGui::Begin(name.c_str(), nullptr, window_flags);
		_render_size = ImGui::GetWindowSize();

		ImGui::Image((void*)(intptr_t)_scene->GetTexture(), ImVec2(_scene->_tex_width, _scene->_tex_height));
		ImGui::End();
	}

	void Application::CreateStatsWindow(const string& name, ImGuiWindowFlags window_flags)
	{
		ImGui::Begin(name.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	void Application::CreateGraphWindow(const string& name, ImGuiWindowFlags window_flags)
	{
		ImGui::Begin(name.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	void Application::CreateDockspace(
		const string& dockspace,
		const string& top_left,
		const string& top_right,
		const string& bot_left,
		const string& bot_right,
		const ImGuiWindowFlags window_flags)
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

				ImGui::DockBuilderDockWindow(top_left.c_str(), dockspace_main_id);
				ImGui::DockBuilderDockWindow(top_right.c_str(), top_right_id);
				ImGui::DockBuilderDockWindow(bot_left.c_str(), bot_left_id);

				auto right_sub_id = ImGui::DockBuilderSplitNode(top_right_id, ImGuiDir_Down, 0.25f, nullptr, &top_right_id);
				ImGui::DockBuilderDockWindow(bot_right.c_str(), right_sub_id);

				ImGui::DockBuilderFinish(dockspace_id);
			}
		}
	}
}