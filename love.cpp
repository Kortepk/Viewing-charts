#include <SFML/Graphics.hpp>  //Библиотека для отрисовки
#include <iostream>
#include <cmath>

#define ANTI_ALIASING 8
#define PI 3.14159265

using namespace sf;  //Подключение пространство имён sf (чтобы не писать sf::)
using namespace std;

int WIDTH = 700, HEIGHT = 500;
float SCALE = 10;
double LEFT_X = -WIDTH/(2*SCALE), RIGHT_X = WIDTH/(2*SCALE), UP_X = HEIGHT/(2*SCALE), CENTER_X = 0, CENTER_Y = 0;

RenderWindow window(VideoMode(WIDTH, HEIGHT), "Veer", Style::Default, ContextSettings(0,0,ANTI_ALIASING));



bool Love(double x, double y, double step){
	double a = x*x + pow(1.5*y - pow(x*x, 1./3), 2);
	//cout<<a<<endl;
	if(1 - 2*step <= a and a <= 1 + 2*step)
		return true;
	else
		return false;
}

void Dot(double x, double y){
	CircleShape circle(2.f); 
	circle.setFillColor(Color(255, 0, 255));  
					
	circle.setPosition(x, y); 
		
	window.draw(circle);  //Отрисовка круга
}

void Render(){
	double size = abs(LEFT_X) + abs(RIGHT_X), graf_x = LEFT_X + CENTER_X, graf_y; 
	double step = size / WIDTH, total_step = LEFT_X;
	
	for(int x = 0; x <= WIDTH; x++){
		graf_y = UP_X + CENTER_Y;
		if(abs(graf_x) < 1.2){
			for(int y = 0; y <= HEIGHT; y++){
				if(abs(graf_y) < 2){
					//cout<<graf_x<<" "<<graf_y<<" ";
					if(Love(graf_x + CENTER_X, graf_y + CENTER_Y, step))
						Dot(x, y);
				}
				graf_y -= step;
			}
		}
		graf_x += step;
	}
}

int main()
{	
	while (window.isOpen())  
	{
		Event event; 
		while (window.pollEvent(event))  
		{
			if (event.type == Event::Closed)  
				window.close();  
				
			if (event.type == Event::Resized) 
			{
	            WIDTH = event.size.width;
	            HEIGHT = event.size.height;          
	            window.setView(
	                View(
	                   Vector2f(WIDTH / 2.0, HEIGHT / 2.0), 
	                   Vector2f(WIDTH, HEIGHT)
	                )
	            );
	        }
	        if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Q)
                	SCALE -= 10*(1/LEFT_X); 
                if(event.key.code == sf::Keyboard::E)
                	SCALE += 10*(1/LEFT_X); 
                if(event.key.code == sf::Keyboard::A)
                	CENTER_X += 10*LEFT_X/WIDTH; 
                if(event.key.code == sf::Keyboard::D)
                	CENTER_X -= 10*LEFT_X/WIDTH; 
                if(event.key.code == sf::Keyboard::W)
                	CENTER_Y -= 10*LEFT_X/WIDTH; 
                if(event.key.code == sf::Keyboard::S)
                	CENTER_Y += 10*LEFT_X/WIDTH; 
                	
                LEFT_X = - WIDTH/(2*SCALE);
				RIGHT_X = WIDTH/(2*SCALE);
				UP_X = HEIGHT/(2*SCALE);
            }
		}
		window.clear(Color(230, 230, 128, 0));   
		
		Render();		
	
		window.display();  //Отрисовка окна
	}
	return 0;
}