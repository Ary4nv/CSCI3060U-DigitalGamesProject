#include "FieldFormat.h"

#include <iomanip>
#include <sstream>

// Number of digits after the decimal point in every amount of money.
static const int DECIMAL_DIGITS = 2;

// The character that separates dollars from cents.
static const char DECIMAL_POINT = '.';

// padRight
// Adds spaces to the end of text until it is width characters long.
std::string FieldFormat::padRight(const std::string& text, int width)
{
    std::string padded = text;
    while (static_cast<int>(padded.size()) < width)
    {
        padded += Constants::FIELD_SEPARATOR;
    }
    return padded;
}

// trimRight
// Returns text with any spaces at the end removed.
std::string FieldFormat::trimRight(const std::string& text)
{
    std::string::size_type lastNonSpace = text.find_last_not_of(Constants::FIELD_SEPARATOR);
    if (lastNonSpace == std::string::npos)
    {
        return "";
    }
    return text.substr(0, lastNonSpace + 1);
}

// moneyField
// Formats cents as a zero padded field, such as "015.00" for width 6.
// The dollars take up everything except the dot and the two cent digits.
std::string FieldFormat::moneyField(Cents cents, int width)
{
    int dollarWidth = width - 1 - DECIMAL_DIGITS;

    std::ostringstream field;
    field << std::setfill('0')
          << std::setw(dollarWidth) << cents / Constants::CENTS_PER_DOLLAR
          << DECIMAL_POINT
          << std::setw(DECIMAL_DIGITS) << cents % Constants::CENTS_PER_DOLLAR;
    return field.str();
}

// moneyDisplay
// Formats cents as terminal text, such as "15.00".
std::string FieldFormat::moneyDisplay(Cents cents)
{
    std::ostringstream display;
    display << cents / Constants::CENTS_PER_DOLLAR
            << DECIMAL_POINT
            << std::setfill('0') << std::setw(DECIMAL_DIGITS)
            << cents % Constants::CENTS_PER_DOLLAR;
    return display.str();
}

// parseMoney
// Reads typed money ("15", "15.5", "15.50") into cents. The text is split at
// the dot into a dollars part and a cents part, and each part must be
// digits only.
bool FieldFormat::parseMoney(const std::string& text, Cents& cents)
{
    std::string::size_type pointPosition = text.find(DECIMAL_POINT);
    std::string dollarDigits = text.substr(0, pointPosition);
    std::string centDigits = "";

    if (pointPosition != std::string::npos)
    {
        centDigits = text.substr(pointPosition + 1);
        bool centsAreValid = isAllDigits(centDigits)
                             && static_cast<int>(centDigits.size()) <= DECIMAL_DIGITS;
        if (!centsAreValid)
        {
            return false;
        }
    }

    if (!isAllDigits(dollarDigits))
    {
        return false;
    }

    // "15.5" means 50 cents, so pad the cent digits out to two places.
    while (static_cast<int>(centDigits.size()) < DECIMAL_DIGITS)
    {
        centDigits += '0';
    }

    cents = digitsToNumber(dollarDigits) * Constants::CENTS_PER_DOLLAR
            + digitsToNumber(centDigits);
    return true;
}

// parseMoneyField
// Reads a file money field ("000500.00") into cents. The dot must be exactly
// two places from the end, with digits on both sides.
bool FieldFormat::parseMoneyField(const std::string& field, Cents& cents)
{
    if (static_cast<int>(field.size()) <= DECIMAL_DIGITS + 1)
    {
        return false;
    }

    std::string::size_type pointPosition = field.size() - DECIMAL_DIGITS - 1;
    std::string dollarDigits = field.substr(0, pointPosition);
    std::string centDigits = field.substr(pointPosition + 1);

    bool fieldIsValid = field[pointPosition] == DECIMAL_POINT
                        && isAllDigits(dollarDigits)
                        && isAllDigits(centDigits);
    if (!fieldIsValid)
    {
        return false;
    }

    cents = digitsToNumber(dollarDigits) * Constants::CENTS_PER_DOLLAR
            + digitsToNumber(centDigits);
    return true;
}

// isAllDigits
// True if text is not empty and every character is 0 to 9.
bool FieldFormat::isAllDigits(const std::string& text)
{
    if (text.empty())
    {
        return false;
    }
    for (std::string::size_type i = 0; i < text.size(); i++)
    {
        if (text[i] < '0' || text[i] > '9')
        {
            return false;
        }
    }
    return true;
}

// digitsToNumber
// Converts a string of digits into its whole number value, one digit at a time.
Cents FieldFormat::digitsToNumber(const std::string& digits)
{
    Cents value = 0;
    for (std::string::size_type i = 0; i < digits.size(); i++)
    {
        value = value * 10 + (digits[i] - '0');
    }
    return value;
}
