#include "helper.h"
#include "gtest/gtest.h"
#include <functional>
#include <tuple>
#include <vector>
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
};
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
  //
  static void SetupTestSuite() { std::cout << "===Beginning of testSuite==="; }
  static void TearDownTestSuite() { std::cout << "===End of testSuite==="; }
};

// przyklad matchera, czyli jak np. fajnie polaczycc koncepcje size=0 z
// isEmpty
/*
MATCHER_P(HasSize, expected, "") {
  return arg.size() == expected && arg.isEmpty() == (0 == expected);
}
TEST_F(ARetweetCollection, DecreasesSizeAfterRemovingTweet) {
  collection.add(Tweet());
  collection.remove(Tweet());
  ASSERT_THAT(collection, HasSize(0u));
}*/

// przyklad test parametryzowany, a ponizej to samo, tylko przerobione, zeby
// byl czytelniejszy output
class SortTest : public testing::TestWithParam<std::vector<int>> {};
/* TEST_P(SortTest, WorksForVariousInputs) { */
/*   auto in = GetParam(); */
/*   auto expected = in; */
/*   SelectionSort(in); // tu jakas funkcja, ktora wlasnie ten test sprawdza */
/*   std::sort(expected.begin(), expected.end()); */
/*   EXPECT_EQ(expected, in); */
/* } */
/* // INSTANTIATE_TEST_SUIT_P(instntiationName, TestSuiteName, */
/* // param_generator,name_generator) */
/* INSTANTIATE_TEST_SUITE_P(SelectionSortVariousInputs, SortTest, */
/*                          testing::Values(std::vector<int>{1}, */
/*                                          std::vector<int>{5, 3, 1, 77}, */
/*                                          std::vector<int>{-4, 122, 1000}));
 */

// fajny parametryzowany test z mapa
/* std::map<std::string, std::vector<int>> input_map = { */
/*     {"SingleElement", {1}}, */
/*     {"Pusty", {}}, */
/*     {"Inny zestaw", {5, 3, 1, 77}}, */
/*     {"i znow", {5, 3, 12, 77}}, */
/*     {"Inny zestaw", {5, 3, 1, 77}}}; */
/* class SortTestNameGenerator */
/*     : public testing::TestWithParam< */
/*           std::pair<const std::string, std::vector<int>>> {}; */
/* TEST_P(SortTestNameGenerator, WorksForVariousInputs) { */
/*   auto in = GetParam().second; */
/*   auto expected = in; */
/*   SelectionSort(in); // tu jakas funkcja, ktora wlasnie ten test sprawdza */
/*   std::sort(expected.begin(), expected.end()); */
/*   EXPECT_EQ(expected, in); */
/* } */
/* INSTANTIATE_TEST_SUITE_P( */
/*     SelectionSortVariousInputsNameGenerator, SortTestNameGenerator, */
/*     testing::ValuesIn(input_map), */
/*     [](const testing::TestParamInfo<SortTestNameGenerator::ParamType> &info)
 * { */
/*       return info.param.first; */
/*     }); */

/* // przyklad wylaczenie testow: */
// class DISABLED_TestFixture :public testing test  //tak wylaczasz caly test
// suit TEST(ExpectPredTest, DISABLED_IsAlmostEq) {//subprzyklad, tak wylaczac
// GTEST_SKIP() << "Ten test na razie pomijam...") <-jako arragne w tescie;
// jak wstawisz w setup to skipuje caly test fixture
//--gtest_filter= TODO sprawdzic,z commandline

// EXPECT_EQ(obiek1,obiekt2) <-wymaga zeby operator== byl overloadowany; zeby
// do tego googletest ladnie wyswietlal mozesz ablo overloadowac opera tor<<
// [to samo expect_eq wywola] albo lepiej "friend void PrintTo" albo
// "std::string DebugString()"->w tescie mozeszrobiwtedy PrintToString(obiekt)

// przyklad: jak rozne zestawy danych przetestowac bez pisania testow do
// kazdego variant 1: w test fixture zadeklaruj zmienna input [i expected] a
// potem w testach przy arrangu oraz cała logike testu wpisz do TearDown, a w
// samym tescie tylko
//  input= {zestaw danych do tego testu}
// vairan 2: jeden test, input={zestaw1, zestaw2, zestawn} i w tescie for
// zestaw in input variatn 3: parametryzowany test
//

/* parametryzowany test, zarowno dane jak i funkcje parametryzowane

class SortTest2
    : public testing::TestWithParam<
        std::tuple<
          std::function<void(std::vector<int> &)>,
          std::vector<int>
        >
      > {};
INSTANTIATE_TEST_SUITE_P(
    NazwaInstacjowanegoSuita, SortTest2,
    Combine(Values(testowanaFunkcja1, testowanaFunkcja2),
            Values(std::vector<int>{},
                   std::vector<int>{1},
                   std::vector<int>{5,3,1,77},
                   std::vector<int>{3,4,5}
                   )
    );
TEST_P(SortTest2, WorksForVariousInputs){
  auto input = std::get<1>(GetParam());
  auto sortFunction = std::get<0>(GetParam());
  auto expected = input;
  std::sort(expected.begin(), expected.end());
  sortFunction(input);
  EXPECT_EQ(expected,input)
 }

*/
