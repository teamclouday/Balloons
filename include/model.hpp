// This header file defines models that are loaded with tinygltf
// 
// IMPORTANT: This is a failed implementation because old OpenGL lacks important features
// So this class is not used in the project but kept as a proof of try
//
// ModelGun
#pragma once

// https://github.com/syoyo/tinygltf/blob/master/examples/basic/main.cpp
#include <tiny_gltf.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <string>
#include <vector>

class ModelGun
{
public:
    ModelGun(std::string file);
    ~ModelGun();
    bool load();
    void render();

private:
    void loadTexture(tinygltf::Model& model);
    void loadSceneNodes(tinygltf::Model& model, tinygltf::Node& node);
    void loadSceneMeshes(tinygltf::Model& model, tinygltf::Mesh& mesh);

    std::string filename;
    std::vector<GLuint> drawLists;
    GLuint textureID;
};