#pragma once

#include <algorithm>

struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct FloatColor {
	FloatColor() = default;

	FloatColor(float _r, float _g, float _b, float _a) :
				r(_r), g(_g), b(_b), a(_a) {}

	FloatColor(const Color& color) :
		r(color.r / 255.0f),
		g(color.g / 255.0f),
		b(color.b / 255.0f),
		a(color.a / 255.0f) { }

	Color toColor() {

		return Color{
			static_cast<unsigned char>(r * 255.0f),
			static_cast<unsigned char>(g * 255.0f),
			static_cast<unsigned char>(b * 255.0f),
			static_cast<unsigned char>(a * 255.0f)
		};
	}

	FloatColor operator*(const FloatColor& color) {
		return FloatColor(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	FloatColor operator*(float escalar) {
		return FloatColor(r * escalar, g * escalar, b * escalar, a * escalar);
	}

	FloatColor operator+(const FloatColor& color) {
		return FloatColor(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	FloatColor operator+(float escalar) {
		return FloatColor(r + escalar, g + escalar, b + escalar, a + escalar);
	}

	FloatColor operator-(const FloatColor& color) {
		return FloatColor(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	FloatColor operator/(float escalar) {
		return FloatColor(r / escalar, g / escalar, b / escalar, a / escalar);
	}

	float toGrey() {
		return (r * 0.299f) + (g * 0.587f) + (b * 0.114f);
	}

	FloatColor& saturate() {
		r = std::clamp(r, 0.0f, 1.0f);
		g = std::clamp(g, 0.0f, 1.0f);
		b = std::clamp(b, 0.0f, 1.0f);
		a = std::clamp(a, 0.0f, 1.0f);

		return *this;
	}

	float r;
	float g;
	float b;
	float a;
};