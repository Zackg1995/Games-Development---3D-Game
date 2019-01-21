#pragma once
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include <glm/gtx/transform.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"
#include "common/text2D.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class View {
private:

	GLFWwindow* window;

	GLuint programID;
	GLuint vertexbuffer1;
	GLuint vertexbuffer2;
	GLuint vertexbuffer3;
	GLuint vertexbuffer4;
	GLuint vertexbuffer5;
	GLuint vertexbuffer6;
	GLuint vertexbuffer7;
	GLuint vertexbuffer8;
	GLuint vertexbuffer9;
	GLuint vertexbuffer10;
	GLuint VertexArrayID;
	GLuint colorbuffer1;
	GLuint colorbuffer2;
	GLuint colorbuffer3;
	GLuint colorbuffer4;
	GLuint colorbuffer5;
	GLuint colorbuffer6;
	GLuint colorbuffer7;
	GLuint colorbuffer8;
	GLuint colorbuffer9;
	GLuint colorbuffer10;
	GLuint MatrixID1;
	double x;
	double y;
	double z;

	//All object vertices
	std::vector<glm::vec3> vertices1;
	std::vector<glm::vec3> vertices2;
	std::vector<glm::vec3> vertices3;
	std::vector<glm::vec3> vertices4;
	std::vector<glm::vec3> vertices5;
	std::vector<glm::vec3> vertices6;
	std::vector<glm::vec3> vertices7;
	std::vector<glm::vec3> vertices8;
	std::vector<glm::vec3> vertices9;
	std::vector<glm::vec3> vertices10;

	//All object colors
	std::vector<glm::vec3> colors1;
	std::vector<glm::vec3> colors2;
	std::vector<glm::vec3> colors3;
	std::vector<glm::vec3> colors4;
	std::vector<glm::vec3> colors5;
	std::vector<glm::vec3> colors6;
	std::vector<glm::vec3> colors7;
	std::vector<glm::vec3> colors8;
	std::vector<glm::vec3> colors9;
	std::vector<glm::vec3> colors10;

	//objectbounding box minimum
	std::vector<glm::vec3> boundingBoxMin1;


	std::vector<glm::vec3> boundingBoxMin2;
	std::vector<glm::vec3> boundingBoxMin3;
	std::vector<glm::vec3> boundingBoxMin4;
	std::vector<glm::vec3> boundingBoxMin5;
	std::vector<glm::vec3> boundingBoxMin6;
	std::vector<glm::vec3> boundingBoxMin7;
	std::vector<glm::vec3> boundingBoxMin8;

	//max object one
	std::vector<glm::vec3> boundingBoxMax1;
	std::vector<glm::vec3> boundingBoxMax1Y;
	std::vector<glm::vec3> boundingBoxMax1Z;
	

	std::vector<glm::vec3> boundingBoxMax2;
	std::vector<glm::vec3> boundingBoxMax3;
	std::vector<glm::vec3> boundingBoxMax4;
	std::vector<glm::vec3> boundingBoxMax5;
	std::vector<glm::vec3> boundingBoxMax6;
	std::vector<glm::vec3> boundingBoxMax7;
	std::vector<glm::vec3> boundingBoxMax8;

	//screen size
	int width;
	int height;

	int numvertices;



public:
	View(int widtht, int heightt);
	~View();
	int initialise();
	void update();
	glm::mat4 getMVPMatrix();
	void getKeys();
	void calculateBoundingBox();




};

