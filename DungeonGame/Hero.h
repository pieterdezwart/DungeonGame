#pragma once
class Hero
{
public:
	Hero();
	~Hero();

	void setLocation();
	int getLocation();

private:
	int x, y = 0;
	int health = 50;
};

