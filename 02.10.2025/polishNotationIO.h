#pragma once

#include <stdbool.h>

/*
 * This header is for polishNotation.c functionality.
 * It provides simple IO.
 */

/*
 * Skip white spaces and tabs and return character from the input.
 */
int getInput();

/*
 * Puts character to the buffered output.
 */
void putOutput(int ch);

/*
 * Flushes buffered output.
 */
void printOutput();

/*
 * Puts one character back into the stream.
 * You can put ONLY ONE character back.
 */
void putback(int ch);

/*
 * is char == EOF or '\n'
 */
bool isEOF(int ch);
