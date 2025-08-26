#include <print>
#include <Graphics/Image.h>

int main() {
	sfr::Image image;

	image.create(400, 400, 24);
	image.clearColor({ 255, 255, 255, 0 });
	image.encode("test.bmp");

	std::println("Image created!");
	return 0;
}