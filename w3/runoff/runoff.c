#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of vonters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    printf("Validating vote...\n");
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    printf("---New Round---\n");
    printf("Tabulating...\n");
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        while (candidates[preferences[i][j]].eliminated == true)
        {
            printf("/%s is eliminated: looking at second option", candidates[preferences[i][j]].name);
            j++;
        }
        candidates[preferences[i][j]].votes++;
        printf("/%s Votes AFTER Elimination Round = %i\n", candidates[preferences[i][j]].name, candidates[preferences[i][j]].votes);
        j = 0;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    printf("Printing winner...\n");
    int total_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        total_votes += candidates[i].votes;
        if (i == candidate_count - 1)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (candidates[j].votes > (total_votes / 2))
                {
                    printf("%s\n", candidates[j].name);
                    return true;
                }
            }
        }
    }
    printf("/No winner\n");
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    printf("Finding min...\n");
    int min_votes = 0;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            while (candidates[preferences[i][j]].eliminated)
            {
                j++;
            }
            min_votes = candidates[preferences[i][j]].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        while (candidates[i].eliminated)
        {
            i++;
        }
        if (candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
            printf("/min = %i\n", min_votes);
        }
    }
    printf("/min = %i\n", min_votes);
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    printf("Calculating if all are tied...\n");
    int candidates_not_eliminated = 0;
    int candidates_tied = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            candidates_not_eliminated++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates_tied++;
        }
        if (candidates_tied == candidates_not_eliminated)
        {
            printf("ALL CANDIDATES ARE TIED\n");
            return true;
        }
    }
    printf("/No ties found\n");
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    printf("Eliminating...\n");
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            printf("Eliminated %s\n", candidates[i].name);
        }
    }
    printf("/No further eliminations\n");
    printf("///End of round///\n");
    return;
}
