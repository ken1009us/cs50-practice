#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

//The number of voters who prefer candidate i over candidate j
int preferences[MAX][MAX];

// if locked[i][j] is true, which means that the existence of an edge pointing from candidate i to candidate j
bool locked[MAX][MAX];

// Each pair has winner and loser
typedef struct
{
    int winner;
    int loser;
}
pair;

string candidates[MAX];

pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i ++)
    {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            locked[i][j] = false;
        }
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i ++)
    {
        int ranks[candidate_count];
        for (int j = 0; j < candidate_count; j ++)
        {
            string name = get_string("rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

}

bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // ex: the rank 0 is i (candidate 0)
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// update the preferences 2D array, times of the rank[i] over rank[j]
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = i + 1; j < candidate_count; j ++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = i + 1; j < candidate_count; j ++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }
    }
    return;
}

void sort_pairs(void)
{
    for (int i = pair_count - 1; i >= 0; i --)
    {
        for (int j = 0; j < i - 1; j ++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

bool is_cycle(int endpoint, int startpoint)
{
    if (endpoint == startpoint)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i ++)
    {
        if(locked[endpoint][i])
        {
            if(locked[i][startpoint])
            {
                return true;
            }
        }
    }
    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i ++)
    {
        if (!is_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i ++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j ++)
        {
            if (locked[j][i] == false)
            {
                count ++;
                if (count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
