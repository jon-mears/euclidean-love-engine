#include "resource-browser.hpp"
#include "resource-manager.hpp"
#include "texture.hpp"
#include "imgui.h"

void ResourceBrowser::Draw() {

	static bool sShowAppMetrics = false;

	ImGui::ShowDemoWindow();

	ImGui::Begin("Browser", NULL, ImGuiWindowFlags_MenuBar);

	Texture2D* pTexture = ResourceManager::Instance().Retrieve<Texture2D>("Container");
	
	ImGui::Image((void*)pTexture->ID(), ImVec2(0.25*pTexture->Width(), 0.25*pTexture->Height()));
	
	if (ImGui::CollapsingHeader("hi")) {
		ImGui::Text("Help");
		ImGui::BulletText("hi");
		ImGui::BulletText("there");
	}

	ImGui::Separator();

	ImGui::End();
}