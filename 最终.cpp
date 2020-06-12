#include<bits/stdc++.h> 
using namespace std;
int zhu=0;
//综合数据库
struct database
{
    database(string res)
    {
        db = res;
        next = NULL;
    }
    string db;
    database *next;
} * headdata, *taildata, *zhongdata;
//前件 if。。。
struct frontEvent
{
    frontEvent(string res)
    {
        reason = res;
        next = NULL;
    };
    frontEvent *next; //指向下一个前件
    string reason;    //前因
};
//后件 then。。。可以有多个前件
struct backEvent
{
    backEvent(string res)
    {
        result = res;
        next = NULL;
        son = NULL;
        isFrontEvent = false;
        isUsed = false;
    };
    backEvent *next;   //指向下一个后件
    frontEvent *son;   //指向后件所需要的前件
    string result;     //后果
    bool isUsed;       //是否被使用过
    bool isFrontEvent; //是否是另一个后件的前件
};
backEvent *headback, *tailback;
//从规则库文件里获取前件和后件，并将前件和后件利用结构体存储成双层链表
void readFile(char *file)
{
    //创建一个文件对象
    fstream jmfile(file);
    //判断文件是否被成功打开
    if (!jmfile.is_open())
    {
        cout << "Unable to open myfile";
        system("pause");
        exit(1);
    }
    string temp;
    //利用getline()读取每一行
    while (getline(jmfile, temp))
    {
        backEvent *currentback = NULL;
        frontEvent *currentfront = NULL, *headfront = NULL, *tailfront = NULL;
        istringstream is(temp);
        string s;
        int column = 0;
        while (is >> s)
        {
            //把每一行的第一个字符串赋值给backeEvent(后件)
            if (column == 0)
            {
                //如果头节点为空先赋值头节点
                if (headback == NULL)
                {
                	 
                    currentback = tailback = headback = new backEvent(s.c_str());
                    cout<<s.c_str()<<endl;
                    cout<<"第"<<zhu+1<<"个头："<<headback->result<<endl;zhu++; 
                }
                //否则创建新的后件
                else
                {
                    currentback = new backEvent(s.c_str());
                    cout<<"第"<<zhu+1<<"个头："<<currentback->result<<endl;zhu++; 
                    tailback->next = currentback;
                    tailback = currentback;
                }
            }
            //把每一行的除了第一个字符串赋值给frontEvent(前件)
            else if (column == 1)
            {
                headfront = tailfront = new frontEvent(s.c_str());
            }
            else if (column > 1)
            {
                currentfront = new frontEvent(s.c_str());
                tailfront->next = currentfront;
                tailfront = currentfront;
            }
            column++;
        }
        currentback->son = headfront;
        cout<<"第"<<zhu<<"的前件都有："; 
        while(headfront!=NULL){
        	cout<<headfront->reason<<" ";
        	headfront=headfront->next; 
		}
		cout<<endl;
    }
}
//遍历一遍规则库，将后件为其他后件的前件的isFrontEvent设为ture
void judgeFrontEvent()
{
    backEvent *k = headback;
    while (k != NULL)
    {
        backEvent *p = headback;
        while (p != NULL)
        {
            frontEvent *q = p->son;
            while (q != NULL)
            {
                if (k->result == q->reason)
                {
                    k->isFrontEvent = true;
                }
                q = q->next;
            }
            p = p->next;
        }
        k = k->next;
    }
}
//综合数据库的输入,并返回字符串个数
void inputData()
{
    string temp, s;
    database *currentdb;
    getline(cin, temp);
    istringstream is(temp);
    while (is >> s)
    {
        if (headdata == NULL)
        {
            headdata = taildata = new database(s.c_str());
        }
        else
        {
            currentdb = new database(s.c_str());
            taildata->next = currentdb;
            taildata = currentdb;
        }
    }
}
//开始进行推理
void outputResult()
{
    int flag = 0;
    int flagstring=1;
    backEvent *p1=headback;
    database *k1 = headdata;
    while(k1!=NULL){
    	while(p1!=NULL){
    		if(k1->db==p1->result){
    			if(zhongdata==NULL){
    				zhongdata=new database(p1->result);
				}else{
					
					database *currentdb1 = new database(p1->result);
            		zhongdata->next = currentdb1;
            		zhongdata = currentdb1;
				}
			}
			p1=p1->next;
		}
		k1=k1->next; 
	}
    while (flag ==0)
    {
        backEvent *p = headback;
        while (p != NULL)
        {
            //如果使用过这个后件，直接跳过
            if (p->isUsed)
            {
                p=p->next;
            }
            else
            {
                frontEvent *q = p->son;
                while (q != NULL)
                {
                    int qflag = 0;
                    database *k = headdata;
                    while (k != NULL)
                    {
                        if (q->reason == k->db)
                        {
                            qflag = 1;
                            break;
                        }
                        
                        k = k->next;
                    }
                    if (qflag == 0)
                    {
                        break;
                    }
                    q = q->next;
                }
                //前件都符合要求，并且后件不是其他后件的前件即最终结果，直接退出循环，输出结果
                if (q == NULL)
                {
                    p->isUsed = true;
                    
                    if(zhongdata==NULL){
                    	zhongdata=new database(p->result);
					}else{
						database *Data = new database(p->result);
						zhongdata->next = Data;
                    	zhongdata = Data;
					} 
                    database *tail=new database(p->result);
                    taildata->next=tail;
                    taildata=tail;
                    if (p->isFrontEvent == false)
                    {
                        flag=1;
                        flagstring++;
                        cout<<"得出的结果为："<<zhongdata->db<<endl;
                        break;
                    }
                }
                //如果后件中前件有一个不符合要求，就判断下一个后件
                p = p->next;
            }
        }
        if(zhongdata!=NULL&&flag==0){
        	cout<<"得出中间结果为："<<zhongdata->db<<endl;
        	flagstring++;
        	break;
		}
        if (flagstring==1)
        {
            cout<<"根据已知综合数据库无法得出结果，需要继续输入特征值"<<endl;
            flag=1;
            break;
        }
    }
}
int main()
{
    char file[] = "jm.txt";
    readFile(file);
    judgeFrontEvent();
    inputData();
    outputResult();
    // inputData();
    return 0;
}
