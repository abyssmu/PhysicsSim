#include "Application.h"

#include "utils/GlfwAndDebugIncludes.h"
#include "graphics/ImGuiManager.h"
#include "graphics/Scene.h"
#include "objects/Object.h"
#include "simulation/Simulation.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"

namespace App
{
	//Structures to hold the simulators' data.
	struct ThermodynamicSimulationVariables
	{
		int num_particles = 0;
		int box_width_perc = 0;
		int box_height_perc = 0;
		float energy_value = 0.0f;
		float temperature = 0.0f;
		float chem_potential = 0.0f;
		float radius = 0.0f;
	};

	struct Application::ApplicationImpl
	{
		//Deleted constructors
		ApplicationImpl(const ApplicationImpl& other) = delete;
		ApplicationImpl& operator=(const ApplicationImpl& other) = delete;
		ApplicationImpl(const ApplicationImpl&& other) = delete;
		ApplicationImpl& operator=(const ApplicationImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		ApplicationImpl() = default;
		~ApplicationImpl() = default;

		//Member methods
		bool Init(const std::string& name, const int& width, const int& height);
		void Run(bool demo);

		//Member variables
		std::unique_ptr<ImGuiManager> imgui;
		std::unique_ptr<Scene::Scene> scene;
		std::unique_ptr<Simulation::ThermodynamicParticleSimulator> simulation;
		int box_width_perc = 0;
		int box_height_perc = 0;
	};

	bool Application::ApplicationImpl::Init(
		const std::string& name,
		const int& width,
		const int& height)
	{
		scene = std::make_unique<Scene::Scene>(name, width, height);

		//If the scene creation failed, return false to exit program
		if (scene->GetWindow() == nullptr) return false;

		imgui = std::make_unique<ImGuiManager>(
			ImVec4(0.45f, 0.55f, 0.60f, 1.00f),
			scene->GetWindow(),
			scene->GetGlslVersion());

		//If the ImGuiManager creation failed, return false to exit program
		if (imgui == nullptr) return false;

		return true;
	}

	void Application::ApplicationImpl::Run(bool demo)
	{
		//Check each frame if the window should close
		while (!scene->WindowShouldClose())
		{
			//Poll GLFW events for input processing
			glfwPollEvents();

			//If the window is minimized, prevent rendering
			if (glfwGetWindowAttrib(scene->GetWindow(), GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}

			//Create new ImGui frame
			imgui->NewFrame();

			//Render either the demo or the actual application window
			if (demo) imgui->SetupDemoWindow();
			else
			{
				//Build the ImGui UI dockspace and framework for rendering
				imgui->SetupWindow(scene->GetTexture(),
									scene->GetTextureAspectRatio());
			}

			//Check for ImGui state changes
			std::string& current_state = imgui->CheckForStateChanged();
			if (current_state == "InitThermoSim")
			{
				//Create the simulation object
				ThermodynamicSimulationVariables vars =
					imgui->GetSimulationVariables();

				if (simulation != nullptr)
				{
					simulation->ClearParticles();
					simulation->UpdateThermodynamicSimulation(
						vars.num_particles,
						vars.box_width_perc,
						vars.box_height_perc,
						vars.energy_value,
						vars.temperature,
						vars.chem_potential,
						vars.radius);
				}
				else
				{
					simulation = std::make_unique<Simulation::ThermodynamicParticleSimulator>(
						vars.num_particles,
						vars.box_width_perc,
						vars.box_height_perc,
						vars.energy_value,
						vars.temperature,
						vars.chem_potential,
						vars.radius);
				}

				box_width_perc = vars.box_width_perc;
				box_height_perc = vars.box_height_perc;

				current_state = "";
			}
			else if (current_state == "StartThermoSim")
			{
				current_state = "";
			}
			
			ImGui::Render();

			if (simulation != nullptr)
			{
				ThermodynamicSimulationVariables vars =
					imgui->GetSimulationVariables();

				//Render the texture for the ImGui render window
				scene->RenderTexture(
					simulation->GetParticleCircles(),
					box_height_perc,
					box_width_perc);
			}

			//Get ImGui background color and render scene
			ImVec4& cc = imgui->GetClearColor();
			scene->Render(cc.x * cc.w, cc.y * cc.w, cc.z * cc.w, cc.w);

			//Draw ImGui to OpenGL window and swap buffers to present frame to screen
			imgui->RenderDrawData();
			scene->SwapBuffers();
		}
	}

	Application::Application() :
		_impl(std::make_unique<ApplicationImpl>())
	{}

	Application::~Application() = default;

	/*
	* Initialization function used to capture a boolean to capture member
	* variable failures and prevent compilation or execution failures and
	* leaking memory.
	*/
	bool Application::Init(
		const std::string& name,
		const int& width,
		const int& height)
	{
		return _impl->Init(name, width, height);
	}

	void Application::Run(bool demo)
	{
		_impl->Run(demo);
	}
}