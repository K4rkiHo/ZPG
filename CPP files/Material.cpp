// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Material.h"


Material::Material(glm::vec4 materialColor)
{
	this->materialColor = materialColor;
}

Material::Material(glm::vec3 materialColor1)
{
	this->materialColor1 = materialColor1;
}

Material::Material(std::vector<const char *> texture_path_vec)
{
	this->texture_path_vec = texture_path_vec;
}

Material::Material(const char* texturePath)
{
	this->texturePath = texturePath;
}

void Material::CreateTexture()
{
	this->textureID = SOIL_load_OGL_texture(this->texturePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->textureID == NULL)
	{
		std::cout << "An error occurred while loading image." << std::endl;
		exit(EXIT_FAILURE);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//opakování textury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	glActiveTexture(GL_TEXTURE1 + this->textureID);
}

void Material::CreateSkyboxTexture()
{
	glActiveTexture(GL_TEXTURE1);
	this->textureID = SOIL_load_OGL_cubemap(this->texture_path_vec[0], this->texture_path_vec[1], this->texture_path_vec[2], this->texture_path_vec[3], this->texture_path_vec[4], this->texture_path_vec[5], SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (this->textureID == NULL) {
		std::cout << "An error occurred while loading CubeMap." << std::endl;
		exit(EXIT_FAILURE);
	}

	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE2);
}

GLuint Material::getTexture()
{
	if (this != nullptr)
	{
		return this->textureID;
	}
	else
	{
		std::cout << "error není TextureID!" << std::endl;
	}
}

void Material::setColor()
{
	notifyObservers(this, "material");
}

void Material::setTexture()
{
	CreateTexture();
	notifyObservers(this, "material");
}

void Material::setTextureSkybox()
{
	CreateSkyboxTexture();
	notifyObservers(this, "material");
}

void Material::setTextureRepeat(float repeat)
{
	this->repeat = repeat;
}

