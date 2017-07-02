/* Michał Radecki mr371591 */
/* IPP - Drugie zadanie zaliczeniowe "Średniowiecze - cz1" */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct line;

typedef struct list_of_lines
{
    struct list_of_lines* next_line;
    struct list_of_lines* previous_line;
    struct line *this_line;
    int map_size, max_number_of_turns, number_of_line;
}type_of_list_of_lines;

typedef struct line
{
    bool king, knight, peasant;
    int pos_x, player_number, last_move_or_action;
    struct line *next;
    struct line *previous;
    type_of_list_of_lines *to_list_of_lines;
}type_of_line;

typedef struct input_parameters
{
    int n, k, p1, x1, y1, x2, y2;
}type_of_input_parameters;

type_of_list_of_lines* constructor_of_main_list = NULL;
type_of_input_parameters input;
int number_of_init = 0;
int player_number;
int counter_of_rounds = 1;

void make_list_empty(type_of_list_of_lines* constructor_of_main_list)
{
    constructor_of_main_list->next_line = NULL;
    constructor_of_main_list->previous_line = NULL;
    constructor_of_main_list->this_line = NULL;
    constructor_of_main_list->number_of_line = 0;
}

void start_game()
{
    constructor_of_main_list = malloc(sizeof(type_of_list_of_lines));
    make_list_empty(constructor_of_main_list);
}

void end_game() {
    type_of_list_of_lines* line = constructor_of_main_list;
    type_of_list_of_lines* next_line = line->next_line;
    type_of_line* field = NULL;
    type_of_line* next_field = NULL;
    free(line);
    line = next_line;
    while(line != NULL)
    {
        next_line = line->next_line;
        field = line->this_line;
        next_field = field->next;
        free(field);
        field = next_field;
        while(field != NULL)
        {
            next_field = field->next;
            free(field);
            field = next_field;
        }
        free(line);
        line = next_line;
    }
}

void incorrect_command()
{
    end_game();
    fprintf(stderr, "input error\n");
    exit(42);
}

void print_symbol(type_of_line* iterator_on_line)
{
    if(iterator_on_line->player_number == 1)
    {
        if(iterator_on_line->king == true) printf("K");
        else if(iterator_on_line->knight == true) printf("R");
        else if(iterator_on_line->peasant == true) printf("C");
    }
    else if(iterator_on_line->player_number == 2)
    {
        if(iterator_on_line->king == true) printf("k");
        else if(iterator_on_line->knight == true) printf("r");
        else if(iterator_on_line->peasant == true) printf("c");
    }
}

void print_empty_line(int size_to_print)
{
    while(size_to_print > 0)
    {
        printf(".");
        size_to_print--;
    }
    printf("\n");
}

void print_topleft()
{
    type_of_list_of_lines* iterator_on_main_list = constructor_of_main_list->next_line;
    type_of_line* iterator_on_line;
    int x, y = 1;
    int size_to_print = constructor_of_main_list->map_size;
    if(size_to_print > 10) size_to_print = 10;
    while(y <= size_to_print)
    {
        x = 1;
        if(iterator_on_main_list != NULL)
        {
            if(iterator_on_main_list->number_of_line == y) //chcę wypisać tą linię
            {
                iterator_on_line = iterator_on_main_list->this_line->next;
                while(x <= size_to_print)
                {
                    if(iterator_on_line != NULL)
                    {
                        if(iterator_on_line->pos_x == x)
                        {
                            print_symbol(iterator_on_line);
                            iterator_on_line = iterator_on_line->next;
                        }
                        else
                        {
                            printf(".");
                        }
                    }
                    else printf(".");
                    x++;
                }
                iterator_on_main_list = iterator_on_main_list->next_line;
                printf("\n");
            }
            else print_empty_line(size_to_print);
        }
        else print_empty_line(size_to_print);
        y++;
    }
    printf("\n");
}

