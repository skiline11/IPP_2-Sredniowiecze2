/* Michał Radecki mr371591 */
/* IPP - Drugie zadanie zaliczeniowe "Średniowiecze - cz1" */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct def_command {
    char name[16];
    int data[7];
    bool correct;
} command;

command make_command_incorrect(command table)
{
    table.correct = false;
    return table;
}

bool correctness_of_spaces(char input[102], command table)
{
    int iterator = 0;
    bool last_space = true;
    while(input[iterator] != '\n')
    {
        if(input[iterator] == ' ')
        {
            if(last_space == true) return false;
            else last_space = true;
        }
        else if(input[iterator] == '\t') return false;
        else if(last_space == true) last_space = false;
        iterator++;
    }
    if(last_space == true) return false;
    else return true;
}

command parse_command()
{
    command table;
    table.correct = true;
    char input[102], bufor[102];
    if(fgets(input, 102, stdin) == NULL) return make_command_incorrect(table);
    if(strlen(input) > 100) return make_command_incorrect(table);
    if(correctness_of_spaces(input, table) == false) return make_command_incorrect(table);
    int memory;
    if(sscanf(input, "%s", table.name) == 0) make_command_incorrect(table); // za duża jest nazwa ?? czy tak można?
    int how_many_operations = sscanf(input, "%s %d %d %d %d %d %d %d %s", table.name, &table.data[0], &table.data[1], &table.data[2], &table.data[3], &table.data[4], &table.data[5], &table.data[6], bufor);
    memory = sscanf(input, "%s %d %d %d %d %d %d %d", table.name, &table.data[0], &table.data[1], &table.data[2], &table.data[3], &table.data[4], &table.data[5], &table.data[6]);
    if(how_many_operations != memory) return make_command_incorrect(table);
    if(strcmp(table.name, "END_TURN") == 0)
    {
        how_many_operations = sscanf(input, "%s", table.name);
        if(how_many_operations == 1 && memory == 1) return table;
        else return make_command_incorrect(table);
    }
    else if(strcmp(table.name, "INIT") == 0)
    {
        if(memory == 8) return table;
        else return make_command_incorrect(table);
    }
    else if(strcmp(table.name, "MOVE") == 0 || strcmp(table.name, "PRODUCE_KNIGHT") == 0 || strcmp(table.name, "PRODUCE_PEASANT") == 0)
    {
        how_many_operations = sscanf(input, "%s %d %d %d %d", table.name, &table.data[0], &table.data[1], &table.data[2], &table.data[3]);
        if(how_many_operations == 5 && memory == 5) return table;
        else return make_command_incorrect(table);
    }
    else
    {
        return make_command_incorrect(table);
    }
}
