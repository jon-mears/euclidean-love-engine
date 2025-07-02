#ifndef UI_RECTANGLE_HPP
#define UI_RECTANGLE_HPP

#include <variant>

#include "camera-tag.hpp"
#include "color.hpp"
#include "game-object.hpp"
#include "texture.hpp"

class UIRectangle {
private:
	float mWidth, mHeight;
	std::variant<Texture2D*, Color> mAppearance;
	GameObject* mpGameObject;

public:
	UIRectangle(float width, float height, Color color = Color::WHITE, 
		CameraTag camera_tag = CameraTag::ALL);

	UIRectangle(float width, float height, Texture2D* pTexture, 
		CameraTag camera_tag = CameraTag::ALL);

	inline float GetWidth() {
		return mWidth;
	}

	inline void SetWidth(float width) {
		mWidth = width;
	}

	inline float GetHeight() {
		return mHeight;
	}

	inline void SetHeight(float height) {
		mHeight = height;
	}
};
#endif