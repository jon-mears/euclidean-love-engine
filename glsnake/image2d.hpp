#ifndef IMAGE2D_HPP
#define IMAGE2D_HPP

#include <string>

class Image2D {
private:
	unsigned char* mData;
	int mWidth, mHeight, mNrChannels;
public:
	Image2D(const std::string &filename);
	inline int width() { return mWidth; }
	inline int height() { return mHeight; }
	inline int nrChannels() { return mNrChannels; }
	inline unsigned char* data() { return mData; }
};

#endif	