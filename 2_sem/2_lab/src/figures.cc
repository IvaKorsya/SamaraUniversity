#pragma warning(disable:6386)
#include <figures/figures.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#define PI 3.14159265
#define EPSILON 0.0001
#define SIZE 4

#define fig_get_point fig->get_point_by_index 

std::string string_figure_type(FigureType type) {
	switch (type) {
	case ELLIPSE:
		return "Ellipse";
	case RECTANGLE:
		return "Rectangle";
	case TRAPEZOID:
		return "Trapezoid";
	default:
		throw std::runtime_error("Wrong type exception");
	}
	return "";
}

std::istream& operator>>(std::istream& is, FigureType& fig_type)
{
	int type;
	is >> type;
	switch (type)
	{
	case 0:
		fig_type = ELLIPSE;
		break;
	case 1:
		fig_type = TRAPEZOID;
		break;
	case 2:
		fig_type = RECTANGLE;
		break;
	default:
		throw std::runtime_error("Wrong type exception");
	}
	return is;
}

struct Indices
{
	int index_max_y = 0;
	int index_max_x = 0;
	int index_min_y = 0;
	int index_min_x = 0;
	int index_max2_y = 0;
};

Indices calc_edge_values(Figure* fig)
{
	Indices value;

	for (int i = 1; i < 4; ++i)
	{
		if (fig_get_point(i)->get_y() > fig_get_point(value.index_max_y)->get_y())
		{
			value.index_max_y = i;
		}
		if (fig_get_point(i)->get_y() < fig_get_point(value.index_min_y)->get_y())
		{
			value.index_min_y = i;
		}
		if (fig_get_point(i)->get_x() > fig_get_point(value.index_max_x)->get_x())
		{
			value.index_max_x = i;
		}
		if (fig_get_point(i)->get_x() < fig_get_point(value.index_min_x)->get_x())
		{
			value.index_min_x = i;
		}
		if (fig_get_point(i)->get_y() == fig_get_point(value.index_max_y)->get_y())
		{
			value.index_max2_y = i;
		}
	}
	return value;
}

Point::Point() : x(0), y(0) {};

Point::Point(double x_ref, double y_ref) : x(x_ref), y(y_ref) {};


double Point::get_x() { return x; }

double Point::get_y() { return y; }

void Point::set_x(double x) { this->x = x; }

void Point::set_y(double y) { this->y = y; }

std::istream& operator>>(std::istream& in, Point& point) {
	std::cout << "x: ";
	in >> point.x;
	std::cout << "y: ";
	in >> point.y;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
	out << "(" << point.x << ", " << point.y << ") ";
	return out;
}

void Point::swap(Point& other)
{
	std::swap(x, other.x);
	std::swap(y, other.y);
}

Point& Point::operator=(Point other)
{
	swap(other);
	return *this;
}

Figure::Figure()
{
	pos = new Point*[SIZE];
	type = RECTANGLE;
	pos[0] =new Point(1, 1);
	pos[1] = new Point(1, -1);
	pos[2] = new Point(-1, -1);
	pos[3] = new Point(-1, 1);
}

Figure::Figure(FigureType type, PointPtr* pos_ref)
{
	pos = new Point*[SIZE];
	this->type = type;
	for (int i = 0; i < SIZE; ++i)
	{
		this->pos[i] = new Point(pos_ref[i]->get_x(), pos_ref[i]->get_y());
	}
}

Figure::Figure(const Figure& fig)
{
	pos = new Point * [SIZE];
	this->type = fig.type;
	for (int i = 0; i < SIZE; ++i) 
	{
		this->pos[i] = fig.pos[i];
	}
}

Figure::~Figure() 
{
	delete[] pos;
}

void Figure::swap(Figure& other)
{
	std::swap(type, other.type);
	std::swap(pos, other.pos);
}

Figure& Figure::operator=(Figure other)
{
	swap(other);
	return *this;
}

PointPtr Figure::get_point_by_index(int i) const { return pos[i]; }

FigureType Figure::get_type() const { return type; }

void Figure::set_figure_type(FigureType type) { this->type = type; }

void Figure::set_point_by_index(int i, Point point)
{
	this->pos[i]->set_x(point.get_x());
	this->pos[i]->set_y(point.get_y());
}

