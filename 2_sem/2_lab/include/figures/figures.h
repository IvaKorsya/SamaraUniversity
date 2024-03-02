#pragma once
#include <iostream>

#define PointPtr Point*
#define FigurePtr Figure*

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
	void swap(Point& other);
	Point& operator=(Point other);

	friend std::istream& operator>>(std::istream& in, Point& point);
	friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

class Figure
{
	FigureType type;
    PointPtr* pos;
public:
	Figure();
	Figure(FigureType type, PointPtr* pos);
	Figure(const Figure& fig);
	~Figure();

	PointPtr get_point_by_index(int i)const;
	FigureType get_type()const;
	void set_point_by_index(int i, Point point);
	void set_figure_type(FigureType type);
	double calc_figure_area();
	double calc_figure_perimetr();
	Figure calc_min_surrounding_rectangle();
	void swap(Figure& other);
	Figure& operator=(Figure other);

	bool check_input();

	friend std::istream& operator>>(std::istream& in, Figure& fig);
	friend std::ostream& operator<<(std::ostream& out, const Figure& fig);
};

bool operator==(const Figure& fig,const Figure& other);
bool operator!=(const Figure& fig, const Figure& other);

class Plane
{
	FigurePtr* figure;
	int size;

public:
	Plane();
	Plane(int size,FigurePtr* figures);
	~Plane();

	FigurePtr get_figure_by_index(int i);
	int get_size();

	FigurePtr operator[](int ind) const;
	FigurePtr& operator[](int ind);
	Plane& operator=(Plane other);

	void add_item(int ind, Figure fig);
	void del_item(int ind);
	void clear();
	void print_current( int ind);
	int find_figure_max_area();
	void swap(Plane& other);
};