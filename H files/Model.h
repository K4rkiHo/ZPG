// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/cube.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/tree.h"
#include "Models/plain_texture.h"
#include "Models/skycube.h"
#include "Models/triangle.h"

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include <iostream>
#include <fstream>
#include <iomanip>   // std::setprecision, std::setw
#include <vector>

#include <SOIL.h>

#include "ShaderProgram.h"
#include "Composite.h"
#include "Material.h"

class Model {
private:
	GLuint VBO;
	GLuint VAO;
	GLuint textureID;
	GLint idTU;
	ShaderProgram* shaderProgram;
	Material* material;
	int points_numbers;
	Composite composite;
	std::vector<float> obj_data;
	int obj_point_numbers;
	std::string obj_path = "";
public:
	Model();
	Model(const float points[], int size, const char* vertex_shader, const char* fragment_shader, std::string shader_name);
	Model(const float points[], int size, const char* vertex_shader, const char* fragment_shader, std::string shader_name, std::string texture_type);
	Model(const char* vertex_shader, const char* fragment_shader, std::string shader_name, std::string texture_type, std::string obj_path);
	void LoadObjData(std::string obj_path);
	void Create_Model();
	void Create_Model_3D();
	void destroyModel();
	void Draw_Model();
	void Create_VBO(const float points[], int size);
	void Create_VBO_3D();
	void Create_VAO(std::string type);
	void Create_VAO();
	void BindVertexArray();
	void UseProgram();
	void unUseProgram();
	void setmodelMatrix(glm::mat4 matice);
	ShaderProgram* getShaderProgram();
	void addTransform(Transform* transform);
	std::string getObj_path();
};