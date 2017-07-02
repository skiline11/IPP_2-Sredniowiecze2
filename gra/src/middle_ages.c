/* Michał Radecki mr371591 */
/* IPP - Drugie zadanie zaliczeniowe "Średniowiecze - cz1" */

/** @file
   Interface of middle_ages.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parse.h"
#include "engine.h"

/**
 * Function main() gets commands, and makes them.
 */
int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    start_game();
    command new_command;
    int number_of_init = 0;
    bool my_turn = true;
    int my_player_number;
    while (true) {
        if(number_of_init < 1)
        {
        	new_command = parse_command();
        	if(new_command.correct == false) incorrect_command();
            if(strcmp(new_command.name, "INIT") == 0) {
                number_of_init++;
                if(new_command.data[2] == 1)
                {
                	my_turn = true;
                	my_player_number = 1;
                }
                else if(new_command.data[2] == 2) 
                {
                	my_turn = false;
                	my_player_number = 2;
                }
                init(new_command.data[0],
                     new_command.data[1],
                     new_command.data[2],
                     new_command.data[3],
                     new_command.data[4],
                     new_command.data[5],
                     new_command.data[6]);
            }
            else incorrect_command();
        }
        else
        {
        	if(my_turn == true)
        	{
        		end_turn();
        		printf("END_TURN\n");
        		my_turn = false;
        	}
        	else
        	{
        		new_command = parse_command();
        		if(new_command.correct == false) incorrect_command();
	            if(strcmp(new_command.name, "END_TURN") == 0)
	            {
	                end_turn();
	                my_turn = true;
	            }
	            else if(strcmp(new_command.name, "MOVE") == 0)
	            {
	                move(new_command.data[0],
	                     new_command.data[1],
	                     new_command.data[2],
	                     new_command.data[3]);
	            }
	            else if(strcmp(new_command.name, "PRODUCE_KNIGHT") == 0)
	            {
	                produce_knight(new_command.data[0],
	                               new_command.data[1],
	                               new_command.data[2],
	                               new_command.data[3]);
	            }
	            else if(strcmp(new_command.name, "PRODUCE_PEASANT") == 0)
	            {
	                produce_peasant(new_command.data[0],
	                                new_command.data[1],
	                                new_command.data[2],
	                                new_command.data[3]);
	            }
	            else incorrect_command();
	        }
	    }
	}
    return 0;
}
