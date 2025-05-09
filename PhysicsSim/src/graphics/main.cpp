/**
* @file main.cpp
* @brief
* Main function for the graphics library. Used as a testing environment.
*/

#include "objects/Circle.hpp"
#include "objects/Box.hpp"
#include "objects/Quad.hpp"
#include "Scene.hpp"
#include "ThermodynamicsRenderItems.hpp"

#include "spdlog/spdlog.h"

#include <random>

/// @brief Create a test scene to work with.
static std::shared_ptr<Graphics::Scene> CreateTestScene()
{
	// Create a scene manager as a unique pointer.
	int width = 1280;
	int height = 720;
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float alpha = 1.00f;
	float bg_color[4] = { red, green, blue, alpha };
	auto scene = std::make_shared<Graphics::Scene>(
		"PhysicsSim",
		width,
		height,
		bg_color);
	if (scene->GetErrorStatus())
	{
		spdlog::error("Error creating scene");
		return nullptr;
	}

	return scene;
}

/*
* @brief Generate a vector of particles with the following structure:
* x, y, z, padding, red, green, blue, padding, x_scale, y_scale, z_scale, padding
* @param num_particles The number of particles to generate.
* @param radius The radius of the particles.
* @return A vector of particles.
*/
static std::vector<float> GenerateParticles(
	const int num_particles,
	const int width,
	const int height)
{
	/*
	* Generate some particles with the following structure:
	* x, y, z, red, green, blue, x_scale, y_scale, z_scale
	*/
	std::vector<float> particles(num_particles * 12);
	std::random_device rd;
	std::mt19937 gen(rd());
	const float limit = 0.98f;
	std::uniform_real_distribution<float> xdis(-limit, limit);
	std::uniform_real_distribution<float> ydis(-limit, limit);

	for (int i = 0; i < num_particles; i++)
	{
		int offset = i * 12;
		float x = xdis(gen);
		float y = ydis(gen);
		float z = 0.0f;
		float red = 1.0f;
		float green = 1.0f;
		float blue = 1.0f;
		float x_scale = 1.0f;
		float y_scale = 1.0f;
		float z_scale = 1.0f;

		if (width > height) y_scale = static_cast<float>(width) / height;

		particles[offset] = x;
		particles[offset + 1] = y;
		particles[offset + 2] = z;
		particles[offset + 3] = 1.0f;
		particles[offset + 4] = red;
		particles[offset + 5] = green;
		particles[offset + 6] = blue;
		particles[offset + 7] = 1.0f;
		particles[offset + 8] = x_scale;
		particles[offset + 9] = y_scale;
		particles[offset + 10] = z_scale;
		particles[offset + 11] = 1.0f;
	}

	return particles;
}

/// @brief Test the Scene class.
static void TestSceneManager()
{
	auto scene = CreateTestScene();

	// Generic OpenGL loop.
	while (!scene->WindowShouldClose())
	{
		scene->PollEvents();
		scene->Render();
		scene->SwapBuffers();
	}
}

/// @brief Test rendering a simple circle
static void TestCircleRendering()
{
	auto scene = CreateTestScene();
	float radius = 0.15f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float red = 1.0f;
	float green = 0.0f;
	float blue = 0.0f;

	auto circle = std::make_shared<Object::Circle>(
		radius,
		x, y, z,
		red, green, blue);

	while (!scene->WindowShouldClose())
	{
		scene->PollEvents();
		scene->Render();
		circle->Draw(scene->GetShaderID());
		scene->RenderTexture();
		scene->SwapBuffers();
	}
}

/// @brief Test rendering a simple quad.
static void TestQuadRendering()
{
	auto scene = CreateTestScene();
	auto [window_width, window_height] = scene->GetWindowSize();

	float center_x = 0.0f;
	float center_y = 0.0f;
	int width = 1000;
	int height = 100;
	float width_ndc = static_cast<float>(width) / (window_width / 2.0f);
	float height_ndc = static_cast<float>(height) / (window_height / 2.0f);
	float red = 1.0f;
	float green = 0.0f;
	float blue = 0.0f;

	auto quad = std::make_shared<Object::Quad>(
		center_x, center_y,
		width, height,
		window_width, window_height,
		red, green, blue);

	while (!scene->WindowShouldClose())
	{
		scene->PollEvents();
		scene->Render();
		quad->Draw(scene->GetShaderID());
		scene->RenderTexture();
		scene->SwapBuffers();
	}
}

/// @brief Test particle generation and rendering.
static void TestParticleGenerationAndRendering()
{
	auto scene = CreateTestScene();
	auto [width, height] = scene->GetWindowSize();
	int num_particles = 100000;
	// Radius defined in pixels.
	const float radius_px = 1.0f;
	// X-radius converted to normalized device coordinates (NDC) for OpenGL.
	const float radius_ndc = radius_px / (width / 2.0f);

	auto particles = GenerateParticles(num_particles, width, height);

	scene->InitializeSimulationRenderItems(
		Graphics::SimulationTypes::THERMODYNAMICS,
		particles,
		radius_ndc);

	// Generic OpenGL loop.
	while (!scene->WindowShouldClose())
	{
		scene->PollEvents();
		scene->Render();
		scene->RenderSimulationItems();
		scene->RenderTexture();
		scene->SwapBuffers();
	}
}

int main()
{
	//TestSceneManager();
	//TestCircleRendering();
	TestQuadRendering();
	//TestParticleGenerationAndRendering();

	return 0;
}