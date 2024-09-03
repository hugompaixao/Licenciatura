#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>

const int max_players = 10000;

// Used Functions

const char *str_dup(const char *str) {
	char *result = (char *) malloc(strlen(str) + 1);
	strcpy(result, str);
	return result;
}

// INTERNACIONALIZACOES = intern;
typedef struct {
  int internationalizations;
  const char *name;
  const char *position;
  int goals;
  int year_birth;
  const char *team;
} Player;

Player players(int internationalizations, const char *name, const char *position, int goals, int year_birth, const char *team) {
  Player result;
  result.internationalizations = internationalizations;
  result.name = name;
  result.position = position;
  result.goals = goals;
  result.year_birth = year_birth;
  result.team = team;
  return result;
} 

int players_read(FILE *f, Player *player) {
  int result = 0;
  int internationalizations;
  char name[max_players];
  char position[max_players];
  int goals;
  int year_birth;
  char team[max_players];
  while(fscanf(f, "%d%s%s%d%d%s", &internationalizations, name, position, &goals, &year_birth, team) != EOF)
    player[result++] = players(internationalizations, str_dup(name), str_dup(position), goals, year_birth, str_dup(team));
  return result;
}

//--------------------------------------------------------------------- A

void players_write(FILE *f, Player *player, int length) {
  for(int i = 0; i < length; i++) {
    printf("[%d][%s][%s][%d][%d][%s]\n", player[i].internationalizations, player[i].name, player[i].position, player[i].goals, player[i].year_birth, player[i].team);
  }
}

void test_players_read_write(const char *filename) {
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  // n_players = length
  int n_players = players_read(f, players);
  players_write(stdout, players, n_players);
}

//----------------------------------------------------------------------- B

int group_players_by_team(Player *players, int length, char *str, int *idx) {
  int i = 0, result = 0;
  while(i < length) {
    if(strcmp(players[i].team, str) == 0)
      idx[result++] = i;
    i++;
  }
  return result;
}

void players_from_club(const char *filename) {
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  int length = players_read(f, players);
  char team[max_players];
  int idx[max_players];
  while(scanf("%s", team) != EOF) {
    int number_players = group_players_by_team(players, length, team, idx);
    if(number_players == 0)
      printf("(void)\n");
    else
      for(int i = 0; i < number_players; i++) 
        printf("%s %d\n", players[idx[i]].name, players[idx[i]].internationalizations);
  }
}

//--------------------------------------------------------------------- C

typedef struct {
  const char *team;
  int internationalizations;
} TeamsContribution;

TeamsContribution team_contribution(const char * team, int internationalizations) {
  TeamsContribution result;
  result.team = team;
  result.internationalizations = internationalizations;
  return result; 
}

void Player_exchange(Player *players, int i, int j) {
  Player team = players[i];
  players[i] = players[j];
  players[j] = team;
}

void sort_players_by_team(Player *players, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && strcmp(players[j-1].team, players[j].team) > 0) {
      Player_exchange(players, j-1, j);
      j--;
    }
  }
}

int team_count_while(Player *players, int length, const char *team) {
  int result = 0;
  while(result < length && strcmp(players[result].team, team) == 0)
    result++;
  return result;
}

int count_internationalizations_by_team(Player *players, int length, const char *team) {
  int result = 0, i = 0;
  while(i < length && strcmp(players[i].team, team) == 0) {
    result += players[i].internationalizations;
    i++;
  }
  return result;
}

int fill_TeamsContribution(Player *players, int length, TeamsContribution *team_contribution) {
  int result = 0, i = 0;
  while(i < length) {
    team_contribution[result].team = players[i].team;
    team_contribution[result++].internationalizations = count_internationalizations_by_team(players+i, length-i, players[i].team);
      i += team_count_while(players+i, length-i, players[i].team);
    }
  return result;
}

void TeamsContribution_exchange(TeamsContribution *team_contribution, int i, int j) {
  TeamsContribution team_contributionTmp = team_contribution[i];
  team_contribution[i] = team_contribution[j];
  team_contribution[j] = team_contributionTmp;
}

int TeamsContribution_cmp(TeamsContribution team_contribution1, TeamsContribution team_contribution2) {
  int result = team_contribution2.internationalizations - team_contribution1.internationalizations;
  if(result == 0)
    result = strcmp(team_contribution1.team, team_contribution2.team);
  return result;
}

void sort_TeamsContribution(TeamsContribution *team_contribution, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && TeamsContribution_cmp(team_contribution[j-1], team_contribution[j]) > 0) {
      TeamsContribution_exchange(team_contribution, j-1, j);
      j--;
    }
  }
}

void print_TeamsContribution(TeamsContribution *team_contribution, int length) {
  for(int i = 0; i < length; i++) 
    printf("%s %d\n", team_contribution[i].team, team_contribution[i].internationalizations);
}

