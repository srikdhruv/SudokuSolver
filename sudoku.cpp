#include <iostream>

using namespace std;

int main()
{
	//Declaration
	int a[9][9], flag[9][9][9], flag2[9][9][9], count = 1, i, j, k, l, m, ch, n, o;
	
	//Initialize arrays to 0
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			a[i][j] = 0;
			for(k = 0; k < 9; k++) flag[i][j][k] = 0;
		}
	}
	
	//Input
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
			cin >> a[i][j];
	}
	/*
	cout << "Enter 1 for every slot input.\nEnter 2 for row column input.\nEnter your choice - ";
	cin >> ch;
	switch(ch)
	{
        	//Lengthy Input
		case 1 : for(i = 0; i < 9; i++)
        		 {
        		 	cout << "Line " << (i + 1) << " starts now...\n";
        		 	for(j = 0; j < 9; j++)
        		 	{
        		 		cout << "Enter value at row " << (i + 1) << " and column " << (j + 1) << " - ";
        		 		cin >> a[i][j];
        		 	}
        		 }
        		 break;
        	//Row Column Input
        	case 2 : for( ; i ; )
         		 {
        		 	cout << "0 to exit. Row - ";
         		 	cin >> i;
         		 	if(i == 0)
         		 		continue;
			 	cout << "Column - ";
                    		cin >> j;
                    		cout << "Enter value - ";
                    		cin >> k;
                    		a[i - 1][j - 1] = k;
                	 }
                	 break;
        	default : cout << "Incorrect entry.";
               	  return 0;
	}
	*/
	
	//Given Sudoku
	cout << "\nYour entered Sudoku :\n";
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			cout << a[i][j];
			if((j + 1)%3 == 0) cout << " ";
		}
		if((i + 1)%3 == 0) cout << endl;
		cout << endl;
	}
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
            if(a[i][j] == 0) continue;
            for(k = 0; k < 9; k++)
            {
                if((k + 1) != a[i][j]) flag[i][j][k] = 1;
                else flag[i][j][k] = 2;
            }
		}
	}
	
	start:
	
	//Second Flag Array Initialization
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			for(k = 0; k < 9; k++)
			{
				flag2[i][j][k] = flag[i][j][k];
			}
		}
	}
	
	//Flag Numbers
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
            		if(a[i][j] != 0)
            			continue;
			for(k = 0; k < 9; k++)
			{
				for(l = 0; l < 9; l++)
				{
					if(flag[l][j][k] == 2) flag[i][j][k] = 1;
					if(flag[i][l][k] == 2) flag[i][j][k] = 1;
				}
				for(l = (i/3)*3; l < (i/3)*3 + 3; l++)
				{
					for(m = (j/3)*3; m < (j/3)*3 + 3; m++)
					{
						if(flag[l][m][k] == 2) flag[i][j][k] = 1;
					}
				}
			}
		}
	}
	
	//Line Flagging
	for(i = 0; i < 9; i += 3)
	{
		for(j = 0; j < 9; j += 3)
		{
			for(k = 0; k < 9; k++)
			{
				int count1 = 0;
				int count2 = 0;
				int count3 = 0;
				for(l = i; l < i + 3; l++)
				{
					for(m = j; m < j + 3; m++)
					{
						if(a[i][j] == (k + 1)) count1++;
						if(flag[l][m][k] == 0) count2++;
					}
				}
				if(count1 || count2 > 3 || count2 <= 1) continue;
				count1 = 0;
				int index[count2][2];
				for(l = i; l < i + 3; l++)
				{
					for(m = j; m < j + 3; m++)
					{
						if(flag[l][m][k] == 0)
                        			{
							index[count1][0] = l;
							index[count1][1] = m;
                            				count1++;
                        			}
					}
				}
				count1 = 0;
				for(l = 0; l < count2 - 1; l++)
                		{
                    			if(index[l][0] == index[l + 1][0]) count1++;
                    			if(index[l][1] == index[l + 1][1]) count3++;
                		}
                		if(count1 == (count2 - 1))
                		{
                    			for(m = 0; m < 9; m++)
					{
						if(m < j || m > (j + 2)) flag[index[0][0]][m][k] = 1;
					}
                		}
                		if(count3 == (count2 - 1))
                		{
                    			for(m = 0; m < 9; m++)
					{
						if(m < i || m > (i + 2)) flag[m][index[0][1]][k] = 1;
					}
                		}
			}
		}
	}
	
	//Integrated Box Flagging with Multiple Numbers Simultaneously
	for(i = 0; i < 9; i += 3)
	{
		for(j = 0; j < 9; j += 3)
		{
            		int no[9][9][2];
            		int ct[9] = {0,0,0,0,0,0,0,0,0};
            		int tally[10] = {0,0,0,0,0,0,0,0,0,0};
			for(k = 0; k < 9; k++)
			{
				int count1 = 0;
				for(l = i; l < i + 3; l++)
				{
					for(m = j; m < j + 3; m++)
					{
						if(flag[l][m][k] == 0)
						{
						    no[k][count1][0] = l;
						    no[k][count1][1] = m;
						    count1++;
						}
					}
				}
         			ct[k] = count1;
			}
			for(k = 0; k < 9; k++)
			{
				tally[ct[k]]++;
			}
			for(k = 0; k < 9; k++)
			{
				int count1 = 0;
				int index[ct[k] + 1];
				if(tally[ct[k]] < ct[k]) continue;
				for(l = 0; l < 9; l++)
		        	{
				    	if(ct[l] == ct[k])
				    	{
						int count2 = 0;
						int count3 = 0;
					        for(m = 0; m < ct[k]; m++)
					        {
					        	if(no[k][m][0] == no[l][m][0]) count2++;
					 	   	if(no[k][m][1] == no[l][m][1]) count3++;
					        }
					        if(count2 == ct[k] && count3 == ct[k])
					        {
				 		   	index[count1] = l;
			 			   	count1++;
		  			        }
				    	}
                		}
				if(count1 == ct[k])
				{
					for(l = 0; l < ct[k]; l++)
				    	{
				        	for(m = 0; m < ct[k]; m++)
				        	{
				            		for(n = 0; n < 9; n++)
				            		{
				                		int count4 = 0;
				                		for(o = 0; o < ct[k]; o++)
				                    			if(n != index[o]) count4++;
				                		if(count4 == ct[k]) flag[no[index[l]][m][0]][no[index[l]][m][1]][n] = 1;
				            		}
				        	}
				    	}
				}
			}
		}
	}
	
	//Integrated Row Flagging with Multiple Numbers Simultaneously
	for(i = 0; i < 9; i++)
	{
		int no[9][9][2];
		int ct[9] = {0,0,0,0,0,0,0,0,0};
		int tally[10] = {0,0,0,0,0,0,0,0,0,0};
		for(k = 0; k < 9; k++)
		{
			int count1 = 0;
			for(j = 0; j < 9; j++)
			{
				if(flag[i][j][k] == 0)
                		{
					no[k][count1][0] = i;
				    	no[k][count1][1] = j;
				    	count1++;  
                		}
			}
            		ct[k] = count1;
        	}
		for(k = 0; k < 9; k++)
		{
			tally[ct[k]]++;
		}
		for(k = 0; k < 9; k++)
		{
			int count1 = 0;
			int index[ct[k] + 1];
			if(tally[ct[k]] < ct[k]) continue;
			for(l = 0; l < 9; l++)
            		{
				if(ct[l] == ct[k])
				{
					int count2 = 0;
					int count3 = 0;
					for(m = 0; m < ct[k]; m++)
					{
						if(no[k][m][0] == no[l][m][0]) count2++;
						if(no[k][m][1] == no[l][m][1]) count3++;
					}
					if(count2 == ct[k] && count3 == ct[k])
					{
						index[count1] = l;
						count1++;
					}
				}
            		}
            		if(count1 == ct[k])
            		{
		        	for(l = 0; l < ct[k]; l++)
		        	{
		            		for(m = 0; m < ct[k]; m++)
		            		{
						for(n = 0; n < 9; n++)
						{
							int count4 = 0;
						    	for(o = 0; o < ct[k]; o++)
								if(n != index[o]) count4++;
						    	if(count4 == ct[k]) flag[no[index[l]][m][0]][no[index[l]][m][1]][n] = 1;
						}
		            		}
		        	}
            		}
        	}
   	}
    	//Integrated Column Flagging with Multiple Numbers Simultaneously
	for(j = 0; j < 9; j++)
	{
	    int no[9][9][2];
        int ct[9] = {0,0,0,0,0,0,0,0,0};
        int tally[10] = {0,0,0,0,0,0,0,0,0,0};
		for(k = 0; k < 9; k++)
		{
			int count1 = 0;
			for(i = 0; i < 9; i++)
			{
				if(flag[i][j][k] == 0)
                {
                    no[k][count1][0] = i;
                    no[k][count1][1] = j;
                    count1++;
                }
			}
            ct[k] = count1;
        }
		for(k = 0; k < 9; k++)
		{
			tally[ct[k]]++;
		}
		for(k = 0; k < 9; k++)
		{
			int count1 = 0;
			int index[ct[k] + 1];
			if(tally[ct[k]] < ct[k]) continue;
			for(l = 0; l < 9; l++)
            {
                if(ct[l] == ct[k])
                {
                    int count2 = 0;
                    int count3 = 0;
                    for(m = 0; m < ct[k]; m++)
                    {
                        if(no[k][m][0] == no[l][m][0]) count2++;
                        if(no[k][m][1] == no[l][m][1]) count3++;
                    }
                    if(count2 == ct[k] && count3 == ct[k])
                    {
                        index[count1] = l;
                        count1++;
                    }
                }
            }
            if(count1 == ct[k])
            {
                for(l = 0; l < ct[k]; l++)
                {
                    for(m = 0; m < ct[k]; m++)
                    {
                        for(n = 0; n < 9; n++)
                        {
                            int count4 = 0;
                            for(o = 0; o < ct[k]; o++)
                                if(n != index[o]) count4++;
                            if(count4 == ct[k]) flag[no[index[l]][m][0]][no[index[l]][m][1]][n] = 1;
                        }
                    }
                }
            }
        }
    }
    //2 box - 2 line flagging
    for(i = 0; i < 9; i += 3)
    {
        for(j = 0; j < 9; j += 3)
        {
            for(k = 0; k < 9; k++)
            {
                int count1 = 0;
				int count2[3] = {0,0,0};
				int count3[3] = {0,0,0};
				for(l = i; l < i + 3; l++)
				{
					for(m = j; m < j + 3; m++)
					{
						if(a[i][j] == (k + 1)) count1++;
						if(flag[l][m][k] == 0)
                        {
                            count2[l]++;
                            count3[m]++;
                        }
					}
				}
				if(count1) continue;
				count1 = 0;
				int index[3];
				for(l = 0; l < 3; l++)
                {
                    index[l] = i + l;
                    if(count2[l] == 0)
                    {
                        count1++;
                        index[l] = -1;
                    }
                }
                if(count1 == 1)
                {
                    for(n = 3; j + n < 9; n += 3)
                    {
                        count1 = 0;
                        for(l = i; l < i + 3; l++)
                        {
                            int count4 = 0;
                            if(index[l - i] == -1) count4 = -2;
                            for(m = j + n; m < j + n + 3; m++)
                            {
                                if(flag[l][m][k] == 0) count4++;
                            }
                            if(count4 > 0) count1++;
                        }
                        if(count1 == 3)
                        {
                            for(l = i; l < i + 3; l++)
                            {
                                for(m = 0; m < 9; m++)
                                {
                                    if((index[l - i] == -1) && (m < j) && (m > j + 2) && (m < j + n) && (m > j + n + 2)) flag[l][m][k] = 1;
                                }
                            }
                        }
                    }
                }
                count1 = 0;
                for(l = 0; l < 3; l++)
                {
                    index[l] = j + l;
                    if(count3[l] == 0)
                    {
                        count1++;
                        index[l] = -1;
                    }
                }
                if(count1 == 1)
                {
                    for(n = 3; i + n < 9; n += 3)
                    {
                        count1 = 0;
                        for(m = j; m < j + 3; m++)
                        {
                            int count4 = 0;
                            if(index[m - j] == -1) count4 = -2;
                            for(l = i + n; l < i + n + 3; l++)
                            {
                                if(flag[l][m][k] == 0) count4++;
                            }
                            if(count4 > 0) count1++;
                        }
                        if(count1 == 3)
                        {
                            for(l = 0; l < 9; l++)
                            {
                                for(m = j; m < j + 3; m++)
                                {
                                    if((index[l - i] == -1) && (m < j) && (m > j + 2) && (m < j + n) && (m > j + n + 2)) flag[l][m][k] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
	//Confirming Numbers
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			for(k = 0; k < 9; k++)
			{
				if(a[i][j] != 0) continue;
				int count1 = 0;
				int count2 = 0;
				int count3 = 0;
				int count4 = 0;
				for(l = 0; l < 9; l++)
				{
					if(flag[l][j][k] == 1 && l != i) count1++;
					if(flag[i][l][k] == 1 && l != j) count2++;
					if(flag[i][j][l] == 1 && l != k) count4++;
				}
				for(l = (i/3)*3; l < (i/3)*3 + 3; l++)
				{
					for(m = (j/3)*3; m < (j/3)*3 + 3; m++)
					{
						if(flag[l][m][k] == 1 && (i != l || j != m)) count3++;
					}
				}
                if(count1 == 8 || count2 == 8 || count3 == 8 || count4 == 8)
				{
					a[i][j] = k + 1;
					for(l = 0; l < 9; l++)
					{
						if((l + 1) != a[i][j]) flag[i][j][l] = 1;
						else flag[i][j][l] = 2;
					}
				}
			}
		}
	}
	//Infinite check
	count = 0;
    for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			for(k = 0; k < 9; k++)
			{
				if(flag2[i][j][k] != flag[i][j][k]) count++;
			}
		}
	}
	if(count == 0)
	{
		cout << "This sudoku cannot be solved with the given values.";
		cout << "\nFinal Sudoku :-\n\n";
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                cout << a[i][j];
                if((j + 1)%3 == 0) cout << " ";
            }
            if((i + 1)%3 == 0) cout << endl;
            cout << endl;
        }
		return 0;
	}
	//Check if over
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(a[i][j] == 0) goto start;
		}
	}
	//Print Sudoku
	cout << "\nSolved Sudoku :-\n\n";
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			cout << a[i][j];
			if((j + 1)%3 == 0) cout << " ";
		}
		if((i + 1)%3 == 0) cout << endl;
		cout << endl;
	}
    return 0;
}
