#include <cstdlib>
#include <iostream>
#include <cstring>
#include <pthread.h>
using namespace std;
/* Функция, которую будет исполнять созданный поток */
void *thread_job(void *arg)
{
    cout << "Thread is running..." << endl;
}
int main()
{
    int n = 0;
    cout << "Enter number of threads: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        // Определяем переменные: идентификатор потока и код ошибки
        pthread_t thread;
        int err;
        // Создаём поток
        err = pthread_create(&thread, NULL, thread_job, NULL);
        // Если при создании потока произошла ошибка, выводим
        // сообщение об ошибке и прекращаем работу программы
        if (err != 0)
        {
            cout << "Cannot create a thread: " << strerror(err) << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}