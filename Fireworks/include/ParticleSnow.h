#ifndef PARTICLESNOW_H
#define PARTICLESNOW_H

#include <Engine/Particle.h>

class ParticleSnow : public DecentEngine::Particle{
public:
	ParticleSnow(float x, float size);
	~ParticleSnow() {}

	bool update();
};

#endif
