#ifndef STRINGS_H
#define STRINGS_H

#include <string>

#include "Util.h"

/**
 * \brief "See previous error" error message.
 */
extern const char* ERROR_MSG_PREVIOUS;

/**
 * \param level The current level of the tree.
 * \return String which pads the tree to the specified level.
 */
std::string alignTree(u32 level);
/**
 * \brief Creates a string which says "expected <n> operands for instruction".
 *
 * \param expected Number of expected argument.
 */
std::string makeArgNumErrorString(u32 expected);

/**
 * \brief Parses the operands of a sub-expression.
 *
 * This is used in conjunction with operands which supports multiple sub-expressions, for example indirect and
 * register-list operands.
 *
 * \param input The operand string to parse.
 * \param numOperands[out] The number of operands parsed by this function.
 * \return Pointer to an array of parsed subexpressions, or `nullptr` if an error has occurred.
 */
std::string* parseSubExprOperands(const std::string& input, u32& numOperands);
/**
 * \brief Trims the input string by removing all leading whitespace, as well as all characters after the first word.
 * \param input The input string to trim.
 * \return Trimmed input string.
 */
std::string trimWord(std::string input);
/**
 * \brief Trims the input string by removing all leading and trailing whitespace.
 * \param line The input line to trim.
 * \return Trimmed input line.
 */
std::string trimLine(std::string line);

#endif  // STRINGS_H
