#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <Windows.h>
/*
Testing out some collision principles using custom functions
I chose not to use an API/Engine for the physics, so I can see how these all work
*/
class Shape
{
private:
	float diameter, radius;
	std::string name;
public:
	Shape(std::string _name, float _diameter, float _radius) : radius(_radius), diameter(_diameter), name(_name){}
	float GetDiameter();
	float GetRadius();
	std::string GetName();
};

std::string Shape::GetName()
{
	return name;
}
float Shape::GetDiameter()
{
	return diameter;
}
float Shape::GetRadius()
{
	return radius;
}
class Collision
{
private:
	float _distance;
	float _gravity;
	bool _is_colliding = false;
public:
	Collision(float gravity) : _gravity(gravity)
	{
		_distance = 0.0f;
	}

	void Collide(Shape &shape1, Shape &shape2);
	void SetDistance(float &distance);
	float GetDistance();
	void ObjectApproach();
	float GetGravitation();
	void SetGravitation(float value);
	bool IsCollided();
	void SetCollided(bool val);
};

void Collision::SetCollided(bool val)
{
	_is_colliding = val;
}
bool Collision::IsCollided()
{
	return _is_colliding;
}
void Collision::SetGravitation(float value)
{
	_gravity= value;
}
float Collision::GetGravitation()
{
	return _gravity;
}

float Collision::GetDistance()
{
	return _distance;
}
void Collision::ObjectApproach()
{
	_distance -= GetGravitation();
}
void Collision::SetDistance(float &distance)
{
	_distance = distance;
}

void Collision::Collide(Shape &shape1, Shape &shape2)
{
	if (_distance <= 0.0f)
	{
		std::cout << "Error, distance is 0";
	}
	if (_distance <= shape1.GetDiameter())
	{
		_is_colliding = true;
		SetGravitation(0.0f);
		//std::cout << shape1.GetName() << " and " << shape2.GetName() << " - [Collided]" << std::endl;
	}
}

void ApplyCollision(bool value)
{
	if (value)
	{

	}
}

std::ostream& operator << (std::ostream &out, const sf::Vector2f &vec)
{
	out << vec;
	return out;
}
int main()
{
	int width = 700, height = 500;
	float distance = 250.0f;
	float gravitation = 2.5f;
	Collision col(gravitation);
	Shape square1 ("Square1", 80.0f, (25.0f / 2));
	Shape square2("Square1", 60.0f, (25.0f / 2));
	
	col.SetDistance(distance);
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Physics_01");
	sf::RectangleShape rectangle1(sf::Vector2f(square1.GetDiameter(), square1.GetDiameter()));
	sf::RectangleShape rectangle2(sf::Vector2f(square2.GetDiameter(), square2.GetDiameter()));
	rectangle1.setFillColor(sf::Color::Red);
	rectangle2.setFillColor(sf::Color::Green);
	

	//std::cout << rectangle1.getPosition();

	rectangle2.setPosition(distance, 0.0f);

	while (window.isOpen())
	{
		Sleep(20);
		if (!col.IsCollided())
			distance -= col.GetGravitation();
		else
		{
			col.SetGravitation(gravitation);
			distance += col.GetGravitation();
		}

		if (distance >= (width - square2.GetDiameter()))
		{
			col.SetCollided(false);
		}
		col.SetDistance(distance);
		col.Collide(square1, square2);
		rectangle2.setPosition(distance, 0.0f);
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			window.close();

			if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				distance -= col.GetGravitation();
				col.SetDistance(distance);
			}
			if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				std::cout << "distance: " << col.GetDistance() << std::endl;
				std::cout << "gravity: " << col.GetGravitation() << std::endl;
			}
		}
		window.clear();
		window.draw(rectangle1);
		window.draw(rectangle2);
		window.display();
	}

	
	std::cin.get();
}