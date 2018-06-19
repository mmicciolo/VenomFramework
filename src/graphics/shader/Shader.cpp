#include "Shader.h"
#include <bx\bx.h>
#include <bx\math.h>
#include <bx\file.h>

VF::Graphics::Shader::Shader(std::string vsFilename, std::string psFilename) {
	LoadShaders(vsFilename, psFilename);
}

void VF::Graphics::Shader::LoadShaders(std::string vsFilename, std::string psFilename) {
	bx::FileReader fileReader;
	bx::Error err;
	fileReader.open(vsFilename.c_str(), &err);
	uint32_t size = (uint32_t)bx::getSize(&fileReader);
	const bgfx::Memory* mem = bgfx::alloc(size + 1);
	bx::read(&fileReader, mem->data, size);
	bx::close(&fileReader);
	mem->data[mem->size - 1] = '\0';

	vsHandle = bgfx::createShader(mem);

	fileReader.open(psFilename.c_str(), &err);
	size = (uint32_t)bx::getSize(&fileReader);
	mem = bgfx::alloc(size + 1);
	bx::read(&fileReader, mem->data, size);
	bx::close(&fileReader);
	mem->data[mem->size - 1] = '\0';

	psHandle = bgfx::createShader(mem);

	programHandle = bgfx::createProgram(vsHandle, psHandle, true);
}

void VF::Graphics::Shader::CreateUniform(std::string name, bgfx::UniformType::Enum uniformType) {
	uniforms[name] = bgfx::createUniform(name.c_str(), uniformType);
	//uniforms.insert(name, handle);
}

void VF::Graphics::Shader::SetUniform(std::string name, void * value) {
	bgfx::setUniform(uniforms[name], value);
}