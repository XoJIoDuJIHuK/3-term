using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ShimanIdiNaHui
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private int Inf = 2147000000;
        private int[,] matSmezh;
        private int N;
        private int[,] masReber;
        private string[] masStrReb;
        private int Nreber = 1;
        private bool graphIsOriented = false;
        private int firstVertexNumber = 0;
        private string BFS()
        {
            var visited = new List<int>();
            visited.Add(firstVertexNumber);
            int lastVisited = firstVertexNumber;
            var queue = new Queue<int>();
            while (visited.Count <= N)
            {
                for (int i = 0; i < N; i++)
                {
                    if (matSmezh[lastVisited, i] != Inf && !visited.Contains(i) && !queue.Contains(i))
                    {
                        queue.Enqueue(i);
                    }
                }
                if (queue.Count == 0) break;
                lastVisited = queue.Dequeue();
                visited.Add(lastVisited);
            }
            string resultBFSString = "";
            for (int i = 0; i < visited.Count; i++)
            {
                resultBFSString += visited[i].ToString() + 1;
                resultBFSString += " ";
            }
            return resultBFSString;
        }

        private string DFS()
        {
            var visited = new List<int>();
            visited.Add(firstVertexNumber);
            int lastVisited = firstVertexNumber;
            var stack = new Stack<int>();
            while (visited.Count <= N)
            {
                for (int i = N - 1; i >= 0; i--)
                {
                    if (matSmezh[lastVisited, i] != Inf && !visited.Contains(i) && !stack.Contains(i))
                    {
                        stack.Push(i);
                    }
                }
                if (stack.Count == 0) break;
                lastVisited = stack.Pop();
                visited.Add(lastVisited);
            }
            string resultDFSString = "";
            for (int i = 0; i < visited.Count; i++)
            {
                resultDFSString += (visited[i] + 1).ToString();
                resultDFSString += " ";
            }
            return resultDFSString;
        }

        private string Dijkstra()
        {
            int[,] matDij = new int[N, N];
            var pointed = new Dictionary<int, int>();
            pointed.Add(firstVertexNumber, 0);
            int lastPointed = firstVertexNumber;
            for (int i = 0; i < N; i++)
            {
                if (i == firstVertexNumber) continue;
                matDij[0, i] = Inf;
            }
            for (int i = 1; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (pointed.ContainsKey(j)) continue;
                    if (matSmezh[lastPointed, j] != Inf)
                    {
                        int newValue = pointed[lastPointed] + matSmezh[lastPointed, j];
                        if (newValue < matDij[i - 1, j])
                        {
                            matDij[i, j] = newValue;
                        }
                        else
                        {
                            matDij[i, j] = matDij[i - 1, j];
                        }
                    }
                    else
                    {
                        matDij[i, j] = matDij[i - 1, j];
                    }
                }
                int smallestValue = Inf;
                int smallestIndex = -1;
                for (int j = 0; j < N; j++)
                {
                    if (pointed.ContainsKey(j)) continue;
                    if (matDij[i, j] < smallestValue)
                    {
                        smallestValue = matDij[i, j];
                        smallestIndex = j;
                    }
                }
                pointed.Add(smallestIndex, smallestValue);
                lastPointed = smallestIndex;
            }

            string result = "(vertex; distance to it)\n";
            for (int i = 0; i < N; i++)
            {
                result += $"({i + 1}; {pointed[i]}) ";
            }
            return result;
        }

        private string FloydWarshall()
        {
            int[,] D = new int[N, N];
            int[,] S = new int[N, N];
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    D[i, j] = matSmezh[i, j];
                    S[i, j] = i + 1;
                    if (i == j) S[i, j] = 0;
                }
            }
            for (int m = 0; m < N; m++)
            {
                for (int i = 0; i < N; i++)
                {
                    if (i == m) continue;
                    for (int j = 0; j < N; j++)
                    {
                        if (j == m || i == j) continue;
                        if (D[i, m] == Inf || D[m, j] == Inf) continue;
                        else if (D[i, m] + D[m, j] < D[i, j])
                        {
                            D[i, j] = D[i, m] + D[m, j];
                            S[i, j] = m + 1;
                        }
                    }
                }
            }
            string result = "";
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    result += $"{D[i, j]}   ";
                }
                result += '\n';
            }
            result += '\n';
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    result += $"{S[i, j]}   ";
                }
                result += '\n';
            }
            return result;
        }
        
        private string Prima()
        {
            var pointed = new Dictionary<int, int>();
            pointed.Add(firstVertexNumber, firstVertexNumber);
            for (int k = 1; k < N; k++)
            {
                int smallestValue = Inf;
                int jSmall = -1;
                int iSmall = -1;
                for (int i = 0; i < N; i++)
                {
                    if (!pointed.ContainsKey(i)) continue;
                    for (int j = 0; j < N; j++)
                    {
                        if (pointed.ContainsKey(j)) continue;
                        if (matSmezh[i, j] < smallestValue)
                        {
                            smallestValue = matSmezh[i, j];
                            jSmall = j;
                            iSmall = i;
                        }
                    }
                }
                if (smallestValue != Inf)
                {
                    pointed.Add(jSmall, iSmall);
                }
            }
            string result = "Рёбра: ";
            for (int i = 1; i < N; i++)
            {
                result += $"{i + 1}-{pointed[i] + 1} ";
            }
            return result;
        }
        private string Krascal()
        {
            var pointed = new List<int>();
            string result = "Рёбра: ";
            int sum = 0;
            while (pointed.Count < N)
            {
                for (int i = 0; i < masReber.Length / 3; i++)
                {
                    if (!(pointed.Contains(masReber[i, 0]) && pointed.Contains(masReber[i, 1])))
                    {
                        result += $"{masReber[i, 0] + 1}-{masReber[i, 1] + 1} ";
                        sum += masReber[i, 2];
                        if (!pointed.Contains(masReber[i, 0])) pointed.Add(masReber[i, 0]);
                        if (!pointed.Contains(masReber[i, 1])) pointed.Add(masReber[i, 1]);
                    }
                }
            }
            result += $"{sum}\nАЛЯРМ не объединяет множества";
            return result;
        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            if (checkBox1.Checked) graphIsOriented = true;
            N = int.Parse(textBox1.Text);
            if (textBox2.Text != "") firstVertexNumber = int.Parse(textBox2.Text) - 1;
            for (int i = 0; i < richTextBox1.TextLength; i++)
            {
                if (richTextBox1.Text[i] == ' ') Nreber++;
            }

            matSmezh = new int[N, N];
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    matSmezh[i, j] = Inf;
                    if (i == j) matSmezh[i, j] = 0;
                }
            }
            masStrReb = richTextBox1.Text.Split(' ');
            masReber = new int[Nreber, 3];
            for (int i = 0; i < Nreber; i++)
            {
                string[] vertex = masStrReb[i].Split(',');
                int a = int.Parse(vertex[0]) - 1;
                int b = int.Parse(vertex[1]) - 1;
                int c = 1;
                if (vertex.Length == 3)
                {
                    c = int.Parse(vertex[2]);
                }
                matSmezh[a, b] = c;
                if (!graphIsOriented) matSmezh[b, a] = c;
                masReber[i, 0] = a;
                masReber[i, 1] = b;
                masReber[i, 2] = c;
            }

            string resultString = "";
            if (radioButton1.Checked)
            {
                resultString = BFS();
            }
            else if (radioButton2.Checked)
            {
                resultString = DFS();
            }
            else if (radioButton3.Checked)
            {
                resultString = Dijkstra();
            }
            else if (radioButton4.Checked)
            {
                resultString = Prima();
            }
            else if (radioButton5.Checked)
            {
                resultString = Krascal();
            }
            else if (radioButton6.Checked)
            {
                resultString = FloydWarshall();
            }
            MessageBox.Show(resultString);
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
