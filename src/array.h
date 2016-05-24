#define ARRAY_INITIAL_CAPACITY 10

#define DEFINE_ARRAY(T) typedef struct {T **data;int length;int capacity;} T_array;

typedef struct
{
	void (*free)();
} freeable;

typedef struct
{
	freeable *data;
	int length;
	int capacity;
} array;

void array_init(struct array *array)
{
	array->length = 0;
	array->capacity = ARRAY_INITIAL_CAPACITY;
	array->data = malloc(sizeof(void *) * array->capacity);
}

//TODO(Lucas): implement

void array_free(struct array *array)
{
	for (int i = 0; i < array->length; i++)
		array->data[i].free();
	free(array->data);
}

//array_reserve();

//array_push();

//array_get();

//array_set();
