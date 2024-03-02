#include <gtest/gtest.h>
#include <figures/figures.h>
#include <memory>
#include <vector>
#define SIZE 4

///POINT
 //1
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
//4
TEST(PointTests, PointOverloadOperatorTest)
{
    Point p = Point();
    Point p1 = Point(9, 9);
    p = p1;
    EXPECT_EQ(p.get_x(), 9);
    EXPECT_EQ(p.get_y(), 9);
}
///RECTANGLE
//5
TEST(RectangleTests, RectangleConstructorTest) {
    
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    Rectangle fig = Rectangle(pos);
    EXPECT_EQ(fig.get_point_by_index(1)->get_x(), 2);
}
//6
TEST(RectangleTests, RectangleCopyConstrTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    Rectangle fig = Rectangle(pos);
    Rectangle fig1(fig);
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 2);
}
//7
TEST(RectangleTests, RectangleOverloadCopyTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    Rectangle fig = Rectangle(pos);
    Rectangle fig1=fig;
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 2);
}
//8
TEST(RectangleTests, RectangleAreaTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    Rectangle fig = Rectangle(pos);
    EXPECT_NEAR(fig.calc_figure_area(), 8 , 0.0001);
}
//9
TEST(RectangleTests, RectanglePerimeterTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    Rectangle fig = Rectangle(pos);
    EXPECT_NEAR(fig.calc_figure_perimetr(), 12, 0.001);
}
//10
TEST(RectangleTests, RectangleSurRectangleTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    Rectangle fig = Rectangle(pos);
    for (int i = 0; i < SIZE; ++i)
    {
        EXPECT_EQ(pos[i]->get_x(), fig.calc_min_surrounding_rectangle()->get_point_by_index(i)->get_x());
        EXPECT_EQ(pos[i]->get_y(), fig.calc_min_surrounding_rectangle()->get_point_by_index(i)->get_y());
    }
}
//11
TEST(RectangleTests, RectangleInputTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 3));
    pos.push_back(make_sp_point(2, 3));
    pos.push_back(make_sp_point(2, 1));
    pos.push_back(make_sp_point(-2, 1));
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(-2, 3));
    pos1.push_back(make_sp_point(0, 3));
    pos1.push_back(make_sp_point(2, 0));
    pos1.push_back(make_sp_point(-2, 1));
    Rectangle fig1 = Rectangle(pos1);
    Rectangle fig = Rectangle(pos);
    EXPECT_TRUE(fig.check_input());
    EXPECT_FALSE(fig1.check_input());
}
///ELLIPSE
//12
TEST(EllipseTests, EllipseConstrTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    EXPECT_EQ(fig.get_point_by_index(1)->get_x(), 3);
}
//13
TEST(EllipseTests, EllipseCopyConstrTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    Ellipse fig1(fig);
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 3);
}
//14
TEST(EllipseTests, EllipseOverloadCopyTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    Ellipse fig1=fig;
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 3);
}
//15
TEST(EllipseTests, EllipseAreaTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    EXPECT_NEAR(fig.calc_figure_area(), 18.85, 0.01);
}
//16
TEST(EllipseTests, EllipsePerimeterTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    EXPECT_NEAR(fig.calc_figure_perimetr(), 15.87, 0.01);
}
//17
TEST(EllipseTests, EllipseMinRectangleTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(-3, 2));
    pos1.push_back(make_sp_point(3, 2));
    pos1.push_back(make_sp_point(3, -2));
    pos1.push_back(make_sp_point(-3, -2));
    for (int i = 0; i < SIZE; ++i)
    {
        EXPECT_EQ(pos1[i]->get_x(), fig.calc_min_surrounding_rectangle()->get_point_by_index(i)->get_x());
        EXPECT_EQ(pos1[i]->get_y(), fig.calc_min_surrounding_rectangle()->get_point_by_index(i)->get_y());
    }
}
//18
TEST(EllipseTests, EllipseInputTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3, 0));
    pos.push_back(make_sp_point(0, -2));
    pos.push_back(make_sp_point(-3, 0));
    Ellipse fig = Ellipse(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(1, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(1, 1));
    pos1.push_back(make_sp_point(-3, 1));
    Ellipse fig1 = Ellipse(pos1);
    EXPECT_TRUE(fig.check_input());
    EXPECT_FALSE(fig1.check_input());
}
//TRAPEZOID
//19
TEST(TrapezoidTests, TrapezoidConstrTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(2, 2));
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3.5, -2));
    pos.push_back(make_sp_point(-4.5, -2));
    Trapezoid fig = Trapezoid(pos);
    EXPECT_EQ(fig.get_point_by_index(1)->get_x(), 0);
}
//20
TEST(TrapezoidTests, TrapezoidCopyConstrTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(2, 2));
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3.5, -2));
    pos.push_back(make_sp_point(-4.5, -2));
    Trapezoid fig = Trapezoid(pos);
    Trapezoid fig1(fig);
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 0);
}
//21
TEST(TrapezoidTests, TrapezoidOverloadCopyTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(2, 2));
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3.5, -2));
    pos.push_back(make_sp_point(-4.5, -2));
    Trapezoid fig = Trapezoid(pos);
    Trapezoid fig1=fig;
    EXPECT_EQ(fig1.get_point_by_index(1)->get_x(), 0);
}
//22
TEST(TrapezoidTests, TrapezoidAreaTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(2, 2));
    pos.push_back(make_sp_point(0, 2));
    pos.push_back(make_sp_point(3.5, -2));
    pos.push_back(make_sp_point(-4.5, -2));
    Trapezoid fig = Trapezoid(pos);
    EXPECT_NEAR(fig.calc_figure_area(), 20, 0.01);
}
//23
TEST(TrapezoidTests, TrapezoidPerimeterTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    EXPECT_NEAR(fig.calc_figure_perimetr(), 18, 0.01);
}
//24
TEST(TrapezoidTests, TrapezoidMinRectangleTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 5));
    pos.push_back(make_sp_point(5, 5));
    pos.push_back(make_sp_point(5, 2));
    pos.push_back(make_sp_point(-5, 2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(-5, 5));
    pos1.push_back(make_sp_point(5, 5));
    pos1.push_back(make_sp_point(5, 2));
    pos1.push_back(make_sp_point(-5, 2));
    for (int i = 0; i < SIZE; ++i)
    {
        EXPECT_EQ(pos1[i]->get_x(), fig.calc_min_surrounding_rectangle()->get_point_by_index(i)->get_x());
        EXPECT_EQ(pos1[i]->get_y(), fig.calc_min_surrounding_rectangle()->get_point_by_index(i)->get_y());
    }
}
//25
TEST(TrapezoidTests, TrapezoidInputTest) {
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(-2, 2));
    pos1.push_back(make_sp_point(1, 2));
    pos1.push_back(make_sp_point(4, -2));
    pos1.push_back(make_sp_point(-2, 0));
    Trapezoid fig1 = Trapezoid(pos1);
    EXPECT_TRUE(fig.check_input());
    EXPECT_FALSE(fig1.check_input());
}

