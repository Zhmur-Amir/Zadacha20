#include "wh.h"
int Add_dot(Area** Last_pointer){
    int input_x, input_y, current_area_size, curr_dot_x, curr_dot_y, add_flag;
    Area* Temp_area;
    Area* Pointer_to_node;
    Area* Pointer_from_node;

    Pointer_to_node = (*Last_pointer);
    Pointer_from_node = Pointer_to_node->Pointer_to_previous;

    printf("Enter coordinates of a new dot:\n");
    printf("X: "); if (scanf("%d", &input_x) == 0){printf("Error: wrong input\n"); exit(-1);}
    printf("Y: "); if (scanf("%d", &input_y) == 0){printf("Error: wrong input\n"); exit(-1);}

    while (1==1){  //Passing through nodes
        add_flag = 0;
        current_area_size = Pointer_to_node->Number_of_dots;
        for (int i = 0; i < current_area_size; i++){
            if ((abs(Pointer_to_node->xs[i] - input_x) <= 1) && (abs(Pointer_to_node->ys[i] - input_y) <= 1)){
                add_flag++;
                Pointer_to_node->Number_of_dots++;
                Pointer_to_node->xs = (int*)realloc(Pointer_to_node->xs, sizeof(int)*Pointer_to_node->Number_of_dots);
                Pointer_to_node->ys = (int*)realloc(Pointer_to_node->ys, sizeof(int)*Pointer_to_node->Number_of_dots);
                if ((!Pointer_to_node->xs) || (!Pointer_to_node->ys)){
                    printf("Error: cannot allocate memory\n");
                    exit(-2);
                }
                Pointer_to_node->xs[Pointer_to_node->Number_of_dots - 1] = input_x;
                Pointer_to_node->ys[Pointer_to_node->Number_of_dots - 1] = input_y;
                return 0;
            }
        }
        Pointer_to_node = Pointer_to_node->Pointer_to_previous;
        if ((Pointer_from_node == NULL) || (add_flag > 0)){
            break;
        }
        Pointer_from_node = Pointer_to_node->Pointer_to_previous;
    }
    if (add_flag == 0){
        Temp_area = (Area*)malloc(sizeof(Area));
        Temp_area->xs = (int*)malloc(sizeof(int));
        Temp_area->ys = (int*)malloc(sizeof(int));
        if ((!Temp_area->xs) || (!Temp_area->ys)){
            printf("Error: cannot allocate memory\n");
            exit(-2);
        }
        Temp_area->Number_of_dots = 1;
        Temp_area->xs[0] = input_x;
        Temp_area->ys[0] = input_y;
        Temp_area->Pointer_to_previous = (*Last_pointer);
        Temp_area->Pointer_to_next = NULL;
        (*Last_pointer) = Temp_area;
    }

    return 0;
}

int Count(Area* Last_pointer){
    int number_of_nodes = 0;
    Area* Pointer_to_node;
    Area* Pointer_from_node;

    Pointer_to_node = Last_pointer;
    Pointer_from_node = Pointer_to_node->Pointer_to_previous;
    if (Pointer_to_node == NULL){
        return 0;
    }
    while (1==1){
        number_of_nodes++;
        if (Pointer_from_node == NULL){
            break;
        }
        Pointer_to_node = Pointer_to_node->Pointer_to_previous;
        Pointer_from_node = Pointer_to_node->Pointer_to_previous;
    }

    return number_of_nodes;
}

int Check_areas(Area** Last_pointer){ //Checks for areas intersections
    Area* Pointer_to_node;
    Area* Pointer_from_node;
    Area* Temp_pointer;
    Area* Pointer_from_node_temp;
    Area* Pointer_to_node_temp;
    Area* Pointer_to_previous_temp;

    int number_of_nodes, prev_len = 0, curr_len, temp_len;

    Pointer_to_node = (*Last_pointer);
    Pointer_from_node = Pointer_to_node->Pointer_to_previous;

    number_of_nodes = Count(*Last_pointer);

    Pointer_to_node = (*Last_pointer);
    Pointer_from_node = Pointer_to_node->Pointer_to_previous;

    if (number_of_nodes == 1){
        return 0;
    }
    for (int i = 0; i < number_of_nodes - 1; i++){ //Passing through areas
        Pointer_to_node_temp = Pointer_to_node->Pointer_to_previous;
        Pointer_from_node_temp = Pointer_to_node_temp->Pointer_to_previous;
        Pointer_to_previous_temp = Pointer_to_node;
        for (int j = 0; j < number_of_nodes - i - 1; j++){ //For current area, checking if it collides with other
            curr_len = Pointer_to_node->Number_of_dots;
            for (int k = 0; k < curr_len; k++){ //For current area, passing through its dots
                temp_len = Pointer_to_node_temp->Number_of_dots;
                for (int h = 0; h < temp_len; h++){ //For temp area, passing through its dots
                    if ((abs(Pointer_to_node->xs[k] - Pointer_to_node_temp->xs[h]) <= 1) && (abs(Pointer_to_node->ys[k] - Pointer_to_node_temp->ys[h]) <= 1)){
                        prev_len = Pointer_to_node->Number_of_dots;
                        Pointer_to_node->Number_of_dots = Pointer_to_node->Number_of_dots + Pointer_to_node_temp->Number_of_dots;
                        Pointer_to_node->xs = (int*)realloc(Pointer_to_node->xs, sizeof(int)*Pointer_to_node->Number_of_dots);
                        Pointer_to_node->ys = (int*)realloc(Pointer_to_node->ys, sizeof(int)*Pointer_to_node->Number_of_dots);
                        if ((!Pointer_to_node->xs) || (!Pointer_to_node->ys)){
                            printf("Error: cannot allocate memory\n");
                            exit(-2);
                        }
                        for (int t = 0; t < Pointer_to_node_temp->Number_of_dots; t++){
                            Pointer_to_node->xs[prev_len + t] = Pointer_to_node_temp->xs[t];
                            Pointer_to_node->ys[prev_len + t] = Pointer_to_node_temp->ys[t];
                        }
                        Pointer_to_previous_temp->Pointer_to_previous = Pointer_from_node_temp;
                        return 0;
                    }
                }
            }
            if (Pointer_from_node_temp == NULL){
                continue;
            }
            Pointer_to_previous_temp = Pointer_to_node_temp;
            Pointer_to_node_temp = Pointer_to_node_temp->Pointer_to_previous;
            Pointer_from_node_temp = Pointer_to_node_temp->Pointer_to_previous;
        }
        Pointer_to_node = Pointer_to_node->Pointer_to_previous;
        Pointer_from_node = Pointer_to_node->Pointer_to_previous;
    }
    return 0;
}

int Printer(Area* Last_pointer){
    Area* Pointer_to_node;
    Area* Pointer_from_node;
    int index = 0;

    Pointer_to_node = Last_pointer;
    Pointer_from_node = Pointer_to_node->Pointer_to_previous;

    while (1==1){
        if (Pointer_to_node->Number_of_dots == 0){
            continue;
        }
        printf("Area %d:\n", index+1);
        for (int i = 0; i < Pointer_to_node->Number_of_dots; i++){
            printf("(%d, %d) ", Pointer_to_node->xs[i], Pointer_to_node->ys[i]);
            printf("\n");
        }
        index++;
        if (Pointer_from_node == NULL){
            break;
        }
        Pointer_to_node = Pointer_to_node->Pointer_to_previous;
        Pointer_from_node = Pointer_to_node->Pointer_to_previous;
    }
    return 0;
}

