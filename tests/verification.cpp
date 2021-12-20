#define BOOST_TEST_MODULE Verification
#include <boost/test/unit_test.hpp>

struct Fixture {};

BOOST_AUTO_TEST_SUITE(VerifyLearning)

BOOST_FIXTURE_TEST_CASE(testLoss, Fixture) {
    BOOST_VERIFY(true);
}

BOOST_AUTO_TEST_SUITE_END()