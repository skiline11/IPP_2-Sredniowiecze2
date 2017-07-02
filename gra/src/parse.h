/* Michał Radecki mr371591 */
/* IPP - Drugie zadanie zaliczeniowe "Średniowiecze - cz1" */

/** @file
   Interface of parser.

*/

#ifndef PARSE_H
#define PARSE_H

typedef struct def_command {
    char name[16];
    int data[7];
    bool correct;
} command;

/**
 * This function return command with parameters correct = false
 */
void make_command_incorrect(command table);

/**
 * This function check if input has has correct spaces.
 * Return true if it's true, and false otherwise.
 */
bool correctness_of_spaces(char input[102], command table);

/** Reads a command.
  Returns command with data points using 'command' structure.
  */
command parse_command();

#endif /* PARSE_H */