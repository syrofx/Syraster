#pragma once

#include <numbers>

static constexpr auto pi = std::numbers::pi;

constexpr static float radiansToDegrees(float angleInRadians) {
	return static_cast<float>(angleInRadians * (180 / pi));
}

constexpr static float degreesToRadians(float angleInDegrees) {
	return static_cast<float>((angleInDegrees * pi) / 180);
}
