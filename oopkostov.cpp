#include < iostream >
#include "Object.h"
#include "TaskFactory.h"
#include <memory>
int main(  )
{
    //auto task = new AddTask();
    auto cTask = new Container<Task*>;
    auto cTaskWaited = new Container<std::string>;
    auto cTaskPerformed = new Container<std::string>;
    auto counter = new GlobalCounterTask(  );
    std::cout << counter->to_string() << std::endl << std::endl;
    std::cout<< "fill the container with random tasks" << std::endl << std::endl;
    for ( int i = 0; i < 20; ++i ) {
        cTask->push_back( TaskFactory::makeRandomTask(  ) );
    }
    std::cout << "Let's look at the tasks before we do them" << std::endl << std::endl;
    cTask->forEach( [cTaskWaited]( Object* const o ) {
        std::cout << o->to_string(  ) << std::endl;
        cTaskWaited->push_back( o->to_string(  ) );
    } );
    std::cout << std::endl;
    int size = cTask->get_count(  );
    for ( int i = 0; i < size; ++i ) {
        auto t = cTask->get_first();
        t->calculate_task();
        cTaskPerformed->push_back(t->to_string());
        cTask->pop_front();
        delete t;
    }
    std::cout << "look at the tasks after completion" << std::endl << std::endl;
    cTaskPerformed->forEach( []( std::string str ) {
        std::cout << str << std::endl;
    } );
    std::cout << counter->to_string(  ) << std::endl;
    delete cTask;
    delete cTaskWaited;
    delete cTaskPerformed;
    delete counter;
    std::cout << "at the moment there are " << Object::copies() <<" Object" << std::endl;
    std::cout << std::endl;
    std::cout <<"reverse order of list" << std::endl;
    auto number = new Container<int>;
    for ( int i = 0; i < 10; ++i ) {
        number->push_back( i );
        std::cout << i << " ";
    }
    std::cout << std::endl;
    number->reverse_list(  );
    std::cout << std::endl;
    number->forEach( []( int n ) {
        std::cout << n << " ";
    } );
    delete number;
}