void create_character(type_of_line* character, int x)
{
    character->king = false;
    character->knight = false;
    character->peasant = false;
    character->pos_x = x;
    character->player_number = player_number;
    character->last_move_or_action = 0;
}

void create_king(type_of_line* king, int x)
{
    create_character(king, x);
    king->king = true;
}
void create_knight(type_of_line* knight, int x)
{
    create_character(knight, x);
    knight->knight = true;
}
void create_peasant(type_of_line* peasant, int x)
{
    create_character(peasant, x);
    peasant->peasant = true;
}

void put_in_line(type_of_line* new_line1, type_of_line* king, type_of_line* peasant, type_of_line* knight1, type_of_line* knight2)
{
    new_line1->next = king;
    king->previous = new_line1;
    king->to_list_of_lines = new_line1->to_list_of_lines;

    king->next = peasant;
    peasant->previous = king;
    peasant->to_list_of_lines = new_line1->to_list_of_lines;

    peasant->next = knight1;
    knight1->previous = peasant;
    knight1->to_list_of_lines = new_line1->to_list_of_lines;

    knight1->next = knight2;
    knight2->previous = knight1;
    knight2->to_list_of_lines = new_line1->to_list_of_lines;
}

void create_line(type_of_list_of_lines* new_line, int y)
{
    type_of_line* this_line1 = malloc(sizeof(type_of_line));
    new_line->this_line = this_line1;
    this_line1->previous = NULL;
    this_line1->next = NULL;
    this_line1->pos_x = -1;
    new_line->this_line->to_list_of_lines = new_line;
    new_line->number_of_line = y;
}

int absolute_value(int number)
{
    if(number < 0) number *= (-1);
    return number;
}

void check_correctness_of_input(int n, int k, int p, int x1, int y1, int x2, int y2)
{
    if(n != input.n || k != input.k || p == input.p1 || x1 != input.x1 || y1 != input.y1 || x2 != input.x2 || y2 != input.y2) incorrect_command();
    else if((input.p1 == 1 && p != 2) || (input.p1 == 2 && p != 1)) incorrect_command();
}

void check_correctness_of_positions_to_move_or_produce(int x1, int y1, int x2, int y2)
{
    if(absolute_value(x1 - x2) > 1 || absolute_value(y1 - y2) > 1 || (x1 == x2 && y1 == y2)) incorrect_command();
    int size = constructor_of_main_list->map_size;
    if(x1 > size || y1 > size || x2 > size || y2 > size) incorrect_command();
    if(x1 <= 0 || y1 <= 0 || x2 <= 0 || y2 <= 0) incorrect_command();
}

void set_input_parameters(int n, int k, int p, int x1, int y1, int x2, int y2)
{
    input.n = n;
    input.k = k;
    input.p1 = p;
    input.x1 = x1;
    input.x2 = x2;
    input.y1 = y1;
    input.y2 = y2;
}

