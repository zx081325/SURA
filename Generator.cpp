#include "Generator.h"
#include "Define.h"
#include "queue"
#include "string.h"
Generator::Generator()
{

}

Generator::~Generator()
{

}

void Generator:: AddMove(int nFromX, int nFromY, int nToX, int nToY, int nSide,int nPly)
{
    m_nMoveList[nPly][m_nMoveCount].From.x = nFromX;
    m_nMoveList[nPly][m_nMoveCount].From.y = nFromY;
    m_nMoveList[nPly][m_nMoveCount].To.x = nToX;
    m_nMoveList[nPly][m_nMoveCount].To.y = nToY;
    m_nMoveList[nPly][m_nMoveCount].Side = nSide;
    m_nMoveCount++;
}

int dx[8] = { -1,1,0,0,-1,-1,1,1 };
int dy[8] = { 0,0,-1,1 ,-1,1,-1,1 };
int vis[6][6];

int xa[] = { 1,2,3,4,0,5,0,5,0,5,0,5,1,2,3,4 };
int ya[] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,5,5 };
int x2[] = { 0,0,5,5,1,4,2,3,2,3,1,4,0,0,5,5 };
int y2[] = { 1,2,2,1,0,0,0,0,5,5,5,5,4,3,3,4 };
int dirx[] = { 1,1,-1,-1,0,0,0,0,0,0,0,0,1,1,-1,-1 };
int diry[] = { 0,0,0,0,1,1,1,1,-1,-1,-1,-1,0,0,0,0 };

struct  loc
{
    int x, y, dirx, diry;
    loc(int x, int y, int dirx, int diry) :x(x), y(y), dirx(dirx), diry(diry) {}
    loc() {}
}loc1;

