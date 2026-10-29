#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>

// Console
// All terminal input and output for the Front End, so no other class touches
// cin or cout. Each prompt, message and answer is one line. The streams are
// passed in, so the program reads standard input and writes standard output
// when run, but any other stream can be used instead.
class Console
{
public:
    // Console
    // Remembers which input stream to read from and which output stream to write to.
    Console(std::istream& input, std::ostream& output);

    // show
    // Prints text as one line on the output.
    void show(const std::string& text);

    // showError
    // Prints message as one line with "ERROR: " in front of it.
    void showError(const std::string& message);

    // readLine
    // Reads one line from the input into line, removing a trailing carriage
    // return left by Windows line endings. Returns false when the input has ended.
    bool readLine(std::string& line);

    // ask
    // Prints prompt as one line, then reads the user's answer into answer.
    // Returns false when the input has ended before an answer was typed.
    bool ask(const std::string& prompt, std::string& answer);

private:
    // The stream the user's commands and answers come from.
    std::istream& input;

    // The stream that prompts, confirmations and errors go to.
    std::ostream& output;
};

#endif
