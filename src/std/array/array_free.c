#include <YutsuOS/std/array.h>
#include <YutsuOS/std/memory.h>

/**
 * @brief Liberates the memory allocated for an Array structure.
 *
 * This function iterates through the 'data' array, freeing each individual
 * string, and then frees the 'data' array itself. It's crucial to call this
 * after you are done with an array created by array_from_string to prevent
 * memory leaks.
 *
 * @param arr A pointer to the Array to be freed.
 */
void array_free(Array *arr)
{
    if (!arr || !arr->data)
    {
        return;
    }

    for (u32 i = 0; i < arr->size; ++i)
    {
        if (arr->data[i])
        {
            liberate((void *)arr->data[i]);
        }
    }

    liberate(arr->data);

    arr->data = NULL;
    arr->size = 0;
}
