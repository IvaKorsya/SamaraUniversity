#include <figures/figures.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include <conio.h>

struct Indices
{
	int index_max_y = 0;
	int index_max_x = 0;
	int index_min_y = 0;
	int index_min_x = 0;
	int index_max2_y = 0;
};

template <typename T>
Indices calc_edge_values(T* fig)
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

FigurePtr input(Figure& fig) {
	int type=-1;
	Rectangle rec;
	Ellipse ell;
	Trapezoid trap;
	while (type < 0 || type>2) {
		std::cout << "Rectangle - 0\nEllipse - 1\nTrapezoid - 2\n";
		std::cin >> type;
	}
	switch (type)
	{
	case 0:
		return (rec.cin(std::cin));
	case 1:
		return (ell.cin(std::cin));
	case 2:
		return (trap.cin(std::cin));
	}
}

//Point
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

PointPtr Point::clone()
{
	return make_sp_point(x,y);
}

//Figure
void Figure::swap(Figure& other)
{
	std::swap(pos, other.pos);
}

PointPtr Figure::get_point_by_index(int i)const
{
	return pos[i];
}

//Rectangle
Rectangle::Rectangle()
{
	for (int i = 0; i < SIZE; ++i) pos.push_back(Point().clone());
}

Rectangle::Rectangle(std::vector<PointPtr> pos_ref)
{
	for (auto elem : pos_ref) pos.push_back(Point(elem->get_x(), elem->get_y()).clone());
}

Rectangle::Rectangle(const Rectangle& fig)
{
	for (auto elem : fig.pos) pos.push_back(elem);
}

Rectangle& Rectangle::operator=(Rectangle& other)
{
	swap(other);
	return *this;
}

double Rectangle::calc_figure_area() const 
{
	double horizontal, vertical;
	Indices indices = calc_edge_values(this);
	horizontal = fabs(this->pos[indices.index_max_x]->get_x() -
				this->pos[indices.index_min_x]->get_x());
	vertical = fabs(this->pos[indices.index_max_y]->get_y() -
				this->pos[indices.index_min_y]->get_y());
	
	return horizontal * vertical;
}

double Rectangle::calc_figure_perimetr() const
{
	double horizontal, vertical;
	Indices indices = calc_edge_values(this);
	horizontal = fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x());
	vertical = fabs(this->pos[indices.index_max_y]->get_y() -
		this->pos[indices.index_min_y]->get_y());
	return 2 * (horizontal + vertical);
}

FigurePtr Rectangle::clone()
{
	return std::make_shared<Rectangle>(pos);
}

FigurePtr Rectangle::calc_min_surrounding_rectangle() 
{
	return this->clone();
}

bool Rectangle::check_input() const
{
	return (this->pos[0]->get_y() == this->pos[1]->get_y() && this->pos[2]->get_y() == this->pos[3]->get_y()&&
			this->pos[0]->get_x() == this->pos[3]->get_x() && this->pos[1]->get_x() == this->pos[2]->get_x()
			&& this->calc_figure_area() > 0);
}

void Rectangle::print(std::ostream& os) const
{
	os << "Rectangle\n";
	for (auto elem : pos) os << *elem;
}

FigurePtr Rectangle::cin(std::istream& in)
{
	for (auto elem : pos)
	{
		in >> *elem;
		std::cout << "\n";
	}
	return this->clone();
}

//Ellipse
Ellipse::Ellipse()
{
	for (int i = 0; i < SIZE;++i) pos.push_back(Point().clone());
}

Ellipse::Ellipse(std::vector<PointPtr> pos_ref)
{
	for (auto elem : pos_ref) pos.push_back(Point(elem->get_x(), elem->get_y()).clone());
}

Ellipse::Ellipse(const Ellipse& fig)
{
	for (auto elem : fig.pos) pos.push_back(elem);
}

Ellipse& Ellipse::operator=(Ellipse& other)
{
	swap(other);
	return *this;
}

FigurePtr Ellipse::clone()
{
	return std::make_shared<Ellipse>(pos);
}

double Ellipse::calc_figure_area() const
{
	double horizontal, vertical;
	Indices indices = calc_edge_values(this);
	horizontal = (fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x())) / 2;
	vertical = (fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y())) / 2;
	return horizontal * vertical * PI;
}

double Ellipse::calc_figure_perimetr() const
{
	Indices indices = calc_edge_values(this);
	double horizontal, vertical;
	horizontal = (fabs(this->pos[indices.index_max_x]->get_x() -
			this->pos[indices.index_min_x]->get_x())) / 2;
    vertical = (fabs(this->pos[indices.index_max_y]->get_y() -
			this->pos[indices.index_min_y]->get_y())) / 2;
	return 4 * (PI * horizontal * vertical + pow(horizontal - vertical, 2)) / (horizontal + vertical);
}

