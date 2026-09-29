#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_HISTORY 5 // Maximum capacity of history stack
#define MAX_LINE 80   // Maximum length of input command

// Data structure used to define a stack of maximum MAX_HISTORY values.
typedef struct
{
    char elements[MAX_HISTORY][MAX_LINE];
    int top;
    int capacity; // Number of non-null elements in elements array
    int size;
} Stack;

// Initialize stack values
void initialize_stack(Stack *stack)
{
    stack->top = -1;
    stack->capacity = 0;
    stack->size = 0;
}

// Push element onto stack
void push(Stack *stack, const char *element)
{
    stack->top = (stack->top + 1) % MAX_HISTORY; // Move `top` pointer to next position
    strncpy(stack->elements[stack->top], element, MAX_LINE);
    stack->size++;
    stack->capacity = (stack->capacity < MAX_HISTORY) ? (stack->capacity + 1) : MAX_HISTORY;
}

// Return element from top of stack
const char *peek(Stack *stack)
{
    return (stack->elements[stack->top]);
}

// Return `1` if stack is empty
int is_empty(Stack *stack)
{
    return (stack->size == 0);
}

// Print last five elements in history, indexed
void print_history(Stack *stack)
{
    int top = stack->top;
    int size = stack->size;
    int capacity = stack->capacity;

    for (int i = 0; i < capacity; i++)
    {
        int index = (i > top) ? (top - i) + MAX_HISTORY : top - i;
        printf("%d %s\n", size - i, stack->elements[index]);
    }
}

int main(void)
{
    char input[MAX_LINE];         // User input
    char *args[MAX_LINE / 2 + 1]; // Command line arguments
    int should_run = 1;           // Flag to determine when to exit program

    Stack history;
    initialize_stack(&history);

    while (should_run)
    {
        printf("osh> ");
        fflush(stdout);

        // Read user input, handle end-of-file and input errors
        fgets(input, MAX_LINE, stdin);

        // Remove new-line character at end of input string
        input[strcspn(input, "\n")] = '\0';

        // If input string is "history", print history then continue to next loop iteration
        if (strcmp(input, "history") == 0)
        {
            print_history(&history);
            continue;
        }
        // If input string is "!!", retrieve last command
        else if (strcmp(input, "!!") == 0)
        {
            if (is_empty(&history))
            {
                printf("No commands in history.\n"); // If the history stack is empty, print an error message
                continue;
            }
            else
            {
                strcpy(input, peek(&history)); // Write the most recent command to input by retrieving the top element from the stack
            }
        }
        else
        {
            push(&history, input); // Otherwise, push the command to the history stack
        }

        // When the user enters `exit`, set should_run to 0 and terminate the program
        if (strcmp(input, "exit") == 0)
        {
            should_run = 0;
            break;
        }

        // Convert user input into tokens
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL)
            args[++i] = strtok(NULL, " ");
        args[i] = NULL;

        // Check if parent process should execute concurrently with child, indicated by an "&" at the end
        int is_parent = 0;
        if (i > 0 && strcmp(args[i - 1], "&") == 0)
        {
            is_parent = 1;
            args[i - 1] = NULL;
        }

        // Create child process
        pid_t pid = fork();

        if (pid == 0)
        {
            execvp(args[0], args); // Execute the input argument in the child process
        }
        else
        {
            if (is_parent == 0)
            {
                waitpid(pid, NULL, 0); // If not is_parent, then this process shouldn't execute concurrently with the child, so wait for the child process to exit
            }
        }
    }
    return 0;
}