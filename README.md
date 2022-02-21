[![codecov](https://codecov.io/gh/s-merritt/NotWordle/branch/develop/graph/badge.svg?token=6OYTC3ENRF)](https://codecov.io/gh/s-merritt/NotWordle)

# NotWordle
just a little side project of mine to recreate the game Wordle.

The game is currently just text-based, but I have plans to make it an Android app.

## How to Build

This project is currently built with CMake (> v3.10) using GCC v7.5.0.

You can build the project by pulling the source code and running the `build.sh` script

```bash
./build.sh
```

## How to Run

After calling the `build.sh` script, you can run the generated executable in the build folder like so

```bash
./build/bin/NotWordle
```

## How to Play

The player is given the option for the length of the word they wish to guess. The number of guesses the player will get is equal to the length of the word plus one. The default length is 5, entering nothing will select this value.

After you have selected a word size, the game will begin. Type in a valid word of that length to enter it as a guess. The game will confirm your answer before revealing the results.

Once a guess is entered, the game will reveal the validity of each letter in your guess:

- GREEN: the letter is in the word and in the correct place
- BLUE: the letter is in the word, but in the wrong place
- RED: the letter is not in the word

You will also be presented with an alphabet that updates with the colors of the letters you've guessed. Bear in mind that some words will have multiple of the same letter!

If you guess the word before you've run out of guesses, you win!