void init(int n, int k, int p, int x1, int y1, int x2, int y2)
{
    number_of_init++;
    if(number_of_init == 1)
    {
        if((absolute_value(x1 - x2) < 8) && (absolute_value(y1 - y2) < 8)) incorrect_command();
        if(n < 3 || k < 1 || p < 1 || p > 2 || x1 < 1 || x1 + 3 > n || x2 < 1 || x2 + 3 > n || y1 < 1 || y1 > n || y2 < 1 || y2 > n) incorrect_command();
        set_input_parameters(n, k, p, x1, y1, x2, y2);
        constructor_of_main_list->map_size = n;
        constructor_of_main_list->max_number_of_turns = k;

        /* create new line */
        type_of_list_of_lines* new_line1 = malloc(sizeof(type_of_list_of_lines));
        create_line(new_line1, y1);

        /* create player1 and put characters on map */
        player_number = 1;
        constructor_of_main_list->next_line = new_line1;
        new_line1->previous_line = constructor_of_main_list;
        type_of_line* king1 = malloc(sizeof(type_of_line));
        create_king(king1, x1);
        type_of_line* peasant1 = malloc(sizeof(type_of_line));
        create_peasant(peasant1, x1 + 1);
        type_of_line* knigth1_1 = malloc(sizeof(type_of_line));
        type_of_line* knigth1_2 = malloc(sizeof(type_of_line));
        create_knight(knigth1_1, x1 + 2);
        create_knight(knigth1_2, x1 + 3);
        put_in_line(new_line1->this_line, king1, peasant1, knigth1_1, knigth1_2);
        knigth1_2->next = NULL;


        /* create player2 and put characters on map */
        player_number = 2;
        type_of_line* king2 = malloc(sizeof(type_of_line));
        create_king(king2, x2);
        type_of_line* peasant2 = malloc(sizeof(type_of_line));
        create_peasant(peasant2, x2 + 1);
        type_of_line* knigth2_1 = malloc(sizeof(type_of_line));
        type_of_line* knigth2_2 = malloc(sizeof(type_of_line));
        create_knight(knigth2_1, x2 + 2);
        create_knight(knigth2_2, x2 + 3);
        if(y1 == y2)
        {
            if(x2 < x1)
            {
                knigth2_2->next = new_line1->this_line->next;
                put_in_line(new_line1->this_line, king2, peasant2, knigth2_1, knigth2_2);
                knigth2_2->next = king1;
                king1->previous = knigth2_2;
            }
            else //(x1 < x2)
            {
                put_in_line(knigth1_2, king2, peasant2, knigth2_1, knigth2_2);
            }
        }
        else
        {
            type_of_list_of_lines* new_line2 = malloc(sizeof(type_of_list_of_lines));
            create_line(new_line2, y2);
            if(y2 < y1)
            {
                constructor_of_main_list->next_line = new_line2;
                new_line2->previous_line = constructor_of_main_list;
                new_line2->next_line = new_line1;
                new_line1->previous_line = new_line2;
            }
            else // y1 < y2
            {
                new_line1->next_line = new_line2;
                new_line2->previous_line = new_line1;
                new_line2->next_line = NULL;
            }
            put_in_line(new_line2->this_line, king2, peasant2, knigth2_1, knigth2_2);
        }
        player_number = 1;
    }
    //print_topleft();
}

type_of_list_of_lines* find_line(int y)
{
    type_of_list_of_lines* iterator = constructor_of_main_list;
    while(iterator->next_line != NULL && iterator->next_line->number_of_line <= y)
    {
        iterator = iterator->next_line;
    }
    if(iterator->number_of_line == y) return iterator;
    else return NULL;

}

type_of_line* find_field(type_of_list_of_lines* iterator, int x)
{
    type_of_line* iterator_over_line = iterator->this_line;
    while(iterator_over_line->next != NULL && iterator_over_line->next->pos_x <= x)
    {
        iterator_over_line = iterator_over_line->next;
    }
    if(iterator_over_line->pos_x == x) return iterator_over_line;
    else return NULL;
}

void delete_field(type_of_line* character)
{
    if(character->previous->pos_x == (-1) && character->next == NULL)
    {
        character->to_list_of_lines->previous_line->next_line = character->to_list_of_lines->next_line;
        if(character->to_list_of_lines->next_line != NULL)
        {
            character->to_list_of_lines->next_line->previous_line = character->to_list_of_lines->previous_line;
        }
        free(character->to_list_of_lines->this_line);
        free(character->to_list_of_lines);
    }
    else
    {
        character->previous->next = character->next;
        if(character->next != NULL)
        {
            character->next->previous = character->previous;
        }
    }
    free(character);
}

void draw()
{
    fprintf(stderr, "draw\n" );
    //print_topleft();
    end_game();
    exit(1);
}

void player_won(int player_number)
{
    fprintf(stderr, "player %d won\n", player_number);
    //print_topleft();
    end_game();
    if(player_number == input.p1) exit(0);
    else exit(2);
}

