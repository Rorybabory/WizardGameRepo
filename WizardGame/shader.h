#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include <string>
#include "GL/glew.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "camera.h"
extern glm::vec3 hsv;
class Shader {
public:
  Shader(const std::string& fileName);
  Shader();
  void InitPPShader(const std::string& fileName);
  void Bind();
  void Bind(glm::vec4 color, glm::vec4 colorFlash);
  void Bind(glm::vec4 color, glm::vec4 colorFlash, float hitCount);
  void TextBind(int x, int y);
  void UnBind();
  void Update(const Transform& transform, const Camera& camera);
  void Update(const Transform& transform);
  virtual ~Shader();
  void InitShader(const std::string& fileName);
  glm::vec4 color = glm::vec4(0.0f,0.0f,0.0f,1.0f);
  int x;
  int y;
  static const unsigned int NUM_SHADERS = 2;
  Shader(const Shader& other) {}
  void operator=(const Shader& other) {}
  enum {
      TRANSFORM_U,
      NUM_UNIFORMS
  };
  std::string LoadShader(const std::string& fileName);
  void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];
protected:
private:
  
};
#endif
