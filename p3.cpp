#include <cstdlib>
#include <iostream>
#include <cstring>
#include <pthread.h>
#include <time.h>
using namespace std;
/* Функция, которую будет исполнять созданный поток */
void *thread_job(void *arg)
{
    clock_t tStart = clock();
    double a = 0;
    for(int i = 0; i < 1000000; i++){
        a += 1;
    }
    printf("Thread time taken: %.1fmcs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC*1000000);
}
int main()
{
    // Определяем переменные: идентификатор потока и код ошибки
    pthread_t thread;
    int err;
    clock_t tStart = clock();
    // Создаём поток
    err = pthread_create(&thread, NULL, thread_job, NULL);
    // Если при создании потока произошла ошибка, выводим
    // сообщение об ошибке и прекращаем работу программы
    if (err != 0)
    {
        cout << "Cannot create a thread: " << strerror(err) << endl;
        exit(-1);
    }
    printf("Time taken: %.1fmcs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC*1000000);
    // Ожидаем завершения созданного потока перед завершением
    // работы программы
    pthread_exit(NULL);
}