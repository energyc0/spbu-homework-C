#pragma once

/*
 * This header is for polishNotation.c functionality.
 * It provides simple IO.
 */

/*
 * Skip white spaces and tabs and return character from 'buf'.
 * Automatically increments index.
 * Return EOF, when '\0' occures or first non-space character.
 */
int getInput(const char* buf, int* idx);

/*
 * Puts character to the buffered output.
 */
void putOutput(int ch);

/*
 * Flushes buffered output.
 */
void printOutput();