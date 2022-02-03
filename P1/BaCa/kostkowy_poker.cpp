// Jakub Lukasiewicz

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int n;
    cin >> n;
    int i, j;

    char player_1, player_2;

    bool player_1_win, player_2_win, draw, player_1_loss, player_2_loss;

    int wins_a = 0, wins_b = 0, wins_c = 0, wins_d = 0, wins_e = 0;
    int draws_a = 0, draws_b = 0, draws_c = 0, draws_d = 0, draws_e = 0;
    int loses_a = 0, loses_b = 0, loses_c = 0, loses_d = 0, loses_e = 0;

    int matches_a, matches_b, matches_c, matches_d, matches_e;

    int dice_1_0, dice_2_0;
    char dice_1_1, dice_1_2, dice_1_3, dice_1_4, dice_2_1, dice_2_2, dice_2_3, dice_2_4;
    char* dice_1 = (char*)&dice_1_0, *dice_2 = (char*)&dice_2_0;

    short hierarchy_1, hierarchy_2;

    short pair_1, pair_2;
    short sum_1, sum_2;

    char temp;

    while (n > 0) {
        player_1_win = player_2_win = 0;
        draw = 0;
        player_1_loss = player_2_loss = 0;

        pair_1 = pair_2 = 0;
        sum_1 = sum_2 = 0;

        cin >> player_1 >> *(dice_1 + 0) >> *(dice_1 + 1) >> *(dice_1 + 2) >> *(dice_1 + 3);
        cin >> player_2 >> *(dice_2 + 0) >> *(dice_2 + 1) >> *(dice_2 + 2) >> *(dice_2 + 3);

        i = 0;
        while (i < 3) {
            j = 0;
            while (j < 3) {
                if ( *(dice_1 + j) > *(dice_1 + j + 1) ) {
                    temp = *(dice_1 + j);
                    *(dice_1 + j) = *(dice_1 + j + 1);
                    *(dice_1 + j + 1) = temp;
                }
                if ( *(dice_2 + j) > *(dice_2 + j + 1) ) {
                    temp = *(dice_2 + j);
                    *(dice_2 + j) = *(dice_2 + j + 1);
                    *(dice_2 + j + 1) = temp;
                }
                ++j;
            }
            ++i;
        }

        sum_1 += dice_1_1 = *(dice_1 + 0);
        sum_1 += dice_1_2 = *(dice_1 + 1);
        sum_1 += dice_1_3 = *(dice_1 + 2);
        sum_1 += dice_1_4 = *(dice_1 + 3);
        sum_2 += dice_2_1 = *(dice_2 + 0);
        sum_2 += dice_2_2 = *(dice_2 + 1);
        sum_2 += dice_2_3 = *(dice_2 + 2);
        sum_2 += dice_2_4 = *(dice_2 + 3);

        if (dice_1_1 == dice_1_4) {
            hierarchy_1 = 1;
        }
        else if (dice_1_1 < dice_1_2 && dice_1_2 < dice_1_3 && dice_1_3 < dice_1_4) {
            hierarchy_1 = 2;
        }
        else if (dice_1_1 == dice_1_2 && dice_1_2 != dice_1_3 && dice_1_3 == dice_1_4) {
            hierarchy_1 = 3;
        }
        else if (dice_1_1 == dice_1_2 && dice_1_2 == dice_1_3) {
            hierarchy_1 = 4;
        }
        else if (dice_1_2 == dice_1_3 && dice_1_3 == dice_1_4) {
            hierarchy_1 = 4;
        }
        else if (dice_1_1 == dice_1_2) {
            hierarchy_1 = 5;
            pair_1 = 1;
        }
        else if (dice_1_2 == dice_1_3) {
            hierarchy_1 = 5;
            pair_1 = 2;
        }
        else if ( dice_1_3 == dice_1_4) {
            hierarchy_1 = 5;
            pair_1 = 3;
        }

        if (dice_2_1 == dice_2_4) {
            hierarchy_2 = 1;
        }
        else if (dice_2_1 < dice_2_2 && dice_2_2 < dice_2_3 && dice_2_3 < dice_2_4) {
            hierarchy_2 = 2;
        }
        else if (dice_2_1 == dice_2_2 && dice_2_2 != dice_2_3 && dice_2_3 == dice_2_4) {
            hierarchy_2 = 3;
        }
        else if (dice_2_1 == dice_2_2 && dice_2_2 == dice_2_3) {
            hierarchy_2 = 4;
        }
        else if (dice_2_2 == dice_2_3 && dice_2_3 == dice_2_4) {
            hierarchy_2 = 4;
        }
        else if (dice_2_1 == dice_2_2) {
            hierarchy_2 = 5;
            pair_2 = 1;
        }
        else if (dice_2_2 == dice_2_3) {
            hierarchy_2 = 5;
            pair_2 = 2;
        }
        else if ( dice_2_3 == dice_2_4) {
            hierarchy_2 = 5;
            pair_2 = 3;
        }

        if (hierarchy_1 < hierarchy_2) {
            player_1_win = 1;
        }
        else if (hierarchy_1 > hierarchy_2) {
            player_2_win = 1;
        }
        else if (hierarchy_1 == hierarchy_2 && (hierarchy_1 == 1 || hierarchy_1 == 2)) {
            if (dice_1_1 > dice_2_1) {
                player_1_win = 1;
            }
            else if ( dice_1_1 < dice_2_1) {
                player_2_win = 1;
            }
            else {
                draw = 1;
            }
        }
        else if (hierarchy_1 == hierarchy_2) {
            if (hierarchy_1 == 3) {
                if (dice_1_4 == dice_2_4) {
                    if (sum_1 == sum_2) {
                        draw = 1;
                    }
                    else if (sum_1 > sum_2) {
                        player_1_win = 1;
                    }
                    else {
                        player_2_win = 1;
                    }
                }
                else if (dice_1_4 > dice_2_4) {
                    player_1_win = 1;
                }
                else {
                    player_2_win = 1;
                }
            }
            else if (hierarchy_1 == 4) {
                if (dice_1_2 == dice_2_2) {
                    if (sum_1 == sum_2) {
                        draw = 1;
                    }
                    else if (sum_1 > sum_2) {
                        player_1_win = 1;
                    }
                    else {
                        player_2_win = 1;
                    }
                }
                else if (dice_1_2 > dice_2_2) {
                    player_1_win = 1;
                }
                else {
                    player_2_win = 1;
                }
            }
            else if (hierarchy_1 == 5) {
                if (*(dice_1 + pair_1) == *(dice_2 + pair_2)) {
                    if (sum_1 == sum_2) {
                        draw = 1;
                    }
                    else if (sum_1 > sum_2) {
                        player_1_win = 1;
                    }
                    else {
                        player_2_win = 1;
                    }
                }
                else if (*(dice_1 + pair_1) > *(dice_2 + pair_2)) {
                    player_1_win = 1;
                }
                else {
                    player_2_win = 1;
                }
            }
        }

        player_1_loss = player_2_win;
        player_2_loss = player_1_win;

        if (player_1 == 'a') {
            wins_a += player_1_win;
            loses_a += player_1_loss;
            draws_a += draw;
        }
        else if (player_1 == 'b') {
            wins_b += player_1_win;
            loses_b += player_1_loss;
            draws_b += draw;
        }
        else if (player_1 == 'c') {
            wins_c += player_1_win;
            loses_c += player_1_loss;
            draws_c += draw;
        }
        else if (player_1 == 'd') {
            wins_d += player_1_win;
            loses_d += player_1_loss;
            draws_d += draw;
        }
        else {
            wins_e += player_1_win;
            loses_e += player_1_loss;
            draws_e += draw;
        }

        if (player_2 == 'a') {
            wins_a += player_2_win;
            loses_a += player_2_loss;
            draws_a += draw;
        }
        else if (player_2 == 'b') {
            wins_b += player_2_win;
            loses_b += player_2_loss;
            draws_b += draw;
        }
        else if (player_2 == 'c') {
            wins_c += player_2_win;
            loses_c += player_2_loss;
            draws_c += draw;
        }
        else if (player_2 == 'd') {
            wins_d += player_2_win;
            loses_d += player_2_loss;
            draws_d += draw;
        }
        else {
            wins_e += player_2_win;
            loses_e += player_2_loss;
            draws_e += draw;
        }

        n--;
    }

    matches_a = wins_a + draws_a + loses_a;
    matches_b = wins_b + draws_b + loses_b;
    matches_c = wins_c + draws_c + loses_c;
    matches_d = wins_d + draws_d + loses_d;
    matches_e = wins_e + draws_e + loses_e;

    if (matches_a) {
        cout << "gracz a" << endl;
        if (wins_a) {
            cout << "    wygrane: " << (float)wins_a / matches_a * 100 << "%" << endl;
        }
        if (draws_a) {
            cout << "    remisy: " << (float)draws_a / matches_a * 100 << "%" << endl;
        }
        if (loses_a) {
            cout << "    przegrane: " << (float)loses_a / matches_a * 100  << "%" << endl;
        }
        cout << endl;
    }
    if (matches_b) {
        cout << "gracz b" << endl;
        if (wins_b) {
            cout << "    wygrane: " << (float)wins_b / matches_b * 100 << "%" << endl;
        }
        if (draws_b) {
            cout << "    remisy: " << (float)draws_b / matches_b * 100 << "%" << endl;
        }
        if (loses_b) {
            cout << "    przegrane: " << (float)loses_b / matches_b * 100  << "%" << endl;
        }
        cout << endl;
    }
    if (matches_c) {
        cout << "gracz c" << endl;
        if (wins_c) {
            cout << "    wygrane: " << (float)wins_c / matches_c * 100 << "%" << endl;
        }
        if (draws_c) {
            cout << "    remisy: " << (float)draws_c / matches_c * 100 << "%" << endl;
        }
        if (loses_c) {
            cout << "    przegrane: " << (float)loses_c / matches_c * 100  << "%" << endl;
        }
        cout << endl;
    }
    if (matches_d) {
        cout << "gracz d" << endl;
        if (wins_d) {
            cout << "    wygrane: " << (float)wins_d / matches_d * 100 << "%" << endl;
        }
        if (draws_d) {
            cout << "    remisy: " << (float)draws_d / matches_d * 100 << "%" << endl;
        }
        if (loses_d) {
            cout << "    przegrane: " << (float)loses_d / matches_d * 100  << "%" << endl;
        }
        cout << endl;
    }
    if (matches_e) {
        cout << "gracz e" << endl;
        if (wins_e) {
            cout << "    wygrane: " << (float)wins_e / matches_e * 100 << "%" << endl;
        }
        if (draws_e) {
            cout << "    remisy: " << (float)draws_e / matches_e * 100 << "%" << endl;
        }
        if (loses_e) {
            cout << "    przegrane: " << (float)loses_e / matches_e * 100  << "%" << endl;
        }
        cout << endl;
    }

    return 0;
}

// vim: fen
