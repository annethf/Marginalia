#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAXLEN 6   //最多属性个数

vector<vector<string> > state;   //训练样本
vector<string> item(MAXLEN);      //每一个训练样本
vector<string> attributeRow;      //属性行
string end = "end";                //输入结束
map<string,vector< string > > attributeValues; //属性值

int treeSize = 0;
struct treeNode
{
    string attribute;
    string arrivedValue;
    vector<treeNode *> childs;
    treeNode()
    {
        attribute = "";
        arrivedValue = "";
    }
};
treeNode * root;

void computeMapFrom2DVector()
{
    unsigned int i,j,k;
    bool exited = false;
    vector<string> values;
    for(i = 1; i < MAXLEN - 1; i++)
    {
        for(j = 1; j < state.size(); j++)
        {
            for(k = 0; k < values.size(); k++)
            {
                if(!values[k].compare(state[j][i]))
                    exited = true;
            }
            if(!exited)
            {
                values.push_back(state[j][i]);
            }
            exited = false;
        }
        attributeValues[state[0][i]] = values;
        values.erase(values.begin(), values.end());
    }
}

double computeEntropy(vector<vector<string> > remainState, string attribute, string value, bool ifparent)
{
    vector<int> count (2,0);
    unsigned int i,j;
    bool doneFlag = false;
    for(j = 1; j < MAXLEN; j++)
    {
        if(doneFlag) break;
        if(!attributeRow[j].compare(attribute))
        {
            for(i = 1; i < remainState.size(); i++)
            {
                if((!ifparent && !remainState[i][j].compare(value)) || ifparent)
                {
                    if(!remainState[i][MAXLEN - 1].compare("yes"))
                    {
                        count[0]++;
                    }
                    else count[1]++;
                }
            }
            doneFlag = true;
        }
    }
    if(count[0] == 0 || count[1] == 0 )
        return 0;

    double sum = count[0] + count[1];
    double entropy = -count[0]/sum*log(count[0]/sum)/log(2.0) - count[1]/sum*log(count[1]/sum)/log(2.0);
    return entropy;
}

double computeGain(vector<vector<string> > remainState, string attribute)
{
    unsigned int j,k,m;
    double parentEntropy = computeEntropy(remainState, attribute, "", true);
    double childrenEntropy = 0;

    vector<string> values = attributeValues[attribute];
    vector<double> ratio;
    vector<int> countValues;
    int tempint;
    for(m = 0; m < values.size(); m++)
    {
        tempint = 0;
        for(k = 1; k < MAXLEN - 1; k++)
        {
            if(!attributeRow[k].compare(attribute))
            {
                for(j = 1; j < remainState.size(); j++)
                {
                    if(!remainState[j][k].compare(values[m]))
                    {
                        tempint++;
                    }
                }
            }
        }
        countValues.push_back(tempint);
    }

    for(j = 0; j < values.size(); j++)
    {
        ratio.push_back((double)countValues[j] / (double)(remainState.size()-1));
    }

    double tempEntropy;
    for(j = 0; j < values.size(); j++)
    {
        tempEntropy = computeEntropy(remainState, attribute, values[j], false);
        childrenEntropy += ratio[j] * tempEntropy;
    }
    return (parentEntropy - childrenEntropy);
}

int findAttriNumByName(string attribute)
{
    for(int i = 0; i < MAXLEN; i++)
    {
        if(!state[0][i].compare(attribute))
            return i;
    }
    cerr<<"can't find the attribute"<<endl;
    return 0;
}

string mostCommonLabel(vector<vector<string> > remainState)
{
    int p = 0, n = 0;
    for(unsigned i = 0; i < remainState.size(); i++)
    {
        if(!remainState[i][MAXLEN-1].compare("yes"))
            p++;
        else n++;
    }
    if(p >= n)
        return "yes";
    else
        return "no";
}

bool allTheSameLabel(vector<vector<string> > remainState, string label)
{
    int count = 0;
    for(unsigned int i = 0; i < remainState.size(); i++)
    {
        if(!remainState[i][MAXLEN-1].compare(label))
            count++;
    }
    if(count == remainState.size()-1)
        return true;
    else
        return false;
}