int Generator:: CreatePossibleMove(BYTE position[6][6], int nPly, int nSide)//nside代表产生哪一方的走法1-红，2-黑
{
    int i, j, k;
    m_nMoveCount = 0;
    taking[1]=taking[2]=0;
    std::queue<loc> Q;
    while (!Q.empty())
    {
        Q.pop();
    }
    for (i = 0;i < 6;i++)
    {
        for (j = 0;j < 6;j++)
        {
            if (position[i][j] == nSide)//1-1,2-2
            {
                position[i][j] = 0;
                memset(vis, 0, sizeof(vis));
                for (k = 0;k < 8;k++)
                {
                    int xx = i + dx[k];int yy = j + dy[k];
                    if (xx >= 0 && xx < 6 && yy >= 0 && yy < 6 && !position[i + dx[k]][j + dy[k]])
                    {
                        AddMove(i, j, xx, yy,nSide, nPly);
                    }
                }

                k = j;k--;
                while (k >= 0 && !position[i][k])
                {
                    k--;
                }
                if (k == -1)
                {
                    if (i == 1 && !vis[0][1] && position[0][1] != nSide)
                    {
                        vis[0][1] = 1;
                        if (!position[0][1])Q.push(loc(0, 1, 1, 0));
                        else { AddMove(i, j, 0, 1,nSide, nPly);taking[nSide]++; }
                    }
                    if (i == 2 && !vis[0][2] && position[0][2] != nSide)
                    {
                        vis[0][2] = 1;
                        if (!position[0][2])Q.push(loc(0, 2, 1, 0));
                        else {AddMove(i, j, 0, 2,nSide, nPly);taking[nSide]++;}
                    }
                    if (i == 3 && !vis[5][2] && position[5][2] != nSide)
                    {
                        vis[5][2] = 1;
                        if (!position[5][2])Q.push(loc(5, 2, -1, 0));
                        else { AddMove(i, j, 5, 2,nSide, nPly);taking[nSide]++; }
                    }
                    if (i == 4 && !vis[5][1] && position[5][1] != nSide)
                    {
                        vis[5][1] = 1;
                        if (!position[5][1])Q.push(loc(5, 1, -1, 0));
                        else {AddMove(i, j, 5, 1,nSide, nPly);taking[nSide]++;}
                    }
                }

                k = j;k++;
                while (k <= 5 && !position[i][k])
                {
                    k++;
                }
                if (k == 6)
                {
                    if (i == 1 && !vis[0][4] && position[0][4] != nSide)
                    {
                        vis[0][4] = 1;
                        if (!position[0][4])Q.push(loc(0, 4, 1, 0));
                        else {AddMove(i, j, 0, 4,nSide, nPly);taking[nSide]++;}
                    }
                    if (i == 2 && !vis[0][3] && position[0][3] != nSide)
                    {
                        vis[0][3] = 1;
                        if (!position[0][3])Q.push(loc(0, 3, 1, 0));
                        else {AddMove(i, j, 0, 3,nSide, nPly);taking[nSide]++;}
                    }
                    if (i == 3 && !vis[5][3] && position[5][3] != nSide)
                    {
                        vis[5][3] = 1;
                        if (!position[5][3])Q.push(loc(5, 3, -1, 0));
                        else {AddMove(i, j, 5, 3,nSide, nPly);taking[nSide]++;}
                    }
                    if (i == 4 && !vis[5][4] && position[5][4] != nSide)
                    {
                        vis[5][4] = 1;
                        if (!position[5][4])Q.push(loc(5, 4, -1, 0));
                        else {AddMove(i, j, 5, 4,nSide, nPly);taking[nSide]++;}
                    }
                }

                k = i;k--;
                while (k >= 0 && !position[k][j])
                {
                    k--;
                }
                if (k == -1)
                {
                    if (j == 1 && !vis[1][0] && position[1][0] != nSide)
                    {
                        vis[1][0] = 1;
                        if (!position[1][0])Q.push(loc(1, 0, 0, 1));
                        else {AddMove(i, j, 1, 0,nSide, nPly);taking[nSide]++;}
                    }
                    if (j == 2 && !vis[2][0] && position[2][0] != nSide)
                    {
                        vis[2][0] = 1;
                        if (!position[2][0])Q.push(loc(2, 0, 0, 1));
                        else {AddMove(i, j, 2, 0, nSide,nPly);taking[nSide]++;}
                    }
                    if (j == 3 && !vis[2][5] && position[2][5] != nSide)
                    {
                        vis[2][5] = 1;
                        if (!position[2][5])Q.push(loc(2, 5, 0, -1));
                        else {AddMove(i, j, 2, 5,nSide, nPly);taking[nSide]++;}
                    }
                    if (j == 4 && !vis[1][5] && position[1][5] != nSide)
                    {
                        vis[1][5] = 1;
                        if (!position[1][5])Q.push(loc(1, 5, 0, -1));
                        else {AddMove(i, j, 1, 5,nSide, nPly);taking[nSide]++;}
                    }
                }

                k = i;k++;
                while (k <= 5 && !position[k][j])
                {
                    k++;
                }
                if (k == 6)
                {
                    if (j == 1 && !vis[4][0] && position[4][0] != nSide)
                    {
                        vis[4][0] = 1;
                        if (!position[4][0])Q.push(loc(4, 0, 0, 1));
                        else {AddMove(i, j, 4, 0,nSide, nPly);taking[nSide]++;}
                    }
                    if (j == 2 && !vis[3][0] && position[3][0] != nSide)
                    {
                        vis[3][0] = 1;
                        if (!position[3][0])Q.push(loc(3, 0, 0, 1));
                        else {AddMove(i, j, 3, 0,nSide, nPly);taking[nSide]++;}
                    }
                    if (j == 3 && !vis[3][5] && position[3][5] != nSide)
                    {
                        vis[3][5] = 1;
                        if (!position[3][5])Q.push(loc(3, 5, 0, -1));
                        else {AddMove(i, j, 3, 5,nSide, nPly);taking[nSide]++;}
                    }
                    if (j == 4 && !vis[4][5] && position[4][5] != nSide)
                    {
                        vis[4][5] = 1;
                        if (!position[4][5])Q.push(loc(4, 5, 0, -1));
                        else {AddMove(i, j, 4, 5,nSide, nPly);taking[nSide]++;}
                    }
                }
                while (!Q.empty())
                {
                    loc1 = Q.front();
                    Q.pop();
                    int xx = loc1.x + loc1.dirx;
                    int yy = loc1.y + loc1.diry;
                    while (xx >= 0 && xx <= 5 && yy >= 0 && yy <= 5)
                    {
                        if (position[xx][yy] == nSide)
                            break;
                        if (position[xx][yy]==3-nSide )
                        {
                            if (!vis[xx][yy])
                            {
                                vis[xx][yy] = 1;
                                AddMove(i, j, xx, yy,nSide, nPly);
                                taking[nSide]++;
                            }
                            break;
                        }

                        for (k = 0;k < 16;k++)
                        {
                            if (xx == xa[k] && yy == ya[k])
                            {
                                if (!position[x2[k]][y2[k]] && !vis[x2[k]][y2[k]])
                                {
                                    vis[x2[k]][y2[k]] = 1;
                                    Q.push(loc(x2[k], y2[k], dirx[k], diry[k]));
                                }
                                else if (position[x2[k]][y2[k]] ==3-nSide && !vis[x2[k]][y2[k]])
                                {
                                    vis[x2[k]][y2[k]] = 1;
                                    AddMove(i, j, x2[k], y2[k],nSide, nPly);
                                    taking[nSide]++;
                                }
                            }
                        }
                        xx += loc1.dirx;
                        yy += loc1.diry;
                    }
                }
                position[i][j] = nSide;
            }
        }
    }
    return m_nMoveCount;//返回总的走法数
}
