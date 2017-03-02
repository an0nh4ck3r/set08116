#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
texture tex;
texture tex2;
texture tex3;
texture tex4;
point_light light;
free_camera freecam;
bool initialise() {
	//Set input mode
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}
bool load_content() {
  // Create plane mesh
  meshes["plane"] = mesh(geometry_builder::create_plane());
  // Pyramid
  meshes["pyra"] = mesh(geometry_builder::create_pyramid(vec3(1.0f, 1.0f, 1.0f)));
  // Cylinder
  meshes["cylinder"] = mesh(geometry_builder::create_cylinder(unsigned int(10), unsigned int(10), vec3(1.0f, 1.0f, 1.0f)));
  // Torus
  meshes["torus"] = mesh(geometry_builder::create_torus(unsigned int(10), unsigned int(10), float(1.0f), float(1.0f)));
  // Transforms for the geometry
  meshes["plane"].get_transform().scale = vec3(5.0f);
  meshes["pyra"].get_transform().scale = vec3(6.0f);
  meshes["pyra"].get_transform().position = vec3(-10.0f, 5.0f, -15.0f);
  meshes["cylinder"].get_transform().scale = vec3(3.0f, 25.0f, 3.0f);
  meshes["cylinder"].get_transform().position = vec3(1.0f, 2.5f, -25.0f);
  meshes["torus"].get_transform().scale = vec3(4.0f, 1.0f, 4.0f);
  meshes["torus"].get_transform().position = vec3(-11.0f, 1.0f, -16.0f);
  // Set materials for the plane
  meshes["plane"].get_material().set_emissive(vec4(0.3f, 0.3f, 0.3f, 0.3f));
  meshes["plane"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["plane"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["plane"].get_material().set_shininess(25.0f);
  // Set materials for pyra
  meshes["pyra"].get_material().set_emissive(vec4(1.0f, 0.5f, 0.0f, 1.0f));
  meshes["pyra"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["pyra"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["pyra"].get_material().set_shininess(25.0f);
  // Set materials for cylinder
  meshes["cylinder"].get_material().set_emissive(vec4(0.3f, 0.3f, 0.3f, 1.0f));
  meshes["cylinder"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["cylinder"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["cylinder"].get_material().set_shininess(25.0f);
  // Set materials for torus
  meshes["torus"].get_material().set_emissive(vec4(0.3f, 0.3f, 0.3f, 1.0f));
  meshes["torus"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["torus"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  meshes["torus"].get_material().set_shininess(25.0f);
  // Load texture
  tex = texture("textures/stonygrass.jpg");
  tex2 = texture("textures/stone 1.png");
  tex3 = texture("textures/fire2.jpg");
  tex4 = texture("textures/bark-1024.jpg");
  // Set lighting values pos
  light.set_position(vec3(-10.0f, 15.0f, -15.0f));
  // Set light colour white
  light.set_light_colour(vec4(1.0f, 0.5f, 0.0f, 1.0f));
  // Set range to 200
  light.set_range(2000);
  light.set_constant_attenuation(0.1);
  // Load in shaders
  eff.add_shader("shaders/Coursework.vert", GL_VERTEX_SHADER);
  eff.add_shader("shaders/Coursework.frag", GL_FRAGMENT_SHADER);
  // Build effect
  eff.build();

  // Set camera properties
  freecam.set_position(vec3(10.0f, 10.0f, 10.0f));
  freecam.set_target(vec3(-100.0f, 0.0f, -100.0f));
  auto aspect = static_cast<float>(renderer::get_screen_width()) / static_cast<float>(renderer::get_screen_height()); 
  freecam.set_projection(quarter_pi<float>(), aspect, 2.414f, 1000.0f);
  return true;
}

bool update(float delta_time) {

	static float range = 20.0f;
	// The ratio of pixels to rotation - remember the fov
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() * renderer::get_screen_aspect()) / static_cast<float>(renderer::get_screen_height());
	static double cursor_x = 0.0;
	static double cursor_y = 0.0;
	double current_x;
	double current_y;
	// Get the current cursor position
	glfwGetCursorPos(renderer::get_window(), &current_x, &current_y);
	// Calculate delta of cursor positions from last frame
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	delta_x *= ratio_width;
	delta_y *= ratio_height;
	// Rotate cameras by delta
	freecam.rotate(delta_x, -delta_y);
	// Use keyboard to move the camera - WASD
	vec3 translation(0.0f, 0.0f, 0.0f);
	if (glfwGetKey(renderer::get_window(), 'W')) {
		translation.z += 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'S')) {
		translation.z -= 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'A')) {
		translation.x -= 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'D')) {
		translation.x += 5.0f * delta_time;
	}
	// Move camera
	freecam.move(translation);
	// Set light range
	light.set_range(range);
	// Update the camera
	freecam.update(delta_time);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;
	return true;
}

bool render() {
  // Render meshes
  for (auto &e : meshes) {
    auto m = e.second;
    // Bind effect
    renderer::bind(eff);
    // Create MVP matrix
    auto M = m.get_transform().get_transform_matrix();
    auto V = freecam.get_view();
    auto P = freecam.get_projection();
    auto MVP = P * V * M;
    // Set MVP matrix uniform
    glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
	// Set M matrix uniform 
	glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
	// Set N matrix uniform
	glUniformMatrix3fv(eff.get_uniform_location("N"),1,GL_FALSE,value_ptr(m.get_transform().get_normal_matrix()));
	// Bind material
	renderer::bind(m.get_material(), "mat");
	// Bind light
	renderer::bind(light, "point");

    // *********************************
    // Bind texture to renderer
	if (e.first == "plane") {
		renderer::bind(tex, 0);
	}
	if (e.first == "torus"){
		renderer::bind(tex2, 0);
	}
	if (e.first == "pyra") {
		renderer::bind(tex3, 0);
	}
	if (e.first == "cylinder") {
		renderer::bind(tex4, 0);
	}
    // Set the texture value for the shader here
	glUniform1i(eff.get_uniform_location("tex"), 0);
	// Set eye position 
	glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(freecam.get_position()));
    // *********************************
    // Render mesh
    renderer::render(m);
  }

  return true;
}

void main() {
  // Create application
  app application("35_Geometry_Builder");
  // Set load content, update and render methods
  application.set_load_content(load_content);
  application.set_initialise(initialise);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}