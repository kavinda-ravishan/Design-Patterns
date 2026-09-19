#pragma once

#include <memory>
#include <random>
#include <string>
#include <iostream>

class Logger {
public:
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	static Logger& Get() {
		return s_instance;
	}

	static void Log(std::string_view message) {
		Get().InternalLog(message);
	}

private:
	static Logger s_instance;

private:
	Logger() {
		std::cout << "Logger Initialized.\n";
	}
	~Logger() {
		std::cout << "Logger Deleted.\n";
	}

	void InternalLog(std::string_view message) {
		std::cout << "[LOG]: " << message << "\n";
	}
};

Logger Logger::s_instance;

class Random {
public:
	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;
	Random(Random&&) = delete;
	Random& operator=(Random&&) = delete;

	static Random& Get() {
		static Random random;
		return random;
	}

	static float Float() {
		return Get().IFloat();
	}
private:
	std::unique_ptr<std::random_device> _p_rd{};
	std::unique_ptr<std::mt19937 > _p_gen{};

	// 2. Define the distribution range [lower_bound, upper_bound)
	std::uniform_real_distribution<float> _random_generator{ 0.0f, 1.0f };
private:
	Random() {
		Logger::Log("Random Initialized");

		// 1. Seed the random number engine
		_p_rd = std::make_unique<std::random_device>();
		_p_gen = std::make_unique<std::mt19937>((*_p_rd)());
	}
	~Random() {
		Logger::Log("Random Deleted");
	}

	float IFloat() {
		// 3. Generate the random float
		return _random_generator((*_p_gen));
	}
};

inline void TestSingleton() {
	Logger::Log("App started");

	const float rand_val[] = { Random::Float(), Random::Float(), Random::Float() };

	std::cout << "Random values : \n";
	for (int i = 0; i < std::size(rand_val); i++) {
		std::cout <<  rand_val[i] << "\n";
	}

	Logger::Log("App ended");
}
