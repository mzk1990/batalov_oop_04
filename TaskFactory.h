#pragma once
#include "Object.h"
#include <string_view>
#include <iostream>
class TaskFactory
{
public:
    static Task* makeRandomTask(  ) {
        switch ( rand(  ) % 3 ) {
        case 0:
            return make_plus(  );
        case 1:
            return make_minus(  );
        case 2:
            return make_multiply(  );
        default:
            return nullptr;
        }
    }

    static Task* make_plus(  ) {
        double x = randomDouble( -1000, 1000 );
        double y = randomDouble( -1000, 1000 );
        std::string plus = "plus";
        return new BinaryTask( plus, x, y );
    }
    static Task* make_minus(  ) {
        double x = randomDouble( -1000, 1000 );
        double y = randomDouble( -1000, 1000 );
        std::string minus = "minus";
        return new BinaryTask( minus, x, y );
    }
    static Task* make_multiply(  ) {
        double x = randomDouble( -1000, 1000 );
        double y = randomDouble( -1000, 1000 );
        std::string multiply = "multiply";
        return new BinaryTask( multiply, x, y );
    }
private:
    static double randomDouble( double min, double max ) {
        double random = ( double )rand(  ) / RAND_MAX;
        return min + random * ( max - min );
    }
};