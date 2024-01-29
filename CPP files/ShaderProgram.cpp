// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "ShaderProgram.h"
#include "Camera.h"

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader, std::string shader_name)
{
	this->shader_name = shader_name;
	ShaderLoader(vertex_shader, fragment_shader, &shaderProgramID);
}

void ShaderProgram::UseShaderProgram()
{
	glUseProgram(shaderProgramID);
}

GLuint ShaderProgram::setSpecs(const std::string& uniformName, glm::mat4 matice)
{
	GLuint matrixLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matice[0][0]);
	return matrixLocation;
}

GLuint ShaderProgram::setSpecs(const std::string& uniformName, glm::vec4 lightVec)
{
	GLuint lightID = glGetUniformLocation(shaderProgramID, uniformName.c_str());
	glUniform4fv(lightID, 1, &lightVec[0]);
	return lightID;
}

GLuint ShaderProgram::setSpecs(const std::string& uniformName, glm::vec3 lightVec)
{
	GLuint lightID = glGetUniformLocation(shaderProgramID, uniformName.c_str());
	glUniform3fv(lightID, 1, &lightVec[0]);
	return lightID;
}

GLuint ShaderProgram::setSpecs(const std::string& uniformName, float stats)
{
	GLint lightSpecsID = glGetUniformLocation(shaderProgramID, uniformName.c_str());
	glUniform1f(lightSpecsID, stats);
	return lightSpecsID;
}

GLuint ShaderProgram::setSpecs(const std::string& uniformName, GLuint idTexture)
{
	GLuint TextureSpecsID = glGetUniformLocation(shaderProgramID, uniformName.c_str());
	glUniform1i(TextureSpecsID, idTexture);
	return TextureSpecsID;
}

void ShaderProgram::notify(void* camera, std::string choose)
{
	UseShaderProgram();

	if (choose == "camera")
	{
		Camera* camera_new = static_cast<Camera*>(camera);

		this->setSpecs("camera_dir", camera_new->target);
		this->setSpecs("camera_pos", camera_new->eye);
		this->setSpecs("viewMatrix", camera_new->viewMatrix);
		this->setSpecs("projectionMatrix", camera_new->projectionMatrix);

	}
	if (choose == "light")
	{
		if (shader_name == "phong_lights")
		{
			Light* light_new = static_cast<Light*>(camera);
			this->setSpecs("lightPosition", light_new->lightPos);
			this->setSpecs("lightDirection", light_new->lightDirection);
			this->setSpecs("lightColor", light_new->lightColor);
			this->setSpecs("ambientStrength", light_new->ambientStrength);
			this->setSpecs("specularStrength", light_new->specularStrength);
			this->setSpecs("shininess", light_new->shininess);
			this->setSpecs("typeLight", light_new->typeLight);
			this->setSpecs("light_on", light_new->light_on);
		}
		if (shader_name == "blinn")
		{
			Light* light_new = static_cast<Light*>(camera);
			this->setSpecs("lightPosition", light_new->lightPos);
			this->setSpecs("lightDirection", light_new->lightDirection);
			this->setSpecs("lightColor", light_new->lightColor);
			this->setSpecs("ambientStrength", light_new->ambientStrength);
			this->setSpecs("specularStrength", light_new->specularStrength);
			this->setSpecs("shininess", light_new->shininess);
			this->setSpecs("typeLight", light_new->typeLight);
		}
		if (shader_name == "phong")
		{
			Light* light_new = static_cast<Light*>(camera);
			this->setSpecs("lightColor", light_new->lightColor);
			this->setSpecs("lightPosition", light_new->lightPos);
			this->setSpecs("ambientStrength", light_new->ambientStrength);
			this->setSpecs("specularStrength", light_new->specularStrength);
			this->setSpecs("shininess", light_new->shininess);
		}
		if (shader_name == "phong_bad")
		{
			Light* light_new = static_cast<Light*>(camera);
			this->setSpecs("lightColor", light_new->lightColor);
			this->setSpecs("lightPosition", light_new->lightPos);
			this->setSpecs("ambientStrength", light_new->ambientStrength);
			this->setSpecs("specularStrength", light_new->specularStrength);
			this->setSpecs("shininess", light_new->shininess);
		}
		if (shader_name == "lambert")
		{
			Light* light_new = static_cast<Light*>(camera);
			this->setSpecs("lightColor", light_new->lightColor);
			this->setSpecs("lightPosition", light_new->lightPos);
			this->setSpecs("ambientStrength", light_new->ambientStrength);
		}
		if (shader_name == "constant")
		{
			Light* light_new = static_cast<Light*>(camera);
			this->setSpecs("ambientStrength", light_new->ambientStrength);
		}
		if (shader_name == "default")
		{
			Light* light_new = static_cast<Light*>(camera);
		}
	}
	if (choose == "material")
	{
		Material* material_new = static_cast<Material*>(camera);
		this->setSpecs("objectColor", material_new->materialColor);
		this->setSpecs("repeat", material_new->repeat);
		this->setSpecs("UISky", material_new->textureID);
		this->setSpecs("textureUnitID", material_new->textureID);
	}
}

void ShaderProgram::unUseShaderProgram()
{
	glUseProgram(0);
}