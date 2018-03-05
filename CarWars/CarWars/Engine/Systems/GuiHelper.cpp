#include "GuiHelper.h"

#include "../Entities/Entity.h"
#include "../Components/Component.h"
#include "../Components/GuiComponents/GuiComponent.h"
#include "../Entities/EntityManager.h"
#include "Content/ContentManager.h"

GuiComponent* GuiHelper::GetSelectedGui(Entity* entity) {
    for (Component *component : entity->components) {
        GuiComponent *gui = static_cast<GuiComponent*>(component);
        if (gui->IsSelected()) return gui;
    }
}

GuiComponent* GuiHelper::GetSelectedGui(std::string entityTag) {
    return GetSelectedGui(EntityManager::FindEntities(entityTag)[0]);
}

std::string GuiHelper::GetSelectedGuiText(Entity* entity) {
    return GetSelectedGui(entity)->GetText();
}

std::string GuiHelper::GetSelectedGuiText(std::string entityTag) {
    return GetSelectedGui(entityTag)->GetText();
}

void GuiHelper::SelectNextGui(Entity* entity) {
    for (auto it = entity->components.begin(); it != entity->components.end(); ++it) {
        GuiComponent *gui = static_cast<GuiComponent*>(*it);
        if (gui->IsSelected()) {
            gui->SetSelected(false);
            if (it + 1 != entity->components.end()) {
                static_cast<GuiComponent*>(*(it + 1))->SetSelected(true);
            } else {
                static_cast<GuiComponent*>(entity->components.front())->SetSelected(true);
            }
            break;
        }
    }
}

void GuiHelper::SelectNextGui(std::string entityTag) {
    return SelectNextGui(EntityManager::FindEntities(entityTag)[0]);
}

void GuiHelper::SelectPreviousGui(Entity* entity) {
    for (auto it = entity->components.begin(); it != entity->components.end(); ++it) {
        GuiComponent *gui = static_cast<GuiComponent*>(*it);
        if (gui->IsSelected()) {
            gui->SetSelected(false);
            if (it - 1 != entity->components.begin() - 1) {
                static_cast<GuiComponent*>(*(it - 1))->SetSelected(true);
            } else {
                static_cast<GuiComponent*>(entity->components.back())->SetSelected(true);
            }
            break;
        }
    }
}

void GuiHelper::SelectPreviousGui(std::string entityTag) {
    return SelectPreviousGui(EntityManager::FindEntities(entityTag)[0]);
}

void GuiHelper::LoadGuiSceneToCamera(size_t cameraIndex, std::string guiScene) {
    CameraComponent *camera = static_cast<CameraComponent*>(EntityManager::GetComponents(ComponentType_Camera)[cameraIndex]);
    ContentManager::LoadScene(guiScene, camera->GetGuiRoot());
}

void GuiHelper::SetGuisEnabled(Entity *entity, bool enabled) {
	for (Component *component : entity->components) {
		component->enabled = enabled;
	}
}

void GuiHelper::SetGuisEnabled(std::string entityTag, bool enabled) {
	SetGuisEnabled(EntityManager::FindEntities(entityTag)[0], enabled);
}

void GuiHelper::SetFirstGuiText(Entity *entity, std::string text) {
	GuiComponent *gui = static_cast<GuiComponent*>(entity->components[0]);
	gui->SetText(text);
}

void GuiHelper::SetFirstGuiText(std::string entityTag, std::string text) {
	SetFirstGuiText(EntityManager::FindEntities(entityTag)[0], text);
}

bool GuiHelper::FirstGuiTextIs(Entity *entity, std::string text) {
	GuiComponent *gui = static_cast<GuiComponent*>(entity->components[0]);
	return gui->GetText().compare(text) == 0;
}

bool GuiHelper::FirstGuiTextIs(std::string entityTag, std::string text) {
	return FirstGuiTextIs(EntityManager::FindEntities(entityTag)[0], text);
}