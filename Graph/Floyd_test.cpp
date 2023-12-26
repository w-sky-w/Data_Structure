#include<iostream>
#include<iomanip>
#include<queue>
#include<vector>
#include<string>
using namespace std;

//用邻接矩阵构建有向图
#define MAX 999//表示无穷
#define MVNum 20//最大结点数
typedef int VertexType;//设置结点的数据类型为int型（方便后续修改成char...）
typedef int ArcType;//设置的权值为int型（方便后续修改成float...）

class Graph//Adjacency Matrix Graph有向图，用邻接矩阵表示
{
public:
	void Create();
	int LocateVex(VertexType u);//查找Graph中的顶点u，并返回其对应在顶点表中的下标，未找到则返回-1
	int firstadj(int v);
	int nextadj(int v, int w);
	void Floyd();//Floyd算法
	void print_path();//打印路径
	void Show();//调试用，打印邻接矩阵
private:
	VertexType vexs[MVNum];//顶点表
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	ArcType path[MVNum][MVNum];//保存路径
	int vexnum, arcnum;//图当前的顶点数和边数
};
int Graph::LocateVex(VertexType u)
{//查找Graph中的顶点u，并返回其对应在顶点表中的下标，未找到则返回-1
	int i;
	for (i = 0; i < this->vexnum; i++)
	{
		if (u == this->vexs[i])
			return i;
	}
	return -1;
}
int Graph::firstadj(int v)
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (this->arcs[v][i] != MAX)
			return i;
	}
	return -1;
}
int Graph::nextadj(int v, int w)
{
	for (int i = w + 1; i < this->vexnum; i++)
	{
		if (this->arcs[v][i] != MAX)
			return i;
	}
	return -1;
}
void Graph::Show()
{
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			cout << setw(4) << this->arcs[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::Create()
{
	cout << "请输入总结点数和总边数:";
	cin >> this->vexnum >> this->arcnum;//输入总顶点数和总边数
	cout << "请输入各结点的信息:";
	for (int i = 0; i < this->vexnum; i++)
	{
		cin >> this->vexs[i];
	}
	//初始化邻接矩阵
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = MAX;
		}
	}
	//构造邻接矩阵
	for (int i = 0; i < this->arcnum; i++)
	{
		int v1, v2, w;
		cout << "请输入第" << i + 1 << "条边的起点和终点及其对应的权值:";
		cin >> v1 >> v2 >> w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		this->arcs[m][n] = w;
	}
	//初始化路径
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->path[i][j] = j;//矩阵P的初值则为各个边的终点顶点的下标
		}
	}
	return;
}
void Graph::Floyd()
{
	for (int k = 0; k < this->vexnum; k++)
		for (int i = 0; i < this->vexnum; i++)
			for (int j = 0; j < this->vexnum; j++)
				if (this->arcs[i][k] + this->arcs[k][j] < this->arcs[i][j])
				{
					this->arcs[i][j] = this->arcs[i][k] + this->arcs[k][j];
					this->path[i][j] = this->path[i][k];//path[i][j]=path[i][k]+path[k][j]
				}
	cout << "利用Floyd算法所得最短路径长度:" << endl;
	//更改到自身距离为0
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			if (i == j)
				this->arcs[i][j] = 0;
		}
	}
	this->Show();
}
void Graph::print_path()
{
	cout << "各个顶点对的最短路径：" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++) 
	{
		for (col = row + 1; col < this->vexnum; col++) 
		{
			if (this->arcs[row][col] != MAX)
			{
				cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col + 1) << " weight: " << this->arcs[row][col] << " path: " << " v" << to_string(row + 1);
				temp = path[row][col];
				//循环输出途径的每条路径。
				while (temp != col)
				{
					cout << "-->" << "v" << to_string(temp + 1);
					temp = path[temp][col];
				}
				cout << "-->" << "v" << to_string(col + 1) << endl;
			}
		}
		cout << endl;
	}
}
int main()
{
	Graph s;
	s.Create();
	s.Show();
	s.Floyd();
	s.print_path();
	system("pause");
	return 0;
}
