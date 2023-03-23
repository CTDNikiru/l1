#include <cstdlib>
#include <iostream>
#include <cstring>
#include <pthread.h>
using namespace std;

struct thread_params {
    // Количество операций внутри потока
    int param1;
    int param2;
};

void *thread_job(void *arg)
{
    // Преобразуем указатель на параметр к правильному типу
    thread_params *params = (thread_params *) arg;
    // Выводим параметр на экран
    cout << "Thread is running... Parameter1 is " << params->param1 << " Parameter2 is " << params->param2 << endl;
}
int main(int argc, char *argv[])
{
    // Определяем переменные
    pthread_t thread;
    int param1;
    int param2;
    int err;
    string s_arg;
    cout << "Enter parameter: ";
    cin >> s_arg;
    param1 = stoi(s_arg);
    cout << "Enter parameter: ";
    cin >> s_arg;
    param2 = stoi(s_arg);
    thread_params params;
    params.param1 = param1;
    params.param2 = param2;
    // Создаем поток
    err = pthread_create(&thread, NULL, thread_job, (void *)&params);
    if (err != 0)
    {
        cout << "Cannot create a thread: " << strerror(err) << endl;
        exit(-1);
    }
    // Ожидаем завершения работы потока
    pthread_join(thread, NULL);
    if (err != 0)
    {
        cout << "Cannot join a thread: " << strerror(err) << endl;
        exit(-1);
    }
}