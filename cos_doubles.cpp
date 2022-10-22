#include <math.h>
#include <string.h>
/*  Compute the cosine of each element in in_array, storing the result in
 *  out_array. */
extern "C" void cos_doubles(double *in_array, double *out_array, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        out_array[i] = cos(in_array[i]);
    }
}

// copy from webots/controllers/ros/RosMathUtils.cpp
// Must use extern "C" to expose c interface to numpy.ctypeslib
extern "C" void matrixToQuaternion(const double *matrix, double *q_)
{
    struct Quaternion
    {
        double x, y, z, w;
    };
    Quaternion &q = *((Quaternion *)(q_)); // convert C pointer as a reference
    if (matrix[0] == matrix[4] && matrix[0] == matrix[8] && matrix[0] == 1.0)
    {
        // exception
        q.w = 1.0;
        q.x = 0.0;
        q.y = 0.0;
        q.z = 0.0;
        return;
    }

    double s = 2.0;
    double invS = 1.0;
    const double trace = matrix[0] + matrix[4] + matrix[8];
    if (trace >= 0.0)
    {
        s *= sqrt(trace + 1);
        invS = 1.0 / s;
        q.w = 0.25 * s;
        q.x = (matrix[7] - matrix[5]) * invS;
        q.y = (matrix[2] - matrix[6]) * invS;
        q.z = (matrix[3] - matrix[1]) * invS;
        return;
    }
    if (matrix[0] > matrix[4] && matrix[0] > matrix[8])
    {
        // matrix[0] is larger than max(M(4), M(8))
        s *= sqrt(1.0 + matrix[0] - matrix[4] - matrix[8]);
        invS = 1.0 / s;
        q.w = (matrix[7] - matrix[5]) * invS;
        q.x = 0.25 * s;
        q.y = (matrix[1] + matrix[3]) * invS;
        q.z = (matrix[6] + matrix[2]) * invS;
        return;
    }
    if (matrix[4] > matrix[8])
    {
        // matrix[4] is the largest
        s *= sqrt(1.0 + matrix[4] - matrix[8] - matrix[0]); // s = 4y
        invS = 1.0 / s;
        q.w = (matrix[2] - matrix[6]) * invS;
        q.x = (matrix[1] + matrix[3]) * invS;
        q.y = 0.25 * s;
        q.z = (matrix[5] + matrix[7]) * invS;
        return;
    }
    // else matrix[8] is the largest
    s *= sqrt(1.0 + matrix[8] - matrix[0] - matrix[4]); // s = 4z
    invS = 1.0 / s;
    q.w = (matrix[3] - matrix[1]) * invS;
    q.x = (matrix[6] + matrix[2]) * invS;
    q.y = (matrix[5] + matrix[7]) * invS;
    q.z = 0.25 * s;
}