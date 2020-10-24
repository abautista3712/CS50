#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Cycle through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check to see if vote cast matches registered candidate
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Add 1 to candidate vote count
            candidates[i].votes++;
            printf("Successful vote for %s registered!\n", name);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0;
    // Cycle through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        string potentialWinners[candidate_count];
        if (max_votes < candidates[i].votes)
        {
            max_votes = candidates[i].votes;
        }
        if (i == candidate_count - 1)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (max_votes == candidates[j].votes)
                {
                    printf("%s\n", candidates[j].name);
                }
            }
        }
    }
    return;
}
