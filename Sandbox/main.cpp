#include <print>
#include <Graphics/Image.h>
#include <Graphics/Vector.h>

int main() {
	sfr::Image image;

	image.create(400, 400, 32);
	image.clearColor({ 0, 0, 0, 0 });
	

	for (int i = 20; i < 200; i++) {
		image.setPixel(i, 50, { 255, 255, 255, 255 });
	}

	image.encode("test.bmp");

	std::println("Image created!");
	return 0;
}