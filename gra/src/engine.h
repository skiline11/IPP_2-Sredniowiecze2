/* Michał Radecki mr371591 */
/* IPP - Drugie zadanie zaliczeniowe "Średniowiecze - cz1" */

/** @file
    Interface of game engine.

 */

#ifndef ENGINE_H
#define ENGINE_H

struct line;

/** Structure of list_of_lines */
typedef struct list_of_lines
{
    /** Indicator to next line in list of lines */
    struct list_of_lines* next_line;
    /** Indicator to previous line in list of lines */
    struct list_of_lines* previous_line;
    /** Indicator to fields in this line */
    struct line *this_line;
    /** Information about map_size */
    int map_size;
    /** Information about max_number_of_turns */
    int max_number_of_turns;
    /** Information about number_of_line */
    int number_of_line;
}type_of_list_of_lines;

/** Structure of single line */
typedef struct line
{
    /** Information about race of unit */
    bool king;
    /** Information about race of unit */
    bool knight;
    /** Information about race of unit */
    bool peasant;
    /* X-coordinate of unit */
    int pos_x;
    /* Y-coordinate of unit */
    int pos_y;
    /* Number of player to which the unit belongs */
    int player_number;
    /* Number of turn, when unit made last move or action */
    int last_move_or_action;
    /** Indicator to next unit in line */
    struct line *next;
    /** Indicator to previous unit in line */
    struct line *previous;
    /** Indicator to list of lines */
    type_of_list_of_lines *to_list_of_lines;
}type_of_line;

/** This structure include input parameters */
typedef struct input_parameters
{
    /** size of map */
    int n;
    /** maximum amount of turns for every player */
    int k;
    /** number of player1 */
    int p1;
    /** number of player2 */
    int p2;
    /** x-coordinate of king of player1 */
    int x1;
    /** y-coordinate of king of player1 */
    int y1;
    /** x-coordinates of king of player2 */
    int x2;
    /** y-coordinate of king of player2 */
    int y2;
}type_of_input_parameters;

/** Pointer to mock of list of lines. */
type_of_list_of_lines* constructor_of_main_list;

/** Memory of input parameters. */
type_of_input_parameters input;

/** Counter of number of initializations. */
int number_of_init;

/** Counter of actually playing player. */
int player_number;

/** Counter of actually playing turn. */
int counter_of_rounds;

/**
 * This function makes main list empty, with no previous, and next field.
 * @param[in] *constructor_of_main_list Pointer to field which is mock for main_list
 */
void make_list_empty(type_of_list_of_lines *constructor_of_main_list);

/** Initializes a game. Needed before first INIT. */
void start_game();

/** Frees memory. Needed after finishing game. */
void end_game();

/** This function enforce incorrect command with exit(42) result. */
void incorrect_command();

/**
 * This function print symbol of given field.
 * @param[in] *iterator_on_line Given field.
 */
void print_symbol(type_of_line *iterator_on_line);

/**
 * This function print empty line (line full of spaces) which include given amount of spaces.
 * @param[in] size_to_print Amount of spaces to print.
 */
void print_empty_line(int size_to_print);

/** Prints (into stdout) top-left corner of the board of size m x m where m = min(n,10). */
void print_topleft();

/**
 * This function create peasant for init.
 * @param[in] character Indicator to field of created character.
 * @param[in] x X-Coordinate of created character.
 */
void create_character(type_of_line* character, int x);

/**
 * This function create peasant for init needs using create_character function.
 * @param[in] king Indicator to field of created king.
 * @param[in] x X-Coordinate of created king.
 */
void create_king(type_of_line* king, int x);

/**
 * This function create knight for init needs using create_character function.
 * @param[in] knight Indicator to field of created knight.
 * @param[in] x X-Coordinate of created knight.
 */
void create_knight(type_of_line* knight, int x);

/**
 * This function create peasant for init needs using create_character function.
 * @param[in] peasant Indicator to field of created peasant.
 * @param[in] x X-Coordinate of created peasant.
 */
