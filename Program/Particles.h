#pragma once
#include "gfx.h"
#include "Vec2.h"
#include "Random.h"
#include <vector>
#include <memory>
class Particles
{
private:
	class Particle
	{
	public:
		Particle(const Vec2f& pos, float speed, float lifeTime, const Color& color);
		void Update(float dt);
		void Draw() const;

	private:
		Vec2f pos;
		Vec2f dir;
		float speed;
		float lifeTime;
		Color color;
	};
public:
	Particles(const Vec2f& pos, int amount, const Color& color);
	Particles(const Vec2i& pos, int amount, const Color& color);
	//Create particles from the image inside the given rect, will skip skippedParticles between each one that is created
	Particles(const Rect& rect, unsigned int skippedParticles);
	void Update(float dt);
	void Draw() const;
	bool Expired() const;

private:
	static constexpr float speedMin = 50.0f;
	static constexpr float speedMax = 150.0f;
	static constexpr float lifeTimeMin = 0.6f;
	static constexpr float lifeTimeMax = 1.2f;
	static constexpr float posOffsetMax = 11.0f;
	float lifeTimeCurrent = lifeTimeMax;
	std::vector < std::unique_ptr<Particle> > particles;


};

