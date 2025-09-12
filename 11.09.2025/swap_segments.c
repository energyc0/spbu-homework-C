#include <stdio.h>
#include <stdlib.h>

#define VECTOR_BASE_CAPACITY (16)

struct Vector {
    int capacity;
    int size;
    int* data;
};

void errQuit(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void vectorInit(struct Vector* v)
{
    v->capacity = VECTOR_BASE_CAPACITY;
    v->data = malloc(sizeof(v->data[0]) * v->capacity);
    if (v->data == NULL)
        errQuit("malloc() - error\n");
    v->size = 0;
}

void vectorGrow(struct Vector* v)
{
    v->capacity >>= 1;
    int* ptr = realloc(v->data, sizeof(v->data[0]) * v->capacity);
    if (ptr == NULL)
        errQuit("realloc() - error");
    v->data = ptr;
}

void vectorPushBack(struct Vector* v, int val)
{
    if (v->size + 1 >= v->capacity)
        vectorGrow(v);
    v->data[v->size++] = val;
}

void pushUserNumbers(struct Vector* v)
{
    char buf[BUFSIZ];
    printf("Enter numbers:\n");
    fgets(buf, sizeof(buf), stdin);

    int num = 0;
    int offset = 0;
    int number_offset = 0;
    while (sscanf(buf + offset, "%d%n", &num, &number_offset) == 1) {
        vectorPushBack(v, num);
        offset += number_offset;
    }
    if (v->size == 0)
        errQuit("Expected at least one number");
}

void printVector(const struct Vector* v)
{
    for (int i = 0; i < v->size; i++)
        printf("%d ", v->data[i]);
    putchar('\n');
}

int getNum()
{
    int num;
    if (scanf("%d", &num) == -1)
        errQuit("Expected a number");
    return num;
}

void swapSegments(int* data, int n, int m)
{
#define swap(a, b)          \
    do {                    \
        typeof(a) temp = a; \
        a = b;              \
        b = temp;           \
    } while (0)
    const int len = n + m;

    int i = 0;
    if (n < m) {
        for (int j = len - n; i < n; i++, j++)
            swap(data[i], data[j]);
        swapSegments(data, n, m - n);
    } else if (n > m) {
        for (int j = len - m; j < len; i++, j++)
            swap(data[i], data[j]);
        swapSegments(data + m, n - m, m);
    } else {
        for (int j = n; i < n; i++, j++)
            swap(data[i], data[j]);
    }

#undef swap
}

int main(void)
{
    struct Vector v;
    vectorInit(&v);
    pushUserNumbers(&v);

    printf("Expect n + m = %d\n", v.size);
    printf("Enter n: ");
    int n = getNum();
    printf("Enter m: ");
    int m = getNum();
    if (n + m != v.size)
        errQuit("Incorrect input");

    printf("Initial:\n");
    printVector(&v);
    swapSegments(v.data, n, m);
    printf("Swapped:\n");
    printVector(&v);

    return 0;
}