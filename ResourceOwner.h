#pragma once
#include <vector>
#include <string>
#include "Shader.h"
#include "Shader_program.h"
#include "Model.h"
#include "DrawAbleObject.h"

// structure for 20 objects
struct ObjectGroup
{
	Shader *vertexShader = nullptr;
	Shader *fragmentShader = nullptr;
	ShaderProgram *shader = nullptr;
	Model *model = nullptr;
	std::vector<DrawAbleObject *> objects;
	std::string name;
};

class ResourceOwner
{
protected:
	// helpry
	int objectId = 1;
	DrawAbleObject *createModelAndObjectFromFile(const std::string &file, ShaderProgram *shader)
	{
		Model *model = new Model(file.c_str());
		DrawAbleObject *obj = new DrawAbleObject(*model, *shader);
		obj->setId(objectId++);
		return obj;
	}

	DrawAbleObject *createModelAndObjectFromData(float floatsPerVertex, float normals, float uv, int count, const float *data, ShaderProgram *shader)
	{
		Model *model = new Model(floatsPerVertex, normals, uv);
		model->loadData(std::vector<float>(data, data + count));

		DrawAbleObject *obj = new DrawAbleObject(*model, *shader);
		obj->setId(objectId++);
		return obj;
	}

	ObjectGroup *createObjectGroup(const std::string &name, ShaderProgram *shader, const float *data, int count, int instances)
	{
		ObjectGroup *group = new ObjectGroup();
		group->name = name;
		group->shader = shader;

		Model *model = new Model(6, 3, 3);
		model->loadData(std::vector<float>(data, data + count));

		for (int i = 0; i < instances; i++)
		{
			DrawAbleObject *obj = new DrawAbleObject(*model, *shader);
			obj->setId(objectId++);
			group->objects.push_back(obj);
		}
		return group;
	}

	ShaderProgram *createShaderProgram(const std::string &vertexFile, const std::string &fragmentFile, const glm::vec3 &color = glm::vec3(1.0f))
	{
		Shader *vertexShader = new Shader(vertexFile.c_str(), GL_VERTEX_SHADER);
		Shader *fragmentShader = new Shader(fragmentFile.c_str(), GL_FRAGMENT_SHADER);

		ShaderProgram *program = new ShaderProgram();
		program->link(*vertexShader, *fragmentShader);
		program->setObjectColor(color);

		return program;
	}

	// scene 1 purple triangle
	Shader *vertexShaderTrinagle = nullptr;
	Shader *fragmentShaderTriangle = nullptr;
	ShaderProgram *shaderTriangle = nullptr;
	Model *modelTriangle = nullptr;
	DrawAbleObject *objectTriangle = nullptr;

	// scene 2 Spheres
	Shader *vertexShaderSphere1 = nullptr;
	Shader *fragmentShaderSphere1 = nullptr;
	ShaderProgram *shaderSphere1 = nullptr;
	Shader *vertexShaderSphere2 = nullptr;
	Shader *fragmentShaderSphere2 = nullptr;
	ShaderProgram *shaderSphere2 = nullptr;
	Shader *vertexShaderSphere3 = nullptr;
	Shader *fragmentShaderSphere3 = nullptr;
	ShaderProgram *shaderSphere3 = nullptr;
	Shader *vertexShaderSphere4 = nullptr;
	Shader *fragmentShaderSphere4 = nullptr;
	ShaderProgram *shaderSphere4 = nullptr;
	Model *modelSphere = nullptr;
	DrawAbleObject *object1Sphere = nullptr;
	DrawAbleObject *object2Sphere = nullptr;
	DrawAbleObject *object3Sphere = nullptr;
	DrawAbleObject *object4Sphere = nullptr;

