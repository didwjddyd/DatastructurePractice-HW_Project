#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include <ncurses.h>

#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSG_TURNEND_SIZE (sizeof(MsgTurnEnd) - sizeof(long))

using namespace std;

// struct for message queue
struct __TurnEnd {
    int rank;
    int score;
};
typedef struct __TurnEnd TurnEnd;

struct __MsgTurnEnd {
    long mtype;
    struct __TurnEnd turnEnd;
};
typedef struct __MsgTurnEnd MsgTurnEnd;

// global variable for message queue
MsgTurnEnd msgTurnEnd_send;
MsgTurnEnd msgTurnEnd_receive;
int priority; // order to play
key_t mykey = 0;
int msqid = 0;

// global const variable for ncurses
const int PLAYER = 15;
const int OPPONENT = 25;
const vector<int> RANK_LINES = {3, 5, 7, 9, 11, 13, 17, 19, 22, 25, 28, 31, 33};

// struct for yacht
struct ScoreBoard {
    const string ranks[14] = {"Aces",           "Twos",           "Threes",
                              "Fours",          "Fives",          "Sixes",
                              "Choice",         "Four of a Kind", "Full House",
                              "Small Straight", "Large Straight", "Yacht",
                              "Discard"};

    vector<int> scores = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    int grandScore = 0;
};

// functions for ncurses
void initScreen();
void makeScoreBoard(WINDOW *scoreBoard);
void clearLine(int x, int y);
void clearLines(int x1, int x2);

// functions for yacht
void ShowDice(vector<int> dices);
int PlayerChoice();
void ThrowDice(ScoreBoard *Player);
void ReRoll(vector<int> &dices);
void Record(vector<int> dices, ScoreBoard *player);
vector<vector<int>> CheckDice(vector<int> dices);
void ShowScore(ScoreBoard &player, const int x);
int Discard(ScoreBoard player);

int main() {
    // variable for ncurses
    WINDOW *scoreBoard, *rounds, *rollDice, *textMessage;

    // varivable for yacht
    ScoreBoard player;
    ScoreBoard opponent;
    int turn = 1;

    // set message queue
    mykey = ftok("mymsgkey", 'P');
    if (msgget(mykey, 0 | 0666) == -1) {
        msqid = msgget(mykey, IPC_CREAT | 0666);
        priority = 1;
    } else {
        msqid = msgget(mykey, IPC_CREAT | 0666);
        priority = 2;
    }

    // set random
    srand(time(NULL));

    // Initialize Main Screen
    initScreen();
    bkgd(COLOR_PAIR(1)); // COLOR_BLACK
    scoreBoard = subwin(stdscr, 36, 32, 0, 0);
    makeScoreBoard(scoreBoard);

    rounds = subwin(stdscr, 5, 33, 0, 34);
    rollDice = subwin(stdscr, 5, 33, 7, 34);
    box(rounds, 0, 0);
    box(rollDice, 0, 0);
    refresh();

    while (turn <= 12) {
        mvprintw(1, 46, "Turn %d", turn);
        mvprintw(2, 46, "Priority: %d", priority);
        mvprintw(3, 46, "Player  ");

        ThrowDice(&player);

        ShowScore(player, PLAYER);

        mvprintw(3, 46, "Opponent");
        refresh();

        if (priority == 1) {
            memset(&msgTurnEnd_receive, 0x00, sizeof(MsgTurnEnd));
            msgrcv(msqid, &msgTurnEnd_receive, MSG_TURNEND_SIZE, 2, 0);
        } else {
            memset(&msgTurnEnd_receive, 0x00, sizeof(MsgTurnEnd));
            msgrcv(msqid, &msgTurnEnd_receive, MSG_TURNEND_SIZE, 1, 0);
        }

        opponent.scores[msgTurnEnd_receive.turnEnd.rank] =
            msgTurnEnd_receive.turnEnd.score;

        ShowScore(opponent, OPPONENT);

        turn++;
        refresh();
    }

    clearLines(12, 25);

    if (player.grandScore > opponent.grandScore) {
        mvprintw(14, 35, "WIN!");

    } else if (player.grandScore == opponent.grandScore) {
        mvprintw(14, 35, "DRAW!");

    } else {
        mvprintw(14, 35, "LOSE!");
    }

    refresh();

    if (priority == 1) {
        msgctl(msqid, IPC_RMID, NULL);
    }
    getchar();
    endwin();
}

// ncurses function implementation
void initScreen() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
}

