#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./inc/main.h"

int main(int argc, char **argv)
{
    int rc = ok;

    if (argc == 5 && (strcmp(argv[ACTION], ADDITION) == ok || strcmp(argv[ACTION], MULTI) == ok))
    {
        FILE *left_mat = fopen(argv[LHS_MAT], READ);
        FILE *right_mat = fopen(argv[RHS_MAT], READ);
        FILE *output = fopen(argv[RESULT], WRITE);
        if (left_mat && right_mat && output)
        {
            matrix *lhs_mat = get_matrix_from_file(left_mat);
            matrix *rhs_mat = get_matrix_from_file(right_mat);
            matrix *res = NULL;
            if (lhs_mat && rhs_mat)
            {
                if (strcmp(argv[ACTION], ADDITION) == ok)
                {
                    res = addition(lhs_mat, rhs_mat);
                    if (res)
                        add_mat_to_file(res, output);
                    else
                        rc = error;
                }
                else if (strcmp(argv[ACTION], MULTI) == ok)
                {
                    res = multiplication(lhs_mat, rhs_mat);
                    if (res)
                        add_mat_to_file(res, output);
                    else
                        rc = error;
                }
                else
                    rc = error;
                free_mat_if_not_null(res);
                free_mat(lhs_mat);
                free_mat(rhs_mat);
            }
            else
            {
                free_mat_if_not_null(lhs_mat);
                free_mat_if_not_null(rhs_mat);
                rc = error;
            }
            fclose(left_mat);
            fclose(right_mat);
            fclose(output);
        }
        else
        {
            close_if_opened_file(right_mat);
            close_if_opened_file(left_mat);
            close_if_opened_file(output);
            rc = error;
        }
    }
    else if (argc == 4 && strcmp(argv[ACTION], GAUSS) == ok)
    {
        FILE *matrix_data = fopen(argv[MATRIX], READ);
        FILE *output = fopen(argv[SOULUTION], WRITE);
        if (matrix_data && output)
        {
            matrix *mat = get_matrix_from_file(matrix_data);;
            if (mat)
            {
                if (gauss_solution(mat) == ok)
                    add_solution_to_file(mat, output);
                else
                    rc = error;
                free_mat(mat);
            }
            else
                rc = error;
            fclose(matrix_data);
            fclose(output);
        }
        else
        {
            close_if_opened_file(matrix_data);
            close_if_opened_file(output);
            rc = error;
        }
    }
    else
        rc = error;
    return rc;
}