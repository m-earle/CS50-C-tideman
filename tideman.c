#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
//true represents the existence of an edge pointing from candidate i to candidate j
// false represents no edge pointing from candidate i to candidate j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
// array that will represent all the pairs of candidates (for which one is perferred over the other) in the election
pair pairs[MAX * (MAX - 1) / 2];

int pair_count; //number of pairs in array pairs
int candidate_count; //number of candidates in array candidates

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false; //initialze so that there are no edges
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks); //take ranks from voter and update global preferences varianble

        printf("\n");
    }

    add_pairs(); //pairs of candidates are added to the pairs array via a call to sort pairs and locked into the graph via lock_pairs
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) //takes arguments rank name and ranks
{
    // TODO
    for (int i = 0; i < candidate_count; i ++) //loop through the candidates name
    {
        if (strcmp(candidates[i], name) == 0) //if name matches the person in the first candidate list spot
        {
            ranks[rank] = i; //fill in the rank position rank with the candidate index
            return true;
            return 0; //then stop looping
        }
    }
    //printf("%i \n", ranks[1]);
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i ++) //loop through all the votes
    {
        for (int j = candidate_count; j > i; j --) //loop downward from candidate_count to i
        {
            preferences[ranks[i]][ranks[j]] ++; //add 1 to this comparison
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i ++) //loop through all the votes
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
        }
    }
    //printf("%i \n", preferences[0][1]);
    //printf("%i %i \n", pairs[0].winner, pairs[0].loser);
    //printf("%i \n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i ++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            int swapwin = pairs[i].winner;
            int swaplos = pairs[i].loser;
            pairs[i].winner = pairs[i + 1].winner;
            pairs[i].loser = pairs[i + 1].loser;
            pairs[i + 1].winner = swapwin;
            pairs[i + 1].loser = swaplos;
        }
    }
    //printf("%i %i \n", pairs[1].winner, pairs[1].loser);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i ++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int wincount = 0;
    for (int j = 0; j < candidate_count; j ++)
    {
        for (int i = 0; i < candidate_count; i ++)
        {
            if (locked[i][j] == false)
            {
                wincount ++;
            }
        }
        if (wincount == candidate_count)
        {
            printf("%s \n", candidates[j]);
        }
    }
    return;
}

