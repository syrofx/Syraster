#pragma once
#include <fstream>

namespace sfr
{
#pragma pack(push, 2)
	struct BitMapFileHeader {
		unsigned short type;
		unsigned short size;
		unsigned short reserved1;
		unsigned short reserved2;
		unsigned short offBits;
	};
#pragma pack(pop)

	struct BitMapInfoHeader {
		unsigned long size;
		unsigned long width;
		unsigned long height;
		unsigned short planes;
		unsigned short bitCount;
	};

	struct BitMapSaveHeader {
		BitMapInfoHeader coreHeader;
		unsigned long compression;
		unsigned long sizeImage;
		long xPixelsPerMeter;
		long yPixelPerMeter;
		unsigned long colorUsed;
		unsigned long colorImportant;
	};

	enum RegionCode {
		INSIDE = 0,
		LEFT = 1,
		RIGHT = 2,
		BOTTOM = 4,
		TOP = 8
	};

	class Image {
	public:
		Image() = default;
		~Image() = default;

		void create(std::size_t width, std::size_t height, std::size_t bpp);
		void encode(const std::string_view& filename);
		void decode();

		int getWidth() const;
		int getHeight() const;
		int getPitch() const;
		int getBytesPerPixel() const;
		int getPadBufferSize() const;

	private:
		std::size_t mWidth;
		std::size_t mHeight;
		std::size_t mBpp;

		unsigned char* mPixels = nullptr;
	};
}