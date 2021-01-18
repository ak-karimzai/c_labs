#include "../inc/main.h"

int main(int argc, char **argv)
{
    int rc = ok;
    FILE *input_file, *output_file;
    int *arr = NULL;
    int num_of_objs = 0;

    if (argc == 3 || (argc == 4 && strcmp(argv[KEY], "f") == ok))
    {
        input_file = fopen(argv[INPUT_FILE], "r");
        output_file = fopen(argv[OUTPUT_FILE], "w");
        if (input_file == NULL || output_file == NULL)
            rc = error;
        else
        {
            arr = procees_data_from_file(input_file, &num_of_objs);
            if (!arr)
                rc = error;
            else if (argc == 3)
            {
                mysort(arr, num_of_objs, sizeof(arr[0]), compare_int);
                write_objs_in_file(output_file, arr, arr + num_of_objs);
            }
            else if (argc == 4)
            {
                int *arr_lhs = NULL, *arr_rhs = NULL;
                if (key(arr, arr + num_of_objs, &arr_lhs, &arr_rhs) != ok)
                    rc = error;
                else
                {
                    mysort(arr_lhs, (arr_rhs - arr_lhs), sizeof(arr_rhs[0]), compare_int);
                    write_objs_in_file(output_file, arr_lhs, arr_rhs);
                    free(arr_lhs);
                }
            }
            fclose(output_file);
            fclose(input_file);
            free(arr);
        }
    }
    else
        rc = error;
    
    return rc;
}