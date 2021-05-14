// model.hpp
// Assignment: CIS425 Final Project
// Environment/Compiler:
//                  Visual Studio Community 2019 (Tested)
//                  Linux GCC (Tested)
//                  MacOS GCC (Not Tested)
// Date: May 14, 2021
// Official Name:  Sida Zhu
// E-mail:
//      szhu28@syr.edu
//      teamclouday@gmail.com
// File Description:
//      This header file defines ModelGun class for loading complex gltf models which are loaded with tinygltf
//      
//      IMPORTANT: This is a failed implementation because old OpenGL lacks important features
//          One of which is VAO, which stores necessary drawing data on GPU and only load for once.
//          In old OpenGL, however, there is no such feature, so when drawing a complex model,
//          it has to load data from disk at each frame, which reduces performance greatly.
//      So this class is not used at the end in the game but kept as a proof of try
#pragma once

// reference: https://github.com/syoyo/tinygltf/blob/master/examples/basic/main.cpp
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