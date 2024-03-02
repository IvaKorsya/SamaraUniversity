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
    bool is_correct = false;
    Figure fi;
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
                plane.del_item(current);
                break;
            case 50:
                plane.clear();
                while (!is_correct) {
                    system("cls");
                    std::cin >> fi;
                    is_correct = fi.check_input();
                }
                is_correct = false;
                plane.add_item(current, fi);
                break;
            case 49:
                system("cls");
                std::cout << "Figure with max area is:\n";
                plane.print_current(plane.find_figure_max_area());
                std::cout << "\nS =" << plane[plane.find_figure_max_area()]->calc_figure_area();
                getchar();
                break;
            case 82:
            {
                Figure f;
                while (!is_correct) {
                    system("cls");
                    std::cin >> f;
                    is_correct = f.check_input();
                }
                is_correct = false;
                plane.add_item(current, f);
                break;
            }
            }
        }
    }
    return 0;
}
