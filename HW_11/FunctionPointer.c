#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*func)(void *);
    void *argument;
} Task;

typedef struct {
    int *arr;
    int lower;
    int upper;
} Data;

typedef struct{
    Task **tasks;   // task array
    int size;       // size of array
} Task_List;

int global_array[25];
Task_List *task_list;    // 指向工作清單的指標

void job1(void* argument) {
    Data *data = (Data *)argument;
    for (int i = data->lower, j = data->upper; i < j ;i++, j--) {
        int temp = data->arr[i];
        data->arr[i] = data->arr[j];
        data->arr[j] = temp;
    }
} // reverse

void job2(void* argument) {
    Data *data = (Data *)argument;
    for (int i = data->lower; i <= data->upper; i++)
        data->arr[i] = -data->arr[i];
} // minus

void job3(void* argument) {
    Data *data = (Data *)argument;
    for (int i = data->lower; i <= data->upper; i++)
        data->arr[i] *= 2;
} // double

void initTask(Task *task, void (*func)(void *), void *argument) {
    task->func = func;
    task->argument = (Data *)argument;
}

void executeTasks(Task_List *task_list) {
    for (int i = 0; i < task_list->size; i++) {
        void (*funcPtr)(void *) = task_list->tasks[i]->func;
        funcPtr((Data *)task_list->tasks[i]->argument);
    }
}

int main() {
    int n, i, upper, lower, method;
    // initial global_array
    for (i = 0; i < 25; ++i) {
        global_array[i] = i + 1;
    }
    scanf("%d", &n);
    task_list = (Task_List *)malloc(sizeof(Task_List));     // 開一個工作清單
    task_list->tasks = (Task **)malloc(sizeof(Task *) * n); // 工作清單裡的工作陣列有n個工作
    task_list->size = n;

    for (int i = 0; i < n; ++i) {   // 初始化n個工作
        scanf("%d%d%d",&method, &lower, &upper);    // 要哪種工作、要隊陣列工作的範圍
        Task *task = (Task*)malloc(sizeof(Task));   // 開一個工作 = 開一個函數
        Data *data = (Data*)malloc(sizeof(Data));   // 開一筆資料 = 存入陣列範圍
        data->arr = global_array;
        data->lower = lower;
        data->upper = upper;        // 把陣列和範圍放進去data
        switch(method) {
            case 0:
                initTask(task, job1, data);
                break;
            case 1:
                initTask(task, job2, data);
                break;
            case 2:
                initTask(task, job3, data);
                break;
            default:
                break;
        }
        task_list->tasks[i] = task;
    }
    // execute job
    executeTasks(task_list);

    // print out result
    for(i=0; i<24; ++i){
        printf("%d ", global_array[i]);
    }printf("%d\n",global_array[24]);

    for(i=0; i<n; ++i){
        free(task_list->tasks[i]->argument);
        free(task_list->tasks[i]);
    } free(task_list);
    return 0;
}