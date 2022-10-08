#include <cstring>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;

double rotateDirection = 4;
double scanSpeed = 1000;
double lineDistance = 0.002;
double xStep = 0.2;
double zOffset = 0;
double xStartOffset = 0;
double xEndOffset = 0;
double zSafePos = 10;
double sLimit = 4000;


double char2num(const char *str)
{
    double sum=0,fac=10;
    int negflag=0;
    if(*str)
    {
       if(*str=='-')
        {
            negflag=1;
            str++;
        }
        while(*str!='.' && *str)
        {
            sum=sum*10+int(*str)-48;
            str++;
        }
        str++;
        while(*str)
        {
            sum=sum+(int(*str)-48)/fac;
            fac=fac*10;
            str++;
        }
        if(negflag==1)
            sum=0-sum;

        return sum;
    }
    else
    {
        return 0;
    }
}

char* str2char(string str)
{
    const char *cpCh = str.c_str();
    int nLen = strlen(cpCh);
    char *pCh = new char[nLen + 1];
    strcpy(pCh, cpCh);
    return pCh;
}

void DispPara()
{
    //system("chcp 936");
    system("cls");
    cout << "目前的参数如下 (mm,N,s):" << endl;
    cout << endl;
    cout << "1. 主轴旋转方向 M(3 or 4)\t\t" << rotateDirection << endl;
    cout << "2. 切削速度\t\t\t\t" << scanSpeed << endl;
    cout << "3. 切痕间距\t\t\t\t" << lineDistance << endl;
    cout << "4. X每走多少更新一次转速\t" << xStep << endl;
    cout << "5. Z偏移(程序离焦)\t\t" << zOffset << endl;
    cout << "6. 起始X偏移量\t\t\t" << xStartOffset << endl;
    cout << "7. 结束X偏移量\t\t\t" << xEndOffset << endl;
    cout << "8. Z安全位置\t\t\t" << zSafePos << endl;
    cout << "9. 最高转速限制 (rpm)\t\t" << sLimit << endl;
    cout << endl;
    cout << "要改哪个参数就先输入前面的序号，按回车确定；设置完成后输入0，按回车输出程序。 " << endl;
}

bool EditPara(int cmd)
{
    //system("chcp 936");
    cout << "输入新参数，按回车确定 (整数或小数)" << endl;
    double newPara;
    cin >> newPara;
    switch(cmd)
    {
    case 1:
        {
            if(newPara == 3)
            {
                rotateDirection = 3;
            }
            else if(newPara == 4)
            {
                rotateDirection = 4;
            }
            else
            {
                system("cls");
                cout << "错误：这个数不是3就是4，不能输其他东西。" << endl;
            }
            break;
        }
    case 2:
        {
            if (newPara < 0)
            {
                system("cls");
                cout << "错误：该参数不能为负，想变换转向请改变参数1" << endl;
            }
            else
            {
                scanSpeed = newPara;

            }
            break;
        }
    case 3:
        {

            lineDistance = newPara;

            break;
        }
    case 4:
        {
            if (newPara <= 0)
            {
                system("cls");
                cout << "错误：该参数必须大于0" << endl;
            }
            else
            {
                xStep = newPara;

            }
            break;
        }
    case 5:
        {
            cout << "提示： 负为进刀，正为退刀" << endl;
            zOffset = newPara;
            break;
        }
    case 6:
        {
            if (newPara < 0)
            {
                system("cls");
                cout << "错误：该参数不能为负, 输入值为x空走刚开始空走的距离。" << endl;
            }
            else
            {
                xStartOffset = newPara;
            }
            break;
        }
    case 7:
        {
            if (newPara < 0)
            {
                system("cls");
                cout << "错误：该参数不能为负，输入的值为中间剩下的不加工的圆的半径。" << endl;
            }
            else
            {
                xEndOffset = newPara;
            }
            break;
        }
    case 8:
        {
            zSafePos = newPara;
            break;
        }
    case 9:
        {
            if (newPara < 0)
            {
                system("cls");
                cout << "错误：该参数不能为负." << endl;
            }
            else
            {
                sLimit = newPara;
            }
            break;
        }

    }
    return true;
}

