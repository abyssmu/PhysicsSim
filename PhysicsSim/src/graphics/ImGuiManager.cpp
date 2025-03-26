#include "ImGuiManager.h"

#include "utils/GlfwAndDebugIncludes.h"
#include "graphics/Texture.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

	struct ImGuiManager::ImGuiManagerImpl
	{
		//Deleted constructors
		ImGuiManagerImpl() = delete;
		ImGuiManagerImpl(const ImGuiManagerImpl& other) = delete;
		ImGuiManagerImpl& operator=(const ImGuiManagerImpl& other) = delete;
		ImGuiManagerImpl(const ImGuiManagerImpl&& other) = delete;
		ImGuiManagerImpl& operator=(const ImGuiManagerImpl&& other) = delete;

		//Custom constructors
		ImGuiManagerImpl(const ImVec4& cc);

		//Default constructors/destructor
		~ImGuiManagerImpl();

		//Member methods
		void HelpMarker(const char* desc);

		//Application specific methods
		void CreateBaseWindow();
		void CreateSelectionWindow();
		void CreateRenderWindow(
			std::shared_ptr<Scene::Texture> texture,
			float aspect_ratio);
		void CreateStatsWindow();
		void CreateGraphWindow();
		void CreateDebugWindow();
		void CreateDockspace();

		//Member variables
		ImVec4 clear_color;
		bool show_demo_window;
		bool show_another_window;
		ImVec2 render_size;
		ImGuiWindowFlags window_flags;

		//Simulation variables
		ThermodynamicSimulationVariables simulation_variables;
		std::string current_state;

		//Simulation methods
		ThermodynamicSimulationVariables GetSimulationVariables() const;
		bool CheckForStateChanged();

		//Application specific member variables
		const std::string dockspace = "Dockspace";
		const std::string simulation = "Simulation";
		const std::string selection = "Selection";
		const std::string render = "Render";
		const std::string stats = "Stats";
		const std::string graph = "Graph";
		const std::string debug = "Debug";
	};

	ImGuiManager::ImGuiManagerImpl::ImGuiManagerImpl(const ImVec4& cc) :
		clear_color(cc),
		show_demo_window(false),
		show_another_window(false),
		render_size(ImVec2(0.0f, 0.0f)),
		window_flags(0),
		current_state("")
	{}

	ImGuiManager::ImGuiManagerImpl::~ImGuiManagerImpl()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

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

	/*
	* Start application specific methods.
	* These functions will need to be rewritten and renamed since they depend
	* on the specifics of the application being built.
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
						"A simulation with a constant number of particles,"
						"constant volume, and constant energy.";
					break;
				case 1: //Canonincal ensemble
					description =
						"A simulation with a constant number of particles,"
						"constant volume, and constant temperature.";
					break;
				case 2: //Grand canonical ensemble
					description =
						"A simulation with a constant chemical potential,"
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

	void ImGuiManager::ImGuiManagerImpl::CreateRenderWindow(
		std::shared_ptr<Scene::Texture> texture,
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
		else DebugMessage("Invalid Texture ID.", __func__);

		ImGui::End();
	}

	void ImGuiManager::ImGuiManagerImpl::CreateStatsWindow()
	{
		ImGui::Begin(stats.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	void ImGuiManager::ImGuiManagerImpl::CreateGraphWindow()
	{
		ImGui::Begin(graph.c_str(), nullptr, window_flags);
		ImGui::End();
	}

	void ImGuiManager::ImGuiManagerImpl::CreateDebugWindow()
	{
		ImGui::Begin(debug.c_str(), nullptr, window_flags);

		auto size = DEBUG_MSG.size();
		for (auto s : DEBUG_MSG)
		{
			ImGui::TextWrapped(s.c_str());
		}

		ImGui::End();
	}

	/*
	* The general structure of this method will stay the same since it builds the
	* starting dockspace for the application.
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
	//End Application specific methods

	//Simulation methods
	ThermodynamicSimulationVariables ImGuiManager::ImGuiManagerImpl::GetSimulationVariables() const
	{
		return simulation_variables;
	}

	bool ImGuiManager::ImGuiManagerImpl::CheckForStateChanged()
	{
		return false;
	}

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

	ImGuiManager::ImGuiManager() = default;
	ImGuiManager::~ImGuiManager() = default;

	void ImGuiManager::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	ImVec4& ImGuiManager::GetClearColor()
	{
		return _impl->clear_color;
	}

	ImVec2& ImGuiManager::GetRenderSize()
	{
		return _impl->render_size;
	}

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

	/*
	* This is another application specific function. The functions used inside will
	* need to be updated according to the functions declared in the PIMPL idiom.
	*/
	void ImGuiManager::SetupWindow(
		std::shared_ptr<Scene::Texture> texture,
		float aspect_ratio)
	{
		_impl->CreateBaseWindow();
		_impl->CreateSelectionWindow();
		_impl->CreateRenderWindow(texture, aspect_ratio);
		_impl->CreateGraphWindow();
		//_impl->CreateDebugWindow();
		_impl->CreateStatsWindow();
	}

	std::string& ImGuiManager::CheckForStateChanged()
	{
		return _impl->current_state;
	}

	ThermodynamicSimulationVariables ImGuiManager::GetSimulationVariables()
	{
		return _impl->GetSimulationVariables();
	}
}