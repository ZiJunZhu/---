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
} * headdata, *taildata, *zhongdata;
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
            //���ʹ�ù���������ֱ������
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
                //ǰ��������Ҫ�󣬲��Һ���������������ǰ�������ս����ֱ���˳�ѭ����������
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
                        cout<<"�ó��Ľ��Ϊ��"<<zhongdata->db<<endl;
                        break;
                    }
                }
                //��������ǰ����һ��������Ҫ�󣬾��ж���һ�����
                p = p->next;
            }
        }
        if(zhongdata!=NULL&&flag==0){
        	cout<<"�ó��м���Ϊ��"<<zhongdata->db<<endl;
        	flagstring++;
        	break;
		}
        if (flagstring==1)
        {
            cout<<"������֪�ۺ����ݿ��޷��ó��������Ҫ������������ֵ"<<endl;
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
