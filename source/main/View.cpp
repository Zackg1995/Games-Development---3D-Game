#include "View.hpp"



View::View(int widtht, int heightt) {
	width = widtht;
	height = heightt;
	x = 0;
	y = 0;
	z = 0;
}
View::~View() {

}

//Creating an MVP matrix and positioning the camera within the MVP matrix
glm::mat4 getMVPMatrix(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix) {
	glm::mat4 Projection = ProjectionMatrix;

	glm::mat4 View = glm::lookAt(
			glm::vec3(0,100,100),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);//ViewMatrix;
	
	glm::mat4 Model = ModelMatrix;
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
	return mvp;
}


int View::initialise() {

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "My Game", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Ensure we can capture the escape key being pressed below

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide the mouse and enable unlimited mouvement

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen

	glfwPollEvents();

	glfwSetCursorPos(window, width / 2, height / 2);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Set the mouse at the center of the screen

	glfwPollEvents();
	//we set the cursor at the centre so that it always start on our origin (0,0,0)
	glfwSetCursorPos(window, width / 2, height / 2);


	// Dark blue background
	glClearColor(0.0f, 0.0f,0.0f, 0.0f);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//VERTEXBUFFER1
	//Maze plane object implementation
	std::vector<unsigned short> indices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool res = loadAssImp("Assets/MazePlane.obj", indices, vertices1, uvs, normals);

	std::cout << vertices1.size() << std::endl;

		for (int j = 0; j < vertices1.size(); j++) {
			std::cout << "Position: " << vertices1[j].x << "  " << vertices1[j].y << "  " << vertices1[j].z << std::endl;
		}

	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size()*sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);
	calculateBoundingBox();

	for (int i = 0; i < vertices1.size(); i++) {
		colors1.push_back(glm::vec3(0.0, 1.0, 0.0));
	}

	std::cout << colors1.size() << std::endl;

	glGenBuffers(1, &colorbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
	glBufferData(GL_ARRAY_BUFFER, colors1.size() * sizeof(glm::vec3), &colors1[0], GL_STATIC_DRAW);
	//End of mazeplane object implementation

	
	//VERTEXBUFFER2
	//left wall object implementation
	bool res2 = loadAssImp("Assets/MazeWallRight.obj", indices, vertices2, uvs, normals);
	std::cout << vertices2.size() << std::endl;

	for (int j = 0; j < vertices2.size(); j++) {
		std::cout << "Position: " << vertices2[j].x << "  " << vertices2[j].y << "  " << vertices2[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices2.size(); i++) {
		colors2.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors2.size() << std::endl;

	glGenBuffers(1, &colorbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer2);
	glBufferData(GL_ARRAY_BUFFER, colors2.size() * sizeof(glm::vec3), &colors2[0], GL_STATIC_DRAW);
	//End of leftwall object implementation

	//VERTEXBUFFER3
	//right wall implementation
	bool res3 = loadAssImp("Assets/MazeWallLeft.obj", indices, vertices3, uvs, normals);
	std::cout << vertices3.size() << std::endl;

	for (int j = 0; j < vertices3.size(); j++) {
		std::cout << "Position: " << vertices3[j].x << "  " << vertices3[j].y << "  " << vertices3[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
	glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices3.size(); i++) {
		colors3.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors3.size() << std::endl;

	glGenBuffers(1, &colorbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer3);
	glBufferData(GL_ARRAY_BUFFER, colors3.size() * sizeof(glm::vec3), &colors3[0], GL_STATIC_DRAW);
	//end of left wall implementation

	//VERTEXBUFFER4
	//player cube implementation
	bool res4 = loadAssImp("Assets/player.obj", indices, vertices4, uvs, normals);
	std::cout << vertices4.size() << std::endl;

	for (int j = 0; j < vertices4.size(); j++) {
		std::cout << "Position: " << vertices4[j].x << "  " << vertices4[j].y << "  " << vertices4[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
	glBufferData(GL_ARRAY_BUFFER, vertices4.size() * sizeof(glm::vec3), &vertices4[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices4.size(); i++) {
		colors4.push_back(glm::vec3(1.0, 0.0, 0.0));
	}

	std::cout << colors4.size() << std::endl;

	glGenBuffers(1, &colorbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer4);
	glBufferData(GL_ARRAY_BUFFER, colors4.size() * sizeof(glm::vec3), &colors4[0], GL_STATIC_DRAW);
	//end of left wall implementation


	//top wall implementation
	bool res5 = loadAssImp("Assets/MazeWallTop.obj", indices, vertices5, uvs, normals);
	std::cout << vertices5.size() << std::endl;

	for (int j = 0; j < vertices5.size(); j++) {
		std::cout << "Position: " << vertices5[j].x << "  " << vertices5[j].y << "  " << vertices5[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer5);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
	glBufferData(GL_ARRAY_BUFFER, vertices5.size() * sizeof(glm::vec3), &vertices5[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices5.size(); i++) {
		colors5.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors5.size() << std::endl;

	glGenBuffers(1, &colorbuffer5);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer5);
	glBufferData(GL_ARRAY_BUFFER, colors5.size() * sizeof(glm::vec3), &colors5[0], GL_STATIC_DRAW);
	//end of top wall implementation

	//Bottom Wall Implementation
	bool res6 = loadAssImp("Assets/MazeWallBottom.obj", indices, vertices6, uvs, normals);
	std::cout << vertices6.size() << std::endl;

	for (int j = 0; j < vertices6.size(); j++) {
		std::cout << "Position: " << vertices6[j].x << "  " << vertices6[j].y << "  " << vertices6[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer6);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
	glBufferData(GL_ARRAY_BUFFER, vertices6.size() * sizeof(glm::vec3), &vertices6[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices6.size(); i++) {
		colors6.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors6.size() << std::endl;

	glGenBuffers(1, &colorbuffer6);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer6);
	glBufferData(GL_ARRAY_BUFFER, colors6.size() * sizeof(glm::vec3), &colors6[0], GL_STATIC_DRAW);
	//End of bottom wall implementation

	//Middle Wall Implementation part 1
	bool res7 = loadAssImp("Assets/MiddleWalls1.obj", indices, vertices7, uvs, normals);
	std::cout << vertices7.size() << std::endl;

	for (int j = 0; j < vertices7.size(); j++) {
		std::cout << "Position: " << vertices7[j].x << "  " << vertices7[j].y << "  " << vertices7[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer7);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer7);
	glBufferData(GL_ARRAY_BUFFER, vertices7.size() * sizeof(glm::vec3), &vertices7[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices7.size(); i++) {
		colors7.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors7.size() << std::endl;

	glGenBuffers(1, &colorbuffer7);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer7);
	glBufferData(GL_ARRAY_BUFFER, colors7.size() * sizeof(glm::vec3), &colors7[0], GL_STATIC_DRAW);
	//end of part 1 wall implementation

	//Middle wall implementation part 2
	bool res8 = loadAssImp("Assets/MiddleWalls2.obj", indices, vertices8, uvs, normals);
	std::cout << vertices8.size() << std::endl;

	for (int j = 0; j < vertices8.size(); j++) {
		std::cout << "Position: " << vertices8[j].x << "  " << vertices8[j].y << "  " << vertices8[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer8);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer8);
	glBufferData(GL_ARRAY_BUFFER, vertices8.size() * sizeof(glm::vec3), &vertices8[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices8.size(); i++) {
		colors8.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors8.size() << std::endl;

	glGenBuffers(1, &colorbuffer8);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer8);
	glBufferData(GL_ARRAY_BUFFER, colors8.size() * sizeof(glm::vec3), &colors8[0], GL_STATIC_DRAW);
	//end of middle wall two implementation

	//middle wall 3 implementation
	bool res9 = loadAssImp("Assets/MiddleWalls3.obj", indices, vertices9, uvs, normals);
	std::cout << vertices9.size() << std::endl;

	for (int j = 0; j < vertices9.size(); j++) {
		std::cout << "Position: " << vertices9[j].x << "  " << vertices9[j].y << "  " << vertices9[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer9);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer9);
	glBufferData(GL_ARRAY_BUFFER, vertices9.size() * sizeof(glm::vec3), &vertices9[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices9.size(); i++) {
		colors9.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors9.size() << std::endl;

	glGenBuffers(1, &colorbuffer9);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer9);
	glBufferData(GL_ARRAY_BUFFER, colors9.size() * sizeof(glm::vec3), &colors9[0], GL_STATIC_DRAW);
	//end of middle wall three implementation

	//collectable
	bool res10 = loadAssImp("Assets/collectable1.obj", indices, vertices10, uvs, normals);
	std::cout << vertices10.size() << std::endl;

	for (int j = 0; j < vertices10.size(); j++) {
		std::cout << "Position: " << vertices10[j].x << "  " << vertices10[j].y << "  " << vertices10[j].z << std::endl;
	}

	glGenBuffers(1, &vertexbuffer10);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer10);
	glBufferData(GL_ARRAY_BUFFER, vertices10.size() * sizeof(glm::vec3), &vertices10[0], GL_STATIC_DRAW);

	for (int i = 0; i < vertices10.size(); i++) {
		colors10.push_back(glm::vec3(0.0, 0.0, 1.0));
	}

	std::cout << colors10.size() << std::endl;

	glGenBuffers(1, &colorbuffer10);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer10);
	glBufferData(GL_ARRAY_BUFFER, colors10.size() * sizeof(glm::vec3), &colors10[0], GL_STATIC_DRAW);
	//end of collectable implementation


	programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
    MatrixID1 = glGetUniformLocation(programID, "MVP");
	

	return 1;
}

//Creating a method for the user to be able to move the character through arrow keys
void View::getKeys() {
	std::cout << "Update values: " << std::endl;
	//movement right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE) {
		x = x + 0.01;
		std::cout << "X pressed: " << x << std::endl;
	}
	//movement left
	if (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE) {
		x = x - 0.01;
		std::cout << "X pressed: " << x << std::endl;
	}
	//movement up
	if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE) {
		z = z - 0.01;
		std::cout << "X pressed: " << x << std::endl;
	}
	//movement down
	if (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE) {
		z = z + 0.01;
		std::cout << "X pressed: " << x << std::endl;
	}
}

//attempted creation of bounding box
void View::calculateBoundingBox(){
	/*
	boundingBoxMin1. = boundingBoxMax1.x = vertices2[0].x;
	boundingBoxMin1.y = boundingBoxMax1.y = vertices2[0].y;
	boundingBoxMin1Z = boundingBoxMax1Z = vertices2[0].z;

	for (int i = 0; i < vertices2.size(); i++) {
	
	}*/
}

void View::update() {



	do {

		getKeys();
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT);
		computeMatricesFromInputs(window, width, height);
	
		// creation of the first model matrix
		glUseProgram(programID);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = glm::lookAt(

			glm::vec3(0, 13, 5),  //x
			glm::vec3(0, 0, 0),	   //y
			glm::vec3(0, 10, 0)    //z
		);
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 mvp1 = ProjectionMatrix * ViewMatrix * ModelMatrix;
		
		//******************* GEOMETRY 1
		// Draw nothing, see you in tutorial 2 !
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp1[0][0]);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);
		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, vertices1.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);
															 
		//2nd model matrix													  
		glm::mat4 ModelMatrix2 = glm::mat4(1.0);
		glm::mat4 mvp2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;
		// Draw nothing, see you in tutorial 2 !
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp2[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer2);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices2.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

	//ModelMatrix 3		
		glm::mat4 ModelMatrix3 = glm::mat4(1.0);
		glm::mat4 mvp3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;
		// Draw nothing, see you in tutorial 2 !
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp3[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer3);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices3.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		//Model matrix 4
		glm::mat4 ModelMatrix4 = glm::translate(glm::vec3(x, y, z));//glm::mat4(1.0);
		//std::cout << "counter: " << x << std::endl;
		glm::mat4 mvp4 = ProjectionMatrix * ViewMatrix * ModelMatrix4;
		

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp4[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer4);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		


		glDrawArrays(GL_TRIANGLES, 0, vertices4.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		//model matrix 5
		glm::mat4 ModelMatrix5 = glm::mat4(1.0);
		glm::mat4 mvp5 = ProjectionMatrix * ViewMatrix * ModelMatrix5;

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp5[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer5);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		glDrawArrays(GL_TRIANGLES, 0, vertices5.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		//model matrix 6
		glm::mat4 ModelMatrix6 = glm::mat4(1.0);
		glm::mat4 mvp6 = ProjectionMatrix * ViewMatrix * ModelMatrix6;

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp6[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer6);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices6.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		//Model matrix 7
		glm::mat4 ModelMatrix7 = glm::mat4(1.0);
		glm::mat4 mvp7 = ProjectionMatrix * ViewMatrix * ModelMatrix7;

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp7[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer7);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer7);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		glDrawArrays(GL_TRIANGLES, 0, vertices7.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);


		//model Matrix 8
		glm::mat4 ModelMatrix8 = glm::mat4(1.0);
		glm::mat4 mvp8 = ProjectionMatrix * ViewMatrix * ModelMatrix8;

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp8[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer8);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer8);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		glDrawArrays(GL_TRIANGLES, 0, vertices8.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);


		//model matrix 9
		glm::mat4 ModelMatrix9 = glm::mat4(1.0);
		glm::mat4 mvp9 = ProjectionMatrix * ViewMatrix * ModelMatrix9;

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp9[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer9);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer9);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		glDrawArrays(GL_TRIANGLES, 0, vertices9.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		//model matrix 10
		glm::mat4 ModelMatrix10 = glm::mat4(1.0);
		glm::mat4 mvp10 = ProjectionMatrix * ViewMatrix * ModelMatrix10;

		// Draw nothing, see you in tutorial 2 ! 
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp10[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer10);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the vertex shader.
			3,                  // size
			GL_FLOAT,     // type
			GL_FALSE,    // normalized?
			0,                   // stride
			(void*)0           // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer10);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		glDrawArrays(GL_TRIANGLES, 0, vertices10.size()); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3
		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();




	} // Check if the ESC key was pressed or the window was closed
	
	
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer1);
	glDeleteBuffers(1, &vertexbuffer2);
	glDeleteBuffers(1, &vertexbuffer3);
	glDeleteBuffers(1, &vertexbuffer4);
	glDeleteBuffers(1, &colorbuffer1);
	glDeleteBuffers(1, &colorbuffer2);
	glDeleteBuffers(1, &colorbuffer3);
	glDeleteBuffers(1, &colorbuffer4);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

}




