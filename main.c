#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_JOBS 10
#define MAX_LEN 1000
#define MAX_KEYWORDS 10

// Job structure
struct Job {
    char title[100];
    char keywords[MAX_KEYWORDS][20];
    int relevanceScore;
    int effort; // Simulate effort or time required
};

// Sample jobs
struct Job jobs[MAX_JOBS] = {
    {"Java Developer Intern", {"java", "oop", "swing"}, 0, 3},
    {"Web Developer HTML CSS JS", {"html", "css", "javascript", "react"}, 0, 2},
    {"Data Analyst Intern", {"data", "analytics", "python", "excel"}, 0, 4},
    {"Embedded Systems Engineer", {"embedded", "c", "microcontroller"}, 0, 5},
    {"AI/ML Intern", {"ml", "machine", "learning", "ai"}, 0, 4},
    {"Cybersecurity Intern", {"cyber", "security", "network", "hacking"}, 0, 2},
    {"Android Developer Intern", {"android", "kotlin", "java"}, 0, 3},
    {"Frontend Developer React", {"react", "javascript", "frontend"}, 0, 2},
    {"Backend Developer NodeJS", {"node", "backend", "express"}, 0, 3},
    {"General Tech Intern", {"intern", "student", "learning"}, 0, 1}
};

// Convert string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// 0/1 Knapsack DP to select max relevance within max effort
int knapsack(int n, int W, int val[], int wt[], int selected[]) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = (val[i - 1] + dp[i - 1][w - wt[i - 1]] > dp[i - 1][w]) ?
                           (val[i - 1] + dp[i - 1][w - wt[i - 1]]) : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Backtrack to find selected jobs
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected[i - 1] = 1;
            w -= wt[i - 1];
        }
    }

    return dp[n][W];
}

int main() {
    char input[MAX_LEN];
    printf("Enter your resume summary:\n");
    fgets(input, MAX_LEN, stdin);
    toLowerCase(input);

    int relevance[MAX_JOBS];
    int effort[MAX_JOBS];
    int selected[MAX_JOBS] = {0};

    // Match keywords
    for (int i = 0; i < MAX_JOBS; i++) {
        jobs[i].relevanceScore = 0;
        for (int j = 0; j < MAX_KEYWORDS && strlen(jobs[i].keywords[j]) > 0; j++) {
            if (strstr(input, jobs[i].keywords[j])) {
                jobs[i].relevanceScore++;
            }
        }
        relevance[i] = jobs[i].relevanceScore;
        effort[i] = jobs[i].effort;
    }

    int maxEffort;
    printf("\nEnter your maximum effort level (1-10): ");
    scanf("%d", &maxEffort);

    int totalScore = knapsack(MAX_JOBS, maxEffort, relevance, effort, selected);

    printf("\nRecommended Jobs (Based on Relevance and Effort Limit):\n");
    int any = 0;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (selected[i]) {
            printf("- %s\n", jobs[i].title);
            any = 1;
        }
    }

    if (!any) {
        printf("No strong matches found. Here are some general roles you can consider:\n");
        printf("- Software Engineering Intern\n");
        printf("- General Tech Intern\n");
    }

    return 0;
}
