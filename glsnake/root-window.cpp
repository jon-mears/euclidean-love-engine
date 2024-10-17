#include "resource-manager.hpp"
#include "root-window.hpp"
#include "window.hpp"

RootWindow::RootWindow() : TexturedWindow{} {
	SetTexture(ResourceManager::Instance().Retrieve<Texture2D>
		("Container"));
}