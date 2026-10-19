#include "Console.h"

#include "Messages.h"

// The carriage return at the end of a line typed or saved on Windows.
static const char CARRIAGE_RETURN = '\r';

// Console
// Remembers which streams to use.
Console::Console(std::istream& input, std::ostream& output)
    : input(input), output(output)
{
}

// show
// Prints text as one line.
void Console::show(const std::string& text)
{
    output << text << std::endl;
}

// showError
// Prints message as one line with "ERROR: " in front.
void Console::showError(const std::string& message)
{
    show(Messages::ERROR_PREFIX + message);
}

// readLine
// Reads one line, removing a trailing carriage return. False at end of input.
bool Console::readLine(std::string& line)
{
    if (!std::getline(input, line))
    {
        return false;
    }
    if (!line.empty() && line[line.size() - 1] == CARRIAGE_RETURN)
    {
        line.erase(line.size() - 1);
    }
    return true;
}

// ask
// Prints the prompt, then reads the answer. False at end of input.
bool Console::ask(const std::string& prompt, std::string& answer)
{
    show(prompt);
    return readLine(answer);
}
