#pragma once

#include <algorithm>
#include <random>

template <typename T>
std::vector<T> Shuffle(std::vector<T> x) {
	std::random_device rd;
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(x.begin(), x.end(), rng);
	return x;
}