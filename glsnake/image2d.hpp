#ifndef IMAGE2D_HPP
#define IMAGE2D_HPP

#include <string>

class Image2D {
private:
	unsigned char* data;
public:
	Image2D(std::string filename);
};

#endif