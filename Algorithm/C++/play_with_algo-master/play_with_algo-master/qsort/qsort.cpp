// qsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void exchange(int *arElem, int m, int n)
{
  int tmp = arElem[m];
  arElem[m] = arElem[n];
  arElem[n] = tmp;
}

int partion(int *arElem, int p, int r)
{
  int x = arElem[r];
  int i = p;
  for(int j = p; j < r; j++)
  {
    if(arElem[j] < x)
    {
      if(i != j)
      {
        exchange(arElem, i, j);
      }
      i++;
    }
  }
  exchange(arElem, i, r);
  return i;
}

void quick_sort(int *arElem, int p, int r)
{
  if(p < r)
  {
    int mid = partion(arElem, p, r);
    quick_sort(arElem, p, mid - 1);
    quick_sort(arElem, mid + 1, r);
  }
}

void Quick_Sort(int *arElem, int n)
{
  quick_sort(arElem, 0, n - 1);
}


int main(int argc, char* argv[])
{
	return 0;
}

bool IsNumberUsed(int num[], int idx, int i)
{
    for (int k = 0; k < idx; k++)
    {
        if (num[k] == i)
        {
            return true;
        }
    }

    return false;
}

void EnumNumber(int num[], int idx)
{
    if (idx > 3) //ö�ٵ���Чidx��0-3������3�˾����˳�����
    {
        return;
    }

    //�Ե�ǰidxλ�������� 1-9 ����
    for (int i = 1; i <= 9; i++)
    {
        if (!IsNumberUsed(num, idx, i))
        {
            num[idx] = i;
            EnumNumber(num, idx + 1); //����ö����һ��λ��
        }
    }
}