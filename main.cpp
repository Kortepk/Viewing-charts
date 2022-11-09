#include <SFML/Graphics.hpp>  //Библиотека для отрисовки
#include <iostream>
#include <cmath>

#define ANTI_ALIASING 8
#define PI 3.14159265

using namespace sf;  //Подключение пространство имён sf (чтобы не писать sf::)
using namespace std;

int WIDTH = 700, HEIGHT = 500;
float SCALE = 200;
double LEFT_X = -WIDTH/(2*SCALE), RIGHT_X = WIDTH/(2*SCALE), CENTER_X = 0, CENTER_Y = 0;

RenderWindow window(VideoMode(WIDTH, HEIGHT), "Veer", Style::Default, ContextSettings(0,0,ANTI_ALIASING));

double Weer(float a, float b, double x){
	float k, m, y = 0;
	for(int i = 0; i < 100; i++){
	   k = cos(PI * x * pow(a, i));
	   m = pow(b, i);
	   y += k * m;
	}
	return y;
}

void Line(double x1, double y1, double x2, double y2){
	/*float dlina = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	
	RectangleShape line_with_thickness(Vector2f(dlina, 3.f));  //Линия с заданной толщиной, т.е прямоугольник, но с маленькой толищной	
	line_with_thickness.rotate(asin((y2 - y1)/dlina) * 180.0 / PI);  //Поворачиваем её на 35 градусов
	line_with_thickness.move(x1, y1);  //Перемещаем её в нижний ряд справа от прямоугольника
 
	line_with_thickness.setFillColor(Color(255, 0, 255)); //Устанавливаем цвет 
 
	window.draw(line_with_thickness);  //Отрисовка линии*/
	
	Vertex line_without_thickness[] =
	{
		Vertex(Vector2f(x1, y1)),  //Координата первой вершины
		Vertex(Vector2f(x2, y2))  //Координата второй вершины
	};
		
	line_without_thickness[0].color = Color(255, 0, 255); 	
	line_without_thickness[1].color = Color(255, 0, 255);  
 
	window.draw(line_without_thickness, 2, Lines);  //Отрисовка линии
}

void Render(){
	double last_x = 0, last_y = 0;
	double size = abs(LEFT_X) + abs(RIGHT_X), graf_x = LEFT_X + CENTER_X, graf_y;
	double step = size / WIDTH, total_step = LEFT_X;
	
	graf_y = Weer(2, 0.5, graf_x + CENTER_X);
	
	last_y = HEIGHT/2 - (graf_y + CENTER_Y)/step; //CENTER_X
	
	graf_x += step;
	double y;
	
	for(int x = 1; x <= WIDTH; x++){
		graf_y = Weer(2, 0.5, graf_x);
		
		y = HEIGHT/2 - (graf_y + CENTER_Y)/step;
		Line(x-1, last_y, x, y);
		
		last_y = y;
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
                	CENTER_Y += 10*LEFT_X/WIDTH; 
                if(event.key.code == sf::Keyboard::S)
                	CENTER_Y -= 10*LEFT_X/WIDTH; 
                	
                LEFT_X = - WIDTH/(2*SCALE);
				RIGHT_X = WIDTH/(2*SCALE);
            }
		}
		window.clear(Color(230, 230, 128, 0));   
		
		Render();		
	
		window.display();  //Отрисовка окна
	}
	return 0;
}