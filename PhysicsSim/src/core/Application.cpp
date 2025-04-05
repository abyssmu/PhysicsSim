/**
* @file Application.cpp
* @brief
* Function definitions for the application. Uses the PIMPL idiom to hide 
* implementation details.
*/

#include "Application.hpp"

#include "utils/GlfwIncludes.hpp"
#include "graphics/ImGuiManager.hpp"
#include "graphics/Scene.hpp"
#include "objects/Object.hpp"
#include "simulation/Simulation.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"

/// @brief Application namespace.
namespace App
{
	//Structures to hold the simulators' data.

	/**
	* @brief Structure to hold the thermodynamic simulation variables.
	* @param num_particles The number of particles to simulate.
	* @param box_width_perc The width of the simulation box as a percentage of the window.
	* @param box_height_perc The height of the simulation box as a percentage of the window.
	* @param energy_value The energy value for the simulation.
	* @param temperature The temperature for the simulation.
	* @param chem_potential The chemical potential for the simulation.
	* @param radius The radius of the particles in the simulation.
	*/
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

	/// @brief Application PIMPL implementation structure.
	struct Application::ApplicationImpl
	{
		//Deleted constructors

		/// @brief Deleted copy constructor.
		ApplicationImpl(const ApplicationImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		ApplicationImpl& operator=(const ApplicationImpl& other) = delete;
		/// @brief Deleted move constructor.
		ApplicationImpl(const ApplicationImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		ApplicationImpl& operator=(const ApplicationImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor

		/// @brief Default constructor.
		ApplicationImpl() = default;
		/// @brief Default destructor.
		~ApplicationImpl() = default;

		//Member methods
		
		/**
		* @brief Initialize the application.
		* @param name The name of the application.
		* @param width The width of the application window.
		* @param height The height of the application window.
		* @return True if the application was initialized successfully, false otherwise.
		*/
		bool Init(const std::string& name, const int& width, const int& height);

		/**
		* @brief Run the application.
		* @param demo True if the application is running in demo mode, false otherwise.
		*/
		void Run(bool demo);

		//Member variables

		/// @brief Unique pointer to the ImGuiManager.
		std::unique_ptr<ImGuiManager> imgui;
		/// @brief Unique pointer to the Scene.
		std::unique_ptr<Scene::Scene> scene;
		/// @brief Unique pointer to the ThermodynamicParticleSimulator.
		std::unique_ptr<Simulation::ThermodynamicParticleSimulator> simulation;
		/// @brief The width of the simulation box as a percentage of the window.
		int box_width_perc = 0;
		/// @brief The height of the simulation box as a percentage of the window.
		int box_height_perc = 0;
	};

	/**
	* @details
	* Create the Scene and ImGuiManager objects for the application. Return false
	* if either object creation fails.
	*/
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

	/**
	* @details
	* Run the application loop using the following steps:
	* 1. Poll GLFW events for input processing.
	* 2. Check if the window is minimized and prevent rendering if it is.
	* 3. Create a new ImGui frame.
	* 4. Render either the demo or the actual application window.
	* 5. Check for ImGui state changes.
	* 6. Render the texture for the ImGui render window.
	* 7. Get ImGui background color and render the scene.
	* 8. Draw ImGui to OpenGL window and swap buffers to present frame to screen.
	*/
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

	/**
	* @details
	* Constructor for the Application class. Initializes the PIMPL pointer.
	*/
	Application::Application() :
		_impl(std::make_unique<ApplicationImpl>())
	{}

	/**
	* @details
	* Default destructor for the Application class.
	*/
	Application::~Application() = default;

	/**
	* @details
	* Initializes the Application class by passing the name, width, and height
	* to the PIMPL implementation.
	*/
	bool Application::Init(
		const std::string& name,
		const int& width,
		const int& height)
	{
		return _impl->Init(name, width, height);
	}

	/**
	* @details
	* Run the Application by passing the demo flag to the PIMPL implementation.
	*/
	void Application::Run(bool demo)
	{
		_impl->Run(demo);
	}
}