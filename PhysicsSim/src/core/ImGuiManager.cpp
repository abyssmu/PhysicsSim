#include "ImGuiManager.hpp"

#include "utils/GlfwIncludes.hpp"
#include "graphics/Texture.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

	/// @brief ImGuiManager PIMPL implementation structure.
	struct ImGuiManager::ImGuiManagerImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		ImGuiManagerImpl() = delete;
		/// @brief Deleted copy constructor.
		ImGuiManagerImpl(const ImGuiManagerImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		ImGuiManagerImpl& operator=(const ImGuiManagerImpl& other) = delete;
		/// @brief Deleted move constructor.
		ImGuiManagerImpl(const ImGuiManagerImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		ImGuiManagerImpl& operator=(const ImGuiManagerImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief
		* Custom constructor for the ImGuiManagerImpl class.
		* @param cc The clear color for the ImGuiManager.
		*/
		ImGuiManagerImpl(const ImVec4& cc);

		//Default constructors/destructor

		/// @brief Destructor.
		~ImGuiManagerImpl();

		//Member methods

		/**
		* @brief
		* ImGui help marker method to display a tooltip with a description.
		* @param desc The description to display in the tooltip.
		*/
		void HelpMarker(const char* desc);

		//Application specific methods

		/// @brief Create the base window.
		void CreateBaseWindow();
		/// @brief Create the simulation selection window.
		void CreateSelectionWindow();
		/**
		* @brief
		* Create the render window for the simulation.
		* @param texture The texture to render in the window.
		* @param aspect_ratio The aspect ratio of the window.
		*/
		void CreateRenderWindow(
			std::shared_ptr<Graphics::Texture> texture,
			float aspect_ratio);
		/// @brief Create the stats window.
		void CreateStatsWindow();
		/// @brief Create the graph window.
		void CreateGraphWindow();
		/// @brief Create the debug window.
		void CreateDebugWindow();
		/// @brief Create the dockspace for the ImGui windows.
		void CreateDockspace();

		//Member variables

		/// @brief Background color for the ImGuiManager.
		ImVec4 clear_color;
		/// @brief Flag to show the demo window.
		bool show_demo_window;
		/// @brief Flag to show another window.
		bool show_another_window;
		/// @brief Size of the render window.
		ImVec2 render_size;
		/// @brief Application wide ImGui window flags.
		ImGuiWindowFlags window_flags;

		//Simulation variables

		/// @brief Simulation variables for the ImGuiManager.
		ThermodynamicSimulationVariables simulation_variables;
		/// @brief The current state of the simulation.
		std::string current_state;

		//Simulation methods

		/**
		* @brief
		* Get the simulation variables from the ImGuiManager.
		* @return
		* Structure containing the simulation variables.
		*/
		ThermodynamicSimulationVariables GetSimulationVariables() const;

		//Application specific member variables
		/// @brief The name of the dockspace window.
		const std::string dockspace = "Dockspace";
		/// @brief The name of the simulation window.
		const std::string simulation = "Simulation";
		/// @brief The name of the selection window.
		const std::string selection = "Selection";
		/// @brief The name of the render window.
		const std::string render = "Render";
		/// @brief The name of the stats window.
		const std::string stats = "Stats";
		/// @brief The name of the graph window.
		const std::string graph = "Graph";
		/// @brief The name of the debug window.
		const std::string debug = "Debug";
	};

	/**
	* @details
	* Custom constructor for the ImGuiManagerImpl class. Initializes the background
	* color with the cc parameter, the demo window and another window are set to
	* false, the render size is initialized to 0.0f, the window flags
	* are empty, and the current state is set to an empty string.
	*/
	ImGuiManager::ImGuiManagerImpl::ImGuiManagerImpl(const ImVec4& cc) :
		clear_color(cc),
		show_demo_window(false),
		show_another_window(false),
		render_size(ImVec2(0.0f, 0.0f)),
		window_flags(0),
		current_state("")
	{}

	/**
	* @details
	* Shutdown ImGui by shutting down OpenGL, GLFW, and destroying the ImGui context.
	*/
	ImGuiManager::ImGuiManagerImpl::~ImGuiManagerImpl()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	/**
	* @details
	* Create a help marker for ImGui tooltips. Based on the ImGui demo in
	* imgui_demo.cpp.
	*/
	void ImGuiManager::ImGuiManagerImpl::HelpMarker(const char* desc)
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

	/**
	* @details
	* Create the base window of the ImGuiManager. Add the NoDocking flag to the
	* window flags to prevent docking of the main window. Then get the main viewport,
	* assign the position and size of the window to the viewport, and set the viewport.
	* Finally create the Application specific dockspace.
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateBaseWindow()
	{
		ImGuiWindowFlags flags = window_flags | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::Begin(simulation.c_str(), nullptr, flags);
		CreateDockspace();
		ImGui::End();
	}

	/**
	* @details
	* Create the simulation selection window. Creates drop down menus that allow
	* the selection of the simulation type and subsimulation type. Then creates
	* the simulation specific parameters to define the simulation. Finally, adds
	* two buttons to setup and start the simulation.
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateSelectionWindow()
	{
		ImGui::Begin(selection.c_str(), nullptr, window_flags);

		/*
		* Create a combo box for selecting the primary simulation type. The combo
		* box is initially filled with "Select a simulation" followed by,
		* "Thermodynamics", "Simulation 2", and "Simulation 3".
		*/
		static const char* items[] = {
			"Select a simulation",
			"Thermodynamics",
			"Simulation 2",
			"Simulation 3" };
		static int item_current = 0;
		if (ImGui::BeginCombo("##Simulation Type", items[item_current]))
		{
			for (int i = 0; i < IM_ARRAYSIZE(items); i++)
			{
				const bool is_selected = (item_current == i);
				if (ImGui::Selectable(items[i], is_selected)) item_current = i;
				if (is_selected) ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		/*
		* Create a combo box for selecting the subsimulation type based on the
		* primary simulation type. The combo box is initially invisible. When an
		* option that is not the first option ("Select a simulation") is selected,
		* it populates with options listed below for the selected simulation type.
		* 
		* For the thermodynamics simulations, the sub-simulation types are:
		* Microcanonical Ensemble, Canonical Ensemble, and Grand Canonical Ensemble.
		* 
		* Each of these options will have a description info box available when
		* hovered over.
		*/
		if(item_current != 0)
		{
			switch (item_current)
			{
			case 1:
				static const char* thermodynamics[] = {
				"Microcanonical Ensemble",
				"Canonical Ensemble",
				"Grand Canonical Ensemble" };
				static int thermo_item_current = 0;
				std::string description = "";
				if (ImGui::BeginCombo("##Subsimulation Type",
					thermodynamics[thermo_item_current]))
				{
					for (int i = 0; i < IM_ARRAYSIZE(thermodynamics); i++)
					{
						const bool is_selected = (thermo_item_current == i);
						if (ImGui::Selectable(thermodynamics[i], is_selected))
							thermo_item_current = i;
						if (is_selected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				//Generate descriptions of simulations.
				switch (thermo_item_current)
				{
				case 0: //Microcanonical ensemble
					description =
						"A simulation with a constant number of particles, "
						"constant volume, and constant energy.";
					break;
				case 1: //Canonincal ensemble
					description =
						"A simulation with a constant number of particles, "
						"constant volume, and constant temperature.";
					break;
				case 2: //Grand canonical ensemble
					description =
						"A simulation with a constant chemical potential, "
						"constant volume, and constant temperature";
				}

				ImGui::SameLine();
				HelpMarker(description.c_str());

				/*
				* Once the subsimulation is selected, create the corresponding simulation
				* controls.
				* 
				* Every simulation type will have the following controls:
				* Text input for number of particles. Natural numbers >= 0
				* Two sliders for the height and width of the box. Natural numbers > 1
				* A slider for the radius of the particles. Real numbers > 0.1
				* 
				* Microcanonical ensemble:
				* Text input for energy value. Real numbers >= 0
				*
				* Canonical ensemble:
				* Text input for the temperature. Real numbers >= 0
				*
				* Grand canonical ensemble
				* Text input for chemical potential. Natural numbers >= 0
				* Text input for the temperature. Real numbers >= 0
				*/
				int flags = ImGuiComboFlags_WidthFitPreview;
				const int min_particles = 1;
				const int min_box_size = 10;
				const int max_box_size = 100;
				const float min_radius = 0.005f;
				const float max_radius = 0.10f;
				const float min_energy = 0.0f;
				const float min_temp = 0.0f;
				const float min_chem_pot = 0.0f;

				ImGui::InputInt("# Particles", &simulation_variables.num_particles);
				ImGui::SliderInt(
					"% Box Height",
					&simulation_variables.box_height_perc,
					min_box_size,
					max_box_size);
				ImGui::SliderInt(
					"% Box Width",
					&simulation_variables.box_width_perc,
					min_box_size,
					max_box_size);
				ImGui::SliderFloat(
					"Radius",
					&simulation_variables.radius,
					min_radius,
					max_radius);

				switch (thermo_item_current)
				{
				case 0: //Microcanonical ensemble
					ImGui::InputFloat(
						"Energy (J)",
						&simulation_variables.energy_value,
						0.0f,
						0.0f,
						"%.3f",
						flags);
					break;
				case 1: //Canonical ensemble
					ImGui::InputFloat(
						"Temp (K)",
						&simulation_variables.temperature,
						0.0f,
						0.0f,
						"%.3f",
						flags);
					break;
				case 2: //Grand canonical ensemble
					ImGui::InputFloat(
						"Chem Potential (J/part)",
						&simulation_variables.chem_potential,
						0.0f,
						0.0f,
						"%.3f",
						flags);
					ImGui::InputFloat(
						"Temp (K)",
						&simulation_variables.temperature,
						0.0f,
						0.0f,
						"%.3f",
						flags);
					break;
				}

				//Ensure that the values are within the correct range
				if (simulation_variables.num_particles < min_particles)
					simulation_variables.num_particles = min_particles;
				if (simulation_variables.box_height_perc < min_box_size)
					simulation_variables.box_height_perc = min_box_size;
				if (simulation_variables.box_width_perc < min_box_size)
					simulation_variables.box_width_perc = min_box_size;
				if (simulation_variables.radius < min_radius)
					simulation_variables.radius = min_radius;
				if (simulation_variables.radius > max_radius)
					simulation_variables.radius = max_radius;
				if (simulation_variables.energy_value < min_energy)
					simulation_variables.energy_value = min_energy;
				if (simulation_variables.temperature < min_chem_pot)
					simulation_variables.temperature = min_chem_pot;

				break;
			};
		}

		/*
		* Add a button to the bottom of the window to start the simulation.
		* The button will be inactive until the primary simulation type is selected.
		*/
		if (item_current != 0)
		{
			if (ImGui::Button("Setup Simulation"))
			{
				current_state = "InitThermoSim";
			}
			if (ImGui::Button("Start Simulation"))
			{
				current_state = "StartThermoSim";
			}
		}
		else
		{
			ImGui::Text("Select a simulation type to begin.");
		}

		ImGui::End();
	}

	/**
	* Creates the render window for the simulation. Takes the provided texture and
	* aspect ratio and scales the texture to fit in the render window. Then
	* converts the image to an ImGui image and displays it in the window.
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateRenderWindow(
		std::shared_ptr<Graphics::Texture> texture,
		float aspect_ratio)
	{
		ImGui::Begin(render.c_str(), nullptr, window_flags);

		//Check if the size of the render window has changed
		ImVec2 size = ImGui::GetContentRegionAvail();
		if (size.x != render_size.x || size.y != render_size.y)
		{
			//If it has, update the texture framebuffer size
			render_size = size;
			texture->SetupFramebufferAndTexture(
				static_cast<int>(size.x),
				static_cast<int>(size.y));
		}

		if (glIsTexture(texture->GetTextureId()))
			ImGui::Image((void*)(intptr_t)texture->GetTextureId(), size);
		//else DebugMessage("Invalid Texture ID.", __func__);

		ImGui::End();
	}

	/**
	* @details
	* Creates the statistics window. WORK IN PROGRESS
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateStatsWindow()
	{
		ImGui::Begin(stats.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	/**
	* @details
	* Creates the graph window. WORK IN PROGRESS
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateGraphWindow()
	{
		ImGui::Begin(graph.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	/**
	* @details
	* Creates the debug window. WORK IN PROGRESS
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateDebugWindow()
	{
		ImGui::Begin(debug.c_str(), nullptr, window_flags);

		/*auto size = DEBUG_MSG.size();
		for (auto s : DEBUG_MSG)
		{
			ImGui::TextWrapped(s.c_str());
		}*/

		ImGui::End();
	}

	/**
	* @details
	* The dockspace will need to be redesigned for each application.
	* 
	* Creates the ImGui dockspace to allow window docking. Defines the structure
	* of the dockspace for each window and locks the windows in place, but allows
	* for resizing.
	*/
	void ImGuiManager::ImGuiManagerImpl::CreateDockspace()
	{
		static ImGuiDockNodeFlags dockspace_flags =
			ImGuiDockNodeFlags_PassthruCentralNode;
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			//Create the dockspace each frame
			auto dockspace_id = ImGui::GetID(dockspace.c_str());
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

			//Generate the layout for the dockspace only once at the beginning
			static auto first_time = true;
			if (first_time)
			{
				first_time = false;

				//Make sure the dockspace has been cleared if it was saved previously
				ImGui::DockBuilderRemoveNode(dockspace_id);
				
				//Create the base node and set it to fill the current window
				ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetWindowSize());
				
				//Split the main dockspace into a left and right half
				/*
				* Counterintuitively, this preserves the base dockspace as a node.
				* So the top left window is actually a node and the base dockspace.
				*/
				auto dockspace_main_id = dockspace_id;
				auto top_right_id = ImGui::DockBuilderSplitNode(
					dockspace_main_id,
					ImGuiDir_Right,
					0.75f,
					nullptr,
					&dockspace_main_id);
				
				//Split the left half into a top and bottom
				auto bot_left_id = ImGui::DockBuilderSplitNode(
					dockspace_main_id,
					ImGuiDir_Down,
					0.5f,
					nullptr,
					&dockspace_main_id);
				
				//Split the right half into a top and bottom
				auto right_sub_id = ImGui::DockBuilderSplitNode(
					top_right_id,
					ImGuiDir_Down,
					0.25f,
					nullptr,
					&top_right_id);

				//Match the window names to the dockspace IDs
				ImGui::DockBuilderDockWindow(selection.c_str(), dockspace_main_id);
				ImGui::DockBuilderDockWindow(render.c_str(), top_right_id);
				ImGui::DockBuilderDockWindow(stats.c_str(), bot_left_id);
				ImGui::DockBuilderDockWindow(graph.c_str(), right_sub_id);
				ImGui::DockBuilderDockWindow(debug.c_str(), right_sub_id);

				ImGui::DockBuilderFinish(dockspace_id);
			}
		}
	}

	/**
	* @details
	* Get the structure containing the simulation variables.
	*/
	ThermodynamicSimulationVariables ImGuiManager::ImGuiManagerImpl::GetSimulationVariables() const
	{
		return simulation_variables;
	}

	/**
	* @details
	* Custom constructor for the ImGuiManager class. Sets the background color,
	* creates the context, style, OpenGL, and GLFW for ImGui, and sets the window
	* flags to the following:
	* NoCollapse
	* NoResize
	* NoMove
	* NoBringToFrontOnFocus
	* NoNavFocus
	*/
	ImGuiManager::ImGuiManager(
		ImVec4 clear_color,
		GLFWwindow* window,
		const char* glsl_version) :
		_impl(std::make_unique<ImGuiManagerImpl>(clear_color))
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

		_impl->window_flags |= ImGuiWindowFlags_NoCollapse;
		_impl->window_flags |= ImGuiWindowFlags_NoResize;
		_impl->window_flags |= ImGuiWindowFlags_NoMove;
		_impl->window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		_impl->window_flags |= ImGuiWindowFlags_NoNavFocus;
	}

	/**
	* @details
	* Default constructor for the ImGuiManager class.
	*/
	ImGuiManager::ImGuiManager() = default;

	/**
	* @details
	* Default destructor for the ImGuiManager class.
	*/
	ImGuiManager::~ImGuiManager() = default;

	/**
	* @details
	* Generate a new frame for ImGui using OpenGL and GLFW.
	*/
	void ImGuiManager::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	/**
	* @details
	* Get the background color for ImGui.
	*/
	ImVec4& ImGuiManager::GetClearColor()
	{
		return _impl->clear_color;
	}

	/**
	* @details
	* Get the size of the ImGui render window.
	*/
	ImVec2& ImGuiManager::GetRenderSize()
	{
		return _impl->render_size;
	}

	/**
	* @details
	* Render the ImGui draw data to the OpenGL window.
	*/
	void ImGuiManager::RenderDrawData()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	/**
	* @details
	* Generate the demo window for ImGui. This is based on the ImGui demo in
	* imgui_demo.cpp.
	*/
	void ImGuiManager::SetupDemoWindow()
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");

		ImGui::Text("This is some useful text.");
		ImGui::Checkbox("Demo Window", &_impl->show_demo_window);
		ImGui::Checkbox("Another Window", &_impl->show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&_impl->clear_color);

		if (ImGui::Button("Button")) counter++;

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text(
			"Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate,
			io.Framerate);
		ImGui::End();

		if (_impl->show_another_window)
		{
			ImGui::Begin("Another Window", &_impl->show_another_window);
			ImGui::Text("Hello from another window!");

			if (ImGui::Button("Close Me")) _impl->show_another_window = false;

			ImGui::End();
		}

		if (_impl->show_demo_window) ImGui::ShowDemoWindow(&_impl->show_demo_window);
	}

	/**
	* @details
	* Generate the application window. The is application dependent and will need
	* to be changed for each application.
	*/
	void ImGuiManager::SetupWindow(
		std::shared_ptr<Graphics::Texture> texture,
		float aspect_ratio)
	{
		_impl->CreateBaseWindow();
		_impl->CreateSelectionWindow();
		_impl->CreateRenderWindow(texture, aspect_ratio);
		_impl->CreateGraphWindow();
		//_impl->CreateDebugWindow();
		_impl->CreateStatsWindow();
	}

	/**
	* @details
	* Check for state change in ImGuiManager. WORK IN PROGRESS
	*/
	std::string& ImGuiManager::CheckForStateChanged()
	{
		return _impl->current_state;
	}

	/**
	* @details
	* Get the simulation variables from the ImGuiManager.
	*/
	ThermodynamicSimulationVariables ImGuiManager::GetSimulationVariables()
	{
		return _impl->GetSimulationVariables();
	}
}