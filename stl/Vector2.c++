// -----------
// Vector2.c++
// -----------

// http://www.cplusplus.com/reference/vector/vector/

#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <vector>    // vector

#include "gtest/gtest.h"

#include "Vector2.h"

using namespace std;

using testing::Test;
using testing::Types;

template <typename T>
struct Vector_Fixture : Test {
    using vector_type    = T;
    using allocator_type = typename vector_type::allocator_type;};

typedef Types<
               vector<int, allocator<int>>,
            my_vector<int, allocator<int>>>
        vector_types;

TYPED_TEST_CASE(Vector_Fixture, vector_types);

TYPED_TEST(Vector_Fixture, test_1) {
    typedef typename TestFixture::vector_type vector_type;

    vector_type x;
    ASSERT_EQ(x.size(), 0);}

TYPED_TEST(Vector_Fixture, test_2) {
    typedef typename TestFixture::vector_type vector_type;

    vector_type x(3);
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x.at(1), 0);
    x.at(1) = 2;
    ASSERT_EQ(x.at(1), 2);
    fill(x.begin(), x.end(), 4);
    ASSERT_EQ(x.at(1), 4);
    ASSERT_THROW(x.at(3), out_of_range);}

TYPED_TEST(Vector_Fixture, test_3) {
    using vector_type    = typename TestFixture::vector_type;
    using allocator_type = typename TestFixture::allocator_type;

    const vector_type x(3, 2, allocator_type());
    ASSERT_EQ(x.at(1), 2);}

TYPED_TEST(Vector_Fixture, test_4) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(3, 4);
    const vector_type y(6, 4);
    ASSERT_TRUE(equal(x.begin(), x.end(), y.begin()));}

TYPED_TEST(Vector_Fixture, test_5) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    const vector_type y(10, 2);
    ASSERT_TRUE(x == y);
    ASSERT_TRUE(!(x != y));
    ASSERT_TRUE(!(x <  y));
    ASSERT_TRUE(x <= y);
    ASSERT_TRUE(!(x >  y));
    ASSERT_TRUE(x >= y);}

TYPED_TEST(Vector_Fixture, test_6) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x (10, 2);
    vector_type y (x);
    vector_type z;
    z = x;
    fill (x.begin(), x.end(), 3);
    ASSERT_TRUE (y[0] == 2);
    ASSERT_TRUE (z[0] == 2);
}

TYPED_TEST(Vector_Fixture, test_7) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x (10, 2);
    vector_type y (20, 5);
    vector_type z (2, 3);

    ASSERT_NE (x.begin(), y.begin());
    y = x;
    ASSERT_NE (x.begin(), y.begin());
    auto b1 = x.begin();
    z = move (x);
    auto b2 = z.begin();
    ASSERT_EQ (x.size(), 0);
    ASSERT_EQ (y.size(), 10);
    ASSERT_EQ (y, z);
    ASSERT_EQ (b1, b2);
}
