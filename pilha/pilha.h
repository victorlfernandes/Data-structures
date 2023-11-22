#define STACK_SIZE 100

typedef int element;
typedef struct stack stack_t;

stack_t *create();

void destroy(stack_t *s);

int is_full(stack_t *s);

int is_empty(stack_t *s);

void push(stack_t *s, element x);

element pop(stack_t *s);

element top(stack_t *s);