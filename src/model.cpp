// model.cpp
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
//      This source file implements all functions in ModelGun class
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE 
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include "model.hpp"
#include <iostream>

ModelGun::ModelGun(std::string file)
{
    filename = file;
}

ModelGun::~ModelGun()
{
    if(textureID) glDeleteTextures(1, &textureID);
    for(auto& drawCommand : drawLists) glDeleteLists(drawCommand, 1);
}

bool ModelGun::load()
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string loadErr, loadWarn;
    // first load model
    if(!loader.LoadASCIIFromFile(&model, &loadErr, &loadWarn, filename.c_str()))
    {
        std::cout << "tinygltf failed to load: " << filename << std::endl;
        if (!loadWarn.empty()) std::cout << "tinygltf load warning: " << loadWarn << "(model: " << filename << ")" << std::endl;
        if (!loadErr.empty()) std::cout << "tinygltf load error: " << loadErr << "(model: " << filename << ")" << std::endl;
        return false;
    }
    // next process model
    loadTexture(model);
    const tinygltf::Scene& scene = model.scenes[model.defaultScene];
    for(auto& nodeID : scene.nodes)
    {
        if(nodeID >= 0 && nodeID < static_cast<int>(model.nodes.size()))
            loadSceneNodes(model, model.nodes[nodeID]);
    }
    return true;
}

void ModelGun::loadTexture(tinygltf::Model& model)
{
    if(model.textures.size() > 0)
    {
        tinygltf::Texture& tex = model.textures[0];
        if(tex.source >= 0)
        {
            glGenTextures(1, &textureID);
            tinygltf::Image& image = model.images[tex.source];
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            GLenum imageFormat = GL_RGBA;
            switch(image.component)
            {
                case 1: imageFormat = GL_RED; break;
                case 3: imageFormat = GL_RGB; break;
                default: break;
            }
            GLenum imageType = GL_UNSIGNED_BYTE;
            switch(image.bits)
            {
                case 16: imageType = GL_UNSIGNED_SHORT; break;
                case 32: imageType = GL_UNSIGNED_INT; break;
                default: break;
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, imageFormat, imageType, &image.image.at(0));
        }
    }
}

void ModelGun::loadSceneNodes(tinygltf::Model& model, tinygltf::Node& node)
{
    if(node.mesh >= 0 && node.mesh < static_cast<int>(model.meshes.size()))
        loadSceneMeshes(model, model.meshes[node.mesh]);
    for(auto& nodeID : node.children)
    {
        if(nodeID >= 0 && nodeID < static_cast<int>(model.nodes.size()))
            loadSceneNodes(model, model.nodes[nodeID]);
    }
}

void ModelGun::loadSceneMeshes(tinygltf::Model& model, tinygltf::Mesh& mesh)
{
    GLuint drawCommand = glGenLists(1);
    glNewList(drawCommand, GL_COMPILE);
    //
    // IMPORTANT: This is a wrong example, client state never works with draw lists
    //
    for(auto& primitive : mesh.primitives)
    {
        for(auto& attrib : primitive.attributes)
        {
            auto& accessor = model.accessors[attrib.second];
            int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
            const auto& buffer = model.buffers[model.bufferViews[accessor.bufferView].buffer];
            int bufferSize = accessor.type;
            if(accessor.type == TINYGLTF_TYPE_SCALAR) bufferSize = 1;
            if(!attrib.first.compare("POSITION"))
            {
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(bufferSize, accessor.componentType, byteStride, buffer.data.data() + accessor.byteOffset);
            }
            if(!attrib.first.compare("NORMAL"))
            {
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(accessor.componentType, byteStride, buffer.data.data() + accessor.byteOffset);
            }
            if(!attrib.first.compare("TEXCOORD_0"))
            {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(bufferSize, accessor.componentType, byteStride, buffer.data.data() + accessor.byteOffset);
            }
            if(!attrib.first.compare("COLOR_0"))
            {
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(bufferSize, accessor.componentType, byteStride, buffer.data.data() + accessor.byteOffset);
            }
        }
        auto& indexAccessor = model.accessors[primitive.indices];
        const auto& buffer = model.buffers[model.bufferViews[indexAccessor.bufferView].buffer];
        glDrawElements(primitive.mode, indexAccessor.count, indexAccessor.componentType, buffer.data.data() + indexAccessor.byteOffset);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glEndList();
    drawLists.push_back(drawCommand);
}

void ModelGun::render()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glCallLists(drawLists.size(), GL_UNSIGNED_INT, drawLists.data());
}