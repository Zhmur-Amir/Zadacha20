#include "wh.h"
int main(void){
    Area* Root_node;
    Area* Last_pointer;
    int x_1, y_1, number_of_nodes, status, input_x, input_y;

    Root_node = (Area*)malloc(sizeof(Area));
    if (!Root_node){
        printf("Error: cannot allocate memory\n");
        exit(-2);
    }
    Autotest();
    Root_node->Number_of_dots = 1;
    printf("Enter coordinates of the first dot:\n");
    printf("X: "); if (scanf("%d", &x_1) == 0){printf("Error: wrong input\n"); exit(-1);}
    printf("Y: "); if (scanf("%d", &y_1) == 0){printf("Error: wrong input\n"); exit(-1);}
    Root_node->Pointer_to_next = NULL; Root_node->Pointer_to_previous = NULL;
    Root_node->xs = (int*)malloc(sizeof(int)); Root_node->xs[0] = x_1;
    Root_node->ys = (int*)malloc(sizeof(int)); Root_node->ys[0] = y_1;

    Last_pointer = Root_node;
    Printer(Last_pointer);
    while (1==1){
        printf("If you want to add a dot, enter '1', to end execution - '2': ");
        scanf("%d", &status);
        if ((status != 1) && (status != 2)){
            printf("Error: wrong status\n");
            exit(-3);
        }
        if (status == 1){
            Add_dot(&Last_pointer);
            number_of_nodes = Count(Last_pointer);
            for (int u = 0; u < number_of_nodes; u++){
                Check_areas(&Last_pointer);
            }
            Printer(Last_pointer);
        }
        if (status == 2){
            printf("Execution complete\n");
            exit(0);
        }
    }
    return 0;
}
