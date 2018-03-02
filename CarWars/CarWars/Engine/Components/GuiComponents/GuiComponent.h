#pragma once

#include "../Component.h"
#include "../CameraComponent.h"
#include "../../Entities/Transform.h"
#include "../../Systems/Content/Texture.h"
#include "json/json.hpp"

#include "FTGL/ftgl.h"

class GuiComponent : public Component {
public:
	GuiComponent(nlohmann::json data);

	Transform transform;		// TODO: GuiTransform

	ComponentType GetType() override;
	void HandleEvent(Event *event) override;

	void RenderDebugGui() override;

	void SetText(std::string _text);
	std::string GetText() const;

	void SetTexture(Texture *_texture);
	Texture* GetTexture() const;

	void SetFont(std::string fontName);
	void SetFontSize(int fontSize);
	void SetFontColor(glm::vec4 _fontColor);

	FTFont* GetFont() const;
	glm::vec4 GetFontColor() const;

	Entity* GetGuiRoot();

	void SetEntity(Entity *_entity) override;

private:
	Entity *guiRoot;

	FTFont *font;		// TODO: Decide which kind of font to use
	glm::vec4 fontColor;
	std::string text;
	Texture *texture;
};