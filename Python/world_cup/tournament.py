# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # create a list for storing the team
    teams = []

    with open(sys.argv[1], "r") as file:
        # loop over to read the file one row at a time,
        # traeting each row as a dictionary
        data = csv.DictReader(file)

        # append data to list
        for row in data:
            teams.append(row)

    # convert the team’s rating to an int
    for i in range(len(teams)):
        teams[i]["rating"] = int(teams[i]["rating"])

    # create a dictionary for storing the winning times of each teams
    counts = {}

    for i in range(0, N, 1):
        final_team = simulate_tournament(teams)
        if final_team in counts:
            counts[final_team] += 1
        else:
            counts[final_team] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """accept as input a list of teams and repeatedly simulate rounds,
       until left with one team."""
    winners = simulate_round(teams)

    if len(winners) % 2 == 0:
        return(simulate_tournament(winners))

    else:
        winner = winners[0]["team"]
        return winner


if __name__ == "__main__":
    main()
