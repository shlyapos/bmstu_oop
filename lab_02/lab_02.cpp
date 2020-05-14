#include <iostream>
#include <vector>

#include "Matrix.h"
#include "MatrixBaseException.h"
#include "MatrixRealization.h"

int main()
{
    try
    {
        std::cout << "Testing constructors:\n";

        Matrix<int> mtrx1(3, 3);
        mtrx1.fill_zero();
        std::cout << mtrx1;

        Matrix<int> mtrx2(mtrx1);
        std::cout << mtrx2;

        Matrix<float> mtrx3({ { 3.3f, 2.1f, 1.4f }, { 0.2f, 0.23f, 1.12f } });
        std::cout << mtrx3;

        std::cout << "Testing addition\n";
        mtrx1.identity_matrix();
        mtrx2.identity_matrix();

        mtrx1 += mtrx2;
        std::cout << mtrx1;

        mtrx1 = mtrx1 + mtrx2;
        std::cout << mtrx1;

        mtrx1.add(mtrx2);
        std::cout << mtrx1;

        mtrx1.add(10);
        std::cout << mtrx1;

        std::cout << "Testing subtraction\n";
        mtrx1.identity_matrix();
        mtrx2.identity_matrix();

        mtrx1 -= mtrx2;
        std::cout << mtrx1;

        mtrx1 = mtrx1 - mtrx2;
        std::cout << mtrx1;

        mtrx1.sub(mtrx2);
        std::cout << mtrx1;

        mtrx1.sub(10);
        std::cout << mtrx1;

        std::cout << "Testing multiplication\n";
        mtrx1.identity_matrix();
        mtrx2.identity_matrix();

        mtrx1.mult(3);
        mtrx2.mult(4);

        std::cout << mtrx1;

        mtrx1 *= mtrx2;
        std::cout << mtrx1;

        mtrx1 = mtrx1 * 2;
        std::cout << mtrx1;

        std::cout << "Testing get value func\n";
        std::cout << mtrx3.get_value(1, 0) << std::endl;


        std::cout << "\nTesting set value func\n";
        mtrx1.set_value(1, 0, 3);
        std::cout << mtrx1[1][0] << std::endl;

        std::cout << "\nTesting iterators";
        auto iter = mtrx3.begin();

        for (size_t i = 0; iter != mtrx3.end(); i++, iter++)
        {
            if (i % mtrx3.get_m() == 0)
            {
                std::cout << std::endl;
            }

            std::cout << *iter << '\t';
        }
    }

    catch (MatrixBaseException& exception)
    {
        std::cout << exception.what();
    }

    return 0;
}
