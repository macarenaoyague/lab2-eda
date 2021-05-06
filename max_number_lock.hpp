#pragma once
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using namespace std;

#define MIN 1.17549e-038

vector<float> numbers;

float max_number; 
mutex mut_max_numb;

void find_max(int start, int end) {
  for (int i = start; i <= end; i++)
  {
    mut_max_numb.lock();
    if (numbers[i] > max_number)
      max_number = numbers[i];
    mut_max_numb.unlock();
  }
}

void create_random_numbers(int n){
  for(int i = 0; i < n; i++)
    numbers.push_back(rand() % 100 + rand() % 100 / 100);
}


void problema1(){
  int N = rand() % 1000 + 1;
  max_number = MIN;

  create_random_numbers(N);

  const auto threads_count = thread::hardware_concurrency();

  int num_thread = N/threads_count;
  int res = N % threads_count;
  
  int start = 0;
  int end = num_thread - 1;

  thread threads[threads_count];
  
  for(auto && thread_ : threads){
    if (res){ 
      end += 1; 
      res--;}
    thread_ = thread(find_max, start, end);
    start = end + 1;
    end = start + num_thread - 1;
  }

  for(auto && thread : threads)
    thread.join();
  
  float theoretical_max = numbers[0];
  for(int i = 0; i < N; i++)
    if (theoretical_max < numbers[i]) theoretical_max = numbers[i];

  max_number == theoretical_max ? cout<<"Son iguales"<<endl : cout<<"No son iguales"<<endl;
  cout << theoretical_max << endl;

  cout << "The max value is " << max_number << endl;
  
}
