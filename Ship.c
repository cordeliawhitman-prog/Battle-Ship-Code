#include "Ship.h"


//menu screen for printing rules exiting or playing
int welcome_screen(void)
{
	int option = 1, play_game = 0;
	printf("lets play Battleship!!\n");
	do
	{
		printf("1. Display Rules.\n");
		printf("2. Play Game.\n");
		printf("3. Exit.\n");
		scanf("%d", &option);
	} while (!(option >= 1 && option <= 3));

	switch (option)
	{
	case 1: printf("Displaying the rules!\n");
		rules();
		system("pause");
		system("cls");
		welcome_screen();
		break;
	case 2: printf("Playing the game!\n");
		play_game = 1;
		return play_game;
		break;
	case 3: printf("Exiting!\n");
		play_game = 0;
		return play_game;
		break;
	default: printf("Error with input!\n");
		break;
	}

}

//prints the rules of the game 
void rules(void)
{
	printf("\n\t\t\tBATTLESHIP!!!\n");
	printf("\n\t\t\tRules of Battleship: \n\n");
	printf("Players place their 'fleet' of 5 ships on their 'ocean', hidden from the\n");
	printf("opponent's view. Taking turns, players call out their 'shots' attempting to\n");
	printf("get 'hits' on the opponent's ships in order to sink them. Strategy and some\n");
	printf("luck must be combined to be the first to locate and sink all 5 opponent's\n");
	printf("ships to win the game. The object of the game is to be the first player to\n");
	printf("sink all five of his opponent's ships. Each player SECRETLY places his fleet\n");
	printf("of 5 ships on his ocean grid. Ships may be placed in any horizontal or vertical\n");
	printf("position - but NOT diagonally. You MAY NOT change the position of any ship.\n");
	printf("To do so would be cheating!\n\n");
	printf("This is a one player game where you are player1, and the computer is player2.\n\n");
	printf("Types of Ships: \tSize:\n\n");
	printf("Aircraft Carrier \t5 \nBattleship \t\t4 \nCruiser \t\t3 \nSubmarine \t\t3 \nDestroyer \t\t2\n\n");
	printf("Symbols: \n c - Aircraft Carrier\n b - Battleship\n r - Cruiser\n s - Submarine\n d - Destroyer\n");
	printf("\n ~ - Water\n * - Hit\n m - Miss\n");
}
//Function prints initizal board before the game begins and lays out the charaters for each of the units
char initialize_game_board(int x1, int y1, int x2, int y2, char board[10][10], int print, int player, int xtar, int ytar, int* hits, char visible[10][10], char type)
{
    int x = 0, y = 0;
    if (print != 0)
    {
        printf("\n\t    0 1 2 3 4 5 6 7 8 9\n");
        printf("\t +---------------------+\n\t");
    }
    for (x = 0; x < 10; x++)
    {
        if ((x < 9) && (print != 0))
        {
            printf("%d | ", x);
        }
        if ((x == 9) && (print != 0))
        {
            printf("%d | ", x);
        }
        for (y = 0; y < 10; y++)
        {
            if ((board[x][y] != 'c') && (board[x][y] != 'b') && (board[x][y] != 'r') && (board[x][y] != 's') && (board[x][y] != 'd')
                && (board[x][y] != '*') && (board[x][y] != 'm'))
            {
                board[x][y] = '~';
                if ((((x == x1) && (y == y1)) || ((x == x2) && (y == y2))) && (print != -1))
                {
                    board[x][y] = type;
                }
                if ((((x < x1) && (x > x2) && (y == y1)) || ((x > x1) && (x < x2) && (y == y1))) && (print != -1))
                {
                    board[x][y] = type;
                }
                if ((((y < y1) && (y > y2) && (x == x1)) || ((y > y1) && (y < y2) && (x == x1))) && (print != -1))
                {
                    board[x][y] = type;
                }
            }
            if (board[x][y] == '~')
            {
                visible[x][y] = '~';
            }
            if ((board[x][y] >= 'b') && (board[x][y] <= 's') && (board[x][y] != 'm'))
            {
                visible[x][y] = '~';
            }
            if (board[x][y] == 'm')
            {
                visible[x][y] = 'm';
            }
            if (board[x][y] == '*')
            {
                visible[x][y] = '*';
            }
            if ((x == xtar) && (y == ytar))
            {
                if ((board[x][y] >= 'b') && (board[x][y] <= 's'))
                {
                    visible[x][y] = '*';
                    board[x][y] = '*';
                    *hits = *hits + 1;
                }
                if (board[x][y] == '~')
                {
                    visible[x][y] = 'm';
                    board[x][y] = 'm';
                }
            }
            if ((print != 0) && (player == 1))
            {
                printf("%c ", board[x][y]);
            }
            if ((print != 0) && (player == 2))
            {
                printf("%c ", visible[x][y]);
            }
            if ((y == 9) && (print != 0))
            {
                printf("| %d\n\t", x);
            }
        }
    }
    if (print != 0)
    {
        printf(" +---------------------+\n");
        printf("\t    0 1 2 3 4 5 6 7 8 9\n\n");
    }
    return board;
}
//This function decides and returns which player goes first.                 
int select_who_starts_first(void)
{
    int select = 0, player = 0;
    select = rand() % 2;
    if (select == 0)
    {
        printf("Player1 (Human) goes first. . .\n\n");
        player = 1;
    }
    if (select == 1)
    {
        printf("Player2 (CPU) goes first. . .\n\n");
        player = 2;
    }
    return player;
}
//This function prompts the user to decide whether to place their ships randomly or manually
int deploy_ships(void)
{
    int deploy = 0;
    printf("How would you like to deploy your ships?\n1) Manually\n2) Randomly\n\n");
    scanf("%d", &deploy);
    return deploy;
}
//This function prompts the user to enter the endpoint coordinates for each ship.    
void manually_place_ships_on_board(int* x1, int* y1, int* x2, int* y2, int size, char board[10][10])
{
    int check = 0, x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, x = 0, y = 0;
    do {
        do {
            check = 0; x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, * x1 = 0, * y1 = 0, * x2 = 0, * y2 = 0;
            printf("Enter the endpoint coordinates for your Ship, size: %d: \n", size);
            scanf("%d %d %d %d", y1, x1, y2, x2);
            if ((*x1 != *x2) && (*y1 != *y2))
            {
                printf("The ship cannot be diagonal!\n");
            }
            if (*y1 == *y2)
            {
                check = abs(*x1 - *x2) + 1;
            }
            if (*x1 == *x2)
            {
                check = abs(*y1 - *y2) + 1;
            }
            if (check != size)
            {
                printf("The ship does not fit those coordinates!\n");
            }
        } while (((*x1 < 0) || (*x1 > 9)) || ((*y1 < 0) && (*y1 > 9)) || ((*x2 < 0) || (*x2 > 9)) || ((*y2 < 0) && (*y2 > 9)) ||
            ((*x1 != *x2) && (*y1 != *y2)) || (check != size));
        if (*y1 == *y2)
        {
            if (*x1 > *x2)
            {
                if (size > 2)
                {
                    x_1 = *x2 + 1;
                    y_1 = *y1;
                }
                if (size > 3)
                {
                    x_2 = *x2 + 2;
                    y_2 = *y1;
                }
                if (size > 4)
                {
                    x_3 = *x2 + 3;
                    y_3 = *y1;
                }
            }
            if (*x1 < *x2)
            {
                if (size > 2)
                {
                    x_1 = *x1 + 1;
                    y_1 = *y1;
                }
                if (size > 3)
                {
                    x_2 = *x1 + 2;
                    y_2 = *y1;
                }
                if (size > 4)
                {
                    x_3 = *x1 + 3;
                    y_3 = *y1;
                }
            }
        }
        if (*x1 == *x2)
        {
            if (*y1 < *y2)
            {
                if (size > 2)
                {
                    x_1 = *x1;
                    y_1 = *y1 + 1;
                }
                if (size > 3)
                {
                    x_2 = *x1;
                    y_2 = *y1 + 2;
                }
                if (size > 4)
                {
                    x_3 = *x1;
                    y_3 = *y1 + 3;
                }
            }
            if (*y1 > *y2)
            {
                if (size > 2)
                {
                    x_1 = *x1;
                    y_1 = *y2 + 1;
                }
                if (size > 3)
                {
                    x_2 = *x1;
                    y_2 = *y2 + 2;
                }
                if (size > 4)
                {
                    x_3 = *x1;
                    y_3 = *y2 + 3;
                }
            }
        }
        if ((((board[*x1][*y1] > 'a') && (board[*x1][*y1] < 'z')) || ((board[*x2][*y2] > 'a') && (board[*x2][*y2] < 'z')) || (((board[x_1][y_1] > 'a') && (board[x_1][y_1] < 'z')) && (size > 2)) ||
            (((board[x_2][y_2] > 'a') && (board[x_2][y_2] < 'z')) && (size > 3)) || (((board[x_3][y_3] > 'a') && (board[x_3][y_3] < 'z') && (size > 4)))))
        {
            printf("Your ships cannot overlap!\n");
        }
    } while ((((board[*x1][*y1] > 'a') && (board[*x1][*y1] < 'z')) || ((board[*x2][*y2] > 'a') && (board[*x2][*y2] < 'z')) || (((board[x_1][y_1] > 'a') && (board[x_1][y_1] < 'z')) && (size > 2)) ||
        (((board[x_2][y_2] > 'a') && (board[x_2][y_2] < 'z')) && (size > 3)) || (((board[x_3][y_3] > 'a') && (board[x_3][y_3] < 'z') && (size > 4)))));
}
// This function randomly generates the endpoint coordinates (x1, y1, x2, y2) for each ship.   
void randomly_place_ships_on_board(int* x1, int* y1, int* x2, int* y2, int size, char board[10][10])
{
    int way = 0, x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0;
    do {
        *x1 = rand() % 10;
        *y1 = rand() % 10;
        way = rand() % 2;
        if (way == 0)
        {
            *x2 = *x1 - size + 1;
            *y2 = *y1;
            if (size > 2)
            {
                x_1 = *x2 + 1;
                y_1 = *y1;
            }
            if (size > 3)
            {
                x_2 = *x2 + 2;
                y_2 = *y1;
            }
            if (size > 4)
            {
                x_3 = *x2 + 3;
                y_3 = *y1;
            }
        }
        if (way == 1)
        {
            *y2 = *y1 - size + 1;
            *x2 = *x1;
            if (size > 2)
            {
                x_1 = *x1;
                y_1 = *y2 + 1;
            }
            if (size > 3)
            {
                x_2 = *x1;
                y_2 = *y2 + 2;
            }
            if (size > 4)
            {
                x_3 = *x1;
                y_3 = *y2 + 3;
            }
        }
    } while ((*x2 < 1) || (*y2 < 1) || (*x2 > 9) || (*y2 > 9) || ((board[*x1][*y1] > 'a') && (board[*x1][*y1] < 'z')) ||
        ((board[*x2][*y2] > 'a') && (board[*x2][*y2] < 'z')) || ((board[x_1][y_1] > 'a') && (board[x_1][y_1] < 'z')) ||
        ((board[x_2][y_2] > 'a') && (board[x_2][y_2] < 'z')) || ((board[x_3][y_3] > 'a') && (board[x_3][y_3] < 'z')));
}
//This function prompts the user to enter the target coordinates (xtarget, ytarget)      
void shoot_manual(int* xtar, int* ytar, char board[10][10])
{
    do {
        do {
            printf("Enter target coordinates: \n");
            scanf("%d %d", ytar, xtar);
            if ((*xtar > 9) || (*xtar < 0) || (*ytar > 9) || (*ytar < 0))
            {
                printf("Your target coordinates must be from 0-9!\n");
            }
        } while ((*xtar > 9) || (*xtar < 0) || (*ytar > 9) || (*ytar < 0));
        if ((board[*xtar][*ytar] == '*') || (board[*xtar][*ytar] == 'm'))
        {
            printf("You have already shot there! \n");
        }
    } while ((board[*xtar][*ytar] == '*') || (board[*xtar][*ytar] == 'm'));
}
void shoot_random(int* xtarget, int* ytarget, char board[10][10])
{
    do {
        *xtarget = rand() % 10;
        *ytarget = rand() % 10;
    } while ((board[*xtarget][*ytarget] == '*') || (board[*xtarget][*ytarget] == 'm'));
}
int check_ship(char board[10][10], int* sinkc, int* sinkb, int* sinkr, int* sinks, int* sinkd)
{
    int x = 0, y = 0, c = 0, b = 0, r = 0, s = 0, d = 0;
    for (x = 0; x < 10; x++)
    {
        for (y = 0; y < 10; y++)
        {
            if ((board[x][y] == 'c') && (*sinkc == 0))
            {
                c++;
            }
            if ((board[x][y] == 'b') && (*sinkb == 0))
            {
                b++;
            }
            if ((board[x][y] == 'r') && (*sinkr == 0))
            {
                r++;
            }
            if ((board[x][y] == 's') && (*sinks == 0))
            {
                s++;
            }
            if ((board[x][y] == 'd') && (*sinkd == 0))
            {
                d++;
            }
        }
    }
    if ((c == 0) && (*sinkc != -1))
    {
        printf("Sunk the Aircraft Carrier!\n");
        *sinkc = 1;
    }
    if ((b == 0) && (*sinkb != -1))
    {
        printf("Sunk the Battleship!\n");
        *sinkb = 1;
    }
    if ((r == 0) && (*sinkr != -1))
    {
        printf("Sunk the Cruiser!\n");
        *sinkr = 1;
    }
    if ((s == 0) && (*sinks != -1))
    {
        printf("Sunk the Submarine!\n");
        *sinks = 1;
    }
    if ((d == 0) && (*sinkd != -1))
    {
        printf("Sunk the Destroyer!\n");
        *sinkd = 1;
    }
}
//This function prints to file, the info associated with each player's shot: Target Coords - hit or miss, if a ship was sunk         
void output_move(FILE* outfile, int xtar, int ytar, int player, int hit, int* sinkc, int* sinkb, int* sinkr, int* sinks, int* sinkd)
{
    if ((xtar != -1) && (ytar != -1))
    {
        fprintf(outfile, "Player%d: (%d,%d)\t", player, xtar, ytar);
    }
    if (hit == 1)
    {
        fprintf(outfile, "Hit!\n");
    }
    if (hit == 0)
    {
        fprintf(outfile, "Miss...\n");
    }
    if (*sinkc == 1)
    {
        fprintf(outfile, "Sunk Aircraft Carrier!\n");
        *sinkc = -1;
    }
    if (*sinkb == 1)
    {
        fprintf(outfile, "Sunk Battleship!\n");
        *sinkb = -1;
    }
    if (*sinkr == 1)
    {
        fprintf(outfile, "Sunk Cruiser!\n");
        *sinkr = -1;
    }
    if (*sinks == 1)
    {
        fprintf(outfile, "Sunk Submarine!\n");
        *sinks = -1;
    }
    if (*sinkd == 1)
    {
        fprintf(outfile, "Sunk Destroyer!\n");
        *sinkd = -1;
    }
    fprintf(outfile, "\n");
}
//This function prints to file, the game stats for each player.(Hits, Misses, Shots, Accuracy)   
void output_stats(FILE* outfile, stats player)
{
    if (player.win == 1)
    {
        fprintf(outfile, "\nPlayer%d Wins!!\n", player.player_num);
    }
    if (player.win == 0)
    {
        fprintf(outfile, "\nPlayer%d Losses... \n", player.player_num);
    }
    fprintf(outfile, "\n***Player%d Stats***\nHits: %d\nMisses: %d\nTotal Shots: %d\nAccuracy: %.2lf%%\n\n",
        player.player_num, player.hits, player.misses, player.shots, player.accuracy);
}
