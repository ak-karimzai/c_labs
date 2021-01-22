#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node *next;
} node_t;

typedef struct
{
    node_t *top;
} stack_t;

node_t *create_node(char x)
{
    node_t *temp = malloc(sizeof(node_t));
    if (temp)
    {
        temp->data = x;
        temp->next = NULL;
    }
    return temp;
}

void push(stack_t *stk, node_t *new_node)
{
    if (new_node)
    {
        if (stk->top == NULL)
            stk->top = new_node;
        else
        {
            new_node->next = stk->top;
            stk->top = new_node;
        }
    }
    else
    {
        puts("stackoverflow!");
    }
}

char pop(stack_t *stk)
{
    node_t *temp;
    char x = 0;

    if (stk->top)
    {
        temp = stk->top;
        x = stk->top->data;
        stk->top = stk->top->next;
        free(temp);
    }
    return x;
}

int is_empty_stk(stack_t *stk)
{
    return stk->top == NULL;
}

char *get_string(void)
{
    char *str = NULL;
    size_t len;
    ssize_t read = getline(&str, &len, stdin);
    if (read > 0)
    {
        str[read - 1] = '\0';
    }
    return str;
}

void free_stk(stack_t *stk)
{
    node_t *temp;
    while (stk->top)
    {
        temp = stk->top;
        stk->top = stk->top->next;
        free(temp);
    }
    free(stk);
}

char *push_to_stack(stack_t *stk, char *str)
{
    while (*str && *str != '*')
    {
        push(stk, create_node(*str));
        str++;
    }
    str++;
    return str;
}

void pop_from_stack(stack_t *stk, char *str)
{
    if (is_empty_stk(stk) && !(*str))
    {
        puts("Yes");
    }
    else
    {
        while (!is_empty_stk(stk) && *str)
        {
            if (*str != pop(stk))
            {
                puts("No");
                return;
            }
            *str++;
        }
        if (*str || !is_empty_stk(stk))
        {
            puts("No");
        }
        else
        {
            puts("Yes");
        }
    }
}

void check(stack_t *stk, char *str)
{
    str = push_to_stack(stk, str);
    pop_from_stack(stk, str);
}

int main()
{
    stack_t *stk = calloc(1, sizeof(stack_t));
    if (stk)
    {
        char *str = get_string();
        if (str)
        {
            check(stk, str);
            free(str);
        }
        free_stk(stk);
    }
    return 0;
}