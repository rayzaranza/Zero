#include "ParticleSystem.h"

#include <glm/gtc/constants.hpp>
#include <random>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

//======================================================================================
//  Random
//======================================================================================
class Random
{
  public:
    static void Init() { s_RandomDevice.seed(std::random_device()()); }

    static float Float() { return (float)s_Distribution(s_RandomDevice) / static_cast<float>(std::numeric_limits<uint32_t>::max()); }

  private:
    static std::mt19937 s_RandomDevice;
    static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};

std::mt19937 Random::s_RandomDevice{};
std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution{};

//======================================================================================
//  Particle System
//======================================================================================
ParticleSystem::ParticleSystem(const uint32_t maxParticles) : m_PoolIndex{ maxParticles - 1 }
{
    m_ParticlePool.resize(maxParticles);
}

void ParticleSystem::OnUpdate(const Zero::DeltaTime deltaTime)
{
    for (Particle& particle : m_ParticlePool)
    {
        if (!particle.IsActive)
            continue;

        if (particle.LifeRemaining <= 0.0f)
        {
            particle.IsActive = false;
            continue;
        }

        particle.LifeRemaining -= deltaTime;
        particle.Position += particle.Velocity * static_cast<float>(deltaTime);
        particle.Rotation += 0.01f * deltaTime;
    }
}

void ParticleSystem::OnRender(const Zero::OrthographicCamera& camera)
{
    Zero::Renderer2D::BeginScene(camera);

    for (const Particle& particle : m_ParticlePool)
    {
        if (!particle.IsActive)
            continue;

        const float life{ particle.LifeRemaining / particle.LifeTime };

        Zero::Renderer2D::DrawQuad(
            { .Position{ particle.Position },
              .Rotation{ particle.Rotation },
              .Scale{ glm::lerp(particle.SizeEnd, particle.SizeBegin, life) },
              .Color{ glm::lerp(particle.ColorEnd, particle.ColorEnd, life) } }
        );
    }

    Zero::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
    Particle& particle{ m_ParticlePool[m_PoolIndex] };
    particle.IsActive = true;
    particle.Position = particleProps.Position;
    particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

    particle.Velocity = particleProps.Velocity;
    particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
    particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

    particle.ColorBegin = particleProps.ColorBegin;
    particle.ColorEnd = particleProps.ColorEnd;

    particle.LifeTime = particleProps.LifeTime;
    particle.LifeRemaining = particleProps.LifeTime;
    particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
    particle.SizeEnd = particleProps.SizeEnd;

    m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
