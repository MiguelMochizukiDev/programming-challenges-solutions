"""
pc110108
uva10142
"""

import sys


def solve_case(names, ballots):
    n = len(names)
    eliminated = [False] * n

    while True:
        votes = [0] * n

        for ballot in ballots:
            for candidate in ballot:
                if not eliminated[candidate]:
                    votes[candidate] += 1
                    break

        active_votes = [votes[i] for i in range(n) if not eliminated[i]]
        max_votes = max(active_votes)
        min_votes = min(active_votes)

        if max_votes * 2 > len(ballots):
            return [names[i] for i in range(n) if not eliminated[i] and votes[i] == max_votes]

        if max_votes == min_votes:
            return [names[i] for i in range(n) if not eliminated[i]]

        for i in range(n):
            if not eliminated[i] and votes[i] == min_votes:
                eliminated[i] = True


def main():
    lines = sys.stdin.read().splitlines()
    idx = 0

    cases = int(lines[idx].strip())
    idx += 1

    outputs = []

    for _ in range(cases):
        while idx < len(lines) and lines[idx].strip() == '':
            idx += 1

        n = int(lines[idx].strip())
        idx += 1

        names = []
        for _ in range(n):
            names.append(lines[idx])
            idx += 1

        ballots = []
        while idx < len(lines) and lines[idx].strip() != '':
            ballots.append([int(x) - 1 for x in lines[idx].split()])
            idx += 1

        winners = solve_case(names, ballots)
        outputs.append('\n'.join(winners))

    sys.stdout.write('\n\n'.join(outputs) + '\n')


if __name__ == '__main__':
    main()
