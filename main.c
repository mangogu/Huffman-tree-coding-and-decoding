#include<stdio.h>
#include<string.h>
#define N 50 

int huffman_matrix[2*N][6];
int min1,min2,where1,where2;
int c[N][10];

char str[100];
int character_and_num_origin[127][2]; 
int n=0; 
int character_and_num[N][2];


void select(int m)//找到满足条件的两个最小权重结点，并将他们的权重赋值给min1,min2，将他们的行号赋值给where1,where2
{
	int i;
	min1=2147483647;
	for(i=1;i<=m-1;i++)
	{
		if(huffman_matrix[i][1]<min1&&huffman_matrix[i][5]==0)
		{
			min1=huffman_matrix[i][1];
			where1=i;
		}
	}
	huffman_matrix[where1][5]=1;
	min2=2147483647;
	for(i=1;i<=m-1;i++)
	{
		if(huffman_matrix[i][1]<min2&&huffman_matrix[i][1]>=min1&&huffman_matrix[i][5]==0)
		{
			if(huffman_matrix[i][5]==0)
			{
				min2=huffman_matrix[i][1];
				where2=i;
			}
		}
	}
	huffman_matrix[where2][5]=1;
}
void initialize_mat_and_code()//初始化huffman_matrix和c数组，使其所有元素为0
{
	int i,j;
	for(i=1;i<=2*N-1;i++)
	{
		for(j=1;j<=5;j++)
		{
			huffman_matrix[i][j]=0;
		}
	}
	for(i=1;i<=N;i++)
	{
		for(j=0;j<10;j++)
		{
			c[i][j]=0;
		}
	}
}
void creat_huffman_matrix()//根据规则将权重生成哈夫曼数组
{
	int i,m;
	for(i=1;i<=n;i++)
	{
		huffman_matrix[i][1]=character_and_num[i][1];
	}
	m=n+1;
	while(m!=2*n)
	{
		select(m);
		huffman_matrix[m][1]=min1+min2;
		huffman_matrix[m][3]=where1; 
		huffman_matrix[m][4]=where2;
		huffman_matrix[where1][2]=m;
		huffman_matrix[where2][2]=m;
		m++;
	}
}
void print_huffman_matrix()//打印哈夫曼数组
{
	int i,j;
	printf("row\tdata\tPrnt\tLchild\tRchild\tSign\n");
	for(i=1;i<=2*n-1;i++)
	{
		printf("%d\t",i);
		for(j=1;j<=5;j++)
		{
			printf("%d\t",huffman_matrix[i][j]);
		}
		printf("\n");
	}
}
void coding()//根据哈夫曼树对字符进行编码，并存储至c数组中
{
	int p,row=1,i;
	for(i=1;i<=n;i++)
	{
		p=9;
		row=i;
		while(huffman_matrix[row][2]!=0)
		{
			if(huffman_matrix[huffman_matrix[row][2]][3]==row)
				c[i][p]=0;
			else
				c[i][p]=1;
			if(huffman_matrix[row][2]!=0)
				row=huffman_matrix[row][2];
			else
				break;
			p--;
		}
		while(p!=0)
		{
			c[i][p]=2; 
			p--;
		} 
	}
}
void print_code()//打印编码
{
	int i,j,k=1;
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("'%c'的编码为：",character_and_num[i][0]); 
		for(j=1;j<10;j++)
		{
			if(c[i][j]==2)
			{
				printf(" ");
			} 
			else
			{
				printf("%d",c[i][j]);
			}
		}
		printf("\n");
		k++;
	}
}
void string_input()//将初始的字符串，存储至str数组中，并统计每个字符出现的次数
{
	int i,j;
	printf("请输入字符串：\n");
	scanf("%[^\n]",&str);
	for(i=0;str[i]!=0;i++)
	{
		for(j=0;j<=127;j++)
		{
			if(str[i]==j)
			{
				character_and_num_origin[j][1]++;
			}
		}
	}
}

void start_character_and_num_origin()//初始化character_and_num_origin数组
{
	int i; 
	for(i=1;i<=127;i++)
	{
		character_and_num_origin[i][0]=i;
		character_and_num_origin[i][1]=0;
	}
	for(i=1;i<N;i++)
	{
		character_and_num[i][0]=0;
		character_and_num[i][1]=0;
	}
}

void count_character_and_num()//将character_and_num_origin数组简化后存储为character_and _num数组，即将前者第二列不为0的行存储到后者的首部
{
	int i,j=1;
	for(i=1;i<=127;i++)
	{
		if(character_and_num_origin[i][1]!=0)
		{
			n++;
			character_and_num[j][0]=character_and_num_origin[i][0];
			character_and_num[j][1]=character_and_num_origin[i][1];
			j++;
		}
	}
}
void recoding()//解码
{
	int i,j,k,t,sign;
	char code[N][10];
	char code_order[100];
	char tem_code_order[10];
	for(i=0;i<N;i++)
	{
		for(j=0;j<10;j++)
		{
			code[i][j]=0;
		}
	}
	for(i=1;i<=n;i++)
	{
		k=0;
		for(j=1;j<10;j++)
		{
			if(c[i][j]!=2)
			{
				code[i-1][k]=c[i][j]+48;
				k++;
			}
		}
	}
	for(i=0;i<10;i++)
	{
		tem_code_order[i]=0;
	}
	printf("请输入需要解码的哈夫曼编码序列：\n");
	scanf("%s",&code_order);
	k=0;
	t=0;
	printf("解出来为：\n");
	while(code_order[k]!=0)
	{
		tem_code_order[t]=code_order[k];
		t++;
		for(i=0;i<n;i++)
		{
			sign=strcmp(tem_code_order,code[i]);
			if(sign==0)
			{
				printf("%c",character_and_num[i+1][0]);
				t=0;
				for(j=0;j<10;j++)
				{
					tem_code_order[j]=0;
				}
				break;
			}
		}
		k++;
	}
	if(tem_code_order[0]!=0)
	{
		printf("\n警告！请检查输入编码！以上结果不一定准确！");
	}
	printf("\n");
}
void main()
{
	start_character_and_num_origin();
	string_input();
	count_character_and_num();
	initialize_mat_and_code();
	creat_huffman_matrix();
	print_huffman_matrix();
	coding();
	print_code();
	recoding();
}