//PLANE
//26
TEST(PlaneTests, PlaneConstrTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    Plane plane=Plane(figures);
    EXPECT_EQ(plane.get_size(),3);
    EXPECT_EQ(plane[0]->get_point_by_index(3)->get_y(), -2);
    EXPECT_EQ(plane[1]->get_point_by_index(1)->get_x(), 3);
    EXPECT_EQ(plane[2]->get_point_by_index(2)->get_x(), 2);
}
//27
TEST(PlaneTests, PlaneCopyConstrTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    Plane plane = Plane(figures);
    Plane plane1(plane);
    EXPECT_EQ(plane1.get_size(), 3);
    EXPECT_EQ(plane1[0]->get_point_by_index(3)->get_y(), -2);
    EXPECT_EQ(plane1[1]->get_point_by_index(1)->get_x(), 3);
    EXPECT_EQ(plane1[2]->get_point_by_index(2)->get_x(), 2);
}
//28
TEST(PlaneTests, PlaneOverloadCopyTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    Plane plane = Plane(figures);
    Plane plane1=plane;
    EXPECT_EQ(plane1.get_size(), 3);
    EXPECT_EQ(plane1[0]->get_point_by_index(3)->get_y(), -2);
    EXPECT_EQ(plane1[1]->get_point_by_index(1)->get_x(), 3);
    EXPECT_EQ(plane1[2]->get_point_by_index(2)->get_x(), 2);
}
//29
TEST(PlaneTests, PlaneInsertTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    Plane plane = Plane(figures);
    plane.insert(1, fig2.clone());
    EXPECT_EQ(plane.get_size(), 4);
    EXPECT_EQ(plane[0]->get_point_by_index(3)->get_y(), -2);
    EXPECT_EQ(plane[2]->get_point_by_index(1)->get_x(), 3);
    EXPECT_EQ(plane[1]->get_point_by_index(2)->get_x(), 2);
}
//30
TEST(PlaneTests, PlaneDelItemTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    Plane plane = Plane(figures);
    plane.del_item(0);
    EXPECT_EQ(plane.get_size(), 2);
    EXPECT_EQ(plane[0]->get_point_by_index(1)->get_x(), 3);
    EXPECT_EQ(plane[1]->get_point_by_index(2)->get_x(), 2);
}
//31
TEST(PlaneTests, PlaneClearTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 2));
    pos.push_back(make_sp_point(1, 2));
    pos.push_back(make_sp_point(4, -2));
    pos.push_back(make_sp_point(-2, -2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    Plane plane = Plane(figures);
    plane.clear();
    EXPECT_EQ(plane.get_size(), 0);
}
//33
TEST(PlaneTests, PlaneMaxAreaTest) {
    std::vector<FigurePtr> figures;
    std::vector<PointPtr> pos;
    pos.push_back(make_sp_point(-2, 5));
    pos.push_back(make_sp_point(5, 5));
    pos.push_back(make_sp_point(5, 2));
    pos.push_back(make_sp_point(-5, 2));
    Trapezoid fig = Trapezoid(pos);
    std::vector<PointPtr> pos1;
    pos1.push_back(make_sp_point(0, 2));
    pos1.push_back(make_sp_point(3, 0));
    pos1.push_back(make_sp_point(0, -2));
    pos1.push_back(make_sp_point(-3, 0));
    Ellipse fig1 = Ellipse(pos1);
    std::vector<PointPtr> pos2;
    pos2.push_back(make_sp_point(-2, 3));
    pos2.push_back(make_sp_point(2, 3));
    pos2.push_back(make_sp_point(2, 1));
    pos2.push_back(make_sp_point(-2, 1));
    Rectangle fig2 = Rectangle(pos2);
    figures.push_back(std::make_shared<Trapezoid>(fig));
    figures.push_back(std::make_shared<Rectangle>(fig2));
    figures.push_back(std::make_shared<Ellipse>(fig1));
    Plane plane = Plane(figures);
    EXPECT_EQ(plane.find_figure_max_area(), 0);
}

