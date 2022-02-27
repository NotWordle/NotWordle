#include <gtest/gtest.h>

#include <fstream>

#include "game/Game.h"

using game::Game;

class GameTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  bool CompareFiles(std::ifstream& actual, std::ifstream& expected) {
    std::ostringstream ss_actual, ss_expected;

    auto read_file = [](std::ifstream& in, std::ostringstream& out) {
      std::string line;
      while (getline(in, line)) {
        out << line;
      }
    };

    read_file(actual, ss_actual);
    read_file(expected, ss_expected);

    bool res = ss_actual.str() == ss_expected.str();

    // if they aren't equal, would be nice to see why
    if (!res) {
      std::cout << "actual: " << ss_actual.str() << "\n\n"
                << "expect: " << ss_expected.str() << "\n\n"
                << "you can also diff the files to make this comparison easier\n";
    }

    return res;
  }

  // some helper functions for resetting input/output

  void Resetter(std::ostringstream& out, std::istringstream& in) {
    out.str("");
    out.clear();

    in.str("");
    in.clear();
  }

  void Resetter(std::istringstream& in) {
    in.str("");
    in.clear();
  }

  void Resetter(std::ostringstream& out) {
    out.str("");
    out.clear();
  }

  Game g1_;
  Game g2_;
  Game g3_;
  Game g4_;
  Game g4plus_;
  Game g5_;
  Game g6_;
};

TEST_F(GameTest, TestConstructor) {
  auto letters = g1_.AvailableLetters();

  for (auto c : letters) {
    EXPECT_EQ(c, game::Validity::EMPTY);
  }
}

TEST_F(GameTest, TestIsValidWord) {
  g1_.GetDictionary().LoadWords(5);

  EXPECT_TRUE(g1_.IsValidWord("trunk"));
  EXPECT_FALSE(g1_.IsValidWord("abcde"));
}

TEST_F(GameTest, TestPrintGrid) {
  std::string exp =
      "\n\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n\n\n";

  std::stringstream output;
  g2_.InitializeGrid(5);
  g2_.PrintGrid(output);

  auto res = output.str();

  EXPECT_EQ(exp, res);
}

TEST_F(GameTest, TestShowAvailableLetters) {
  g3_.InitializeGrid(5);

  // test inital print
  std::stringstream res;
  g3_.ShowAvailableLetters(res);

  std::string exp =
      "\x1B[39mA\x1B[0m \x1B[39mB\x1B[0m \x1B[39mC\x1B[0m \x1B[39mD\x1B[0m \x1B[39mE\x1B[0m \x1B[39mF\x1B[0m "
      "\x1B[39mG\x1B[0m\n\x1B[39mH\x1B[0m \x1B[39mI\x1B[0m \x1B[39mJ\x1B[0m \x1B[39mK\x1B[0m \x1B[39mL\x1B[0m "
      "\x1B[39mM\x1B[0m \x1B[39mN\x1B[0m\n\x1B[39mO\x1B[0m \x1B[39mP\x1B[0m \x1B[39mQ\x1B[0m \x1B[39mR\x1B[0m "
      "\x1B[39mS\x1B[0m \x1B[39mT\x1B[0m \x1B[39mU\x1B[0m\n\x1B[39mV\x1B[0m \x1B[39mW\x1B[0m \x1B[39mX\x1B[0m "
      "\x1B[39mY\x1B[0m \x1B[39mZ\x1B[0m\n\n";

  ASSERT_EQ(res.str(), exp);

  // test print with close letter, wrong letter, and correct letter
  g3_.UpdateGrid("APPLE");
  g3_.CheckGuess("PAILS");  // A and P are close, L is correct, I and E are incorrect

  res.str(std::string());
  res.clear();
  g3_.ShowAvailableLetters(res);

  exp =
      "\x1B[34mA\x1B[0m \x1B[39mB\x1B[0m \x1B[39mC\x1B[0m \x1B[39mD\x1B[0m \x1B[31mE\x1B[0m \x1B[39mF\x1B[0m "
      "\x1B[39mG\x1B[0m\n\x1B[39mH\x1B[0m \x1B[39mI\x1B[0m \x1B[39mJ\x1B[0m \x1B[39mK\x1B[0m \x1B[32mL\x1B[0m "
      "\x1B[39mM\x1B[0m \x1B[39mN\x1B[0m\n\x1B[39mO\x1B[0m \x1B[34mP\x1B[0m \x1B[39mQ\x1B[0m \x1B[39mR\x1B[0m "
      "\x1B[39mS\x1B[0m \x1B[39mT\x1B[0m \x1B[39mU\x1B[0m\n\x1B[39mV\x1B[0m \x1B[39mW\x1B[0m \x1B[39mX\x1B[0m "
      "\x1B[39mY\x1B[0m \x1B[39mZ\x1B[0m\n\n";

  EXPECT_EQ(res.str(), exp);
}

