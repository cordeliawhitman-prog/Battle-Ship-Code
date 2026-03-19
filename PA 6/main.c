#include "Ship.h"

int main(void)
{
        int choice = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, deploy = 0, carrier = 5, battleship = 4, pointer = 3, submarine = 3, destroyer = 2, x = 0, y = 0,
            shots1 = 0, shots2 = 0, status = 0, player = 0, p1_hits = 0, p2_hits = 0, xtar = -1, ytar = -1,
            sunkc = 0, sunkb = 0, sunkr = 0, sunks = 0, sunkd = 0, num_miss1 = 0, num_miss1 = 0, hit1 = 0, hit2 = 0,
            c = 0, b = 0, r = 0, s = 0, d = 0;
        stats player_1, player_2;
        char player1[10][10], player2[10][10], visible[10][10], carr = 'c', battle = 'b', cruise = 'r', sub = 's', destroy = 'd',
            initial = '\0', type = '\0';
        double accuracy1 = 0.0, accuracy2 = 0.0;
        FILE* output_file = NULL;
        srand(time(NULL));
        output_file = fopen("Battleship.log", "w");
        //Game Play starts 
        welcome_screen();
        system("Pause");
        system("cls");
        deploy = deploy_ships();
        printf("\t **** Enemy's Board ****\n");
        randomly_place_ships_on_board(&x1, &y1, &x2, &y2, carrier, player2);
        player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 0, 2, xtar, ytar, &p2_hits, visible, carr);
        randomly_place_ships_on_board(&x1, &y1, &x2, &y2, battleship, player2);
        player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 0, 2, xtar, ytar, &p2_hits, visible, battle);
        randomly_place_ships_on_board(&x1, &y1, &x2, &y2, pointer, player2);
        player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 0, 2, xtar, ytar, &p2_hits, visible, cruise);
        randomly_place_ships_on_board(&x1, &y1, &x2, &y2, submarine, player2);
        player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 0, 2, xtar, ytar, &p2_hits, visible, sub);
        randomly_place_ships_on_board(&x1, &y1, &x2, &y2, destroyer, player2);
        player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p2_hits, visible, destroy);
        //Places Enemy's ships on his board
        printf("\n\t   **** Your Board ****\n");
        if (deploy == 1)
        {
            manually_place_ships_on_board(&x1, &y1, &x2, &y2, carrier, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p1_hits, visible, carr);
            manually_place_ships_on_board(&x1, &y1, &x2, &y2, battleship, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p1_hits, visible, battle);
            manually_place_ships_on_board(&x1, &y1, &x2, &y2, pointer, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p1_hits, visible, cruise);
            manually_place_ships_on_board(&x1, &y1, &x2, &y2, submarine, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p1_hits, visible, sub);
            manually_place_ships_on_board(&x1, &y1, &x2, &y2, destroyer, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p1_hits, visible, destroy);
        }//Manually places your ships on your board
        if (deploy == 2)
        {
            randomly_place_ships_on_board(&x1, &y1, &x2, &y2, carrier, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 0, 1, xtar, ytar, &p1_hits, visible, carr);
            randomly_place_ships_on_board(&x1, &y1, &x2, &y2, battleship, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 0, 1, xtar, ytar, &p1_hits, visible, battle);
            randomly_place_ships_on_board(&x1, &y1, &x2, &y2, pointer, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 0, 1, xtar, ytar, &p1_hits, visible, cruise);
            randomly_place_ships_on_board(&x1, &y1, &x2, &y2, submarine, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 0, 1, xtar, ytar, &p1_hits, visible, sub);
            randomly_place_ships_on_board(&x1, &y1, &x2, &y2, destroyer, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p1_hits, visible, destroy);
        }//Randomly places your ships on your board
        x1 = -1, y1 = -1, x2 = -1, y2 = -1;
        player = select_who_starts_first();
        system("Pause");
        if (player == 2)
        {
            shots2 = 1;
        }
        switch (player)//Runs game based on who goes first
        {//Player 1 
        case 1: do {
            xtar = -1, ytar = -1;
            system("cls");
            printf("\t **** Aponents's Board ****\n");
            initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p1_hits, visible, initial);
            printf("Hits: %d\tShots: %d\n", p2_hits, shots2);
            printf("\n\t   **** Your Board ****\n");
            initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p2_hits, visible, initial);
            printf("Hits: %d\tShots: %d\n", p1_hits, shots1);
            //Prints Boards

            shoot_manual(&xtar, &ytar, player2);
            shots1++;
            system("cls");
            printf("\t **** Aponents's Board ****\n");
            player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p1_hits, visible, initial);
            printf("Hits: %d\tShots: %d   Target(%d,%d)", p2_hits, shots2, ytar, xtar);
            if (player2[xtar][ytar] == '*')
            {
                printf("\tHit!\n");
                hit1 = 1;
            }
            if (player2[xtar][ytar] == 'm')
            {
                printf("\tMiss...\n");
                hit1 = 0;
            }
            check_ship(player2, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
            output_move(output_file, xtar, ytar, 1, hit1, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
            xtar = -1, ytar = -1;
            printf("\n\t   **** Your Board ****\n");
            initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p2_hits, visible, initial);
            printf("Hits: %d\tShots: %d\n", p1_hits, shots1);
            system("Pause");
            system("cls");
            //Player1 shot
            if (p1_hits < 17)
            {
                printf("\t **** Aponents's Board ****\n");
                xtar = -1, ytar = -1;
                initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p1_hits, visible, initial);
                printf("Hits: %d\tShots: %d\n", p2_hits, shots2);
                printf("\n\t   **** Your Board ****\n");
                shoot_random(&xtar, &ytar, player1);
                shots2++;
                player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p2_hits, visible, initial);
                printf("Hits: %d\tShots: %d   Target: (%d,%d)", p1_hits, shots1, ytar, xtar);
                if (player1[xtar][ytar] == '*')
                {
                    printf("\tHit!\n");
                    hit1 = 1;
                }
                if (player1[xtar][ytar] == 'm')
                {
                    printf("\tMiss...\n");
                    hit1 = 0;
                }
                check_ship(player1, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
                output_move(output_file, xtar, ytar, 2, hit1, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
            }
            system("Pause");
            system("cls");
            //Player2 shot
        } while ((p1_hits < 17) && (p2_hits < 17));
        break;
        //Player 2 goes first:
        case 2: do {
            xtar = -1, ytar = -1;
            system("cls");
            printf("\t **** Aponents's Board ****\n");
            initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p1_hits, visible, initial);
            printf("Hits: %d\tShots: %d\n", p2_hits, shots2);
            printf("\n\t   **** Your Board ****\n");
            initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p2_hits, visible, initial);
            printf("Hits: %d\tScore: %d\n", p1_hits, shots1);
            system("cls");
            //Prints Boards

            printf("\t **** Aponents's Board ****\n");
            initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p1_hits, visible, initial);
            printf("Hits: %d\tShots: %d\n", p2_hits, shots2);
            printf("\n\t   **** Your Board ****\n");
            shoot_random(&xtar, &ytar, player1);
            player1[10][10] = initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p2_hits, visible, initial);
            printf("Hits: %d\tShots: %d   Target: (%d,%d)", p1_hits, shots1, ytar, xtar);
            if (player1[xtar][ytar] == '*')
            {
                printf("\tHit!\n");
                hit1 = 1;
            }
            if (player1[xtar][ytar] == 'm')
            {
                printf("\tMiss...\n");
                hit1 = 0;
            }
            check_ship(player1, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
            output_move(output_file, xtar, ytar, 2, hit1, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
            //Player2 shot
            if (p2_hits < 17)
            {
                shoot_manual(&xtar, &ytar, player2);
                shots1++;
                system("cls");
                printf("\t **** Aponents's Board ****\n");
                player2[10][10] = initialize_game_board(x1, y1, x2, y2, player2, 1, 2, xtar, ytar, &p1_hits, visible, initial);
                printf("Hits: %d\tShots: %d   Target: (%d,%d)", p2_hits, shots2, ytar, xtar);
                if (player2[xtar][ytar] == '*')
                {
                    printf("\tHit!\n");
                    hit1 = 1;
                }
                if (player2[xtar][ytar] == 'm')
                {
                    printf("\tMiss...\n");
                    hit1 = 0;
                }
                check_ship(player2, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
                printf("\n\t **** Your Board ****\n");
                initialize_game_board(x1, y1, x2, y2, player1, 1, 1, xtar, ytar, &p2_hits, visible, initial);
                printf("Hits: %d\tShots: %d\n", p1_hits, shots1);
                output_move(output_file, xtar, ytar, 1, hit1, &sunkc, &sunkb, &sunkr, &sunks, &sunkd);
            }
            shots2++;
            system("Pause");
            system("cls");
            //Player1 shot
        } while ((p1_hits < 17) && (p2_hits < 17));
        break;
        }
        if (p1_hits == 17)
        {
            printf("\nPlayer1 Wins!!!\n\n");
            player_1.win = 1;
            player_2.win = 0;
        }
        if (p2_hits == 17)
        {
            printf("\nPlayer2 Wins!!!\n\n");
            player_1.win = 0;
            player_2.win = 1;
        }
        num_miss1 = shots1 - p1_hits;
        num_miss1 = shots2 - p2_hits;
        accuracy1 = 100 * ((double)p1_hits) / ((double)shots1);
        accuracy2 = 100 * ((double)p2_hits) / ((double)shots2);
        player_1.player_num = 1;
        player_1.hits = p1_hits;
        player_1.misses = num_miss1;
        player_1.shots = shots1;
        player_1.accuracy = accuracy1;

        player_2.player_num = 2;
        player_2.hits = p2_hits;
        player_2.misses = num_miss1;
        player_2.shots = shots2;
        player_2.accuracy = accuracy2;
        output_stats(output_file, player_1);
        output_stats(output_file, player_2);
        printf("***Player1 Stats***\nHits: %d\nMisses: %d\nShots: %d\nAccuracy: %.2lf%%\n\n", p1_hits, num_miss1, shots1, accuracy1);
        printf("***Player2 Stats***\nHits: %d\nMisses: %d\nShots: %d\nAccuracy: %.2lf%%\n\n", p2_hits, num_miss1, shots2, accuracy2);
        //Prints stats to screen and to file
        fclose(output_file);
        return 0;
    
}