void rakings_teams_by_number_internationalizations(const char *filename) {
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  TeamsContribution team_contribution[max_players];
  int length = players_read(f, players);
  sort_players_by_team(players, length);
  int n = fill_TeamsContribution(players, length, team_contribution);
  sort_TeamsContribution(team_contribution, n);
  print_TeamsContribution(team_contribution, n);
}

//--------------------------------------------------------------------- D

void ints_exchange_position(int *arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void position_to_number(Player *players, int length, int *arr) {
  for(int i = 0; i < length; i++) {
    if(strcmp(players[i].position, "Guarda_Redes") == 0)
      arr[i] = 0;
    else if (strcmp(players[i].position, "Defesa") == 0)
      arr[i] = 1;
    else if (strcmp(players[i].position, "Medio") == 0)
      arr[i] = 2;
    else
      arr[i] = 3;
  }
}

int Player_position_cmp(Player players1, Player players2, int p1, int p2 ) {
  int result = p1 - p2;
  if(result == 0) {
    result = players2.goals - players1.goals;
    if(result == 0) {
      result = strcmp(players1.name, players2.name);
    }
  }
  return result;
}

void sort_players_by_position(Player *players, int length, int *arr) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && Player_position_cmp(players[j-1], players[j], arr[j-1], arr[j]) > 0) {
      Player_exchange(players, j-1, j);
      ints_exchange_position(arr, j-1, j);
      j--;
    }
  }
}

void ranking_by_position(const char *filename) {
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  int arr[max_players];
  int length = players_read(f, players);
  position_to_number(players, length, arr);
  sort_players_by_position(players, length, arr);
  players_write(stdout, players, length);
}

//--------------------------------------------------------------------- E

Player *players_pointers(int internationalizations, const char *name, const char *position, int goals, int year_birth, const char *team) {
  Player *result = (Player *) malloc(sizeof(Player));
  result->internationalizations = internationalizations;
  result->name = name;
  result->position = position;
  result->goals = goals;
  result->year_birth = year_birth;
  result->team = team;
  return result;
}

int players_pointer_read(FILE *f, Player **player) {
  int result = 0;
  int internationalizations;
  char name[max_players];
  char position[max_players];
  int goals;
  int year_birth;
  char team[max_players];
  while(fscanf(f, "%d%s%s%d%d%s", &internationalizations, name, position, &goals, &year_birth, team) != EOF)
    player[result++] = players_pointers(internationalizations, str_dup(name), str_dup(position), goals, year_birth, str_dup(team));
  return result;
}

// TODO
void position_to_number_pointer(Player **players, int length, int *arr) {
  for(int i = 0; i < length; i++) {
    if(strcmp(players[i]->position, "Guarda_Redes") == 0)
      arr[i] = 0;
    else if (strcmp(players[i]->position, "Defesa") == 0)
      arr[i] = 1;
    else if (strcmp(players[i]->position, "Medio") == 0)
      arr[i] = 2;
    else
      arr[i] = 3;
  }
}

void Player_pointers_exchange(Player **players, int i, int j) {
  Player *tmp = players[i];
  players[i] = players[j];
  players[j] = tmp;
}

int Player_pointer_position_cmp(Player *players1, Player *players2, int p1, int p2 ) {
  int result = p1 - p2;
  if(result == 0) {
    result = players2->goals - players1->goals;
    if(result == 0) {
      result = strcmp(players1->name, players2->name);
    }
  }
  return result;
}

void sort_players_pointer_by_position(Player **players, int length, int *arr) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && Player_pointer_position_cmp(players[j-1], players[j], arr[j-1], arr[j]) > 0) {
      Player_pointers_exchange(players, j-1, j);
      ints_exchange_position(arr, j-1, j);
      j--;
    }
  }
}

void player_pointer_write(Player **players, int length) {
  for(int i = 0; i < length; i++) {
    printf("[%d][%s][%s][%d][%d][%s]\n", players[i]->internationalizations, players[i]->name, players[i]->position ,players[i]->goals, players[i]->year_birth, players[i]->team);
  }
}

void ranking_by_pointers(const char *filename) {
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player *players[max_players];
  int length = players_pointer_read(f, players);
  int arr[max_players];
  position_to_number_pointer(players, length, arr);
  sort_players_pointer_by_position(players, length, arr);
  player_pointer_write(players, length);
}

//--------------------------------------------------------------------- F

void eder() {
}

// main
int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];
  const char *filename = "futebolistas.txt";
  const char *filenameExeption = "eder.txt";
  if(x == 'A') {
    test_players_read_write(argc > 2 ? argv[2] : filename);
  } else if(x == 'B') {
    players_from_club(argc > 2 ? argv[2] : filename);
  } else if(x == 'C') {
    rakings_teams_by_number_internationalizations(argc > 2 ? argv[2] : filename);
  } else if(x == 'D') {
    ranking_by_position(argc > 2 ? argv[2] : filename);
  }else if(x == 'E') {
    ranking_by_pointers(argc > 2 ? argv[2] : filename);
  } else if(x == 'F') {
    eder(argc > 2 ? argv[2] : filenameExeption);
  } else if("All unit tests PASSED.\n")
  return 0;
}