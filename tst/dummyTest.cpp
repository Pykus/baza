#include "gtest/gtest.h"
#include "helper.h"
TEST(blahTest, test2) { EXPECT_EQ(1, 1); }

// przyklad testu z predykatem, troszke wiecej info daje w przypadku faila
bool IsAlmostEq(int a, int b) {
  if (std::abs(a - b) < 10)
    return true;
  else
    return false;
}
TEST(ExpectPredTest, IsAlmostEq) {
  int a = 0;
  int b = 11;
  EXPECT_TRUE(IsAlmostEq(a, b));
  EXPECT_PRED2(IsAlmostEq, a, b);
}

// przykład testu z assetion faiil, mozna sobie duzo dodopisywac
::testing::AssertionResult IsAlmostEq2(int a, int b) {
  if (std::abs(a - b) < 10) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure() << "a is " << a << " andb is " << b
                                         << " difference: " << std::abs(a - b);
  };
}
TEST(ExpectPredTest, IsAlmostEq2) {
  int a = 0;
  int b = 11;
  EXPECT_TRUE(IsAlmostEq2(a, b));
}

// przyklad jak zrobic test timeout przy pomocy setup, teardown
class TestFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    start_time_ms_ = std::chrono::high_resolution_clock::now();
  }
  void TearDown() override {
    auto end_time_ms_ = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time_ms_ - start_time_ms_);
    std::cout << "Test took: " << duration.count() << " ms" << std::endl;
    EXPECT_TRUE(duration.count() <= 1000) << "-> The test took too long!";
    std::cout << "=====Test ended=====" << std::endl;
  }
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_ms_;
};

// przyklad matchera, czyli jak np. fajnie polaczycc koncepcje size=0 z isEmpty
/*
MATCHER_P(HasSize, expected, "") {
  return arg.size() == expected && arg.isEmpty() == (0 == expected);
}
TEST_F(ARetweetCollection, DecreasesSizeAfterRemovingTweet) {
  collection.add(Tweet());
  collection.remove(Tweet());
  ASSERT_THAT(collection, HasSize(0u));
}*/
