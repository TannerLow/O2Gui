#pragma once
#include <SFML/System.hpp>

class RateLimiter {
private:
	sf::Clock clock;
	double timePerTick = 0;
	int limit = 0;

public:
	RateLimiter() {}

	RateLimiter(int limit) {
		setLimit(limit);
	}

	~RateLimiter() {}

	bool isReady() {
		if (limit == 0) {
			return true;
		}

		if (clock.getElapsedTime().asSeconds() < timePerTick) {
			return false;
		}

		clock.restart();

		return true;
	}

	void setLimit(int limit) {
		this->limit = limit;
		this->timePerTick = 1.0 / limit;
	}
};