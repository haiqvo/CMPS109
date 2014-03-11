
#include <iostream>
#include <iomanip> 
#include <vector>
#include <cmath>
#include <cstdlib>

//so that there is no need to type std:: all the time
#include <iostream>
using namespace std;

class S {
public:
        int x;
               int y;
        S ()                 { x = -1; y = -1; }
        S ( int zz )         { x = zz; y = zz; }
        S ( int xx, int yy ) { x = xx; y = yy; }
};

main()
{
        S a;
        S b(1);
        S c(5,6);

        cout << a.x << " " << a.y << "\n";
        cout << b.x << " " << b.y << "\n";
        cout << c.x << " " << c.y << "\n";
}