#include "Camera.h"
#include <fstream>
#include <sstream>
#include <curses.h>
#include <thread>
#include <chrono>

#include <crtdbg.h>

using namespace std;

constexpr auto scr_width = 200;
constexpr auto scr_height = 100;


int main()
{
    auto ret_val = 0;
    {
        int face_count;
        ifstream in("Objects/ezio.txt");
        Vector3 Origin;
        in >> face_count >> Origin;
        auto* faces = new Triangle[face_count];
        for (int i = 0; i < face_count; i++)
        {
            Vector3 v1, v2, v3;
            in >> v1 >> v2 >> v3;
            auto* vertices = new Vector3[3]{ v1, v2, v3 };
            faces[i] = std::move(Triangle(vertices));
        }
        auto* s = new Shape[1];
        s[0] = std::move(Shape(Origin, faces, face_count));
        auto c = Camera(s, 1, Vector3(0, 0, 0), Vector3(0, 0, 1), scr_width, scr_height);

        auto start = std::chrono::steady_clock::now();
        auto* w = initscr();
        (void)echo();
        resize_term(scr_height + 1, scr_width + 1);
        nodelay(w, true);
        while (true)
        {
            auto end = std::chrono::steady_clock::now();
            auto delta = end - start;
            if (delta.count() / 100000 >= 10)
            {
                auto ch = getch();
                while (getch() != ERR) {}
                if (ch == ERR)
                    continue;
                if (ch == 113) // Q --> exit
                    break;
                if (ch == 119) // W
                    s[0].RotateX(-5);
                else if (ch == 100) // D
                    s[0].RotateY(5);
                else if (ch == 97) // A
                    s[0].RotateY(-5);
                else if (ch == 115) // S
                    s[0].RotateX(5);
                else continue;
                c.Render();
                ostringstream out;
                out << c << '\n';
                out.flush();
                wclear(w);
                waddstr(w, out.str().c_str());
                wrefresh(w);
            }
            start = end;
        }
        endwin();
    }
    _CrtDumpMemoryLeaks();

    return ret_val;
}
