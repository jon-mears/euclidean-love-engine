#ifndef ANGLES_HPP
#define ANGLES_HPP

class Radians;

class Degrees {
public:
	explicit Degrees(float val);
	Degrees(Radians rad);

	operator float() const noexcept;

private:
	float mVal;
};

class Radians {
public:
	explicit Radians(float val);
	Radians(Degrees deg);

	operator float() const noexcept;

private:
	float mVal;
};

Degrees Deg(float deg) noexcept;

Radians Rad(float rad) noexcept;

Radians Deg2Rad(Degrees deg) noexcept;
Degrees Rad2Deg(Radians rad) noexcept;
#endif