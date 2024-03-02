#include <gtest/gtest.h>
#include <iostream>
#include <figures/figures.h>
#define CAPACITY 10

// 1
TEST(FiguresTests, FigureDefaultConstructorTypeTest) {
    Figure fig = Figure();
    EXPECT_EQ(fig.get_figure_type(), RECTANGLE);
}

// 2
TEST(FiguresTests, FigureDefaultConstructorPosTest) {
    Figure fig = Figure();
    EXPECT_EQ(fig.get_point_by_index(0).get_x(), 1);
}

// 3
TEST(PointTests,PointDefaultConstructorTest)
{
    Point p = Point();
    EXPECT_EQ(p.get_x(), 0);
}

// 4
TEST(PointTests, PointConstructorTest)
{
    Point p1 = Point(5,6);
    EXPECT_EQ(p1.get_x(), 5);
}

// 5
TEST(PointTests, PointSetterTest)
{
    const double NEW_VAL = 5;
    Point p= Point();
    p.set_x(NEW_VAL);
    EXPECT_EQ(p.get_x(), NEW_VAL);
}

// 6
TEST(FiguresTests, FigureConstructorTypeTest) {
    Point pos[4];
    pos[0] = Point(-2, 2);
    pos[1] = Point(1, 2);
    pos[2] = Point(4, -2);
    pos[3] = Point(-2, 2);
    Figure fig = Figure(TRAPEZOID,pos);
    EXPECT_EQ(fig.get_figure_type(), TRAPEZOID);
}

// 7
TEST(FiguresTests, FigureConstructorPosTest) {
    Point pos[4];
    pos[0] = Point(-2, 2);
    pos[1] = Point(1, 2);
    pos[2] = Point(4, -2);
    pos[3] = Point(-2, 2);
    Figure fig = Figure(TRAPEZOID, pos);
    EXPECT_EQ(fig.get_point_by_index(0).get_x(), -2);
}

// 8
TEST(FiguresTests, FigureEllipseAreaTest) {
    Point pos[4];
    pos[0] = Point(0, 2);
    pos[1] = Point(3, 0);
    pos[2] = Point(0, -2);
    pos[3] = Point(-3, 0);
    Figure fig = Figure(ELLIPSE, pos);
    EXPECT_LT(fig.calc_figure_area(), 18.9);
    EXPECT_GT(fig.calc_figure_area(), 18.7);
}

// 9
TEST(FiguresTests, FigureTrapezoidAreaTest) {
    Point pos[4];
    pos[0] = Point(2, 2);
    pos[1] = Point(0, 2);
    pos[2] = Point(3.5, -2);
    pos[3] = Point(-4.5,-2);
    Figure fig = Figure(TRAPEZOID, pos);
    EXPECT_LT(fig.calc_figure_area(), 20.1);
    EXPECT_GT(fig.calc_figure_area(), 19.9);
}

// 10
TEST(FiguresTests, FigureRectangleAreaTest) {
    Point pos[4];
    pos[0] = Point(-2, 3);
    pos[1] = Point(2, 3);
    pos[2] = Point(2, 1);
    pos[3] = Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    EXPECT_LT(fig.calc_figure_area(), 8.1);
    EXPECT_GT(fig.calc_figure_area(), 7.9);
}

// 11
TEST(FiguresTests, FigureEllipsePerimeterTest) {
    Point pos[4];
    pos[0] = Point(0, 2);
    pos[1] = Point(3, 0);
    pos[2] = Point(0, -2);
    pos[3] = Point(-3, 0);
    Figure fig = Figure(ELLIPSE, pos);
    EXPECT_LT(fig.calc_figure_perimetr(), 15.9);
    EXPECT_GT(fig.calc_figure_perimetr(), 15.8);
}

// 12
TEST(FiguresTests, FigureRectanglePerimeterTest) {
    Point pos[4];
    pos[0] = Point(-2, 3);
    pos[1] = Point(2, 3);
    pos[2] = Point(2, 1);
    pos[3] = Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    EXPECT_LT(fig.calc_figure_perimetr(), 12.1);
    EXPECT_GT(fig.calc_figure_perimetr(), 11.9);
}

// 13
TEST(FiguresTests, FigureTrapezoidPerimeterTest) {
    Point pos[4];
    pos[0] = Point(-2, 2);
    pos[1] = Point(1, 2);
    pos[2] = Point(4, -2);
    pos[3] = Point(-2, -2);
    Figure fig = Figure(TRAPEZOID, pos);
    EXPECT_LT(fig.calc_figure_perimetr(), 18.1);
    EXPECT_GT(fig.calc_figure_perimetr(), 17.9);
}