void fight(type_of_line* character1, type_of_line* character2)
{
    if(character1->king == true)
    {
        if(character2->king == true)
        {
            delete_field(character1);
            delete_field(character2);
            draw();
        }
        else if(character2->knight == true)
        {
            delete_field(character1);
            player_won(character2->player_number);
        }
        else if(character2->peasant == true)
        {
            character2->peasant = false;
            character2->king = true;
            character2->player_number = character1->player_number;
            character2->last_move_or_action = counter_of_rounds;
            delete_field(character1);
        }
    }
    else if(character1->knight == true)
    {
        if(character2->king == true)
        {
            character2->king = false;
            character2->knight = true;
            character2->player_number = character1->player_number;
            delete_field(character1);
            player_won(character2->player_number);
        }
        else if(character2->knight == true)
        {
            delete_field(character1);
            delete_field(character2);
        }
        else if(character2->peasant == true)
        {
            character2->peasant = false;
            character2->knight = true;
            character2->player_number = character1->player_number;
            character2->last_move_or_action = counter_of_rounds;
            delete_field(character1);
        }
    }
    else if(character1->peasant == true)
    {
        if(character2->peasant == true)
        {
            delete_field(character1);
            delete_field(character2);
        }
        else if(character2->peasant == false)
        {
            delete_field(character1);
        }
    }
}

void clone_field(type_of_line* field, type_of_line* new_field)
{
    new_field->king = field->king;
    new_field->knight = field->knight;
    new_field->peasant = field->peasant;
    new_field->player_number = field->player_number;
    new_field->last_move_or_action = field->last_move_or_action;
}