void makeScoreBoard(WINDOW *scoreBoard) {
    mvprintw(1, 12, "Player");
    mvprintw(1, 22, "Opponent");

    mvprintw(3, 2, "Aces");
    mvprintw(5, 2, "Twos");
    mvprintw(7, 2, "Threes");
    mvprintw(9, 2, "Fours");
    mvprintw(11, 2, "Fives");
    mvprintw(13, 2, "Sixes");
    mvprintw(17, 2, "Choice");
    mvprintw(19, 2, "4 of a\n  kind");
    mvprintw(22, 2, "Full\n  House");
    mvprintw(25, 2, "Small\n  Straight");
    mvprintw(28, 2, "Large\n  Straight");
    mvprintw(31, 2, "Yacht");
    mvprintw(33, 2, "Grand\n  total");

    for (vector<int>::const_iterator i = RANK_LINES.begin();
         i != RANK_LINES.end(); ++i) {
        mvprintw(*i, PLAYER, "0");
        mvprintw(*i, OPPONENT, "0");
    }

    box(scoreBoard, 0, 0);
}

void clearLine(int x, int y) {
    move(x, y);
    clrtoeol();
}

void clearLines(int x1, int x2) {
    for (int i = x1; i <= x2; ++i) {
        clearLine(i, 35);
    }
}

// yacht function implementation
void ShowDice(vector<int> dices) {
    int col1 = 8;
    int col2 = 10;
    int row = 36;

    for (int index = 0; index < dices.size(); ++index) {
        mvprintw(col1, row, "  ");
        printw("%d", index + 1);
        printf("  ");

        mvprintw(col2, row, "[ ");
        printw("%d", dices[index]);
        printw(" ]");

        row += 6;
    }
}

void ThrowDice(ScoreBoard *player) {
    vector<int> dices = {0, 0, 0, 0, 0};
    int count = 0;
    char key;

    for (int diceNumber = 0; diceNumber != 5; ++diceNumber) {
        dices[diceNumber] = rand() % 6 + 1;
    }

    for (int count = 0; count != 2; ++count) {
        ShowDice(dices);

        mvprintw(12, 35, "You Can ReRoll ");
        printw("%d", 2 - count);
        printw(" Times.");

        mvprintw(13, 35, "Press 'r' to reroll, 's' to record to scoreboard. ");
        clearLine(14, 35);

        key = getch();

        if (key == 'r') {
            clearLines(12, 15);
            ReRoll(dices);
        } else if (key == 's') {
            clearLines(12, 15);
            Record(dices, player);
            clearLines(12, 25);
            return;
        } else {
            mvprintw(14, 35, "Wrong input. Please Input Correctly.");
            count--;
        }
    }
    ShowDice(dices);
    clearLines(12, 22);
    Record(dices, player);
    clearLines(12, 25);

    refresh();
}

void ReRoll(vector<int> &dices) {
    int num;

    mvprintw(12, 35, "REROLL");
    mvprintw(13, 35, "Enter number of dice to roll again: ");
    scanw("%d", &num);

    if (num == 5) {
        for (int i = 0; i != 5; ++i) {
            dices[i] = rand() % 6 + 1;
        }
    } else {
        clearLine(14, 35);
        mvprintw(14, 35, "Enter dice number to roll again.");
        for (int i = 0; i != num; ++i) {
            int temp;
            mvprintw(15 + i, 35, "input dice number: ");
            scanw("%d", &temp);
            dices[temp - 1] = rand() % 6 + 1;
        }
    }

    clearLines(12, 22);
}

