#include "Image.h"
#include <iostream>

void sfr::Image::create(std::size_t width, std::size_t height, std::size_t bpp) {
	mWidth = width;
	mHeight = height;
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
	fileHeader.size = headerSize + (lineMemoryWidth + mHeight);
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

void sfr::Image::decode() {
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