// 14
TEST(FiguresTests, FigureMinRectangleForRectangleTest) {
    Point pos[4];
    pos[0] = Point(-2, 3);
    pos[1] = Point(2, 3);
    pos[2] = Point(2, 1);
    pos[3] = Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    for (int i = 0; i < 4; ++i)
    {
        EXPECT_EQ(pos[i].get_x(), fig.calc_min_surrounding_rectangle().get_point_by_index(i).get_x());
        EXPECT_EQ(pos[i].get_y(), fig.calc_min_surrounding_rectangle().get_point_by_index(i).get_y());
    } 
}

// 15
TEST(FiguresTests, FigureMinRectangleForEllipseTest) {
    Point pos[4];
    pos[0] = Point(0, 2);
    pos[1] = Point(3, 0);
    pos[2] = Point(0, -2);
    pos[3] = Point(-3, 0);

    Point new_pos[4];
    new_pos[0] = Point(-3, 2);
    new_pos[1] = Point(3, 2);
    new_pos[2] = Point(3, -2);
    new_pos[3] = Point(-3, -2);
    Figure fig = Figure(ELLIPSE, pos);
    for (int i = 0; i < 4; ++i)
    {
        EXPECT_EQ(new_pos[i].get_x(), fig.calc_min_surrounding_rectangle().get_point_by_index(i).get_x());
        EXPECT_EQ(new_pos[i].get_y(), fig.calc_min_surrounding_rectangle().get_point_by_index(i).get_y());
    }
}

//16
TEST(FiguresTests, FigureMinRectangleForTrapezoidTest) {
    Point pos[4];
    pos[0] = Point(-2, 5);
    pos[1] = Point(5, 5);
    pos[2] = Point(5, 2);
    pos[3] = Point(-5, 2);

    Point new_pos[4];
    new_pos[0] = Point(-5, 5);
    new_pos[1] = Point(5, 5);
    new_pos[2] = Point(5, 2);
    new_pos[3] = Point(-5, 2);
    Figure fig = Figure(TRAPEZOID, pos);
    for (int i = 0; i < 4; ++i)
    {
        EXPECT_EQ(new_pos[i].get_x(), fig.calc_min_surrounding_rectangle().get_point_by_index(i).get_x());
        EXPECT_EQ(new_pos[i].get_y(), fig.calc_min_surrounding_rectangle().get_point_by_index(i).get_y());
    }
}

//17
TEST(PlaneTests, PlaneDefoltConstructorTest)
{
    Plane plane = Plane();
    double point = plane.get_figure_by_index(3).get_point_by_index(2).get_x();
    EXPECT_EQ(plane.get_size(),5);
    EXPECT_EQ(point, -1);
}

//18
TEST(PlaneTests, PlaneConstructorTest)
{
    const int SIZE = 4;
    Figure fig[CAPACITY];

    Point pos1[4];
    pos1[0] = Point(-2, 5);
    pos1[1] = Point(5, 5);
    pos1[2] = Point(5, 2);
    pos1[3] = Point(-5, 2);
    //1
    fig[0] = Figure(TRAPEZOID, pos1);

    Point pos2[4];
    pos2[0] = Point(-2, 3);
    pos2[1] = Point(2, 3);
    pos2[2] = Point(2, 1);
    pos2[3] = Point(-2, 1);
    //2
    fig[1] = Figure(RECTANGLE, pos2);

    Point pos3[4];
    pos3[0] = Point(0, 2);
    pos3[1] = Point(3, 0);
    pos3[2] = Point(0, -2);
    pos3[3] = Point(-3, 0);
    //3
    fig[2] = Figure(ELLIPSE, pos3);

    Point pos4[4];
    pos4[0] = Point(2, 2);
    pos4[1] = Point(0, 2);
    pos4[2] = Point(3.5, -2);
    pos4[3] = Point(-4.5, -2);
    fig[3] = Figure(TRAPEZOID, pos4);   

    Plane plane = Plane(fig, SIZE);
    EXPECT_EQ(plane.get_size(), SIZE); 
    EXPECT_EQ(plane[3].get_figure_type(), TRAPEZOID);
    EXPECT_EQ(plane[0].get_point_by_index(0).get_x(), -2);
    EXPECT_EQ(plane[1].get_point_by_index(0).get_x(), -2);
}

