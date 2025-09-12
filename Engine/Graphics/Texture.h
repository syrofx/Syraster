#pragma once

#include "Image.h"
#include "Types.h"

#include <d3d11_2.h>

namespace sfr {
	enum class TextureAddress : uint8_t {
		Clamp,
		Wrap,
		Mirror,
		MirrorOnce // once in an axis i mean
	};

	enum class BlendMode : uint8_t {
		None,
		AlphaBlend,
		Additive
	};

	enum class SamplerFilter : uint8_t {
		Point,
		Linear
	};

	class Texture {
	public:
		Texture() = default;
		~Texture();

		void createImage(const Image& image);
		
		void adjustTextureAddress(TextureAddress textureAddressMode, float& u, float& v);
		
	};
}