#include <stdlib.h>
#include <stdio.h>

class XYCoord
{int x; int y;
 public:
 XYCoord(int nX, int nY) {x = nx;, y = ny;}
 int getX() const { return(x); }
 int getY() const { return(y); }
};

XYCoord* pPtr = new XYChord(1,2);
printf("%d, %d\n", (*pPtr).getX(), (*pPtr).getY());
delete(pPtr);
