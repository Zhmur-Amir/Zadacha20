#include "wh.h"
int Autotest(void){
    Area* Test_area_1;
    Area* Test_area_2;
    Area* Test_pointer;
    int Number_of_nodes = 0;

    Test_area_1 = (Area*)malloc(sizeof(Area));
    if (!Test_area_1){
        printf("Error: cannot allocate memory\n");
        exit(-2);
    }
    Test_area_1->xs = (int*)malloc(sizeof(int));
    Test_area_1->ys = (int*)malloc(sizeof(int));
    Test_area_1->xs[0] = 1; Test_area_1->ys[0] = 1;
    Test_area_1->Number_of_dots = 1;
    Test_area_1->Pointer_to_next = NULL;
    Test_area_1->Pointer_to_previous = NULL;

    Test_area_2 = (Area*)malloc(sizeof(Area));
    if (!Test_area_2){
        printf("Error: cannot allocate memory\n");
        exit(-2);
    }
    Test_area_2->xs = (int*)malloc(sizeof(int));
    Test_area_2->ys = (int*)malloc(sizeof(int));
    Test_area_2->xs[0] = 2; Test_area_2->ys[0] = 2;
    Test_area_2->Number_of_dots = 1;
    Test_area_2->Pointer_to_previous = Test_area_1;
    Test_area_2->Pointer_to_next = NULL;
    Test_area_1->Pointer_to_next = Test_area_2;
    Test_pointer = Test_area_2;

    Check_areas(&Test_pointer);
    Number_of_nodes = Count(Test_pointer);
    if (Number_of_nodes == 1){
        printf("Autotest passed successfully\n");
    }
    else{
        printf("Autotest not passed\n");
        exit(-4);
    }
    return 0;
}
