#include<stdio.h>
#include<math.h>

int points_result(int home, int away) {
int a;
if (home==away)
a = 1;
if (home>away)
a = 3;
else a = 0; 
return a;
}

int points_score_win(int home, int away) {
int a = home - away;
int b;
if ((a>=2) ||(home>=3))
b = 1; 
else b = 0;
return b;
}

int points_score_lose(int home, int away) {
int a = away - home;
int b;
if (a<=2)
b = 1;
else b = 0;
return b;
}

int points(int home, int away) {
int a = points_result(home,away) + points_score_win(home,away) + points_score_lose(home,away);
int b;
if (a>4)
b = 4;
else b = a;
return b;
} 

void test() {
int home;
int away;
while((scanf("%d%d", &home, &away))!=EOF) {
	int result1 = points(home,away);
	int result2 = points(away,home);
	printf("%d %d\n", result1, result2);
	}	
}
int main() {
test();
return 0;
}