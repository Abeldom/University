#include <iostream>
using namespace std;

class buvos
{
    int **matrix;
    int meret;

  public:
    buvos(int n);
    ~buvos();

  public:
    bool isOk();
};

buvos::buvos(int n)
{
    meret = n;
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }
}
buvos::~buvos()
{
    for (int i = 0; i < meret; i++)
    {
        delete[] matrix[i];
    }
    delete matrix;
}

bool buvos::isOk()
{
    int ellenoriz[meret * meret] = {0};
    int szukseges_s = (meret * (meret + 1) / 2) / meret;

    for (int i = 0; i < meret; i++)
    {
        int s = 0;
        for (int j = 0; j < meret; j++)
        {

            int ind = matrix[i][j] - 1;
            ellenoriz[ind]++;
            if (ellenoriz[ind] == 1)
            {
                return false;
            }

            s += ind + 1;
        }
        if (s != szukseges_s)
        {
            return false;
        };
    }
    int s = 0;

    return true;
}

int main()
{

    return 0;
}