//19
TEST(PlaneTests, PlaneAddItemTest)
{
    Plane plane = Plane();
    Point pos4[4];
    pos4[0] = Point(2, 2);
    pos4[1] = Point(0, 2);
    pos4[2] = Point(3.5, -2);
    pos4[3] = Point(-4.5, -2);
    Figure fig = Figure(TRAPEZOID, pos4);
   
    plane.add_item(2, fig);
    EXPECT_EQ(plane.get_size(), 6);
    EXPECT_EQ(plane[2].get_figure_type(), TRAPEZOID);
    EXPECT_EQ(plane[2].get_point_by_index(0).get_y(), 2);
    EXPECT_EQ(plane[3].get_figure_type(), RECTANGLE);
}

//20
TEST(PlaneTests, PlaneDelItemTest)
{
    Plane plane = Plane();
    plane.del_item(2);
    EXPECT_EQ(plane.get_size(), 4);
    EXPECT_EQ(plane[3].get_figure_type(),RECTANGLE);
}

//21
TEST(PlaneTests, PlaneClearTest)
{
    Plane plane = Plane();
    plane.clear();
    EXPECT_EQ(plane.get_size(), 0);
}

//22
TEST(PlaneTests, PlaneGetItemTest)
{
    Plane plane = Plane();
    EXPECT_EQ(plane[3].get_figure_type(), RECTANGLE);
}

//23
TEST(PlaneTests, PlaneSetItemTest)
{
    Plane plane = Plane();
    plane[3].set_figure_type(ELLIPSE);
    EXPECT_EQ(plane[3].get_figure_type(), ELLIPSE);
}

//24
TEST(PlaneTests, PlaneMaxAreaTest)
{
    const int SIZE = 4;
    Figure fig[CAPACITY];

    Point pos1[4];
    pos1[0] = Point(-2, 5);
    pos1[1] = Point(5, 5);
    pos1[2] = Point(5, 2);
    pos1[3] = Point(-5, 2);
    //1
    fig[0] = Figure(TRAPEZOID, pos1);

    Point pos2[4];
    pos2[0] = Point(-2, 3);
    pos2[1] = Point(2, 3);
    pos2[2] = Point(2, 1);
    pos2[3] = Point(-2, 1);
    //2
    fig[1] = Figure(RECTANGLE, pos2);

    Point pos3[4];
    pos3[0] = Point(0, 2);
    pos3[1] = Point(3, 0);
    pos3[2] = Point(0, -2);
    pos3[3] = Point(-3, 0);
    //3
    fig[2] = Figure(ELLIPSE, pos3);

    Point pos4[4];
    pos4[0] = Point(2, 2);
    pos4[1] = Point(0, 2);
    pos4[2] = Point(3.5, -2);
    pos4[3] = Point(-4.5, -2);
    fig[3] = Figure(TRAPEZOID, pos4);

    Plane plane = Plane(fig, SIZE);

    EXPECT_EQ(plane.find_figure_max_area(fig), 0);
}

//25
TEST(ExceptionTests, ExeptionIndexOutTest)
{
    Plane plane = Plane();
    EXPECT_THROW(plane[-1].calc_figure_area(), std::runtime_error);
    EXPECT_THROW(plane[10].calc_figure_area(), std::runtime_error);
}

//26
TEST(ExceptionTests, ExeptionCapacityTest)
{
    Plane plane = Plane();
    Figure fig = Figure();
    plane.set_size(10);
    EXPECT_THROW(plane.add_item(1,fig), std::runtime_error);
}

//27
TEST(ExceptionTests, ExeptionEmptyTest)
{
    Plane plane = Plane();
    plane.set_size(0);
    EXPECT_THROW(plane.del_item(1), std::runtime_error);
}

//28
TEST(ExceptionTests, ExeptionUncorrectFiguresTest)
{
    Point pos3[4];
    pos3[0] = Point(0, 2);
    pos3[1] = Point(3, 0);
    pos3[2] = Point(0, -2);
    pos3[3] = Point(3, 1);

    Figure fig1 = Figure(ELLIPSE, pos3);
    Point pos2[4];
    pos2[0] = Point(-2, 3);
    pos2[1] = Point(2, 3);
    pos2[2] = Point(2, 1);
    pos2[3] = Point(-2, 2);

    Figure fig2 = Figure(RECTANGLE, pos2);
    Point pos4[4];
    pos4[0] = Point(2, 2);
    pos4[1] = Point(0, 2);
    pos4[2] = Point(3.5, -2);
    pos4[3] = Point(-4.5, 0);

    Figure fig3 = Figure(TRAPEZOID, pos4);
    EXPECT_THROW(fig1.check_input(), std::runtime_error);
    EXPECT_THROW(fig2.check_input(), std::runtime_error);
    EXPECT_THROW(fig3.check_input(), std::runtime_error);
}
