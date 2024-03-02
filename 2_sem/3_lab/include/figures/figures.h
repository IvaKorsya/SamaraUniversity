#pragma once
#include <iostream>
#include <memory>
#include <vector>

#define PI 3.14159265
#define SIZE 4

#define fig_get_point fig->get_point_by_index 
#define PointPtr std::shared_ptr<Point>
#define FigurePtr std::shared_ptr<Figure>
#define make_sp_point std::make_shared<Point>
#define make_sp_figure std::make_shared<Figure>

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
	PointPtr clone();

	friend std::istream& operator>>(std::istream& in, Point& point);
	friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

class Figure
{
protected:
	std::vector<PointPtr> pos;
public:
	void swap(Figure& other);

	virtual ~Figure() = default;

	PointPtr get_point_by_index(int i) const;
	
	virtual double calc_figure_area() const = 0;
	virtual double calc_figure_perimetr() const = 0;
	virtual FigurePtr calc_min_surrounding_rectangle() = 0;
	virtual bool check_input() const = 0;
	virtual FigurePtr clone() = 0;
	virtual void print(std::ostream& os) const = 0;
	virtual FigurePtr cin(std::istream& in) = 0;
protected:
	Figure() = default;
	Figure(const Figure& fig) = default;
	Figure& operator=(const Figure& other) = default;
};

class Rectangle : public Figure
{
public:
	Rectangle();
	Rectangle(std::vector<PointPtr> pos_ref);
	Rectangle(const Rectangle& fig);

	Rectangle& operator=(Rectangle& other);
	FigurePtr clone() override;

	double calc_figure_area() const override;
	double calc_figure_perimetr() const override;
	FigurePtr calc_min_surrounding_rectangle() override;
	bool check_input() const override;
	void print(std::ostream& os) const override;
	FigurePtr cin(std::istream& in) override;
};

class Ellipse : public Figure
{
public:
	Ellipse();
	Ellipse(std::vector<PointPtr> pos_ref);
	Ellipse(const Ellipse& fig);

	Ellipse& operator=(Ellipse& other);
	FigurePtr clone() override;

	double calc_figure_area() const override;
	double calc_figure_perimetr() const override;
	FigurePtr calc_min_surrounding_rectangle() override;
	bool check_input() const override;
	void print(std::ostream& os) const override;
	FigurePtr cin(std::istream& in) override;
};

class Trapezoid : public Figure
{
public:
	Trapezoid();
	Trapezoid(std::vector<PointPtr> pos_ref);
	Trapezoid(const Trapezoid& fig);

	Trapezoid& operator=(Trapezoid& other);
	FigurePtr clone() override;

	double calc_figure_area() const override;
	double calc_figure_perimetr() const override;
	FigurePtr calc_min_surrounding_rectangle() override;
	bool check_input() const override;
	void print(std::ostream& os) const override;
	FigurePtr cin(std::istream& in) override;
};

class Plane
{
	std::vector<FigurePtr> figure;
public:
	Plane() = default;
	Plane(std::vector<FigurePtr> arr);
	Plane(Plane& other);
	void swap(Plane& other);
	Plane& operator=(Plane& other);

	int get_size();
	FigurePtr operator[](int ind) const;
	FigurePtr& operator[](int ind);
	void insert(int ind, FigurePtr fig);
	void del_item(int ind);
	void clear();
	int find_figure_max_area();
	void print_current(int ind);
};

FigurePtr input(Figure& fig);