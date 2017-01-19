#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <iostream>

using namespace std;
using namespace glm;

int main() 
{
	// Just Variables
	vec2 u(1.0f, 0.0f);
	vec2 u2(0.0f, 1.0f);
	vec3 v(1.0f, 0.0f, 0.0f);
	vec3 v2(0.0f, 1.0f, 0.0f);
	vec4 w(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 w2(0.0f, 1.0f, 0.0f, 0.0f);
	//Addition And Subtraction
	vec3 u3(vec2 (1.0f, 0.0f),0.0f);
	vec4 u4(vec2(0.0f, 1.0f),0.0f,0.0f);
	vec2 v3(vec3(1.0f, 0.0f, 0.0f));
	vec4 v4(vec3(0.0f, 1.0f, 0.0f),0.0f);
	vec3 w3(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vec2 w4(vec4(0.0f, 1.0f, 0.0f, 0.0f));
	//Vector Addition 
	vec2 u5(1.0f, 0.0f);
	vec2 u6(0.0f, 1.0f);
	vec2 a = u5 + u6;
	vec2 s = u5 - u6;
	vec3 v5(1.0f, 0.0f, 0.0f);
	vec3 v6(0.0f, 1.0f, 0.0f);
	vec3 a2 = v5 + v6;
	vec3 s2 = v5 - v6;
	vec4 w5(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 w6(0.0f, 1.0f, 0.0f, 0.0f);
	vec4 a3 = w5 + w6;
	vec4 s3 = w5 - w6;
	//Vector Scaling
	vec2 u7(1.0f, 0.0f);
	vec2 u8(0.0f, 1.0f);
	vec2 m = 5.0f * u7;
	vec2 d = u7 / 5.0f;
	vec3 v7(1.0f, 0.0f, 0.0f);
	vec3 v8(0.0f, 1.0f, 0.0f);
	vec3 m2 = 5.0f * v7;
	vec3 d2 = v7 / 5.0f;
	vec4 w7(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 w8(0.0f, 1.0f, 0.0f, 0.0f);
	vec4 m3 = 5.0f * w7;
	vec4 d3 = w7 / 5.0f;
	//Length of a vector
	float l1 = length(u);
	float l2 = length(v);
	float l3 = length(w);
	//Normalising a Vector
	vec2 n1 = normalize(u);
	vec3 n2 = normalize(v);
	vec4 n3 = normalize(w);
	//Dot Product
	float d = dot(u, u2);
	float d2 = dot(v, v2);
	float d3 = dot(w, w2);
	//Projections
	vec2 p = proj(u, u2);
	vec3 p2 = proj(v, v2);
	vec4 p3 = proj(w, w2);
	//Cross Product
	vec3 c = cross(v, v2);
	//Defining a Matrix
	mat4 M(1.0f); // Identiy Matrix
	mat4 M2(2.0f);
	mat4 M3(5.0f);
	//Matrix Addition
	mat4 A = M2 + M3;
	mat4 S = M2 - M3;
	// Matrix Scaling
	mat4 SC = 5.0f * M2;
	mat4 SC2 = M2 / 5.0f;
	// Matrix Multiplication
	mat4 Mu = M2 * M3;
	//Matrix Vector Multi
	mat4 M4(10.0f);
	vec4 vm = M4 * w;
	//Trandformations
	mat4 T = translate(mat4(1.0f), vec3(1.0f, 0.0f, 0.0f));






		


}

