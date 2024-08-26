#include "Application.h"

namespace App
{
	Application::~Application()
	{
		_imgui->Terminate();
		_scene->Terminate();
	}

	bool Application::Init(const int& width, const int& height, const string& name)
	{
		_scene = make_unique<Scene::Scene>(name, width, height);
		if (_scene->GetWindow() == nullptr) return false;

		_imgui = make_unique<ImGuiManager>(ImVec4(0.45f, 0.55f, 0.60f, 1.00f), _scene->GetWindow(), _scene->GetGlslVersion());

		return true;
	}

	void Application::Run(bool demo)
	{
		if (_scene->GetWindow() == nullptr) return;

		while (!_scene->WindowShouldClose())
		{
			glfwPollEvents();
			if (glfwGetWindowAttrib(_scene->GetWindow(), GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}

			if (!demo) _scene->RenderTexture();

			_imgui->NewFrame();

			if (demo) _imgui->SetupDemoWindow();
			else
			{
				bool resize = false;
				_imgui->SetupSimWindow(resize, _scene->GetTexture(), _scene->GetTextureAspectRatio());

				if (resize)
				{
					ImVec2& size = _imgui->GetRenderSize();
					_scene->ResizeTexture(size.x, size.y);
				}
			}

			ImGui::Render();

			ImVec4& cc = _imgui->GetClearColor();
			_scene->Render(cc.x * cc.w, cc.y * cc.w, cc.z * cc.w, cc.w);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO();

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			_scene->SwapBuffers();
		}
	}
}