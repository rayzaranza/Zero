#pragma once
#include <Zero.h>

struct ParticleProps {
  glm::vec2 Position{};
  glm::vec2 Velocity{};
  glm::vec2 VelocityVariation{};
  glm::vec4 ColorBegin{};
  glm::vec4 ColorEnd{};
  float SizeBegin{};
  float SizeEnd{};
  float SizeVariation{};
  float LifeTime{ 1.0f };
};

struct Particle {
  glm::vec2 Position{};
  glm::vec2 Velocity{};
  glm::vec4 ColorBegin{};
  glm::vec4 ColorEnd{};
  float Rotation{};
  float SizeBegin{};
  float SizeEnd{};
  float LifeTime{};
  float LifeRemaining{};
  bool IsActive{ false };
};

class ParticleSystem {
public:
  ParticleSystem(const uint32_t maxParticles = 100000u);
  void OnUpdate(const Zero::DeltaTime deltaTime);
  void OnRender(const Zero::CameraOrthographic& camera);
  void Emit(const ParticleProps& particleProps);

private:
  Zero::Array<Particle> m_ParticlePool{};
  uint32_t m_PoolIndex;
  uint32_t m_QuadVertexArray{ 0u };
  Zero::Scope<Zero::Shader> m_ParticleShader{};
  int32_t m_ParticleShaderViewProjection{};
  int32_t m_ParticleShaderTransform{};
  int32_t m_ParticleShaderColor{};
};
