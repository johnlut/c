#include <stdio.h>
#include <stdlib.h> 

typedef struct node
{
    int val; 
    struct node * next; 
} node_t;

void app(node_t * head, int val)
{   
    node_t * current = head; 

    while(current->next != NULL)
    {
        current = current->next; 
    }

    current->next = malloc(sizeof(node_t)); 
    current->next->val = val; 
    current->next->next = NULL; 

}

void add(node_t ** head, int val)
{
    node_t * new_node = malloc(sizeof(node_t)); 

    new_node->val = val; 
    new_node->next = *head; 
    *head = new_node; 
}

void rm_f(node_t ** head)
{

    node_t * next; 

    if(*head == NULL)
    {
        perror("empty list"); 
    }

    next = (*head)->next;
    free(*head);
    *head = next; 

}

void rm_l(node_t * head)
{

    node_t * current = head;

    if(head == NULL)
    {
        perror("empty list"); 
    }

    if(head->next == NULL)
    {
        free(head); 
    }

    while(current->next->next != NULL)
    {
        current = current->next; 
    }

    free(current->next);
    current->next = NULL; 

}

void rm_n(node_t ** head, int n)
{

    node_t * current = *head; 
    node_t * temp = NULL;

    if(n == 0)
    {
        rm_f(head);
    }

    for(int i = 0; i < n - 1; i++)
    {
        if(current->next == NULL)
        {
            perror("out of bounds");
        }

        current = current->next; 
    }
    
    temp = current->next; 
    current->next = temp->next; 

}

int rm_x(node_t ** head, int x)
{
    node_t * current = *head; 
    node_t * temp = NULL; 

    if(current->val == x)
    {
        rm_f(head);
        return 0;
    }

    while(current->next->next != NULL)
    {
        if(current->next->val == x)
        {
            break;
        }
        current = current->next;
    }

    if((current->next == NULL) && current->val != x)
    {
        return -1; 
    }

    temp = current->next; 
    current->next = temp->next; 
    free(temp); 


    return 0; 
}

int populate(node_t ** head, int *list, int len)
{
    
    //int len = sizeof(list) / sizeof(list[0]); 
    //printf("len: %d\n", len);

    for(int i = 0; i < len; i++)
    {
        //add(head, list[i]); 
        printf("%d\n", list[i]);
    }
    return 0; 
}



void print(node_t * head)
{

    node_t * current = head; 

    while(current != NULL)
    {
        printf("%d\n", current->val);
        current = current->next; 
    }

}



int main() 
{

    node_t * my_list; 
    
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int len = sizeof(list) / sizeof(list[0]); 
    
    populate(&my_list, list, len); 

    print(my_list);
    //printf("\n");
    
   
    //rm_x(&my_list, 7);
    //rm_x(&my_list, 1);
    //rm_f(&my_list);
    //rm_l(my_list); 

    //print(my_list);


    return 1; 
}