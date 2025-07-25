#include "hierarchy-view.hpp"
#include "resource-manager.hpp"
#include "imgui.h"
#include "editor-manager.hpp"

#include "transform-component.hpp"
#include "game-object.hpp"

#include <map>
#include <unordered_set>
#include <iostream>

void HierarchyView::DrawTree(TransformComponent* pTransformC) {
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	auto pGO = pTransformC->GO();

	if (mSelection.count(pGO))
		node_flags |= ImGuiTreeNodeFlags_Selected;

	if (pTransformC->GetNumChildren()) {
		bool node_open = ImGui::TreeNodeEx(pGO->Name().c_str(),
			node_flags);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			mpClicked = pGO;

		if (ImGui::BeginDragDropSource()) {
			ImGui::SetDragDropPayload("SO", pGO,
				sizeof(GameObject));
			ImGui::Text(pGO->Name().c_str());
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload =
				ImGui::AcceptDragDropPayload("SO")) {
				GameObject* pSource = (GameObject*)payload->Data;
				
				auto pSourceTC = pSource->Retrieve<TransformComponent>();

				if (pSourceTC == nullptr) {
					std::cout << "gameobject does not have a t component" <<
						std::endl;
				}
				else {
					pTransformC->AddChild(pSourceTC);
				}
			}

			ImGui::EndDragDropTarget();
		}

		if (node_open) {
			for (auto child : pTransformC->GetChildren()) {
				DrawTree(child);
			}

			ImGui::TreePop();
		}
	}
	else {
		ImGui::TreeNodeEx(pGO->Name().c_str(),
			node_flags |
			ImGuiTreeNodeFlags_Leaf |
			ImGuiTreeNodeFlags_NoTreePushOnOpen);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
			mpClicked = pGO;
		}

		if (ImGui::BeginDragDropSource()) {
			ImGui::SetDragDropPayload("SO", pGO,
				sizeof(GameObject));
			ImGui::Text(pGO->Name().c_str());
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload =
				ImGui::AcceptDragDropPayload("SO")) {
				GameObject* pSource = (GameObject*)payload->Data;

				auto pSourceTC = pSource->Retrieve<TransformComponent>();
				pTransformC->AddChild(pSourceTC);
			}

			ImGui::EndDragDropTarget();
		}
	}
}

void HierarchyView::Draw() {
	mpClicked = nullptr;

	if (ImGui::Begin("Scene", &mbOpen, ImGuiWindowFlags_MenuBar)) {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Add")) {
				ImGui::MenuItem("Empty SceneObject");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersInnerV)) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);

			DrawHierarchy();

			ImGui::TableSetColumnIndex(1);

			DrawProperties();

			ImGui::EndTable();
		}

		ImGui::End();
	}
	else {
		ImGui::End();
	}
}

void HierarchyView::DrawHierarchy() {
	ResourceManager& rm = ResourceManager::Instance();

	for (auto it = rm.Begin<GameObject>(); it != rm.End<GameObject>();
		++it) {
		GameObject* pGO = it->second;

		auto pTransformC1 = pGO->Retrieve<TransformComponent>();

		if (pTransformC1 != nullptr) {
			if (pTransformC1->Parent() != nullptr) continue;
			DrawTree(pTransformC1);
		}
		else {
			ImGui::TreeNodeEx(pGO->Name().c_str(),
				ImGuiTreeNodeFlags_Leaf |
				ImGuiTreeNodeFlags_NoTreePushOnOpen |
				ImGuiTreeNodeFlags_OpenOnDoubleClick |
				ImGuiTreeNodeFlags_OpenOnArrow |
				ImGuiTreeNodeFlags_SpanAvailWidth);

			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
				mpClicked = pGO;
			}

			if (ImGui::BeginDragDropSource()) {
				ImGui::SetDragDropPayload("SO", pGO,
					sizeof(GameObject));
				ImGui::Text(pGO->Name().c_str());
				ImGui::EndDragDropSource();
			}
		}
	}

	if (mpClicked != nullptr) {
		if (ImGui::GetIO().KeyCtrl) {
			if (mSelection.count(mpClicked)) {
				mSelection.erase(mpClicked);
			}
			else {
				mSelection.insert(mpClicked);
			}
		}
		else {
			mSelection.clear();
			mSelection.insert(mpClicked);
		}
	}
}


void HierarchyView::DrawProperties() {
	for (auto go = mSelection.begin(); go != mSelection.end(); ++go) {
		ImGui::PushID("properties");
		if (ImGui::CollapsingHeader((*go)->Name().c_str(),
			ImGuiTreeNodeFlags_DefaultOpen)) {
			for (auto cmpnt = (*go)->Begin<Component>(); cmpnt !=
				(*go)->End<Component>(); ++cmpnt) {
				(*cmpnt)->Interface();
			}
		}
		ImGui::PopID();
	}
}