#ifndef _LIB_IMPORT_MODEL_IMAC_LSM
#define _LIB_IMPORT_MODEL_IMAC_LSM
#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <glimac/glm.hpp>
#include <glimac/Except.hpp>
#include <random>
#include <algorithm>
#include <queue>

#include <glimac/FreeflyCamera.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace sausageRunner
{

  /*! \struct Vertex
     * \brief
     *    Contains the values of a vertex : 
     *    its position, its normal and its Texture Coordinates
     */

  struct Vertex {
      glm::vec3 Position; /*!< Position of the vertex*/
      glm::vec3 Normal; /*!< Normal of the vertex*/
      glm::vec2 TexCoords; /*<! Texture coordinate of the vertex*/
  };

  /*! \struct Texture
     * \brief
     *    Contains the basic information of a 3D texture
     */
  struct Texture {
      unsigned int id; /*!< Id of the texture in the GPU*/
      std::string type;  /*!< Type of the texture : diffuse / specular*/
      aiString path; /*!< Path of the texture*/
  };

  /*! \class Mesh
     * \brief
     *    Contains the 3D values of a mesh
     */

  class Mesh {
      private:
          unsigned int vao, vbo, ebo; /*!< Vertex Array Object, Vertex Buffer Object, Element Buffer Object*/
          void setupMesh(); /*!< Setup the mesh at his initialisation*/
      public:
          std::vector<Vertex> _vertices; /*!< Vertex of the mesh*/
          std::vector<unsigned int> _indices; /*!< Index of the vertex*/
          std::vector<Texture> _textures; /*!< Textures of the mesh*/

          Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex):_vertices(vert),_indices(ind),_textures(tex){
              setupMesh();
          };
          void draw() const; /*!< Bind the VAO and the textures and send its*/
  };

  /*! \class Model
     * \brief
     *    browse the an obj Model and find its Mesh and its textures
     */
  class Model{
      private:
          std::vector<Mesh> meshes; /*!< Stock the meshs of the model*/
          std::string directory; /*!< Directory of the model*/

          void loadModel(std::string path); /*!< Load a model from his path*/
          void processNode(aiNode *node, const aiScene *scene); /*!< Browse all the nodes of the model*/
          Mesh processMesh(aiMesh *mesh, const aiScene *scene); /*!< Process a Mesh from a node of the model*/
          std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName); /*<! Load a Material */
      public:
          Model(std::string path){
            try
            {
               loadModel(path);
            }
            catch(Except err)
            {
                std::cerr << err.what() << std::endl;
            }
          }
          void draw() const; /*!< Draw all the mesh of the model*/
  };
}

#endif
