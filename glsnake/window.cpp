#include <iostream>

#include "material.hpp"
#include "mesh.hpp"
#include "primitives.hpp"
#include "resource-manager.hpp"
#include "shader-component.hpp"
#include "vertex-data.hpp"
#include "window.hpp"

TexturedWindow::TexturedWindow() : Window{} {
	mpMesh = Primitives::Plane(Vertex::POSITION |
		Vertex::TEXTURE_COORD);

	mpMaterial = new Material();
	mpMaterial->SetShader(ResourceManager::Instance().
		Retrieve<Shader>("Texture Shader"));
}

void TexturedWindow::SetTexture(Texture2D* pTexture) {
	mpMaterial->SetUniform("uSampler", pTexture);
}

void TexturedWindow::Draw() {
	GLint viewport_data[4];
	glGetIntegerv(GL_VIEWPORT, viewport_data);

	GLint x = viewport_data[0] * mOriginX,
		y = viewport_data[1] * mOriginY,
		width = viewport_data[2] * mWidth,
		height = viewport_data[3] * mHeight;

	glViewport(x, y, width, height);
	
	mpMesh->Enable();
	mpMaterial->Enable();

	glDrawArrays(GL_TRIANGLES, 0, mpMesh->GetNumVertices());
}

TexturedWindow::~TexturedWindow() { }