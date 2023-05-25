#pragma once
#include < iostream >
#include "Container.h"
#include < string >
#include< sstream > 
template< class T > 
struct numcopies {
static size_t copies() { return sm_counter; } 
protected: 
    numcopies() { ++sm_counter; }
    numcopies(numcopies const& other) { ++sm_counter; }
    ~numcopies() { --sm_counter; }
private: 
    inline static size_t sm_counter = 0; 
};


class Object : public numcopies<  Object > {
public:
    virtual ~Object(  ) {}
    virtual std::string to_string(  ) const = 0;
};

class Named :virtual public Object {
public:
    Named( std::string & s  ):m_name( s ) {};
protected:
    std::string m_name;
};

class Task : virtual public Object { 
public:
    virtual int calculate_task(  ) = 0;
};

class BinaryTask : public Named, public Task {
public:
    BinaryTask( std::string & name, double x, double y ) : Named( name ), m_x( x ), m_y( y ) {};
    std::string to_string(  ) const override {
        if ( dont_calculate ) {
            return "operation " + Named::m_name + " is not performed";
        }
        return "operation " + Named::m_name + " has the m_result equal to " + std::to_string(m_res);
    }
    int calculate_task(  ) {
        if ( dont_calculate ) {
            dont_calculate = false;
            if ( Named::m_name == "plus" ) {
                m_res = m_x + m_y;
            }
            if ( Named::m_name == "minus" ) {
                m_res = m_x - m_y;
            }
            if ( Named::m_name == "multiply" ) {
                m_res = m_x * m_y;
            }
            if ( Named::m_name == "div" ) {
                try
                {
                    if ( m_y == 0 ) throw std::exception( "Деление на 0" );
                    m_res = m_x / m_y;
                }
                catch ( std::exception& e )
                {
                    std::cout <<  e.what(  );
                }
            }
        }
        return 0;
    }
private:
    double m_x, m_y;
    double m_res = 0;
    bool dont_calculate = true;
};

class AddTask : public Task {
public:
    std::string to_string(  ) const override {
        return "AddTask";
    }

    int calculate_task( Container< Object&> &c, Object & t ) {
        c.push_back( t );
        return 0;
    }
};

class CounterTask : public Task {
public:
    std::string to_string(  ) const override {
        return "CounterTask";
    }

    int calculate_task( Container< Object*>& c ) {
        return c.get_count(  );
    }
};

class CounterNammedTask : public Task {
public:
    std::string to_string(  ) const override {
        if ( dont_calculate ) {
            return "CounterTask is not performed";
        }
        return "operation CounterTask has the m_result equal to" + std::to_string(m_res);
    }

    int calculate_task( Container< Object*>& c ) {
        if ( dont_calculate ) {
            dont_calculate = false;
            m_res = c.get_count(  ); //не планирую добавлять задачи без результата
        }
        return 0;
    }
private:
    bool dont_calculate = true;
    int m_res = 0;
};

class CleanerTask : public Task {
    std::string to_string(  ) const override {
        return "CleanerTask";
    }

    int calculate_task( Container< Object&>& c ) {
        c.clear(  );
        return 0;
    }
};

class GlobalCounterTask : public Task {
public:
    std::string to_string(  ) const override {
        return "at the moment there are " + std::to_string(Object::copies()) + " Object";
    }

    int calculate_task(  ) {
        return 0;
    }
};