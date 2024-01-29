// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Model.h"

Model::Model()
{

}

Model::Model(const float points[], int size, const char* vertex_shader, const char* fragment_shader, std::string shader_name)
{
	this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader, shader_name);
	Create_VBO(points, size);
	Create_VAO("normal");
}

Model::Model(const float points[], int size, const char* vertex_shader, const char* fragment_shader, std::string shader_name, std::string texture_type)
{
	this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader, shader_name);
	Create_VBO(points, size);
	if (texture_type == "texture")
	{
		Create_VAO(texture_type);
	}
	if (texture_type == "skybox")
	{
		Create_VAO(texture_type);
	}
}

Model::Model(const char* vertex_shader, const char* fragment_shader, std::string shader_name, std::string texture_type, std::string obj_path)
{
	this->obj_path = obj_path;
	this->obj_data = obj_data;
	this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader, shader_name);
	LoadObjData(obj_path);
	Create_VBO_3D();
	Create_VAO("texture");
}

void Model::LoadObjData(std::string obj_path)
{
	this->obj_point_numbers = 0;
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // sloučení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
	const aiScene* scene = importer.ReadFile(obj_path.c_str(), importOptions);
	if (scene) {
		aiMesh* mesh = scene->mMeshes[0];
		this->obj_point_numbers = mesh->mNumFaces * 3;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (unsigned int j = 0; j < 3; j++)
			{
				this->obj_data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
				this->obj_data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
				this->obj_data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
				this->obj_data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
				this->obj_data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
				this->obj_data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
				this->obj_data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
				this->obj_data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
			}
		}
	}
}

void Model::Create_Model()
{
	UseProgram();
	setmodelMatrix(this->composite.traverse());
	BindVertexArray();

	if (this->obj_path != "")
	{
		glDrawArrays(GL_TRIANGLES, 0, this->obj_point_numbers);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, this->points_numbers / 6);
	}
}

void Model::Create_Model_3D()
{
	UseProgram();
	setmodelMatrix(this->composite.traverse());
	BindVertexArray();
	glDrawArrays(GL_TRIANGLES, 0, this->obj_point_numbers);
}

void Model::destroyModel()
{
	unUseProgram();
}

void Model::Draw_Model()
{
	glDrawArrays(GL_TRIANGLES, 0, this->points_numbers / 6);
}

void Model::Create_VBO(const float points[], int size)
{
	this->VBO = 0;
	glGenBuffers(1, & this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
	this->points_numbers = size;
}

void Model::Create_VBO_3D()
{
	this->VBO = 0;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->obj_data.size() * sizeof(float), &this->obj_data[0], GL_STATIC_DRAW);
}

void Model::Create_VAO(std::string type)
{
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	if (type == "texture")
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
	}
	if (type == "normal")
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	if (type == "skybox")
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	}
}

void Model::Create_VAO()
{
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Model::BindVertexArray()
{
	glBindVertexArray(this->VAO);
}

void Model::UseProgram()
{
	this->shaderProgram->UseShaderProgram();
}

void Model::unUseProgram()
{
	this->shaderProgram->unUseShaderProgram();
}

void Model::setmodelMatrix(glm::mat4 matice)
{
	this->shaderProgram->setSpecs("modelMatrix", matice);
}

ShaderProgram * Model::getShaderProgram()
{
	return this->shaderProgram;
}

void Model::addTransform(Transform * transformation)
{
	this->composite.Add(transformation);
}

std::string Model::getObj_path()
{
	return this->obj_path;
}


