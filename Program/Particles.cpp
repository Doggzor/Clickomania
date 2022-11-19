#include "Particles.h"

Particles::Particles(const Vec2f& pos, int amount, const Color& color)
{
	Vec2f realPos;
	float realSpeed;
	float realLifeTime;
	particles.reserve(amount);
	for (int i = 0; i < amount; ++i) {
		realPos = { pos.x + Random::Float(-posOffsetMax, posOffsetMax), pos.y + Random::Float(-posOffsetMax, posOffsetMax) };
		realSpeed = Random::Float(speedMin, speedMax);
		realLifeTime = Random::Float(lifeTimeMin, lifeTimeMax);
		particles.emplace_back(std::make_unique<Particle>(realPos, realSpeed, realLifeTime, color));
	}
}

Particles::Particles(const Vec2i& pos, int amount, const Color& color)
	:
	Particles(Vec2f((float)pos.x, (float)pos.y), amount, color)
{
}

Particles::Particles(const Rect& rect, unsigned int skippedParticles)
{
	Color pixel;
	Vec2i realPos;
	float realSpeed;
	float realLifeTime;
	int d = skippedParticles;
	++skippedParticles;
	for (int w = 0; w < rect.width; ++w) {
		for (int h = 0; h < rect.height; ++h) {
			realPos = Vec2i(rect.x + w, rect.y + h);
			pixel = gfx::GetPixel(realPos.x, realPos.y);
			if (pixel != gfx::BackgroundColor && !(++d % skippedParticles)) {
				realSpeed = Random::Float(speedMin, speedMax);
				realLifeTime = Random::Float(lifeTimeMin, lifeTimeMax);
				particles.emplace_back(std::make_unique<Particle>((Vec2f)realPos, realSpeed, realLifeTime, pixel));
			}
		}
	}
}

void Particles::Update(float dt)
{
	lifeTimeCurrent -= dt;
	for (auto& p : particles) {
		p->Update(dt);
	}
}

void Particles::Draw() const
{
	for (const auto& p : particles) {
		p->Draw();
	}
}

bool Particles::Expired() const
{
	return lifeTimeCurrent <= -0.0f;
}

Particles::Particle::Particle(const Vec2f& pos, float speed, float lifeTime, const Color& color)
	:
	pos(pos),
	speed(speed),
	color(color),
	lifeTime(lifeTime)
{
	dir = { Random::Float(-1.0f, 1.0f), Random::Float(-1.0f, 1.0f) };
}

void Particles::Particle::Update(float dt)
{
	lifeTime -= dt;
	if (lifeTime > 0.0f)
		pos += dir * (speed * dt);
}

void Particles::Particle::Draw() const
{
	if (lifeTime > 0.0f)
		gfx::SetPixel((int)pos.x, (int)pos.y, color);
}
