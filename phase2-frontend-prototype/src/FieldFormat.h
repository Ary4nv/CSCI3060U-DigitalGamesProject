#ifndef FIELD_FORMAT_H
#define FIELD_FORMAT_H

#include <string>
#include "Constants.h"

// FieldFormat
// Static helpers that convert text and money to and from the fixed width
// fields used in the files, and to and from what the user types. It holds no
// data and is never instantiated; call its methods as FieldFormat::padRight(...).
class FieldFormat
{
public:
    // padRight
    // Adds spaces to the end of text until it is width characters long.
    // Text that is already width or longer is returned unchanged.
    static std::string padRight(const std::string& text, int width);

    // trimRight
    // Returns text with any spaces at the end removed.
    static std::string trimRight(const std::string& text);

    // moneyField
    // Formats an amount of cents as a zero padded file field of the given
    // width, for example 1500 cents with width 6 gives "015.00".
    static std::string moneyField(Cents cents, int width);

    // moneyDisplay
    // Formats an amount of cents as plain terminal text with no padding,
    // for example 1500 cents gives "15.00".
    static std::string moneyDisplay(Cents cents);

    // parseMoney
    // Reads money typed by the user, such as "15", "15.5" or "15.50", into cents.
    // Returns false (leaving cents unchanged) if the text is empty, has anything
    // but digits and one dot, or has more than two digits after the dot.
    static bool parseMoney(const std::string& text, Cents& cents);

    // parseMoneyField
    // Reads a money field from a file, such as "000500.00", into cents.
    // Returns false (leaving cents unchanged) unless the field is digits, a dot,
    // then exactly two digits.
    static bool parseMoneyField(const std::string& field, Cents& cents);

private:
    // isAllDigits
    // True if text is not empty and every character is 0 to 9.
    static bool isAllDigits(const std::string& text);

    // digitsToNumber
    // Converts a string that isAllDigits into its whole number value.
    static Cents digitsToNumber(const std::string& digits);
};

#endif
