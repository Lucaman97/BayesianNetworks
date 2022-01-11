#include "examples.cpp"

#define CASE 2

int main(){

    switch(CASE) {
        case 1:
            example1();
            break;
        case 2:
            example2();
            break;
        case 3:
            example3();
            break;
        case 4:
            example4();
            break;
        default:
            example1();

    }

    return 0;
}