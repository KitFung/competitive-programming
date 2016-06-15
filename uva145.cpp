#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int START_DAY = 480;
const int START_EVENING = 1080;
const int START_NIGHT = 1320;
const int END_DAY = 1440;

double cost[5][3] =  {{0.1, 0.06, 0.02},
                      {0.25, 0.15, 0.05},
                      {0.53, 0.33, 0.13},
                      {0.87, 0.47, 0.17},
                      {1.44, 0.80, 0.30}};
int period[3];
char plan[3];
int start[3] = {START_DAY, START_EVENING, START_NIGHT};
char ID[10];

void init_cost() {
  period[0] = START_EVENING - START_DAY;
  period[1] = START_NIGHT - START_EVENING;
  period[2] = (END_DAY - START_NIGHT) + (START_DAY);
}

inline int time_to_mins(int h, int m) {
  return h*60 + m;
}

int period_to_mins(int fromh, int fromm, int toh, int tom) {
  int vf = time_to_mins(fromh, fromm);
  int vt = time_to_mins(toh, tom);
  if(vt < vf)
    return END_DAY - vf + vt;
  else
    return vt - vf;
}

int start_from(int v) {
  if(v < START_DAY)
    return 2;
  else if(v < START_EVENING)
    return 0;
  else if(v < START_NIGHT)
    return 1;
  else
    return 2;
}

int f_len(int h, int m, int &sumv, int periodidx) {
  int tv;
  int ct = time_to_mins(h, m);

  int vvv =  period[periodidx] - (ct - start[periodidx]);

  int ccc = start[periodidx] + ct;

  if(ccc < start[periodidx] + period[periodidx]) {
    tv = sumv;
    sumv = 0;
  } else {
    tv = vvv;
    sumv -= vvv;
  }
  return tv;
}

int v_len(int &sumv, int periodidx) {
  int tv;
  int t = period[periodidx];

  // printf("[%d   %d]\n", sumv, periodidx);
  if(sumv < t) {
    tv = sumv;
    sumv = 0;
  } else {
    tv = t;
    sumv -= t;
  }
  return tv;
}

int main() {
  freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  int fromh, fromm, toh, tom;
  int ans[3];
  init_cost();
  while (scanf("%s", plan) != EOF && plan[0] != '#') {
    scanf("%s%d%d%d%d", ID, &fromh, &fromm, &toh, &tom);
    memset(ans, 0, sizeof(ans));

    int caseid = plan[0] - 'A';
    double answer = 0;
    int psum = period_to_mins(fromh, fromm, toh, tom);
    int curp = start_from(time_to_mins(fromh, fromm));

    printf("%d  --  %d\n", psum, curp);

    ans[curp] = f_len(fromh, fromm, psum, curp);

    printf("[%d  %lf  %d   %d]\n", ans[curp], cost[caseid][curp], caseid, curp);
    answer += ans[curp]*cost[caseid][curp];
    while(psum > 0) {
      curp = (curp+1) % 3;
      ans[curp] = v_len(psum, curp);
      answer += ans[curp]*cost[caseid][curp];
      printf("[%d  %lf  %d   %d]\n", ans[curp], cost[caseid][curp], caseid, curp);
    }
    printf("%10s%6d%6d%6d%3c%8.2lf\n", ID, ans[0], ans[1], ans[2], plan[0], answer);
  }
  return 0;
}
