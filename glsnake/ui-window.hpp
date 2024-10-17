#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

class UIWindow {
public:
	virtual ~UIWindow();
	virtual void Draw() = 0;
};

#endif