TEST_F(GameTest, TestQueryUserForGuess) {
  const std::string good("apple");

  std::ostringstream output;
  std::istringstream input(good);

  g4_.InitializeGrid(5);

  // test valid input
  auto res = g4_.QueryUserForGuess(output, input);
  std::string exp_output = "Enter a 5 letter word:\n";

  ASSERT_EQ(res, good);
  EXPECT_EQ(output.str(), exp_output);
  Resetter(output, input);

  // test word wrong size (then valid to terminate loop)
  input.str("longer apple");
  res = g4_.QueryUserForGuess(output, input);
  exp_output += exp_output;

  ASSERT_EQ(res, good);
  EXPECT_EQ(output.str(), exp_output);
  Resetter(output, input);

  // test invalid word (then valid to terminate loop)
  input.str("abcde apple");
  res = g4_.QueryUserForGuess(output, input);

  ASSERT_EQ(res, good);
  EXPECT_EQ(output.str(), exp_output);
  Resetter(output, input);
}

TEST_F(GameTest, TestQueryUserForWordSize) {
  std::ostringstream output;
  std::istringstream input;

  const std::string kQuery = "Enter game word size [4-9] (default is 5):";

  uint16_t res = 0;

  // valid input
  input.str("6");
  res = g4plus_.QueryUserForWordSize(output, input);

  EXPECT_EQ(res, 6);
  EXPECT_EQ(output.str(), kQuery);
  Resetter(output, input);

  // garbage input (e.g. some string)
  // followed by valid input so we can terminate
  input.str("abcdef\n7");

  res = g4plus_.QueryUserForWordSize(output, input);

  EXPECT_EQ(res, 7);
  EXPECT_EQ(output.str(), kQuery + kQuery);
  Resetter(output, input);

  // value too low
  // followed by valid input so we can terminate
  input.str("2\n7");

  res = g4plus_.QueryUserForWordSize(output, input);

  EXPECT_EQ(res, 7);
  EXPECT_EQ(output.str(), kQuery + kQuery);
  Resetter(output, input);

  // value too high
  // followed by valid input so we can terminate
  input.str("12\n7");

  res = g4plus_.QueryUserForWordSize(output, input);

  EXPECT_EQ(res, 7);
  EXPECT_EQ(output.str(), kQuery + kQuery);
  Resetter(output, input);

  // default value (no input)
  res = g4plus_.QueryUserForWordSize(output, input);

  EXPECT_EQ(res, 5);
  EXPECT_EQ(output.str(), kQuery);
  Resetter(output, input);
}

TEST_F(GameTest, TestSelectedWord) {
  std::ostringstream output;
  std::istringstream input;
  input.str("apple y");

  const std::string kChosenWord = "APPLE";

  g5_.Run(output, input, kChosenWord);

  EXPECT_EQ(g5_.SelectedWord(), kChosenWord);
}

TEST_F(GameTest, TestRunEasy) {
  std::ofstream output("TestRunEasyActual.txt");
  std::istringstream input;

  // test with pre-selected word to make deterministic test cases
  const std::string kChosenWord = "APPLE";

  input.str("apple y");

  g6_.Run(output, input, kChosenWord);
  output.close();

  std::ifstream iactual("TestRunEasyActual.txt");
  std::ifstream iexpected("expected/GameTest/TestRunEasyExpected.txt");

  EXPECT_TRUE(CompareFiles(iactual, iexpected));
  Resetter(input);
  iactual.close();
  iexpected.close();
}
TEST_F(GameTest, TestRunSingleWrongGuess) {
  std::ofstream output("TestRunSingleWrongGuessActual.txt");
  std::istringstream input;

  // test with pre-selected word to make deterministic test cases
  const std::string kChosenWord = "APPLE";

  input.str("trunk n pails y apple y");

  g6_.Run(output, input, kChosenWord);
  output.close();

  std::ifstream iactual("TestRunSingleWrongGuessActual.txt");
  std::ifstream iexpected("expected/GameTest/TestRunSingleWrongGuessExpected.txt");

  EXPECT_TRUE(CompareFiles(iactual, iexpected));
  Resetter(input);
  iactual.close();
  iexpected.close();
}

TEST_F(GameTest, TestRunLoser) {
  std::ofstream output("TestRunLoserActual.txt");
  std::istringstream input;

  // test with pre-selected word to make deterministic test cases
  const std::string kChosenWord = "APPLE";

  // get all guesses wrong
  input.str("trunk y trunk y trunk y trunk y trunk y trunk y");

  g6_.Run(output, input, kChosenWord);
  output.close();

  std::ifstream iactual("TestRunLoserActual.txt");
  std::ifstream iexpected("expected/GameTest/TestRunLoserExpected.txt");
  EXPECT_TRUE(CompareFiles(iactual, iexpected));
  Resetter(input);
  iactual.close();
  iexpected.close();
}
