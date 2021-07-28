#ifndef H_MERGESORT
#define H_MERGESORT

# include <pthread.h>
# include <cstdlib>
# include <vector>

template <typename T>
struct thread_data{
    int length;
    T *ptr;
    int NumThreads;
};

template <typename T>
void MyMerge(T *ptr, int length);

template <typename T>
void MySort(T *ptr, int length, int NumThreads);

template <typename T>
void *merge_sort(void *varargin){
    thread_data<T> *datas_struct;
    datas_struct = reinterpret_cast<thread_data<T> *>(varargin); 
    MySort(datas_struct->ptr,datas_struct->length, datas_struct->NumThreads);
    return nullptr;
}

template <typename T>
void MySort(T *ptr,int length, int NumThreads){
    if (length <= 2) {
        std::sort(ptr, ptr+length);
    } else {
        int length1 = length/2;
        int length2 = length - length1;

        if(NumThreads>1) {
            thread_data<T> td;
            td.ptr = ptr;
            td.length = length1;
            td.NumThreads = NumThreads/2;
            pthread_t threads;
            pthread_create(&threads, NULL, merge_sort<T>, (void *)&td);
            NumThreads = NumThreads/2;
            MySort<T>(ptr+length1, length2, NumThreads);
            pthread_join (threads, nullptr);
        } else {
            MySort<T>(ptr, length1, NumThreads/2);
            MySort<T>(ptr+length1, length2, NumThreads/2);
        }
        MyMerge<T>(ptr,length);
    }
}

template <typename T>
void MyMerge(T *ptr, int length){
    std::inplace_merge(ptr, ptr+length/2 ,ptr+length);
}


#endif