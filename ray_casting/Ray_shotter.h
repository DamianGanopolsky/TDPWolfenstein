#ifndef __RAY_SHOTTER_H__
#define __RAY_SHOTTER_H__

#include <map>
#include "Ray.h"

//Simula un disparador de rayos con un ángulo fijo;
class Ray_shotter {
public:
	/*
	Game map es una tira de boleanos que representan cada cuadrícula
	del mapa, supone que el tamaño es de 8x8 y que cada cuadricula es de
	64x64 (pueden ser cambiados). También supone que si una cuadricula 
	está asociada con false, entonces está bloqueda. 
	*/
	Ray_shotter(std::map<int, bool>& game_map, const float angle);
	~Ray_shotter();

	/*
	Devuelve un rayo que fue disparado desde los puntos pos_x y 
	pos_y con la dirección del shotter.
	*/
	Ray shoot(const int pos_x, const int pos_y);
	
private:
	std::map<int, bool>& game_map;
	const float angle;

	//Análogo a Ray_shotter::shoot pero solo impacta de forma vertical
	Ray shoot_by_y(const int pos_x, const int pos_y);
	//Análogo a Ray_shotter::shoot pero solo impacta de forma horizontal
	Ray shoot_by_x(const int pos_x, const int pos_y);
	//Modula el código de shoot_by_y y shoot_by_x con simetría
	Ray shoot_by(const int pos_x, const int pos_y, bool pos_exchange,
				bool reverse, float point_factor, float dist_factor);
	//Indica si el shooter apunta completamente hacia arriba o abajo
	bool is_horizontal_shooter();
	//Indica si el shooter apunta completamente hacia la derecha o izquierda
	bool is_vertical_shooter();
	//Dado dos posiciones del tablero indica el punto correspondiente a game_map
	int get_point(const int pos_x, const int pos_y);
};

#endif
