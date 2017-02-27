#include <boost/thread/thread.hpp>

#include <iostream>

// Small printer class which will be used in a shared_ptr
class Printer
{
public:

  void print(size_t threadNum)
  {
    std::cout << "Hello from thread " << threadNum << std::endl;
  }
};

// global object, shared by all threads
boost::shared_ptr<Printer> globalPrinter(new Printer());

// Prints every 1000000th iteration a little message, containing the thread id
void printFuncNoRef(boost::shared_ptr<Printer> printer, size_t threadNum, size_t iteration)
{
  if(0 == (iteration % 1000000)) {
    printer->print(threadNum);
  }
} 

// Thread worker func
void threadFunc(size_t threadId)
{
  for(size_t i = 0; i < 100000000; ++i) 
  {
    printFuncNoRef(globalPrinter, threadId, i);
  }
}

// main
int main(int argc, char* argv[])
{
  if(argc < 2) {
    std::cout << "Please specify number of threads ./main N" << std::endl;
    return 1;
  }

  size_t numThreads = atoi(argv[1]);

  boost::thread* threadArray = new boost::thread[numThreads];

  for(size_t i = 0; i < numThreads; ++i) {
    threadArray[i] = boost::thread(boost::bind(&threadFunc, i + 1));
  }

  
  for(size_t i = 0; i < numThreads; ++i) {
    threadArray[i].join();
  }

  delete [] threadArray;

  return 0;
}