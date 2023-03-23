#include <cstdlib>
#include <iostream>
#include <cstring>
#include <pthread.h>
using namespace std;
/* Функция, которую будет исполнять созданный поток */
void *thread_job(void *arg)
{
    int err;
    // Получаем индентефикатор текущего потока
    pthread_t thread;
    thread = pthread_self();

    // Получаем переменную с информацией об атрибутах текущего потока
    pthread_attr_t attr;
    pthread_getattr_np(thread, &attr);
    if (err != 0)
    {
        cout << "Cannot get thread attributes: " << strerror(err) << endl;
        exit(-1);
    }

    //Тип создаваемого потока
    int detach_state;
    pthread_attr_getdetachstate(&attr, &detach_state);
    if (err != 0)
    {
        cout << "Cannot get detachet state: " << strerror(err) << endl;
        exit(-1);
    }

    //Размер охранной зоны, байт
    size_t guard_size;
    pthread_attr_getguardsize(&attr, &guard_size);
    if (err != 0)
    {
        cout << "Cannot get guard size: " << strerror(err) << endl;
        exit(-1);
    }

    //Размер стека, байт
    size_t stack_size;

    //Адрес стека
    void *stack_addr;
    pthread_attr_getstack(&attr, &stack_addr, &stack_size);
    if (err != 0)
    {
        cout << "Cannot get stack: " << strerror(err) << endl;
        exit(-1);
    }

    cout << "Detach state: ";
    if (detach_state == PTHREAD_CREATE_JOINABLE)
    {
        cout << "joinable";
    }
    else
    {
        cout << "detached";
    }
    cout << endl;

    cout << "Guard size: " << guard_size << endl;
    cout << "Stack address: " << stack_addr << endl;
    cout << "Stack size: " << stack_size << endl;
}
int main()
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
    // Ожидаем завершения созданного потока перед завершением
    // работы программы
    pthread_exit(NULL);
}