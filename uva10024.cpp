#include <cstdlib>
#include <cstdio>

int row[11] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2};
int column[11] = {4, 4, 4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,5};
int block[11][3][5] = {
	1, 0, 0, 0, 0,  1, 1, 1, 1, 0,  1, 0, 0, 0, 0,
	1, 0, 0, 0, 0,  1, 1, 1, 1, 0,  0, 1, 0, 0, 0,
	1, 0, 0, 0, 0,  1, 1, 1, 1, 0,  0, 0, 0, 1, 0,
	1, 0, 0, 0, 0, 	1, 1, 1, 1, 0, 	0, 0, 1, 0, 0,
	0, 1, 0, 0, 0,  1, 1, 1, 1, 0,  0, 1, 0, 0, 0,
	0, 1, 0, 0, 0,  1, 1, 1, 1, 0,  0, 0, 1, 0, 0,
	1, 0, 0, 0, 0,  1, 1, 1, 0, 0,  0, 0, 1, 1, 0,
	0, 0, 1, 0, 0,  1, 1, 1, 0, 0,  0, 0, 1, 1, 0,
	0, 1, 0, 0, 0,  1, 1, 1, 0, 0,  0, 0, 1, 1, 0,
	1, 1, 0, 0, 0,  0, 1, 1, 0, 0,  0, 0, 1, 1, 0,
	1, 1, 1, 0, 0,  0, 0, 1, 1, 1,  0, 0, 0, 0, 0
};
int M[6][6], S[6][6];

int main()
{
    int n;
    while (~scanf("%d",&n))
    while (n --) {
		for (int i = 0; i < 6; ++ i)
		for (int j = 0; j < 6; ++ j)
		    scanf("%d",&M[i][j]);

		int find = 0;
		for (int k = 0; k < 8; ++ k) {
		    for (int i = 0; i < 6; ++ i)
		    for (int j = 0; j < 6; ++ j)
			S[i][j] = M[i][j];

		    for (int t = 0; t < 11 && !find; ++ t)
		    for (int x = 0; x <= 6-row[t] && !find; ++ x)
		    for (int y = 0; y <= 6-column[t] && !find; ++ y) {
			int sum = 0;
			for (int p = 0; p < row[t]; ++ p)
			for (int q = 0; q < column[t]; ++ q)
			    if (S[x+p][y+q] && block[t][p][q])
		   	        sum ++;

			    if (sum == 6) {
			        find = 1;
					break;
			    }
		    }

		    if (find) break;

		    for (int i = 0; i < 6; ++ i)
		    for (int j = 0; j < 6; ++ j)
			M[i][j] = S[5-j][i];
			if (k == 3) {//翻转
			    for (int i = 0; i < 6; ++ i)
			    for (int j = 0; j < i; ++ j) {
			        M[i][j] ^= M[j][i];
			        M[j][i] ^= M[i][j];
			        M[i][j] ^= M[j][i];
				}
			}
		}

		if (find)
			puts("correct");
		else puts("incorrect");
		if (n) puts("");
    }
    return 0;
}
