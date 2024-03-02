#include <iostream>
#include <figures/figures.h>
#include <conio.h>
#define SIZE 4

int get_key()
{
    int key = _getch();
    if (!key || key == 224) key = _getch();
    return key;
}

int menu1()
{
    std::cout<<"\nViewing and editing an array of figures 'Enter'\nExit 'Esc'";
    while (true)
    {
        int key = get_key();
        if (key == 27 || key == 13) return key;
    }
}

int menu2()
{
    std::cout<<"\n\n-> following figure \n<- previous figure \n\nDelete current 'Del'\nInsert figure 'Ins'";
    std::cout << "\nFind figure with max area '1'\n\nClear '2'\nExit 'Esc'\n";
    while (true)
    {
        int key = get_key();
        if (key == 27 || key == 75 || key == 77 || key == 83 || key == 82 || key == 49 || key==50) return key;
    }
}
int main() {
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
    bool is_correct = false;
    FigurePtr figure;
   
    while (1)
    {
        system("cls");
        int m1 = menu1();
        if (m1 == 27)break;
        int current = 0;
        while (1)
        {
            plane.print_current(current);
            int m2 = menu2();
            if (m2 == 27)break;
            switch (m2)
            {
            case 75:
                if (current > 0) current--;
                break;
            case 77:
                if (current < plane.get_size() - 1) current++;
                break;
            case 83:
                if (plane.get_size() == 1) {
                    system("cls");
                    std::cout << "The plane is empty, add a figure!\n";
                    plane.clear();
                    while (!is_correct) {
                        figure = input(*figure);
                        is_correct = figure->check_input();
                    }
                    is_correct = false;
                    plane.insert(current, figure);
                }
                else if (current == plane.get_size() - 1) {
                    plane.del_item(current);
                    current--;
                }
                else plane.del_item(current);
                break;
            case 50:
                plane.clear();
                while (!is_correct) {
                    system("cls");
                    figure = input(*figure);
                    is_correct = figure->check_input();
                }
                is_correct = false;
                plane.insert(current,figure);
                current = 0;
                break;
            case 49:
                system("cls");
                std::cout << "Figure with max area is:\n";
                plane.print_current(plane.find_figure_max_area());
                std::cout << "\nS =" << plane[plane.find_figure_max_area()]->calc_figure_area();
                current = 0;
                getchar();
                break;
            case 82:
            {
                while (!is_correct) {
                    system("cls");
                    figure = input(*figure);
                    is_correct = figure->check_input();
                }
                is_correct = false;
                plane.insert(current, figure);
                break;
            }
            }
        }
    }
    return 0;
}
