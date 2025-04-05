# Physics Simulator

### Included Projects

This simulator uses [Dear ImGui](https://github.com/ocornut/imgui), [OpenGL](https://www.opengl.org/), and [spdlog](https://github.com/gabime/spdlog) as the foundation for its GUI, graphics rendering, and logging respectively.

### Building

The project was built in Visual Studio 2022. To generate the program's structure clone the repository, open a command prompt and navigate to the project's main folder (`.\PhysicsSim`), type in `premake5 vs2022`, and hit enter. This will build the solution file for the project. Note: I have not tested any other versions of Visual Studio for this build. Feel free to change it, but I have no idea what will or won't work.

Once the solution is created, open it and build the three base projects mentioned above. They are named `imgui_build`, `glfw_build`, and `spdlog_build`. Note: building `spdlog` will generate many warning messages. They can safely be ignored.

Now the project itself can be built and ran. If it is not already, right click the main project (`PhysicsSim`) and make it the target build (`Set as startup project`). At this point, you can either build it or run it in debug or release mode with Visual Studio.

### Functionality

Currently, the functionality is pretty bare as it's a pretty new project of mine. It doesn't do much but generate the beginnings of a thermodynamic particle simulator.

Please see documentation hosted on GitHub pages for the full documentation. (WORK IN PROGRESS)

### Simulators

#### Thermodynamics (Statistical Mechanics)

The following are the three main experiments in stat mech.

##### [Microcanonical Ensemble](https://en.wikipedia.org/wiki/Microcanonical_ensemble)

A system characterized by the constants $N$, $V$, and $E$. The system is isolated, i.e. it cannot exchange energy or particles with the environment. The energy of the entire system is also held constant (energy is entirely conserved), but the energy of an individual particle can change.

##### [Canonical Ensemble](https://en.wikipedia.org/wiki/Canonical_ensemble)

A system characterized by the constants $N$, $V$, and $T$. The system is mostly closed, but can be setup to include a heat bath. This allows only energy exchange with the environment at the barrier of the system.

##### [Grand Canonical Ensemble](https://en.wikipedia.org/wiki/Grand_canonical_ensemble)

A system characterized by the constants $\mu$, $V$, and $T$. The system is considered open and can exchange heat and particles with the environment.

##### Variables

- $N$ number of particles
- $\mu$ chemical potential
- $V$ volume
- $E$ total energy
- $T$ temperature

##### Simulator Variables

These variables are needed to further define the simulation.

- $h$ box height
- $w$ box width
- $r$ particle radius