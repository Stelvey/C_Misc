#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
char candidates[50][MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int found_index(int start);
bool cycle_check(int start_candidate, int end_candidate);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i], argv[i + 1]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    printf("Number of voters: ");
    int voter_count;
    scanf("%i", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %i: ", j + 1);
            char name[50];
            scanf("%s", name);

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
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char name[], int ranks[])
{
    // TODO
    for (int i = 0; i != candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i != candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i != candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp;
    int strongest;

    for (int i = 0; i != pair_count; i++)
    {
        strongest = found_index(i);

        temp.winner = pairs[i].winner;
        temp.loser = pairs[i].loser;
        pairs[i].winner = pairs[strongest].winner;
        pairs[i].loser = pairs[strongest].loser;
        pairs[strongest].winner = temp.winner;
        pairs[strongest].loser = temp.loser;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i != pair_count; i++)
    {
        if (!cycle_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int loss;

    for (int i = 0; i != candidate_count; i++)
    {
        loss = 0;

        for (int j = 0; j != candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                loss++;
            }
        }

        if (loss == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}




// Linear search: Find an index of a pair with the strongest winner
int found_index(int start)
{
    int strength;
    int highest = 0;
    int found;

    for (int i = start; i != pair_count; i++)
    {
        strength = preferences[pairs[i].winner][pairs[i].loser];

        if (strength > highest)
        {
            highest = strength;
            found = i;
        }
    }
    return found;
}

// Check a candidate for cycles
bool cycle_check(int start_candidate, int end_candidate)
{
    for (int i = 0; i != candidate_count; i++)
    {
        if (locked[start_candidate][i] == true)
        {
            if (i == end_candidate)
            {
                return true;
            }
            else if (cycle_check(i, end_candidate))
            {
                return true;
            }
        }
    }
    return false;
}