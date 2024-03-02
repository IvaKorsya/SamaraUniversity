#include <figures/figures.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#define PI 3.14159265
#define fig_get_point fig->get_point_by_index 

struct Indices
{
	int index_max_y=0;
	int index_max_x=0;
	int index_min_y=0;
	int index_min_x=0;
	int index_max2_y=0;
};

Indices calc_edge_values(Figure* fig)
{
	Indices value;

	for (int i = 1; i < 4; ++i)
	{
		if (fig_get_point(i).get_y() > fig_get_point(value.index_max_y).get_y())
		{
			value.index_max_y = i;
		}
		if (fig_get_point(i).get_y() < fig_get_point(value.index_min_y).get_y())
		{
			value.index_min_y=i;
		}
		if (fig_get_point(i).get_x() > fig_get_point(value.index_max_x).get_x())
		{
			value.index_max_x = i;
		}
		if (fig_get_point(i).get_x() < fig_get_point(value.index_min_x).get_x())
		{
			value.index_min_x = i;
		}
		if (fig_get_point(i).get_y() == fig_get_point(value.index_max_y).get_y())
		{
			value.index_max2_y = i;
		}
	}
	return value;
}

Point::Point() : x(0), y(0) {};

Point::Point(double x_ref, double y_ref) : x(x_ref), y(y_ref) {};


double Point::get_x() {return x;}

double Point::get_y() {return y;}

void Point::set_x(double x) {this->x = x;}

void Point::set_y(double y) { this->y = y; }

Figure::Figure()
{
	type = RECTANGLE;
	pos[0] = Point(1, 1);
	pos[1] = Point(1, -1);
	pos[2] = Point(-1, -1);
	pos[3] = Point(-1, 1);
}

Figure::Figure(FigureType type,Point pos_ref[4])
{
	this->type = type;
	for (int i = 0; i < 4; ++i)
	{
		this->pos[i] = Point(pos_ref[i].get_x(), pos_ref[i].get_y());
	}
}

Point Figure::get_point_by_index(int i) { return pos[i]; }

FigureType Figure::get_figure_type() { return type; }

void Figure::set_figure_type(FigureType type) { this->type = type; }

void Figure::set_point_by_index(int i,Point point)
{
	this->pos[i].set_x(point.get_x());
	this->pos[i].set_y(point.get_y());
}

Figure Figure::check_input()
{
	switch (this->type)
	{
	case ELLIPSE:
		if (this->pos[0].get_x() == this->pos[1].get_y() == this->pos[2].get_x() == this->pos[3].get_y() &&
			this->pos[0].get_y()==(-(this->pos[2].get_y())) && this->pos[1].get_x() == (-(this->pos[3].get_y()))){
			return *this;
		}
		else throw std::runtime_error("Points error");
	case RECTANGLE:
		if (this->pos[0].get_y() == this->pos[1].get_y() && this->pos[2].get_y() == this->pos[3].get_y() &&
			this->pos[0].get_x() == this->pos[3].get_x() && this->pos[1].get_x() == this->pos[2].get_x()) {
			return *this;
		}
		else throw std::runtime_error("Points error");
	case TRAPEZOID:
		if (this->pos[0].get_y() == this->pos[1].get_y() && this->pos[2].get_y() == this->pos[3].get_y()) {
			return *this;
		}
		else throw std::runtime_error("Points error");
	}
}

double Figure::calc_figure_area()
{
	double height, horizontal, vertical, horizontal_2;

	Indices indices = calc_edge_values(this);
	switch (this->type)
	{
	case ELLIPSE:
		horizontal = (fabs(this->pos[indices.index_max_x].get_x() -
			this->pos[indices.index_min_x].get_x())) / 2;

		vertical = (fabs(this->pos[indices.index_max_y].get_y() -
			this->pos[indices.index_min_y].get_y())) / 2;

		return horizontal * vertical * PI;

	case TRAPEZOID:
		horizontal = fabs(this->pos[indices.index_max2_y].get_x() - 
			this->pos[indices.index_max_y].get_x());

		horizontal_2 = fabs(this->pos[indices.index_max_x].get_x() -
			this->pos[indices.index_min_x].get_x());

		height = fabs(this->pos[indices.index_max_y].get_y() -
			this->pos[indices.index_min_y].get_y());

		return ((horizontal + horizontal_2) / 2) * height;
	case RECTANGLE:
		horizontal = fabs(this->pos[indices.index_max_x].get_x() -
			this->pos[indices.index_min_x].get_x());

		vertical = fabs(this->pos[indices.index_max_y].get_y() -
			this->pos[indices.index_min_y].get_y());

		return horizontal * vertical;
	}
	return 0;
}

