#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


#define PI 3.14159265

int main() {

  int N;
  double radius;
  double m1, n1, m2, n2, m3, n3;
  double a, b, c, k;

  scanf("%d\n", &N);
  for(;N-- > 0;) {
    scanf("%lf", &radius);
    scanf("%lf%lf%lf%lf%lf%lf", &m1, &n1, &m2, &n2, &m3, &n3);

    a = 1.0;
    b = (m2+n2) / ( (m2/n1) * (n1+m1));
    c = (m3+n3) / ( (n3/m1) * (n1+m1));
    k = radius*sqrt((a+b+c)/(b+c-a)/(a+c-b)/(a+b-c))*2;
    printf("%.4lf\n",(a+b+c)*radius*k*0.5);
  }

  return 0;
}
