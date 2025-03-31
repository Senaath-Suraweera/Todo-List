#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    char todo[200];
    char todoDescription[1000];
}TODO;

typedef struct Node
{
    TODO ToDo;
    struct Node *next;
}Node;


Node *head = NULL;

Node* createNode(char todo[], char todoDescription[])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->ToDo.todo, todo);
    strcpy(newNode->ToDo.todoDescription, todoDescription);
    newNode->next = NULL;
    return newNode;
}

void addTodo(char todo[], char todoDescription[])
{
    Node *newNode = createNode(todo, todoDescription);
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    printf("Todo added successfully\n");
}

void updateTodo(char todo[], char todoDescription[], char initialTodo[])
{
    Node *temp = head;
    while(temp != NULL)
    {
        if(strcmp(temp->ToDo.todo, initialTodo) == 0)
        {
            strcpy(temp->ToDo.todo, todo);
            strcpy(temp->ToDo.todoDescription, todoDescription);
            printf("Todo updated successfully\n");
            return;
        }
        temp = temp->next;
    }
    printf("Todo not found\n");
}

void deleteTodo(char todo[])
{
    Node *temp = head;
    Node *prev = NULL;

    while(temp != NULL)
    {
        if(strcmp(temp->ToDo.todo, todo) == 0)
        {
            if(prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            printf("Todo deleted successfully\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Todo not found\n");
}

int returnIndex(char todo[])
{
    int num = 0;
    Node *temp = head;
    while(temp != NULL)
    {
        if(strcmp(temp->ToDo.todo, todo) == 0)
            return num + 1;
        num++;
        temp = temp->next;
    }
    return -1;
}

void serialize(Node *head){
    FILE *file = fopen("resources/todo.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Node *temp = head;
    while(temp != NULL){
        fprintf(file, "%d. %s : %s\n", returnIndex(temp->ToDo.todo), temp->ToDo.todo, temp->ToDo.todoDescription);
        temp = temp->next;
    }
    fclose(file);
}

void deserialize()
{
    FILE *fp;
    fp = fopen("resources/todo.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char todo[200];
    char todoDescription[1000];
    while(fgets(todo, sizeof(todo), fp) != NULL)
    {
        todo[strcspn(todo, "\n")] = 0;
        fgets(todoDescription, sizeof(todoDescription), fp);
        todoDescription[strcspn(todoDescription, "\n")] = 0;
        addTodo(todo, todoDescription);
    }
    fclose(fp);
}

int main()
{
    deserialize();
    printf("=====================================================================\n");
    printf("Welcome to TODO List\n");
    printf("=====================================================================\n");
    printf("1. Add a new todo\n");
    printf("2. Update an exsisting todo\n");
    printf("3. Delete a todo\n");
    printf("4. Display all todos\n");
    printf("5. Exit\n");
    printf("=====================================================================\n");

    int option;
    Node *temp;
    char initialTodo[200];
    bool running = true;
    char todo[200];
    char todoDescription[1000];
    

    while(running)
    {
        printf("=====================================================================\n");
        printf("Select an option:\n");
        printf("=====================================================================\n");

        scanf("%d", &option);
        printf("=====================================================================\n");

        switch(option)
        {
            case 1:
                printf("Enter todo: ");
                getchar(); 
                fgets(todo, sizeof(todo), stdin);
                todo[strcspn(todo, "\n")] = 0;

                printf("Enter todo description: ");
                fgets(todoDescription, sizeof(todoDescription), stdin);
                todoDescription[strcspn(todoDescription, "\n")] = 0;

                addTodo(todo, todoDescription);
                serialize(head);
                break;

            case 2:
                printf("Enter todo to be updated: ");
                scanf("%s", initialTodo);
                printf("Enter new todo: ");
                scanf("%s", todo);
                printf("Enter new todo description: ");
                scanf("%s", todoDescription);
                updateTodo(todo, todoDescription, initialTodo);
                serialize(head);
                break;
            case 3:
                printf("Enter todo to be deleted: ");
                scanf("%s", todo);
                deleteTodo(todo);
                serialize(head);
                break;
            case 4:
                temp = head;
                while(temp != NULL)
                {
                    printf("%d. %s : %s\n", returnIndex(temp->ToDo.todo), temp->ToDo.todo, temp->ToDo.todoDescription);
                    temp = temp->next;
                }
                break;
            case 5:
                running = false;
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option\n");
                break;
                
                
        }
    }

}