bool Figure::check_input()
{
	switch (this->type)
	{
	case ELLIPSE:
		return (this->calc_figure_area() > 0 && this->pos[0]->get_x()==this->pos[2]->get_x() &&
			this->pos[1]->get_y() == this->pos[3]->get_y());
	case RECTANGLE:
		return (this->pos[0]->get_y() == this->pos[1]->get_y() && this->pos[2]->get_y() == this->pos[3]->get_y() &&
			this->pos[0]->get_x() == this->pos[3]->get_x() && this->pos[1]->get_x() == this->pos[2]->get_x()
			&& this->calc_figure_area() > 0);
	case TRAPEZOID:
		return (this->pos[0]->get_y() == this->pos[1]->get_y() && this->pos[2]->get_y() == this->pos[3]->get_y()
			&& this->calc_figure_area() > 0 && this->pos[0]->get_x() != this->pos[1]->get_x()
			&& this->pos[2]->get_x() != this->pos[3]->get_x());
	default:
		return false;
	}
}

std::istream& operator>>(std::istream& in, Figure& fig)
{
	std::cout << "choose figure type:\n 0 - Ellipse\n 1 - Trapezoid\n 2 - Rectangle\n ";
	in >> fig.type;
	std::cout << "enter points:\n ";
	for (int i = 0; i < 4; ++i)
	{
		in >> *fig.pos[i];
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Figure& fig)
{
	out << "type:" << string_figure_type(fig.type) << "\n";
	for (int i = 0; i < 4; ++i)
	{
		out << *fig.pos[i];
	}
	return out;
}

bool operator==(const Figure& fig, const Figure& other) {
	bool is_eq_type = false;
	bool is_eq_points = true;
	if (fig.get_type() == other.get_type()) is_eq_type = true;
	for (int i = 0; i < 4; ++i) {
		if(!(fabs(fig.get_point_by_index(i)->get_x() - other.get_point_by_index(i)->get_x()<EPSILON))
			&& !(fabs(fig.get_point_by_index(i)->get_y() - other.get_point_by_index(i)->get_y() < EPSILON))) {
			is_eq_points = false;
			break;
		}
	}
	return is_eq_type && is_eq_points;
}

bool operator!=(const Figure& fig, const Figure& other) {
	return !(fig == other);
}

double Figure::calc_figure_area()
{
	double height, horizontal, vertical, horizontal_2;

	Indices indices = calc_edge_values(this);
	switch (this->type)
	{
	case ELLIPSE:
		horizontal = (fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x())) / 2;

		vertical = (fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y())) / 2;

		return horizontal * vertical * PI;

	case TRAPEZOID:
		horizontal = fabs(this->pos[indices.index_max2_y]->get_x() -
			this->pos[indices.index_max_y]->get_x());

		horizontal_2 = fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x());

		height = fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y());

		return ((horizontal + horizontal_2) / 2) * height;
	case RECTANGLE:
		horizontal = fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x());

		vertical = fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y());

		return horizontal * vertical;
	}
	return 0;
}

double Figure::calc_figure_perimetr()
{
	Indices indices = calc_edge_values(this);
	double horizontal, vertical, horizontal_2, height, delta_x1, delta_x2, side1, side2;
	switch (this->type)
	{
	case ELLIPSE:
		horizontal = (fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x())) / 2;

		vertical = (fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y())) / 2;

		return 4 * (PI * horizontal * vertical + pow(horizontal - vertical, 2)) / (horizontal + vertical);
	case RECTANGLE:
		horizontal = fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x());

		vertical = fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y());
		return 2 * (horizontal + vertical);
	case TRAPEZOID:
		horizontal = fabs(this->pos[indices.index_max2_y]->get_x() -
			this->pos[indices.index_max_y]->get_x());

		horizontal_2 = fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x());

		height = fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y());

		if (this->pos[indices.index_max_y]->get_x() <
			this->pos[indices.index_max2_y]->get_x())
		{
			delta_x1 = this->pos[indices.index_min_x]->get_x() -
				this->pos[indices.index_max_y]->get_x();
			delta_x2 = this->pos[indices.index_max_x]->get_x() -
				this->pos[indices.index_max2_y]->get_x();
		}
		else
		{
			delta_x1 = this->pos[indices.index_min_x]->get_x() -
				this->pos[indices.index_max2_y]->get_x();
			delta_x2 = this->pos[indices.index_max_x]->get_x() -
				this->pos[indices.index_max_y]->get_x();
		}
		side1 = sqrt(pow(delta_x1, 2) + pow(height, 2));
		side2 = sqrt(pow(delta_x2, 2) + pow(height, 2));
		return side1 + side2 + horizontal + horizontal_2;
	}
	return 0;
}