FigurePtr Ellipse::calc_min_surrounding_rectangle()
{
	Indices indices = calc_edge_values(this);
	std::vector<PointPtr> pos_rec;
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_min_x)->get_x(), this->get_point_by_index(indices.index_max_y)->get_y()));
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_max_x)->get_x(), this->get_point_by_index(indices.index_max_y)->get_y()));
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_max_x)->get_x(), this->get_point_by_index(indices.index_min_y)->get_y()));
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_min_x)->get_x(), this->get_point_by_index(indices.index_min_y)->get_y()));
	Rectangle fig = Rectangle(pos_rec);
	return fig.clone();
}

bool Ellipse::check_input() const
{
	return (this->calc_figure_area() > 0 && this->pos[0]->get_x() == this->pos[2]->get_x()&&
			this->pos[1]->get_y() == this->pos[3]->get_y());
}

void Ellipse::print(std::ostream& os) const
{
	os << "Ellipse\n";
	for (auto elem : pos) os << *elem;
}

FigurePtr Ellipse::cin(std::istream& in)
{
	for (auto elem : pos)
	{
		in >> *elem;
		std::cout << "\n";
	}
	return this->clone();
}

//Trapezoid
Trapezoid::Trapezoid()
{
	for (int i = 0; i < SIZE; ++i) pos.push_back(Point().clone());
}

Trapezoid::Trapezoid(std::vector<PointPtr> pos_ref)
{
	for (auto elem : pos_ref) pos.push_back(Point(elem->get_x(), elem->get_y()).clone());
}

Trapezoid::Trapezoid(const Trapezoid& fig)
{
	for (auto elem : fig.pos) pos.push_back(elem);
}

Trapezoid& Trapezoid::operator=(Trapezoid& other)
{
	swap(other);
	return *this;
}

FigurePtr Trapezoid::clone()
{
	return std::make_shared<Trapezoid>(pos);
}

double Trapezoid::calc_figure_area() const
{
	double height, horizontal, horizontal_2;
	Indices indices = calc_edge_values(this);
	horizontal = fabs(this->pos[indices.index_max2_y]->get_x() -
		this->pos[indices.index_max_y]->get_x());
	horizontal_2 = fabs(this->pos[indices.index_max_x]->get_x() -
		this->pos[indices.index_min_x]->get_x());
	height = fabs(this->pos[indices.index_max_y]->get_y() -
	    this->pos[indices.index_min_y]->get_y());
	return ((horizontal + horizontal_2) / 2) * height;
}

double Trapezoid::calc_figure_perimetr() const
{
	Indices indices = calc_edge_values(this);
	double horizontal, horizontal_2, height, delta_x1, delta_x2, side1, side2;
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

FigurePtr Trapezoid::calc_min_surrounding_rectangle()
{
	Indices indices = calc_edge_values(this);
	std::vector<PointPtr> pos_rec;
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_min_x)->get_x(), this->get_point_by_index(indices.index_max_y)->get_y()));
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_max_x)->get_x(), this->get_point_by_index(indices.index_max_y)->get_y()));
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_max_x)->get_x(), this->get_point_by_index(indices.index_min_y)->get_y()));
	pos_rec.push_back(make_sp_point(this->get_point_by_index(indices.index_min_x)->get_x(), this->get_point_by_index(indices.index_min_y)->get_y()));
	Rectangle fig = Rectangle(pos_rec);
	return fig.clone();
}

bool Trapezoid::check_input() const
{
	return (this->pos[0]->get_y() == this->pos[1]->get_y() && this->pos[2]->get_y() == this->pos[3]->get_y()
		&& this->calc_figure_area() > 0 && this->pos[0]->get_x() != this->pos[1]->get_x()
		&& this->pos[2]->get_x() != this->pos[3]->get_x());
}

void Trapezoid::print(std::ostream& os) const
{
	os << "Trapezoid\n";
	for (auto elem : pos) os << *elem;
}

FigurePtr Trapezoid::cin(std::istream& in)
{
	for (auto elem : pos)
	{
		in >> *elem;
		std::cout << "\n";
	}
	return this->clone();
}

///Plane
Plane::Plane(std::vector<FigurePtr> arr)
{
	for (auto elem : arr) figure.push_back(elem->clone());
}

Plane::Plane(Plane& other)
{
	figure.reserve(other.get_size());
	for (auto elem : other.figure) figure.push_back(elem->clone());
}

int Plane::get_size()
{
	return figure.size();
}

FigurePtr Plane::operator[](int ind) const
{
	return figure[ind];
}

FigurePtr& Plane::operator[](int ind)
{
	return figure[ind];
}

void Plane::swap(Plane& other)
{
	std::swap(figure, other.figure);
}

Plane& Plane::operator=(Plane& other)
{
	swap(other);
	return *this;
}

void Plane::insert(int ind, FigurePtr fig)
{
	if(ind == (this->get_size()-1)) figure.push_back(fig);
	else figure.insert(figure.begin() + ind, fig);
}

void Plane::del_item(int ind)
{
    figure.erase(figure.begin()+ind);
}

void Plane::clear()
{
	figure.clear();
}

int Plane::find_figure_max_area()
{
	int ind = 0;
	double max_area = figure[0]->calc_figure_area();
	for (int i = 1; i < figure.size() - 1; ++i)
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
	figure[ind]->print(std::cout);
}

