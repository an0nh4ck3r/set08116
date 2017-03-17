#version 440

// Spot light data
struct spot_light {
  vec4 light_colour;
  vec3 position;
  vec3 direction;
  float constant;
  float linear;
  float quadratic;
  float power;
};

// Material data
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Spot light being used in the scene
uniform spot_light spot;
// Material of the object being rendered
uniform material mat;
// Position of the eye (camera)
uniform vec3 eye_pos;
// Texture to sample from
uniform sampler2D tex;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {
  // *********************************
  // Calculate direction to the light
  vec3 l = normalise(spot.position - position);
  // Calculate distance to light
  float d = distance(spot.position, position);
  // Calculate attenuation value
  float af = (spot.constant + (spot.linear*d) + (spot.quadratic*d*d));
  // Calculate spot light intensity
  float spintensity = pow(max(dot(-spot.direction, l), 0), spot.power);
  // Calculate light colour
  vec4 light_colour = spot.light_colour/af;
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos-position);
  // Now use standard phong shading but using calculated light colour and direction
  // - note no ambient



   // Calculate diffuse component
  float kd = max(dot(normal, l), 0.0);
  vec4 diffuse = kd * (mat.diffuse_reflection * light_colour);
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos-position);
  // Calculate half vector
  vec3 half_vector = normalize(l + view_dir);
  // Calculate specular component
  float ks = pow(max(dot(normal, half_vector), 0.0), mat.shininess);
  vec4 specular = ks * (mat.specular_reflection * light_colour);
  // Sample texture
  vec4 tex_colour = texture(tex, tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  // Calculate final colour - remember alpha
  vec4 secondary = specular;
  colour = primary * tex_colour + secondary;
  colour.a = 1.0;





  // *********************************
}