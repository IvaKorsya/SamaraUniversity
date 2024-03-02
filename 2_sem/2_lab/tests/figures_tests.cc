#include <gtest/gtest.h>
#include <figures/figures.h>
#define SIZE 4

/////POINT
// 1
TEST(PointTests, PointDefaultConstructorTest)
{
    Point p = Point();
    EXPECT_EQ(p.get_x(), 0);
}
//2
TEST(PointTests, PointConstructorTest)
{
    Point p1 = Point(5, 6);
    EXPECT_EQ(p1.get_x(), 5);
}
//3
TEST(PointTests, PointSetterTest)
{
    const double NEW_VAL = 5;
    Point p = Point();
    p.set_x(NEW_VAL);
    EXPECT_EQ(p.get_x(), NEW_VAL);
}

TEST(PointTests, PointOverloadOperatorTest)
{
    Point p = Point();
    Point p1 = Point(9, 9);
    p = p1;
    EXPECT_EQ(p.get_x(), 9);
    EXPECT_EQ(p.get_y(), 9);
}
/////FIGURE
//4
TEST(FiguresTests, FigureDefaultConstructorTypeTest) {
    Figure fig = Figure();
    EXPECT_EQ(fig.get_type(), RECTANGLE);
}
//5
TEST(FiguresTests, FigureDefaultConstructorPosTest) {
    Figure fig = Figure();
    EXPECT_EQ(fig.get_point_by_index(0)->get_x(), 1);
}
// 6
TEST(FiguresTests, FigureConstructorTypeTest) {
    
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    EXPECT_EQ(fig.get_type(), RECTANGLE);
}
// 7
TEST(FiguresTests, FigureConstructorPosTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    EXPECT_EQ(fig.get_point_by_index(0)->get_x(), -2);
}
//8
TEST(FiguresTests, FigureEllipseAreaTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(0, 2);
    pos[1] = new Point(3, 0);
    pos[2] = new Point(0, -2);
    pos[3] = new Point(-3, 0);
    Figure fig = Figure(ELLIPSE,pos);
    EXPECT_LT(fig.calc_figure_area(), 18.9);
    EXPECT_GT(fig.calc_figure_area(), 18.7);
}
//9
TEST(FiguresTests, FigureTrapezoidAreaTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(2, 2);
    pos[1] = new Point(0, 2);
    pos[2] = new Point(3.5, -2);
    pos[3] = new Point(-4.5, -2);
    Figure fig = Figure(TRAPEZOID, pos);
    EXPECT_LT(fig.calc_figure_area(), 20.1);
    EXPECT_GT(fig.calc_figure_area(), 19.9);
}
//10
TEST(FiguresTests, FigureRectangleAreaTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    EXPECT_LT(fig.calc_figure_area(), 8.1);
    EXPECT_GT(fig.calc_figure_area(), 7.9);
}
//11
TEST(FiguresTests, FigureEllipsePerimeterTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(0, 2);
    pos[1] = new Point(3, 0);
    pos[2] = new Point(0, -2);
    pos[3] = new Point(-3, 0);
    Figure fig = Figure(ELLIPSE, pos);
    EXPECT_LT(fig.calc_figure_perimetr(), 15.9);
    EXPECT_GT(fig.calc_figure_perimetr(), 15.8);
}
//12
TEST(FiguresTests, FigureRectanglePerimeterTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    EXPECT_LT(fig.calc_figure_perimetr(), 12.1);
    EXPECT_GT(fig.calc_figure_perimetr(), 11.9);
}
//13
TEST(FiguresTests, FigureTrapezoidPerimeterTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 2);
    pos[1] = new Point(1, 2);
    pos[2] = new Point(4, -2);
    pos[3] = new Point(-2, -2);
    Figure fig = Figure(TRAPEZOID, pos);
    EXPECT_LT(fig.calc_figure_perimetr(), 18.1);
    EXPECT_GT(fig.calc_figure_perimetr(), 17.9);
}
//14
TEST(FiguresTests, FigureMinRectangleForRectangleTest) {
    PointPtr* pos = new Point* [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE,pos);
    for (int i = 0; i < SIZE; ++i)
    {
        EXPECT_EQ(pos[i]->get_x(), fig.calc_min_surrounding_rectangle().get_point_by_index(i)->get_x());
        EXPECT_EQ(pos[i]->get_y(), fig.calc_min_surrounding_rectangle().get_point_by_index(i)->get_y());
    }
}
//15
TEST(FiguresTests, FigureMinRectangleForEllipseTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(0, 2);
    pos[1] = new Point(3, 0);
    pos[2] = new Point(0, -2);
    pos[3] = new Point(-3, 0);
    Figure fig = Figure(ELLIPSE, pos);

    Point new_pos[4];
    new_pos[0] = Point(-3, 2);
    new_pos[1] = Point(3, 2);
    new_pos[2] = Point(3, -2);
    new_pos[3] = Point(-3, -2);

    for (int i = 0; i < SIZE; ++i)
    {
        EXPECT_EQ(new_pos[i].get_x(), fig.calc_min_surrounding_rectangle().get_point_by_index(i)->get_x());
        EXPECT_EQ(new_pos[i].get_y(), fig.calc_min_surrounding_rectangle().get_point_by_index(i)->get_y());
    }
}
//16
TEST(FiguresTests, FigureMinRectangleForTrapezoidTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 5);
    pos[1] = new Point(5, 5);
    pos[2] = new Point(5, 2);
    pos[3] = new Point(-5, 2);

    Point new_pos[4];
    new_pos[0] = Point(-5, 5);
    new_pos[1] = Point(5, 5);
    new_pos[2] = Point(5, 2);
    new_pos[3] = Point(-5, 2);
    Figure fig = Figure(TRAPEZOID, pos);
    for (int i = 0; i < SIZE; ++i)
    {
        EXPECT_EQ(new_pos[i].get_x(), fig.calc_min_surrounding_rectangle().get_point_by_index(i)->get_x());
        EXPECT_EQ(new_pos[i].get_y(), fig.calc_min_surrounding_rectangle().get_point_by_index(i)->get_y());
    }
}
//17
TEST(FiguresTests, FigureSetterTest) {
    Figure fig = Figure();
    Point p = Point(9, 9);
    fig.set_point_by_index(1, p);
    fig.set_figure_type(TRAPEZOID);
    EXPECT_EQ(fig.get_type(), TRAPEZOID);
    EXPECT_EQ(fig.get_point_by_index(1)->get_x(), 9);
    EXPECT_EQ(fig.get_point_by_index(1)->get_y(), 9);
}
//18
TEST(FiguresTests, FigureCopyTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);

    Figure fig1 = Figure(fig);
    EXPECT_EQ(fig1.get_type(), RECTANGLE);
    EXPECT_EQ(fig.get_point_by_index(1)->get_x(), 2);
    EXPECT_EQ(fig.get_point_by_index(3)->get_y(), 1);
}
//19
TEST(FiguresTests, FigureOverloadTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    Figure fig1 = Figure();
    fig1 = fig;
    EXPECT_EQ(fig1.get_type(), RECTANGLE);
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 2);
    EXPECT_EQ(fig1.get_point_by_index(3)->get_y(), 1);
}

