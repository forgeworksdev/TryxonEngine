/* #include "engine.h"

int main() {
    Engine engine;
    engine.run();
    return 0;
}

 */

#include "vector.h"
#include <iostream>

int main() {
    // Test basic functionality
    Vector3f v1(1.0f, 2.0f, 3.0f);
    Vector3f v2(4.0f, 5.0f, 6.0f);
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    Vector3f v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;
    
    float dotResult = dot(v1, v2);
    std::cout << "dot product: " << dotResult << std::endl;
    
    return 0;
}