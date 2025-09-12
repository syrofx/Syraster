#include "Image.h"

#include <iostream>
#include <print>

void sfr::Image::create(std::size_t width, std::size_t height, std::size_t bpp) {
	mWidth = width;
	mHeight = height;
	mBpp = bpp;
	mPixels = new unsigned char[getPitch() * mHeight];
}

void sfr::Image::encode(const std::string_view& filename) {
	std::fstream file(filename.data(), std::ios::binary | std::ios::out);
	if (!file.is_open()) {
		std::cerr << "Error tring to open bmp file" << std::endl;
		return;
	}

	BitMapFileHeader fileHeader;
	std::memset(&fileHeader, 0, sizeof(BitMapFileHeader));

	BitMapSaveHeader bmpInfo;
	std::memset(&bmpInfo, 0, sizeof(BitMapSaveHeader));

	int padding = getPitch() % 4;
	int lineMemoryWidth = getPitch();

	if (padding) {
		padding = 4 - padding;
		lineMemoryWidth += padding;
	}

	int headerSize = sizeof(BitMapFileHeader) + sizeof(BitMapSaveHeader);

	fileHeader.type = 0x4D42;
	fileHeader.size = headerSize + (lineMemoryWidth * mHeight);
	fileHeader.offBits = headerSize;

	bmpInfo.coreHeader.size = sizeof(BitMapSaveHeader);
	bmpInfo.coreHeader.width = mWidth;
	bmpInfo.coreHeader.height = mHeight;
	bmpInfo.coreHeader.planes = 1;
	bmpInfo.coreHeader.bitCount = mBpp;
	bmpInfo.xPixelsPerMeter = 3780;
	bmpInfo.yPixelPerMeter = 3780;

	file.write(reinterpret_cast<char*>(&fileHeader), sizeof(BitMapFileHeader));
	file.write(reinterpret_cast<char*>(&bmpInfo), sizeof(BitMapSaveHeader));

	char padBuffer[3] = { 0, 0, 0 };
	for (int line = mHeight - 1; line >= 0; --line) {
		file.write(reinterpret_cast<char*>(&mPixels[getPitch() * line]), getPitch());
		if (padding) {
			file.write(padBuffer, padding);
		}
	}
}

void sfr::Image::decode(const std::string_view& filename) {
	std::fstream file(filename.data(), std::ios::in | std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		return;
	}

	auto fileSize = file.tellg();
	file.seekp(std::ios::beg);

	BitMapFileHeader fileHeader;
	file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitMapFileHeader));
	if (fileHeader.type != 0x4D42) {
		std::println("Is not a bmp file");
		return;
	}

	BitMapInfoHeader infoHeader;
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitMapInfoHeader));

	file.seekg(fileHeader.offBits);
	create(infoHeader.width, infoHeader.height, infoHeader.bitCount);

	int padding = getPitch() % 4;
	int lineMemoryWidth = getPitch();
	if (padding) {
		padding = 4 - padding;
		lineMemoryWidth += padding;
	}

	for (int line = mHeight - 1; line >= 0; --line) {
		file.seekp(lineMemoryWidth * line + fileHeader.offBits);
		file.read(reinterpret_cast<char*>(&mPixels[getPitch() * (mHeight - 1 - line)]), getPitch());
	}
}

void sfr::Image::setPixel(int x, int y, const Color& color) {
	if (x > mWidth || x < 0 || y >= mHeight || y < 0) {
		std::println("Pixel out of image bounds");
		return;
	}

	int pixelPos = (y * getPitch()) + (x * getBytesPerPixel());
	
	// if bitdepth is 4, it supports alpha
	if (getBytesPerPixel() == 4) {
		mPixels[pixelPos + 3] = color.a;
	}

	mPixels[pixelPos + 2] = color.r;
	mPixels[pixelPos + 1] = color.g;
	mPixels[pixelPos + 0] = color.b;
}

Color sfr::Image::getPixel(int x, int y) const {
	if (!mPixels) {
		return Color{ 0, 0, 0, 0 };
	}

	if (x >= mWidth || x < 0 || y >= mHeight || y < 0) {
		return Color{ 0, 0, 0, 0 };
	}

	Color color{};
	int pixelPos = (y * getPitch()) + (x * getBytesPerPixel());

	color.r = mPixels[pixelPos + 2];
	color.g = mPixels[pixelPos + 1];
	color.b = mPixels[pixelPos + 0];

	// if bitdepth is 4, it supports alpha
	if (getBytesPerPixel() == 4) {
		mPixels[pixelPos + 3] = color.a;
	}
	else {
		color.a = 255;
	}

	return color;
}

void sfr::Image::clearColor(const Color& color) {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			setPixel(x, y, color);
		}
	}
}

int sfr::Image::getWidth() const {
	return mWidth;
}

int sfr::Image::getHeight() const {
	return mHeight;
}

int sfr::Image::getPitch() const {
	return getBytesPerPixel() * mWidth;
}

int sfr::Image::getBytesPerPixel() const {
	return mBpp >> 3;
}

int sfr::Image::getPadBufferSize() const
{
	return 0;
}