void create_peasant(type_of_line* peasant, int x);

/** This function put king, peasant, knight1 and knigth2 to line behind new_line1. */
void put_in_line(type_of_line* new_line1, type_of_line* king, type_of_line* peasant, type_of_line* knight1, type_of_line* knight2);

/** This function create mock for new_line and set pos_x of this mock on (-1). */
void create_line(type_of_list_of_lines* new_line, int y);

/** This function return absolute value of given number. */
int absolute_value(int number);

/** This function check if input is correct. */
void check_correctness_of_input(int n, int k, int p, int x1, int y1, int x2, int y2);

/** This function check if positions are correct to make action. */
void check_correctness_of_positions_to_move_or_produce(int x1, int y1, int x2, int y2);

/** This function memorize parameters given with INIT. */
void set_input_parameters(int n, int k, int p, int x1, int y1, int x2, int y2);

/** Initializes a game with size of a board, number of rounds and positions of kings. */
void init(int n, int k, int p, int x1, int y1, int x2, int y2);

/** This function look for line with index y */
type_of_list_of_lines* find_line(int y);

/**
 * This function look for field with index x, in the given line.
 * @param[in] iterator Pointer to line where function looks for field with X-Coordinate = x.
 * @param[in] x X-Coordinate of searches field.
 */
type_of_line* find_field(type_of_list_of_lines* iterator, int x);

/**
 * This function delete given field
 * and if it was last field delete whole line
 * @param[in] character Field which will be delete
 */
void delete_field(type_of_line* character);

/** This function end game with draw result */
void draw();

/**
 * This function end game with win result of one of players.
 * @param[in] player_number Number of player which won.
 */
void player_won(int player_number);

/**
 * This function make fight between character1 and character2
 * and delete fields killed characters.
 * @param[in] character1 Participant of fight.
 * @param[in] character2 Participant of fight.
 */
void fight(type_of_line* character1, type_of_line* character2);

/**
 * This function copy every parameters from field to new_field.
 * @param[in] field Field with parameters which we copy.
 * @param[in] new_field Field which receive copied parameters.
 */
void clone_field(type_of_line* field, type_of_line* new_field);

/**
 * This function move characters from place coordinates (x1, y1) to (x2, y2) if it is possible.
 * If on field with coordinates (x2, y2) is enemy unit, this function makes a fight between them.
 * @param[in] x1 Column number before a move.
 * @param[in] y1 Row number before a move.
 * @param[in] x2 Column number after a move.
 * @param[in] y2 Row number before a move.
 */
void move(int x1, int y1, int x2, int y2);

/**
 * This function results in production unit on field with coordinates (x2, y2) by peasant on field with coordinates (x1, y1)
 * @param[in] x1 Column number of peasant which produce unit.
 * @param[in] y1 Row number of peasant which produce unit.
 * @param[in] x2 Column number of place to produce unit.
 * @param[in] y2 Row number of place to produce unit.
 */
type_of_line* produce_unit(int x1, int y1, int x2, int y2);

/**
 * This function produce unit using produce_unit(x1, y1, x2, y2) function and give to this unit knight attribute.
 * @param[in] x1 Column number of peasant which produce knight.
 * @param[in] y1 Row number of peasant which produce knight.
 * @param[in] x2 Column number of place to produce knight.
 * @param[in] y2 Row number of place to produce knight.
 */
void produce_knight(int x1, int y1, int x2, int y2);

/**
 * This function produce unit using produce_unit(x1, y1, x2, y2) function and give to this unit peasant attribute.
 * @param[in] x1 Column number of peasant which produce peasant.
 * @param[in] y1 Row number of peasant which produce peasant.
 * @param[in] x2 Column number of place to produce peasant.
 * @param[in] y2 Row number of place to produce peasant.
 */
void produce_peasant(int x1, int y1, int x2, int y2);

/** This function end turn of one of players, and check if the number of played turns isn't bigger than max_number_of_turns. */
void end_turn();

#endif /* ENGINE_H */