treeNode * bulidDecisionTreeDFS(treeNode * p, vector<vector<string> > remainState, vector<string> remainAttribute)
{
    if(p == NULL)
        p = new treeNode();

    if(allTheSameLabel(remainState, "yes"))
    {
        p->attribute = "yes";
        return p;
    }
    if(allTheSameLabel(remainState, "no"))
    {
        p->attribute = "no";
        return p;
    }
    if(remainAttribute.size() == 0)
    {
        string label = mostCommonLabel(remainState);
        p->attribute = label;
        return p;
    }

    double maxGain = 0, tempGain;
    vector <string>::iterator maxIt = remainAttribute.begin();
    vector <string>::iterator it1;
    for(it1 = remainAttribute.begin(); it1 < remainAttribute.end(); it1++)
    {
        tempGain = computeGain(remainState, (*it1));
        if(tempGain > maxGain)
        {
            maxGain = tempGain;
            maxIt = it1;
        }
    }

    vector <string> newAttribute;
    vector <vector<string> > newState;
    for(vector <string>::iterator it2 = remainAttribute.begin(); it2 < remainAttribute.end(); it2++)
    {
        if((*it2).compare(*maxIt))
            newAttribute.push_back(*it2);
    }

    p->attribute = *maxIt;
    vector <string> values = attributeValues[*maxIt];
    int attribueNum = findAttriNumByName(*maxIt);
    newState.push_back(attributeRow);
    for(vector <string>::iterator it3 = values.begin(); it3 < values.end(); it3++)
    {
        for(unsigned int i = 1; i < remainState.size(); i++)
        {
            if(!remainState[i][attribueNum].compare(*it3))
            {
                newState.push_back(remainState[i]);
            }
        }
        treeNode * newNode = new treeNode();
        newNode->arrivedValue = *it3;
        if(newState.size() == 0)
        {
            newNode->attribute = mostCommonLabel(remainState);
        }
        else
            bulidDecisionTreeDFS(newNode, newState, newAttribute);
        p->childs.push_back(newNode);
        newState.erase(newState.begin()+1,newState.end());
    }
    return p;
}

void inPut()
{
    string str;
    while(cin >> str, str.compare(end) != 0)
    {
        item[0] = str;
        for(int i = 1; i < MAXLEN; i++)
        {
            cin >> item[i];
        }
        state.push_back(item);
    }
    for(int j = 0; j < MAXLEN; j++)
    {
        attributeRow.push_back(state[0][j]);
    }
}

void printTree(treeNode *p, int depth)
{
    for(int i = 0; i < depth; i++)
        cout << '\t';
    if(!p->arrivedValue.empty())
    {
        cout << p->arrivedValue << endl;
        for(int i = 0; i < depth+1; i++)
            cout << '\t';
    }
    cout << p->attribute << endl;
    for(vector<treeNode*>::iterator it = p->childs.begin(); it != p->childs.end(); it++)
    {
        printTree(*it, depth + 1);
    }
}

void freeTree(treeNode *p)
{
    if(p == NULL)
        return;
    for(vector<treeNode*>::iterator it = p->childs.begin(); it != p->childs.end(); it++)
    {
        freeTree(*it);
    }
    delete p;
    treeSize++;
}


int main()
{
    inPut();

    vector <string> remainAttribute;
    //判断是否背包

    string hair = "Hair";
    string clothColor = "ClothColor";
    string glasses = "Glasses";
    string glass = "Glass";
    string phoneColor = "PhoneColor";
    //string bag = "Bag";

    remainAttribute.push_back(hair);
    remainAttribute.push_back(clothColor);
    remainAttribute.push_back(glasses);
    remainAttribute.push_back(glass);
    remainAttribute.push_back(phoneColor);
    //remainAttribute.push_back(bag);


    //判断是否长发
    /*
    string clothColor = "ClothColor";
    string glasses = "Glasses";
    string glass = "Glass";
    string phoneColor = "PhoneColor";
    string bag = "Bag";
    //string hair = "Hair";

    remainAttribute.push_back(clothColor);
    remainAttribute.push_back(glasses);
    remainAttribute.push_back(glass);
    remainAttribute.push_back(phoneColor);
    remainAttribute.push_back(bag);
    //remainAttribute.push_back(hair);
    */

    vector<vector<string> > remainState;
    for(unsigned int i = 0; i < state.size(); i++)
    {
        remainState.push_back(state[i]);
    }

    computeMapFrom2DVector();

    root = bulidDecisionTreeDFS(root,remainState,remainAttribute);
    cout << "the decision tree is :" << endl;
    printTree(root,0);
    freeTree(root);

    cout << endl;
    cout << "treeSize:" << treeSize << endl;
    system("pause");
    return 0;
}