void Record(vector<int> dices, ScoreBoard *player) {
    vector<vector<int>> rankpairs = CheckDice(dices);
    int num, index;

    mvprintw(12, 35, "SET SCORE");

    for (index = 0; index != rankpairs.size(); ++index) {
        if (player->scores[rankpairs[index][0]] <= 0) {
            mvprintw(13 + index, 35, "%d. %s", index + 1,
                     player->ranks[rankpairs[index][0]].c_str());
        }
    }
    while (1) {
        mvprintw(13 + index + 1, 35, "Enter number: ");
        scanw("%d", &num);
        if (num <= 0 || num > rankpairs.size()) {
            clearLine(13 + index + 2, 35);
            mvprintw(13 + index + 2, 35, "Please Enter Correct Number.");
        } else if (num == 1) {
            clearLines(12, 16 + index + 2);
            int discardNum = Discard(*player);
            player->scores[discardNum] = 0;

            // send message to opponent
            memset(&msgTurnEnd_send, 0x00, sizeof(MsgTurnEnd));

            msgTurnEnd_send.mtype = priority;
            msgTurnEnd_send.turnEnd.rank = discardNum;
            msgTurnEnd_send.turnEnd.score = 0;

            msgsnd(msqid, &msgTurnEnd_send, MSG_TURNEND_SIZE, 0);

            return;
        } else {
            clearLine(13 + index + 2, 35);
            mvprintw(13 + index + 2, 35, "RECORDING");
            player->scores[rankpairs[num - 1][0]] = rankpairs[num - 1][1];

            // send message to opponent
            memset(&msgTurnEnd_send, 0x00, sizeof(MsgTurnEnd));

            msgTurnEnd_send.mtype = priority;
            msgTurnEnd_send.turnEnd.rank = rankpairs[num - 1][0];
            msgTurnEnd_send.turnEnd.score = rankpairs[num - 1][1];

            msgsnd(msqid, &msgTurnEnd_send, MSG_TURNEND_SIZE, 0);

            return;
        }
    }
}

//  return pair of rank and score.
vector<vector<int>> CheckDice(vector<int> dices) {
    vector<vector<int>> rankpairs; //  Discard
    vector<int> diceNumbers = {0, 0, 0, 0, 0, 0};
    int choiceSum = 0;
    int counter = 0, straightCounter = 1;
    int tripleNumber, doubleNumber;

    rankpairs.push_back({12, 0});
    sort(dices.begin(), dices.end());
    for (vector<int>::const_iterator iter = dices.begin(); iter != dices.end();
         ++iter) {
        diceNumbers[(*iter) - 1]++;

        if (*iter + 1 == *(iter + 1)) {
            straightCounter++;
        }
    }
    for (int i = 0; i != 6; ++i) {
        choiceSum += diceNumbers[i] * (i + 1);
    }
    rankpairs.push_back({6, choiceSum}); //  Choice
    for (int index = 0; index != diceNumbers.size(); ++index) {
        if (diceNumbers[index] >= 1) {
            //  Aces, Deuces, Threes, Fours, Fives, Sixes
            rankpairs.push_back({index, (index + 1) * diceNumbers[index]});
            switch (diceNumbers[index]) {
            case 2:
                doubleNumber = index;
                counter++;
                break;
            case 3:
                tripleNumber = index;
                counter++;
                break;
            case 4:
                rankpairs.push_back({7, index * 4}); //  Four of a kind
                break;
            case 5:
                rankpairs.push_back({11, 50}); //  Yacht
                break;
            }
        }
    }
    if (counter == 2) {
        int fhSum = (doubleNumber + 1) * diceNumbers[doubleNumber] +
                    (tripleNumber + 1) * diceNumbers[tripleNumber];

        rankpairs.push_back({8, fhSum}); //  Full House
    }
    if (straightCounter == 4) {
        rankpairs.push_back({9, 15}); //  Small Straight
    }
    if (straightCounter == 5) {
        rankpairs.push_back({10, 30}); //  Large Straight
    }
    return rankpairs;
}

void ShowScore(ScoreBoard &player, const int x) {
    int sum = 0;

    for (int index = 0; index != 12; ++index) {
        switch (player.scores[index]) {
        case -1:
            sum += player.scores[index] + 1;
            mvprintw(RANK_LINES[index], x, "%d", player.scores[index] + 1);
            break;
        case 0:
            sum += player.scores[index];
            mvprintw(RANK_LINES[index], x, "DIS");
            break;
        default:
            sum += player.scores[index];
            mvprintw(RANK_LINES[index], x, "%d", player.scores[index]);
            break;
        }
    }
    mvprintw(*(RANK_LINES.end() - 1), x, "%d", sum);
    player.grandScore = sum;
    refresh();
}

int Discard(ScoreBoard player) {
    int num, index;

    mvprintw(12, 35, "DISCARD");
    for (index = 0; index != 12; ++index) {
        if (player.scores[index] < 0) {
            mvprintw(13 + index, 35, "%d. %s", index + 1,
                     player.ranks[index].c_str());
        }
    }
    do {
        clearLine(13 + index + 1, 35);
        mvprintw(13 + index + 1, 35, "Enter number to discard: ");
        scanw("%d", &num);
    } while (num <= 0 || num > 12);

    clearLines(12, 13 + index + 1);

    return num - 1;
}