void move(int x1, int y1, int x2, int y2)
{
    check_correctness_of_positions_to_move_or_produce(x1, y1, x2, y2);
    type_of_list_of_lines* iterator1 = find_line(y1);
    if(iterator1 == NULL) incorrect_command();
    type_of_line* field = find_field(iterator1, x1);
    if(field == NULL || field->player_number != player_number) incorrect_command();
    if(field->last_move_or_action == counter_of_rounds) incorrect_command();
    field->last_move_or_action = counter_of_rounds;
    if(y2 == y1)
    {
        if(x2 < x1) // move left
        {
            if(field->previous->pos_x < x2)
            {
                field->pos_x--;
            }
            else if(field->previous->pos_x == x2)
            {
                if(field->previous->player_number == player_number) incorrect_command();
                else
                {
                    fight(field, field->previous);
                }
            }
        }
        else if(x2 > x1) // move right
        {
            if(field->next == NULL || field->next->pos_x > x2)
            {
                field->pos_x++;
            }
            else if(field->next->pos_x == x2)
            {
                if(field->next->player_number == player_number) incorrect_command();
                else
                {
                    fight(field, field->next);
                }
            }
        }
    }
    else if(y2 < y1) // move up
    {
        iterator1 = field->to_list_of_lines->previous_line;
        if(field->previous->pos_x == (-1) && field->next == NULL && iterator1->number_of_line < y2)
        {
            field->pos_x = x2;
            field->to_list_of_lines->number_of_line = y2;
        }
        else if(iterator1->number_of_line != y2)
        {
            type_of_list_of_lines* new_line = malloc(sizeof(type_of_list_of_lines));

            new_line->previous_line = iterator1;
            new_line->next_line = iterator1->next_line;
            new_line->previous_line->next_line = new_line;
            new_line->next_line->previous_line = new_line;

            create_line(new_line, y2);

            // type_of_line* new_field = create_field(new_line, x2); ?

            type_of_line* new_field = malloc(sizeof(type_of_line));
            new_line->this_line->next = new_field;
            new_field->to_list_of_lines = new_line;
            new_field->previous = new_line->this_line;
            new_field->next = NULL;
            new_field->pos_x = x2;
            clone_field(field, new_field);
            delete_field(field);
        }
        else // line number y2 exist
        {
            type_of_line* field2 = iterator1->this_line;
            while(field2->next != NULL && field2->next->pos_x <= x2)
            {
                field2 = field2->next;
            }
            if(field2->pos_x == x2)
            {
                if(field2->player_number == player_number) incorrect_command();
                else
                {
                    fight(field, field2);
                }
            }
            else // field2->pos_x < x2
            {
                type_of_line* new_field = malloc(sizeof(type_of_line));
                new_field->next = field2->next;
                new_field->previous = field2;
                field2->next = new_field;
                new_field->to_list_of_lines = field2->to_list_of_lines;
                new_field->pos_x = x2;
                if(new_field->next != NULL)
                {
                    new_field->next->previous = new_field;
                }
                clone_field(field, new_field);
                delete_field(field);
            }
        }
    }
    else if(y2 > y1) // move down
    {
        iterator1 = field->to_list_of_lines;
        if(field->previous->pos_x == (-1) && field->next == NULL && ( iterator1->next_line == NULL || iterator1->next_line->number_of_line > y2) )
        {
            field->pos_x = x2;
            field->to_list_of_lines->number_of_line = y2;
        }
        else if(iterator1->next_line == NULL || iterator1->next_line->number_of_line != y2)
        {
            type_of_list_of_lines *new_line = malloc(sizeof(type_of_list_of_lines));

            new_line->previous_line = iterator1;
            new_line->next_line = iterator1->next_line;
            new_line->previous_line->next_line = new_line;
            if (new_line->next_line != NULL)
            {
                new_line->next_line->previous_line = new_line;
            }
            create_line(new_line, y2);

            type_of_line *new_field = malloc(sizeof(type_of_line));
            new_line->this_line->next = new_field;
            new_field->to_list_of_lines = new_line;
            new_field->previous = new_line->this_line;
            new_field->next = NULL;
            new_field->pos_x = x2;
            clone_field(field, new_field);
            delete_field(field);
        }
        else // line number y2 exist
        {
            type_of_line* field2 = iterator1->next_line->this_line;
            while(field2->next != NULL && field2->next->pos_x <= x2)
            {
                field2 = field2->next;
            }
            if(field2->pos_x == x2)
            {
                if(field2->player_number == player_number) incorrect_command();
                else
                {
                    fight(field, field2);
                }
            }
            else
            {
                type_of_line* new_field = malloc(sizeof(type_of_line));
                new_field->next = field2->next;
                new_field->previous = field2;
                field2->next = new_field;
                new_field->to_list_of_lines = field2->to_list_of_lines;
                new_field->pos_x = x2;
                if(new_field->next != NULL)
                {
                    new_field->next->previous = new_field;
                }
                clone_field(field, new_field);
                delete_field(field);
            }
        }
    }
    //print_topleft();
}

