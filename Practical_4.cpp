// Write a program using pthreads to demonstrate the reader writer synchronization problem.
// Implement appropriate synchronization. Show the different results with and without
// synchronization
 
//with
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t x, y;
int readercount = 0;

void* reader(void* arg) {
    sem_wait(&x);
    readercount++;
    if (readercount == 1) {
        sem_wait(&y); // First reader locks the resource
    }
    sem_post(&x);

    cout << "Reader " << readercount << " is reading\n";
    sleep(1);

    sem_wait(&x);
    readercount--;
    if (readercount == 0) {
        sem_post(&y); // Last reader releases the resource
    }
    sem_post(&x);

    cout << "Reader " << readercount + 1 << " has finished reading\n";
    return NULL;
}

void* writer(void* arg) {
    cout << "Writer is trying to write\n";
    sem_wait(&y);
    cout << "Writer is writing...\n";
    sleep(2);
    cout << "Writer has finished writing\n";
    sem_post(&y);
    return NULL;
}

int main() {
    int n;
    cout << "Enter number of readers/writers: ";
    cin >> n;

    pthread_t readers[n], writers[n];

    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);

    for (int i = 0; i < n; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&x);
    sem_destroy(&y);

    return 0;
}




//without



// #include<iostream>
// #include<pthread.h>
// #include<unistd.h>
// //#include<semaphore.h>
// using namespace std;

// //sem_t x,y;
// int readcount;

// void* readers(void* args)
// {

//       //sem_wait(&x);
//     readcount++;

//     if(readcount==1)
//     {
//           //sem_wait(&y);
//     }
//     //sem_post(&x);

//     cout<<"reading"<<readcount<<endl;
//     sleep(1);

//     //sem_wait(&x);
//     readcount--;
//     if(readcount==0)
//     {
// //        sem_post(&y);
//     }
//   //  sem_post(&x);
    
//     cout<<"done reading"<<readcount+1<<endl;
//     return NULL;
// }


// void* writers(void* args)
// {

// cout<<"writer wants to "<<endl;
// //sem_wait(&y);
// cout<<"writer writes"<<endl;
// sleep(2);
// cout<<"writer done write"<<endl;
// //sem_post(&y);
    
// return NULL;
// }

// int main()
// {
// int n;


// cout<<"Enter no of reader and writer"<<endl;
// cin>>n;

// pthread_t reader[n],writer[n];


// //sem_init(&x,0,1);
// //sem_init(&y,0,1);

// for(int i=0;i<n;i++)
// {
//  pthread_create(&reader[i], NULL, readers, NULL);
//  pthread_create(&writer[i], NULL, writers, NULL);
// }


// for(int i=0;i<n;i++)
// {
//  pthread_join(reader[i],NULL);
//  pthread_join(writer[i],NULL);
// }

// //sem_destroy(&x);
// //sem_destroy(&y);
// //

//     return 0;

// }