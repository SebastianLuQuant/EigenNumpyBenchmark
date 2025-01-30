#include "rot90.h"

Eigen::MatrixXd rot90(const Eigen::MatrixXd& input, int k)
{
    // Normalize k to the range [0..3].
    // e.g. k=-1 => k=3, k=5 => k=1, etc.
    k = (k % 4 + 4) % 4;

    // switch case is faster than for-loop for i < k
    switch (k) {
    case 0:
        // k=0 => no rotation
        return input;
    case 1:
        // k=1 => 90 deg clockwise
        // Method: transpose, then flip columns
        {
            Eigen::MatrixXd trans = input.transpose();
            // Flip columns => rowwise reverse
            Eigen::MatrixXd result = trans.rowwise().reverse();
            return result;
        }
    case 2:
        // k=2 => 180 deg: flip rows + flip cols
        // We can do rowwise().reverse().colwise().reverse() in one statement:
        {
            Eigen::MatrixXd result = input.rowwise().reverse().colwise().reverse();
            return result;
        }
    case 3:
        // k=3 => 270 deg clockwise => or 90 deg counter-clockwise
        {
            Eigen::MatrixXd trans = input.transpose();
            // Flip rows => colwise().reverse()
            Eigen::MatrixXd result = trans.colwise().reverse();
            return result;
        }
    }
    // theoretically unreachable due to normalization
    return input;
}