Figure Figure::calc_min_surrounding_rectangle()
{
	Indices indices = calc_edge_values(this);
	PointPtr* pos_rec = new Point * [SIZE];
	pos_rec[0] = new Point(this->get_point_by_index(indices.index_min_x)->get_x(), this->get_point_by_index(indices.index_max_y)->get_y());
	pos_rec[1] = new Point(this->get_point_by_index(indices.index_max_x)->get_x(), this->get_point_by_index(indices.index_max_y)->get_y());
	pos_rec[2] = new  Point(this->get_point_by_index(indices.index_max_x)->get_x(), this->get_point_by_index(indices.index_min_y)->get_y());
	pos_rec[3] = new Point(this->get_point_by_index(indices.index_min_x)->get_x(), this->get_point_by_index(indices.index_min_y)->get_y());
	Figure fig = Figure(RECTANGLE, pos_rec);
	return fig;
}

Plane::Plane()
{
	this->size = 5;
	figure = new Figure * [size];
	for (int i = 0; i < size; ++i) this->figure[i] = new Figure();
}

Plane::Plane(int size, FigurePtr* figures){
	this->size = size;

	figure = new Figure * [size];
	for (int i = 0; i < size; ++i)
	{
		this->figure[i] = new Figure();
		this->figure[i]->set_figure_type(figures[i]->get_type());
		for (int j = 0; j < SIZE; ++j)
		{
			this->figure[i]->set_point_by_index(j,*figures[i]->get_point_by_index(j));
		}
	}
}

void Plane::swap(Plane& other)
{
	std::swap(figure, other.figure);
	std::swap(size, other.size);
}

Plane& Plane::operator=(Plane other)
{
	swap(other);
	return *this;
}

Plane::~Plane()
{
	for (int i = 0; i < size; ++i) { delete figure[i]; }
	delete[] figure;
}

FigurePtr Plane::get_figure_by_index(int i) { return figure[i]; }

int Plane::get_size() { return size; }

FigurePtr Plane::operator[](int ind) const
{
	if (ind < 0 || ind >= size)
	{
		throw std::runtime_error("Index out of range.");
	}
	return figure[ind];
}

FigurePtr& Plane::operator[](int ind)
{
	if (ind < 0 || ind >= size)
	{
		throw std::runtime_error("Index out of range.");
	}
	return figure[ind];
}

void Plane::add_item(int ind, Figure fig)
{
	if (ind < 0 || (ind>size))
	{
		throw std::runtime_error("Index out of range.");
	}

	++size;
	FigurePtr *figures = new Figure * [size];

	for (int i = 0; i < ind; ++i)
	{
		figures[i] =new Figure(*this->figure[i]);
	}

	figures[ind] = new Figure(fig);

	for (int i = size - 1; i > ind; --i)
	{
		figures[i] = new Figure(*this->figure[i - 1]);
	}

	std::swap(this->figure,figures);
}

void Plane::clear() 
{ 
	figure=nullptr;
	size = 0; 
}

void Plane::del_item(int ind)
{
	if (size <= 0)
	{
		throw std::runtime_error("Plane is empty.");
	}
	for (int i = ind; i < size - 1; ++i) { figure[i] = figure[i + 1]; }
	--size;
}

int Plane::find_figure_max_area()
{
	int ind = 0;
	double max_area = figure[0]->calc_figure_area();
	for (int i = 1; i < size - 1; ++i)
	{
		double cur_area = figure[i]->calc_figure_area();
		if (cur_area > max_area)
		{
			ind = i;
			max_area = cur_area;
		}
	}
	return ind;
}

void Plane::print_current(int ind) {
	system("cls");
	std::cout << *figure[ind];
}

