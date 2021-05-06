#include "problema1.hpp"
#include "problema2.hpp"

// funcion para generar los threads
// funcion para generar la data -> templates, no solo float
// tests

int main() {

  srand(time(NULL));

  problema1();

  const auto thread_count = thread::hardware_concurrency();
  Stack<char>* s = new Stack<char>;
  char letter = 'A';
  thread threads[thread_count];

  for(auto && thread_ : threads){
    thread_ = thread(push_and_pop<char>, s, letter, rand()%50 + 1);
    letter++;
  }

  for(auto && thread : threads)
    thread.join();

  s->print();
  print_count(s);

	return 0;
}