int main()
{
    //cout.imbue(locale("chs"));

    //打开文件
    ifstream inPgm("inpgm.txt",ios::in); //以文本模式打开in.txt备读
    if(!inPgm) { //打开失败
        cout << "在本程序所在的文件夹下没找到 inpgm.txt 这个文件！" << endl;
        cout << "本程序使用方法：" << endl;
        cout << "1. 把DIFFSYS导出的pgm文件用记事本打开保存成文本格式txt，并命名为inpgm.txt" << endl;
        cout << "2. 把inpgm.txt 拿到和我这个文件相同的文件夹下，然后运行我这个程序。" << endl;
        cout << "3. 程序正确运行结束会在相同目录下输出一个outpgm.txt文件。" << endl;
        cout << "4. 打开这个 outpgm.txt 文件，文件-另存为-文件类型选择“全部文件”，然后文件名要带上后缀.pgm，这样就得到程序文件了。" << endl;
        system("pause");
        return 0;
    }
    ofstream outPgm("outpgm.txt",ios::out); //以文本模式打开out.txt备写
    if(!outPgm) {
        inPgm.close(); //程序结束前不能忘记关闭以前打开过的文件
        cout << "打开outpgm时出错." << endl;
        system("pause");
        return 0;
    }

    //system("chcp 936");

    //主界面


    //进入改参数环节
    while(true)
    {
        int cmd = -1;
        DispPara();
        cin >> cmd;
        if(cmd > 0)
        {
            if(!EditPara(cmd))
            {
                system("cls");
                cout << "修改参数失败！" << endl;
                system("pause");
            }
        }
        else if(cmd == 0)
        {
            cout << cmd << endl;
            break;
        }
        else
        {
            system("cls");
            cout << "输入无效！" << endl;
            system("pause");
        }
    }

    //正式运行开始
    bool flag = true;

    string aline;
    string shortline;
    string straim;
    /*inPgm >> straim;//>>>>>>>>>>>>>
    straim = straim.substr(4,1);//string 识别目标
    char charaim = straim.c_str()[0]; //char 识别目标
    int aim = charaim - '0'; //int 识别目标
    int fly;//uatch this and insert S F*/
    char* charx;
    double prevx = 10000;
    double x = 0;
    double z = zSafePos;
    double s;
    double f;

    string sHead;
    if(rotateDirection == 3.0)
    {
        sHead = "M3S";
    }
    else
    {
        sHead = "M4S";
    }
    string fHead = "F";

    //start from the 1st line
    while(inPgm >> aline)//>>>>>>>>>>>>>>>>>>>>>>
    {
        transform(aline.begin(), aline.end(), aline.begin(), ::toupper); // to upper

        //Find X Z position
        int idx_x = aline.find("X");//18995613516
        int idx_z = aline.find("Z");
        x = char2num( str2char(aline.substr(idx_x+1, idx_z-idx_x-1)) );
        z = char2num( str2char(aline.substr(idx_z+1)) );

        /*shortline = aline.substr(4,1); //kan di ji uei
        charaim = shortline.c_str()[0];
        fly = charaim - '0';*/
        if(abs(x) < abs(xEndOffset))
        {
            continue;
        }

        if(abs(x-prevx) >= xStep)
        {
            prevx = x;

            s = 9.549297*scanSpeed/abs(x);
            f = s*lineDistance;

            if(flag)//程序头
            {
                outPgm << "G01\n";
                outPgm << sHead << to_string(s) << '\n';
                outPgm << "T01\nG18 G40 G59\nG71 G90 G81\nM7.1 M7.2\n";
                outPgm << "Z" << to_string(zSafePos+zOffset) << "F200" << endl;
                outPgm << "X" << to_string(x+(x>=0?xStartOffset:-xStartOffset)) << endl;
                outPgm << "Z" << to_string(z+zOffset) << "F50" << endl;
                flag = false;
            }

            // Rotaton Speed Limit
            if(s > sLimit)
            {
                 outPgm << "X" << to_string(x) << "Z" << to_string(z+zOffset) << '\n';
                 continue;
            }

            outPgm << sHead << to_string(s) << '\n';
            outPgm << "X" << to_string(x) << "Z" << to_string(z+zOffset) << fHead << to_string(f) << '\n';

        }
        else
        {
            outPgm << "X" << to_string(x) << "Z" << to_string(z+zOffset) << '\n';
        }

    }

    outPgm << "Z" << zSafePos+zOffset << "F1000" <<endl;
    outPgm << "M9\nM5";//程序尾
    outPgm.close();
    inPgm.close();

    cout << "程序已输出!\n输出的程序在同目录下 outpgm.txt\n";
    system("pause");

    return 0;
}



