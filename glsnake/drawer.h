#ifndef DRAWER_H
#define DRAWER_H

#include <string>
#include <vector>

#include "renderer.h"

namespace {
	class Drawer {
	private:
		std::vector<std::string> commands;
	public:
		void register_object(Renderer* r) {

		};

		void draw();
		void pre();
		void post();
		void override_render(Renderer* r);
	};
}

Drawer* drawer = new Drawer();

#endif