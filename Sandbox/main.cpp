#include <print>
#include <Graphics/Image.h>

int main() {
	sfr::Image image;

	image.create(400, 400, 32);
	image.clearColor({ 0, 0, 0, 0 });
	image.encode("test.bmp");

	std::println("Image created!");
	return 0;
}