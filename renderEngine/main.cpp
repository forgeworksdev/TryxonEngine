#include <abstract.hpp>

// clang++ projpoints.cc


typedef float Point[3];

int main()
{
    Point corners[8] = {
         { 1, -1, -5},
         { 1, -1, -3},
         { 1,  1, -5},
         { 1,  1, -3},
         {-1, -1, -5},
         {-1, -1, -3},
         {-1,  1, -5},
         {-1,  1, -3}
    };

    uint32_t image_width = 640;
    uint32_t image_height = 480;
    float aspect_ratio = image_width / static_cast<float>(image_height);

    for (int i = 0; i < 8; ++i) {
        // Divide the x and y coordinates by the z coordinate to
        // project the point onto the canvas
        float x_proj = corners[i][0] / -corners[i][2]; // option 1: divide by aspect_ratio
        float y_proj = corners[i][1] / -corners[i][2] * aspect_ratio; // option 2
        float x_proj_remap = (1 + x_proj) / 2;
        float y_proj_remap = (1 + y_proj) / 2;
        float x_proj_pix = x_proj_remap * image_width;
        float y_proj_pix = y_proj_remap * image_height;
        printf("Corner: %d x:%f y:%f\n", i, x_proj_pix, y_proj_pix);
    }

    return 0;
}