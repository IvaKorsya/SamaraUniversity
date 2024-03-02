#pragma once

enum FigureType
{
	ELLIPSE,
	TRAPEZOID,
	RECTANGLE
};

class Point
{
	double x, y;

public:
	Point();
	Point(double x, double y);
	double get_x();
	double get_y();
	void set_x(double x);
	void set_y(double y);
};

class Figure
{
	FigureType type;
	Point pos[4];

public:
	Figure();
	Figure(FigureType type, Point pos[4]);

	Point get_point_by_index(int i);
	FigureType get_figure_type();
	void set_point_by_index(int i,Point point);
	void set_figure_type(FigureType type);

	double calc_figure_area();
	double calc_figure_perimetr();
	Figure calc_min_surrounding_rectangle();

	Figure check_input();
};

class Plane
{
	static const int CAPACITY = 10;
	Figure figure[CAPACITY];
	int size;

public:
	Plane();
	Plane(Figure figures[], int size);

	Figure get_figure_by_index(int i);
	int get_size();
	void set_size(int size);
	Figure operator[](int ind) const;
	Figure& operator[](int ind);
	void add_item(int ind,Figure fig);
	void del_item(int ind);
	void clear();
	int find_figure_max_area(Figure Figures[]);
};