/////PLANE
//19
TEST(PlaneTests, PlaneDefoltConstructorTest)
{
    Plane plane = Plane();
    double point = plane.get_figure_by_index(3)->get_point_by_index(2)->get_x();
    EXPECT_EQ(plane.get_size(), 5);
    EXPECT_EQ(point, -1);
}
//20
TEST(PlaneTests, PlaneConstructorTest)
{
    FigurePtr* figures = new Figure * [SIZE];

    PointPtr* pos1 = new Point * [SIZE];
    pos1[0] = new Point(-2, 5);
    pos1[1] = new Point(5, 5);
    pos1[2] = new Point(5, 2);
    pos1[3] = new Point(-5, 2);
    
    figures[0] = new Figure(TRAPEZOID, pos1);

    PointPtr* pos2 = new Point * [SIZE];
    pos2[0] = new Point(-2, 3);
    pos2[1] = new Point(2, 3);
    pos2[2] = new Point(2, 1);
    pos2[3] = new Point(-2, 1);
  
    figures[1] = new Figure(RECTANGLE, pos2);

    PointPtr* pos3 = new Point * [SIZE];
    pos3[0] = new Point(0, 2);
    pos3[1] = new Point(3, 0);
    pos3[2] = new Point(0, -2);
    pos3[3] = new Point(-3, 0);
    
    figures[2] = new Figure(ELLIPSE, pos3);

    PointPtr* pos4 = new Point * [SIZE];
    pos4[0] = new Point(2, 2);
    pos4[1] = new Point(0, 2);
    pos4[2] = new Point(3.5, -2);
    pos4[3] = new Point(-4.5, -2);

    figures[3] = new Figure(TRAPEZOID, pos4);

    Plane plane = Plane(SIZE,figures);
    EXPECT_EQ(plane.get_size(), SIZE);
    EXPECT_EQ(plane[0]->get_type(), TRAPEZOID);
    EXPECT_EQ(plane[3]->get_point_by_index(0)->get_x(), 2);
    EXPECT_EQ(plane[1]->get_point_by_index(0)->get_x(), -2);
}
//21
TEST(PlaneTests, PlaneAddItemTest)
{
    Plane plane = Plane();

    PointPtr* pos4 = new Point * [SIZE];
    pos4[0] = new Point(2, 2);
    pos4[1] = new Point(0, 2);
    pos4[2] = new Point(3.5, -2);
    pos4[3] = new Point(-4.5, -2);

    Figure fig = Figure(TRAPEZOID, pos4);

    plane.add_item(5, fig);
    plane.add_item(2, fig);
    EXPECT_EQ(plane.get_size(), 7);
    EXPECT_EQ(plane.get_figure_by_index(5)->get_type(), RECTANGLE);
    EXPECT_EQ(plane.get_figure_by_index(6)->get_type(), TRAPEZOID);
    EXPECT_EQ(plane.get_figure_by_index(2)->get_type(), TRAPEZOID);
    EXPECT_EQ(plane[6]->get_point_by_index(0)->get_y(), 2);
}
//22
TEST(PlaneTests, PlaneDelItemTest)
{
    Plane plane = Plane();
    plane.del_item(2);
    EXPECT_EQ(plane.get_size(), 4);
    EXPECT_EQ(plane[3]->get_type(), RECTANGLE);
}
TEST(PlaneTests, PlaneGetItemTest)
{
    Plane plane = Plane();
    EXPECT_EQ(plane[3]->get_type(), RECTANGLE);
}
//24
TEST(PlaneTests, PlaneSetItemTest)
{
    Plane plane = Plane();
    plane[3]->set_figure_type(ELLIPSE);
    EXPECT_EQ(plane[3]->get_type(), ELLIPSE);
}
//25
TEST(PlaneTests, PlaneMaxAreaTest)
{
    FigurePtr* figures = new Figure * [SIZE];

    PointPtr* pos1 = new Point * [SIZE];
    pos1[0] = new Point(-2, 5);
    pos1[1] = new Point(5, 5);
    pos1[2] = new Point(5, 2);
    pos1[3] = new Point(-5, 2);

    figures[0] = new Figure(TRAPEZOID, pos1);

    PointPtr* pos2 = new Point * [SIZE];
    pos2[0] = new Point(-2, 3);
    pos2[1] = new Point(2, 3);
    pos2[2] = new Point(2, 1);
    pos2[3] = new Point(-2, 1);

    figures[1] = new Figure(RECTANGLE, pos2);

    PointPtr* pos3 = new Point * [SIZE];
    pos3[0] = new Point(0, 2);
    pos3[1] = new Point(3, 0);
    pos3[2] = new Point(0, -2);
    pos3[3] = new Point(-3, 0);

    figures[2] = new Figure(ELLIPSE, pos3);

    PointPtr* pos4 = new Point * [SIZE];
    pos4[0] = new Point(2, 2);
    pos4[1] = new Point(0, 2);
    pos4[2] = new Point(3.5, -2);
    pos4[3] = new Point(-4.5, -2);

    figures[3] = new Figure(TRAPEZOID, pos4);

    Plane plane = Plane(SIZE, figures);

    EXPECT_EQ(plane.find_figure_max_area(), 0);
}
//26
TEST(FiguresTests, FigureOverloadOperatorsTest) {
    PointPtr* pos = new Point * [SIZE];
    pos[0] = new Point(-2, 3);
    pos[1] = new Point(2, 3);
    pos[2] = new Point(2, 1);
    pos[3] = new Point(-2, 1);
    Figure fig = Figure(RECTANGLE, pos);
    Figure fig1 = Figure();
    Figure fig2 = Figure();
    EXPECT_TRUE(fig2 == fig1);
    EXPECT_TRUE(fig != fig1);
}
//27
TEST(PlaneTests, PlaneClearTest)
{
    Plane plane = Plane();
    plane.clear();
    EXPECT_EQ(plane.get_size(), 0);
}
/////EXCEPTIONS
//28
TEST(ExceptionTests, ExeptionIndexOutTest)
{
    Plane plane = Plane();
    EXPECT_THROW(plane[-1]->calc_figure_area(), std::runtime_error);
    EXPECT_THROW(plane[10]->calc_figure_area(), std::runtime_error);
}
//29
TEST(ExceptionTests, ExeptionEmptyTest)
{
    Plane plane = Plane();
    plane.clear();
    EXPECT_THROW(plane.del_item(1), std::runtime_error);
}
//30
TEST(ExceptionTests, ExeptionUncorrectFiguresTest)
{
    FigurePtr* figures = new Figure * [SIZE];

    PointPtr* pos1 = new Point * [SIZE];
    pos1[0] = new Point(-2, 5);
    pos1[1] = new Point(5, 5);
    pos1[2] = new Point(5, 2);
    pos1[3] = new Point(0, 0);

    figures[0] = new Figure(TRAPEZOID, pos1);

    PointPtr* pos2 = new Point * [SIZE];
    pos2[0] = new Point(-2, 3);
    pos2[1] = new Point(2, 3);
    pos2[2] = new Point(2, 1);
    pos2[3] = new Point(0, 1);

    figures[1] = new Figure(RECTANGLE, pos2);

    PointPtr* pos3 = new Point * [SIZE];
    pos3[0] = new Point(0, 2);
    pos3[1] = new Point(3, 0);
    pos3[2] = new Point(0, -2);
    pos3[3] = new Point(0, 1);

    figures[2] = new Figure(ELLIPSE, pos3);
    Plane plane = Plane(3, figures);
    EXPECT_FALSE(plane[0]->check_input());
    EXPECT_FALSE(plane[1]->check_input());
    EXPECT_FALSE(plane[2]->check_input());
}

