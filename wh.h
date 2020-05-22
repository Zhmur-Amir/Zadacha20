#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef
struct Area_{
    int* xs;
    int* ys;
    int Number_of_dots;
    struct Area_* Pointer_to_next;
    struct Area_* Pointer_to_previous;
}Area;
int Add_dot(Area** Last_pointer);
int Count(Area* Last_pointer);
int Check_areas(Area** Last_pointer);
int Printer(Area* Last_pointer);
int Autotest(void);
