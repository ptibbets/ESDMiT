#pragma once

#include <Eigen/Eigen>

namespace helpers
{
    template<typename tVector>
    class Vector
    {
        tVector &mEigenVector;
        std::size_t mVectorLength;

    public:
        Vector(Eigen::VectorXd &vEigenVector, std::size_t vVectorLength = 0) :
            mEigenVector(vEigenVector),
            mVectorLength(vVectorLength) {}

        std::size_t getLength()
        {
            return mVectorLength;
        }

        template<typename tValue>
        Vector & pushBack(tValue vValue)
        {
            if((unsigned)mEigenVector.size() > mVectorLength)
            {
                mEigenVector[mVectorLength++] = vValue;
            }
            return *this;
        }

        Vector & pushBegin(double vValue)
        {
            if(mEigenVector.size() > mVectorLength)
            {
                for(auto aIndex = mVectorLength; aIndex > 0; aIndex--)
                {
                    mEigenVector[aIndex] = mEigenVector[aIndex - 1];
                }
                mEigenVector[0] = vValue;
                mVectorLength++;
            }
            return *this;
        }
    };
}
