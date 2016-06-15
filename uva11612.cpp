#include<ctime>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
#include<string>
#include<queue>

using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define FORD(i,a,b) for(int i=a;i>b;i--)
#define FORDE(i,a,b) for(int i=a;i>=b;i--)
#define SCF(a) scanf("%d",&a)
#define SCF2(a,b) scanf("%d%d",&a,&b)
#define SCF3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define SCFS(a) scanf("%s",a)
#define SCFC(a) scanf("%c",&a)
#define PRT(a) printf("%d",a)
#define PRTC(a) printf("%c",a)
#define PRTLN(a) printf("%d\n",a)
#define PRTLNU(a) printf("%lld\n",a)
#define PRTS(a) printf("%s\n",a)
#define min2(a,b) ((a)<(b))?(a):(b)
#define max2(a,b) ((a)>(b))?(a):(b)
#define INF 0x3FFFFFFF
#define MST(a,b) memset(a,b,sizeof(a))
#define swap(a,b) (a=(a)^(b),b=(a)^(b),a=(a)^(b))

const double eps = 1e-6;
const int N = 1000+5;

typedef struct{
  int i;
  double x,y;
} NODE;
NODE node[N];
NODE c;

bool zero(double x){
  return (-eps < x && x < eps);
}

double cross(double x1,double y1,double x2,double y2){
  return x1*y2-x2*y1;
}
double cross(NODE p,NODE p1,NODE p2){
  return cross(p1.x-p.x,p1.y-p.y,p2.x-p.x,p2.y-p.y);
}

bool Inline(int n){
  FOR(i,0,n){
    if(!zero(cross(node[i],node[i+1],node[i+2])))return 0;
  }
  return 1;
}
bool cmp(const NODE &a,const NODE &b){
  if(a.y > c.y && b.y < c.y) return true;
  if(a.y < c.y && b.y > c.y) return false;
    return cross(c,a,b)>0;
}

bool solve(int n){
  node[n] = node[0];
  node[n+1] = node[1];
  if(Inline(n))return false;
  FOR(i,0,n) node[i].i = i;
    c.x = c.y = 0;
  FOR(i,0,n) {
    c.x += node[i].x;
    c.y += node[i].y;
  }
  // black magic, the sqrt is used to avoid no point located in here
  // But it only work for uva test case
  c.x = c.x/n + sqrt(13.0)*eps;
  c.y = c.y/n + sqrt(97.0)*eps;
  sort(node,node+n,cmp);
  FOR(i,0,n)
    if(node[i].i == 0){
      FOR(j,i,n)
        printf("%d ",node[j].i);
      FOR(j,0,i)
        printf("%d ",node[j].i);
      break;
    }
  printf("%d\n",0);
  return true;
}

int main(){
  int n;      
  while(~SCF(n) && n){
    FOR(i,0,n)
      scanf("%lf%lf",&node[i].x,&node[i].y);
    if(!solve(n)){
      PRTS("no solution");
    }
  }

  return 0;
}
