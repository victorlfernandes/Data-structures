#define STACK_SIZE 100

typedef struct stack stack_t;

stack_t *create();

void destroy(stack_t *s);

int is_full(stack_t *s);

int is_empty(stack_t *s);

void push(stack_t *s, void *x);

void *pop(stack_t *s, void **x);

void *top(stack_t *s);