type_of_line* produce_unit(int x1, int y1, int x2, int y2)
{
    check_correctness_of_positions_to_move_or_produce(x1, y1, x2, y2);
    type_of_list_of_lines *iterator1 = find_line(y1);
    if (iterator1 == NULL) incorrect_command();
    type_of_line* field = find_field(iterator1, x1);
    type_of_line* new_field;
    type_of_list_of_lines* new_line;
    if (field == NULL || field->player_number != player_number || field->peasant == false) incorrect_command();
    if(field->last_move_or_action > counter_of_rounds - 3) incorrect_command();
    field->last_move_or_action = counter_of_rounds;
    if (y1 == y2)
    {
        if (x2 < x1) // produce on left
        {
            if (field->previous->pos_x < x2) {
                new_field = malloc(sizeof(type_of_line));
                create_character(new_field, x2);
                new_field->to_list_of_lines = field->to_list_of_lines;
                new_field->next = field;
                new_field->previous = field->previous;
                field->previous->next = new_field;
                field->previous = new_field;
            }
            else incorrect_command();
        }
        else if (x2 > x1) // produce on right
        {
            if (field->next == NULL || field->next->pos_x > x2) {
                new_field = malloc(sizeof(type_of_line));
                create_character(new_field, x2);
                new_field->to_list_of_lines = field->to_list_of_lines;
                new_field->previous = field;
                new_field->next = field->next;
                field->next->previous = new_field;
                field->next = new_field;
            }
            else incorrect_command();
        }
    }
    else if (y2 < y1) // produce up
    {
        iterator1 = field->to_list_of_lines->previous_line;
        if (iterator1->number_of_line != y2) {
            new_line = malloc(sizeof(type_of_list_of_lines));

            new_line->previous_line = iterator1;
            new_line->next_line = iterator1->next_line;
            new_line->previous_line->next_line = new_line;
            new_line->next_line->previous_line = new_line;

            create_line(new_line, y2);


            new_field = malloc(sizeof(type_of_line));
            create_character(new_field, x2);
            new_line->this_line->next = new_field;
            new_field->to_list_of_lines = new_line;
            new_field->previous = new_line->this_line;
            new_field->next = NULL;
        }
        else // line number y2 exist
        {
            type_of_line *field2 = iterator1->this_line;
            while (field2->next != NULL && field2->next->pos_x <= x2) {
                field2 = field2->next;
            }
            if (field2->pos_x == x2) incorrect_command();
            else
            {
                new_field = malloc(sizeof(type_of_line));
                create_character(new_field, x2);
                new_field->next = field2->next;
                new_field->previous = field2;
                field2->next = new_field;
                new_field->to_list_of_lines = field2->to_list_of_lines;
                if (new_field->next != NULL)
                {
                    new_field->next->previous = new_field;
                }
            }
        }
    }
    else if(y2 > y1) // produce down
    {
        iterator1 = field->to_list_of_lines;
        if(iterator1->next_line == NULL || iterator1->next_line->number_of_line != y2)
        {
            new_line = malloc(sizeof(type_of_list_of_lines));

            new_line->previous_line = iterator1;
            new_line->next_line = iterator1->next_line;
            new_line->previous_line->next_line = new_line;
            if(new_line->next_line != NULL)
            {
                new_line->next_line->previous_line = new_line;
            }
            new_line->next_line->previous_line = new_line;

            create_line(new_line, y2);

            new_field = malloc(sizeof(type_of_line));
            create_character(new_field, x2);
            new_line->this_line->next = new_field;
            new_field->to_list_of_lines = new_line;
            new_field->previous = new_line->this_line;
            new_field->next = NULL;
        }
        else // line number y2 exist
        {
            type_of_line* field2 = iterator1->next_line->this_line;
            while(field2->next != NULL && field2->next->pos_x <= x2)
            {
                field2 = field2->next;
            }
            if(field2->pos_x == x2) incorrect_command();
            else
            {
                new_field = malloc(sizeof(type_of_line));
                create_character(new_field, x2);
                new_field->next = field2->next;
                new_field->previous = field2;
                field2->next = new_field;
                new_field->to_list_of_lines = field2->to_list_of_lines;
                if(new_field->next != NULL)
                {
                    new_field->next->previous = new_field;
                }
            }
        }
    }
    return new_field;
}

void produce_knight(int x1, int y1, int x2, int y2)
{
    type_of_line* knight = produce_unit(x1, y1, x2, y2);
    knight->knight = true;
    //print_topleft();
}

void produce_peasant(int x1, int y1, int x2, int y2)
{
    type_of_line* knight = produce_unit(x1, y1, x2, y2);
    knight->peasant = true;
    //print_topleft();
}

void end_turn()
{
    if(player_number == 2)
    {
        player_number = 1;
        counter_of_rounds++;
        if(counter_of_rounds > constructor_of_main_list->max_number_of_turns)
        {
            end_game();
            fprintf(stderr, "draw\n" );
            exit(1);
        }
    }
    else if(player_number == 1) player_number = 2;
}