double Figure::calc_figure_perimetr()
{
	Indices indices = calc_edge_values(this);
	double horizontal, vertical, horizontal_2,height,delta_x1,delta_x2,side1,side2;
	switch (this->type)
	{
	case ELLIPSE:
		horizontal = (fabs(this->pos[indices.index_max_x].get_x() -
			this->pos[indices.index_min_x].get_x())) / 2;

		vertical = (fabs(this->pos[indices.index_max_y].get_y() -
			this->pos[indices.index_min_y].get_y())) / 2;
		
		return 4 * (PI*horizontal*vertical+pow(horizontal-vertical,2))/(horizontal + vertical);
	case RECTANGLE:
		horizontal = fabs(this->pos[indices.index_max_x].get_x() -
			this->pos[indices.index_min_x].get_x());

		vertical = fabs(this->pos[indices.index_max_y].get_y() -
			this->pos[indices.index_min_y].get_y());
		return 2 * (horizontal + vertical);
	case TRAPEZOID:
		horizontal = fabs(this->pos[indices.index_max2_y].get_x() -
			this->pos[indices.index_max_y].get_x());

		horizontal_2 = fabs(this->pos[indices.index_max_x].get_x() -
			this->pos[indices.index_min_x].get_x());

		height = fabs(this->pos[indices.index_max_y].get_y() -
			this->pos[indices.index_min_y].get_y());

		if (this->pos[indices.index_max_y].get_x() <
			this->pos[indices.index_max2_y].get_x())
		{
			delta_x1 = this->pos[indices.index_min_x].get_x() -
				this->pos[indices.index_max_y].get_x();
			delta_x2=this->pos[indices.index_max_x].get_x() -
				this->pos[indices.index_max2_y].get_x();
		}
		else
		{
			delta_x1 = this->pos[indices.index_min_x].get_x() -
				this->pos[indices.index_max2_y].get_x();
			delta_x2=this->pos[indices.index_max_x].get_x()-
				this->pos[indices.index_max_y].get_x();
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
	Point pos[4];
	pos[0] = Point(this->get_point_by_index(indices.index_min_x).get_x(), this->get_point_by_index(indices.index_max_y).get_y());
	pos[1] = Point(this->get_point_by_index(indices.index_max_x).get_x(), this->get_point_by_index(indices.index_max_y).get_y());
	pos[2] = Point(this->get_point_by_index(indices.index_max_x).get_x(), this->get_point_by_index(indices.index_min_y).get_y());
	pos[3] = Point(this->get_point_by_index(indices.index_min_x).get_x(), this->get_point_by_index(indices.index_min_y).get_y());
	Figure fig = Figure(RECTANGLE, pos);
	return fig;
}

Plane::Plane()
{
	this->size = 5;
	for (int i = 0; i < size; ++i) figure[i] = Figure();
}

Plane::Plane(Figure figures[], int size)
{
	this->size = size;
	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			this->figure[i].set_point_by_index(j,figures[i].get_point_by_index(j));
			this->figure[i].set_figure_type(figures[i].get_figure_type());
		}
	}
}

Figure Plane::get_figure_by_index(int i) { return figure[i]; }

int Plane::get_size() { return size; }

void Plane::set_size(int size) { this->size = size; }

Figure Plane::operator[](int ind) const
{
	if (ind<0 || ind>=size)
	{
		throw std::runtime_error("Index out of range.");
	}
	return figure[ind];
}

Figure& Plane::operator[](int ind)
{
	if (ind < 0 || ind >= size)
	{
		throw std::runtime_error("Index out of range.");
	}
	return figure[ind];
}

void Plane::add_item(int ind,Figure fig)
{
	if (size == CAPACITY)
	{
		throw std::runtime_error("Full capacity reached.");
	}

	if (ind < 0 || ind >= size)
	{
		throw std::runtime_error("Index out of range.");
	}

	for (int i = size-1; i >= ind; --i) { figure[i] = figure[i-1];}
	figure[ind] = fig;
	++size;
}

void Plane::clear() {size = 0;}

void Plane::del_item(int ind)
{
	if (size<=0)
	{
		throw std::runtime_error("Plane is empty.");
	}
	for (int i = ind; i < size-1; ++i) { figure[i] = figure[i + 1];}
	--size;
}

int Plane::find_figure_max_area(Figure figures[])
{
	int ind = 0;
	double max_area = figures[0].calc_figure_area();
	for (int i = 1; i < size - 1; ++i)
	{
		double cur_area = figures[i].calc_figure_area();
		if (cur_area > max_area)
		{
			ind = i;
			max_area = cur_area;
		}
	}
	return ind;
}