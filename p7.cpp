#include <cstdlib>
#include <iostream>
#include <cstring>
#include <pthread.h>
#include <chrono>
#include <cmath>

using namespace std;

struct thread_params
{
    float *arr_ptr;  // Указатель на начало отсчета
    int array_block; // Размер блока
    int func_num;    // Функция
};

// Выбор функций
float func_choice(float input_number, int func_num)
{
    float result;
    switch (func_num)
    {
    case 1:
        result = sin(input_number);
        break;
    case 2:
        result = cos(input_number);
        break;
    case 3:
        result = sqrt(input_number);
        break;
    case 4:
        result = abs(input_number);
        break;
    case 5:
        result = exp(input_number);
        break;
    case 6:
        result = log(input_number);
        break;
    }
    return result;
}

void *thread_job(void *arg)
{
    int err;
    thread_params *params = (thread_params *)arg;
    for (int i = 0; i < params->array_block; i++)
    {
        *(params->arr_ptr + i) = func_choice(*(params->arr_ptr + i), params->func_num);
    }
}

int main(int argc, char *argv[])
{
    string temp;
    cout << "Array size: ";
    cin >> temp;
    int a_len = stoi(temp);
    cout << "Thread count: ";
    cin >> temp;
    int t_count = stoi(temp);
    cout << "Func choice: ";
    cin >> temp;
    int func_choice = stoi(temp);

    if (t_count > a_len)
    {
        cout << "Array length is less than the number of threads" << endl;
        exit(-1);
    }

    int array_block = a_len / t_count;
    int remain = a_len % t_count;

    pthread_t *thread_arr = new pthread_t[t_count];
    float *test_array = new float[a_len];

    //Распределяем 
    for (int i = 0; i < a_len; i++)
    {
        test_array[i] = (float)i;
    }

    thread_params *params = new thread_params[t_count];

    int err;
    for (unsigned int i = 0; i < t_count; i++)
    {
        params[i].arr_ptr = test_array + i * array_block;
        params[i].array_block = array_block;
        params[i].func_num = func_choice;
        if (i == t_count - 1)
        {
            params[i].array_block += remain;
        }

        err = pthread_create(thread_arr + i, NULL, thread_job, (void *)(params + i));
        if (err != 0)
        {
            cout << "Cannot create a thread: " << strerror(err) << endl;
            exit(-1);
        }
    }

    // Ждём завершения всех дочерних потоков
    for (int i = 0; i < t_count; i++)
    {
        pthread_join(thread_arr[i], NULL);
    }

    for (int i = 0; i < a_len; i++)
    {
        cout << "arr[" << i << "] = " << test_array[i] << endl;
    }
}