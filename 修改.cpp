#include<bits/stdc++.h> 
using namespace std;
int zhu=0;
//�ۺ����ݿ�
struct database
{
    database(string res)
    {
        db = res;
        next = NULL;
    }
    string db;
    database *next;
} * headdata, *taildata;
//ǰ�� if������
struct frontEvent
{
    frontEvent(string res)
    {
        reason = res;
        next = NULL;
    };
    frontEvent *next; //ָ����һ��ǰ��
    string reason;    //ǰ��
};
//��� then�����������ж��ǰ��
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
    backEvent *next;   //ָ����һ�����
    frontEvent *son;   //ָ��������Ҫ��ǰ��
    string result;     //���
    bool isUsed;       //�Ƿ�ʹ�ù�
    bool isFrontEvent; //�Ƿ�����һ�������ǰ��
};
backEvent *headback, *tailback;
//�ӹ�����ļ����ȡǰ���ͺ��������ǰ���ͺ�����ýṹ��洢��˫������
void readFile(char *file)
{
    //����һ���ļ�����
    fstream jmfile(file);
    //�ж��ļ��Ƿ񱻳ɹ���
    if (!jmfile.is_open())
    {
        cout << "Unable to open myfile";
        system("pause");
        exit(1);
    }
    string temp;
    //����getline()��ȡÿһ��
    while (getline(jmfile, temp))
    {
        backEvent *currentback = NULL;
        frontEvent *currentfront = NULL, *headfront = NULL, *tailfront = NULL;
        istringstream is(temp);
        string s;
        int column = 0;
        while (is >> s)
        {
            //��ÿһ�еĵ�һ���ַ�����ֵ��backeEvent(���)
            if (column == 0)
            {
                //���ͷ�ڵ�Ϊ���ȸ�ֵͷ�ڵ�
                if (headback == NULL)
                {
                	 
                    currentback = tailback = headback = new backEvent(s.c_str());
                    cout<<s.c_str()<<endl;
                    cout<<"��"<<zhu+1<<"��ͷ��"<<headback->result<<endl;zhu++; 
                }
                //���򴴽��µĺ��
                else
                {
                    currentback = new backEvent(s.c_str());
                    cout<<"��"<<zhu+1<<"��ͷ��"<<currentback->result<<endl;zhu++; 
                    tailback->next = currentback;
                    tailback = currentback;
                }
            }
            //��ÿһ�еĳ��˵�һ���ַ�����ֵ��frontEvent(ǰ��)
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
        cout<<"��"<<zhu<<"��ǰ�����У�"; 
        while(headfront!=NULL){
        	cout<<headfront->reason<<" ";
        	headfront=headfront->next; 
		}
		cout<<endl;
    }
}
//����һ�����⣬�����Ϊ���������ǰ����isFrontEvent��Ϊture
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
//�ۺ����ݿ������,�������ַ�������
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
//��ʼ��������
void outputResult()
{
    int flag = 0;
    string flagstring=taildata->db;
    while (flag ==0)
    {
        backEvent *p = headback;
        while (p != NULL)
        {
            //���ʹ�ù���������ֱ������
            if (p->isUsed)
            {
                continue;
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
                //ǰ��������Ҫ�󣬲��Һ���������������ǰ�������ս����ֱ���˳�ѭ����������
                if (q == NULL)
                {
                    p->isUsed = true;
                    database *Data = new database(p->result);
                    taildata->next = Data;
                    taildata = Data;
                    
                    if (p->isFrontEvent == false)
                    {
                        flag=1;
                        cout<<"�ó��Ľ��Ϊ��"<<taildata->db<<endl;
                        break;
                    }
                }
                //��������ǰ����һ��������Ҫ�󣬾��ж���һ�����
                p = p->next;
            }
        }
        if (flagstring==taildata->db)
        {
            cout<<"������֪�ۺ����ݿ��޷��ó��������Ҫ������������ֵ"<<endl;
            flag=1;
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
    database *currentdb=headdata;
    while (currentdb!=NULL)
    {
        cout<<currentdb->db<<endl;
        currentdb=currentdb->next;
    }
    return 0;
}