	// scene3 forest
	std::vector<ObjectGroup *> groupForScene3;
	Shader *vertexShaderUniverzal = nullptr;
	Shader *fragmentShaderUniverzal = nullptr;
	ShaderProgram *shaderUniverzal = nullptr;
	Shader *vertexShaderSphereForest = nullptr;
	Shader *fragmentShaderSphereForest = nullptr;
	ShaderProgram *shaderSphereForest = nullptr;
	Shader *vertexShaderPlaineForest = nullptr;
	Shader *fragmentShaderPlainForest = nullptr;
	ShaderProgram *shaderPlainForest = nullptr;
	DrawAbleObject *objectForestSphere = nullptr;
	// shrek,fiona and toilet
	Shader *vertexShaderShrekTexture = nullptr;
	Shader *fragmentShaderShrekTexture = nullptr;
	ShaderProgram *shaderShrekTexture = nullptr;
	Model *modelShrek = nullptr;
	DrawAbleObject *shrek = nullptr;
	Shader *vertexShaderFionaTexture = nullptr;
	Shader *fragmentShaderFionaTexture = nullptr;
	ShaderProgram *shaderFionaTexture = nullptr;
	Model *modelFiona = nullptr;
	DrawAbleObject *fiona = nullptr;
	Shader *vertexShaderToiletTexture = nullptr;
	Shader *fragmentShaderToiletTexture = nullptr;
	ShaderProgram *shaderToiletTexture = nullptr;
	Model *modelToilet = nullptr;
	DrawAbleObject *toilet = nullptr;

	// scene 4 Solar system
	Shader *vertexShaderSun = nullptr;
	Shader *fragmentShaderSun = nullptr;
	ShaderProgram *shaderSun = nullptr;
	Shader *vertexShaderEarth = nullptr;
	Shader *fragmentShaderEarth = nullptr;
	ShaderProgram *shaderEarth = nullptr;
	Shader *vertexShaderMoon = nullptr;
	Shader *fragmentShaderMoon = nullptr;
	ShaderProgram *shaderMoon = nullptr;
	Model *modelSolarSystem = nullptr;
	DrawAbleObject *objectSun = nullptr;
	DrawAbleObject *objectEarth = nullptr;
	DrawAbleObject *objectMoon = nullptr;
	DrawAbleObject *objectMercury;
	DrawAbleObject *objectVenus;
	DrawAbleObject *objectMars;
	DrawAbleObject *objectJupiter;
	DrawAbleObject *objectSaturn;
	DrawAbleObject *objectUranus;
	DrawAbleObject *objectNeptune;
	DrawAbleObject *objectMoonJupiter1;
	DrawAbleObject *objectMoonJupiter2;
	DrawAbleObject *objectMoonSaturn1;
	DrawAbleObject *objectMoonSaturn2;
	DrawAbleObject *objectLogin;

	// models from assests
	// scene 5 formula
	Shader *vertexShaderFormula1Texture = nullptr;
	Shader *fragmentShaderFormula1Texture = nullptr;
	ShaderProgram *shaderFormula1Texture = nullptr;
	Model *modelFormula1 = nullptr;
	DrawAbleObject *formula1 = nullptr;
	// scene 6 house
	Shader *vertexShaderHouseTexture = nullptr;
	Shader *fragmentShaderHouseTexture = nullptr;
	ShaderProgram *shaderHouseTexture = nullptr;
	Model *modelHouse = nullptr;
	DrawAbleObject *house = nullptr;

	// scene7
	Shader *vertexShaderCup = nullptr;
	Shader *fragmentShaderCup = nullptr;
	ShaderProgram *shaderCup = nullptr;
	Model *modelCup = nullptr;
	std::vector<ObjectGroup *> groupForScene7;

	Shader *vertexShaderBall = nullptr;
	Shader *fragmentShaderBall = nullptr;
	ShaderProgram *shaderBall = nullptr;
	Model *modelBall = nullptr;
	DrawAbleObject *ball = nullptr;

	Shader *vertexShaderTable = nullptr;
	Shader *fragmentShaderTable = nullptr;
	ShaderProgram *shaderTable = nullptr;
	Model *modelTable = nullptr;
	DrawAbleObject *table = nullptr;

	// scene8
	Shader *vertexShaderFormula1Texture2 = nullptr;
	Shader *fragmentShaderFormula1Texture2 = nullptr;
	ShaderProgram *shaderFormula1Texture2 = nullptr;
	Model *modelFormula1_2 = nullptr;
	DrawAbleObject *formula1_scene8 = nullptr;
};