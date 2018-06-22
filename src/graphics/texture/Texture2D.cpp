#include "Texture2D.h"


VF::Graphics::Texture2D::Texture2D(std::string fileName) {
	LoadTexture(fileName);
}

void VF::Graphics::Texture2D::LoadTexture(std::string fileName) {
	bx::FileReader fileReader;
	bx::Error err;
	fileReader.open(fileName.c_str(), &err);
	uint32_t size = (uint32_t)bx::getSize(&fileReader);
	const bgfx::Memory* mem = bgfx::alloc(size + 1);
	bx::read(&fileReader, mem->data, size);
	bx::close(&fileReader);
	mem->data[mem->size - 1] = '\0';

	bimg::ImageContainer* imageContainer = bimg::imageParse(getDefaultAllocator(), mem->data, size);

	const bgfx::Memory* mem2 = bgfx::makeRef(
		imageContainer->m_data
		, imageContainer->m_size
		, imageReleaseCb
		, imageContainer
	);

	textureHandle = bgfx::createTexture2D(
		uint16_t(imageContainer->m_width)
		, uint16_t(imageContainer->m_height)
		, 1 < imageContainer->m_numMips
		, imageContainer->m_numLayers
		, bgfx::TextureFormat::Enum(imageContainer->m_format)
		, 0
		, mem2
	);


}