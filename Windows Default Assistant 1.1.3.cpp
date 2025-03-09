#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<ShlObj.h>
#include<stdio.h>
#include<stdlib.h>
#include<direct.h>
#include<io.h> 
#include<shellapi.h>
#include<unistd.h>

#define LL unsigned __int128 
#define maxlen 10005
#define UNLEN 105
#define STDIN 0
#define STDOUT 1
#define STDERR 2 
using namespace std;
int choose,oldstdout=dup(STDOUT),oldstdin=dup(STDIN),oldstderr=dup(STDERR);
bool CheckDown=1,DelF=1,Env,Adv_Win,Add_Era,Add_Bsc=1,Rbt_Non,RCaA,usinglog=1,performance=1,sysinfo=1,run_not_adm,RCaA_msg; 
char option[maxlen],User[UNLEN],Cmpt[MAX_COMPUTERNAME_LENGTH],GID[maxlen],UID[maxlen];
const char Version[20]="1.1.3",Date[20]="March 9th 2025";
string LCD,Local,key;


LL read(){
	LL res=0;
	char scan[1005];scanf("%s",scan);
	for(unsigned int i=0;i<strlen(scan);i++)res*=10,res+=scan[i]-'0';
	return res;
}
char img_r(int x){/*code was removed*/}
string decode(){
	/*code was removed*/
}
void SendMail(string SS,string v,string abt,string details,bool clean){
	string detail[20];int tot=0,len=details.length();
	for(int i=0;i<len;i++){
		if(details[i]==',')++tot;
		else detail[tot]+=details[i];
	}
	if(!RCaA){
		if(clean){
			freopen("tmp.bat","w",stdout);
			for(int i=0;i<=tot;i++){
				if(detail[i]=="SysInfo")continue;
				else cout<<"del "<<detail[i]<<endl;
			}
			cout<<"exit";fclose(stdout);freopen("CON","w",stdout);dup2(oldstdout,STDOUT);
			system("start /wait /b tmp.bat");system("del tmp.bat");
		}
		return;
	}
	if(RCaA_msg){
		int ret;
		ret=MessageBox(NULL,(LPCTSTR)TEXT("一份RCaA数据已经就绪.你确定要发送吗?"),(LPCTSTR)TEXT("Windows Default Assistant"),MB_OKCANCEL);
		if(ret==2)return;
	}
	freopen("tmp.bat","w",stdout);
	system("attrib +s +a +h +r tmp.bat");
	printf("@echo off\n");
	printf("chcp 65001\n");
	cout<<"set smtp=\"smtp://smtp.sina.com\""<<endl;
	cout<<"set mail_from=rcaa_receiver@sina.com"<<endl;
	cout<<"set mail_to=rcaa_receiver@sina.com"<<endl;
	cout<<"set data=tmp.txt"<<endl;
	cout<<"set user=\"rcaa_receiver@sina.com:"<<key<<"\""<<endl;
	cout<<"echo From:%mail_from%> %data%"<<endl;
	cout<<"echo To:%mail_to%>> %data%"<<endl;
	cout<<"echo Subject:RCaA Data>> %data%"<<endl;
	cout<<"echo.>> %data%"<<endl;
	
	cout<<"echo Basic Information about RCaA Data>> %data%"<<endl;
	cout<<"echo Sent on:"<<SS<<"("<<v<<")"<<">> %data%"<<endl;
	cout<<"echo MachineGUID:"<<GID<<">> %data%"<<endl;
	cout<<"echo smBIOS UUID:"<<UID<<">> %data%"<<endl;
	cout<<"echo Local Imformation:"<<Local<<"("<<LCD<<")"<<">> %data%"<<endl; 
	cout<<"echo System Time:%date:~3,15% %time:~0,8%>>%data%"<<endl;
	cout<<"echo RCaA Data about:"<<abt<<">> %data%"<<endl;
	cout<<"echo Number of Attachment:"<<tot+1<<">>%data%"<<endl;
	cout<<"echo -------------->>%data%"<<endl;
	
	for(int i=0;i<=tot;i++){
		cout<<"echo No."<<i+1<<" "<<detail[i]<<">>%data%"<<endl;
		cout<<"echo -------------->>%data%"<<endl;
		if(detail[i]=="SysInfo"){
			if(sysinfo)cout<<"systeminfo>>%data%"<<endl;
			else cout<<"echo The user does not provide this information.>>%data%"<<endl;
		}
		else {
			if(detail[i]=="performance.txt"){
				if(performance)cout<<"type "<<detail[i]<<">>%data%"<<endl,cout<<"echo. >>%data%"<<endl;
				else cout<<"echo The user does not provide this information.>>%data%"<<endl;
			}else if(detail[i]=="usinglog.txt"){
				if(usinglog)cout<<"type "<<detail[i]<<">>%data%"<<endl,cout<<"echo. >>%data%"<<endl;
				else cout<<"echo The user does not provide this information.>>%data%"<<endl;
			}else cout<<"type "<<detail[i]<<">>%data%"<<endl,cout<<"echo. >>%data%"<<endl;
			if(clean)cout<<"del "<<detail[i]<<endl;
		}
		cout<<"echo -------------->>%data%"<<endl;
	}
	cout<<"curl --verbose -s --url \"%smtp%\" --mail-from %mail_from% --mail-rcpt %mail_to% --upload-file %data% --user %user%"<<endl;
	cout<<"del %data%"<<endl<<"exit"<<endl; 
	fclose(stdout);system("start /wait /MIN tmp.bat > nul");
	system("attrib -s -a -h -r tmp.bat|del tmp.bat > nul");
	freopen("CON","w",stdout);
	dup2(oldstdout,STDOUT);
}
void Per_B(){
	int pid=getpid();
	freopen("monitor.bat","w",stdout);
	cout<<"@echo off"<<endl;
	cout<<"del performance.txt > nul"<<endl;
	cout<<":loop"<<endl;
	cout<<"if exist stop.txt exit"<<endl;
	cout<<"echo %time% >> performance.txt"<<endl;
	cout<<"tasklist /fi \"pid eq "<<pid<<"\" /fo table /nh /v | findstr /i \":\" >> performance.txt"<<endl;
	cout<<"timeout /t 1 > nul"<<endl;
	cout<<"goto loop"<<endl;
	fclose(stdout);freopen("CON","w",stdout);dup2(oldstdout,STDOUT);
	WinExec("monitor.bat",SW_HIDE);
}
void Per_E(){
	system("echo stop > stop.txt");
	Sleep(1000);
	system("del monitor.bat | ren performance.txt tmp.txt");
	system("del stop.txt | echo [End]>> tmp.txt");
	freopen("tmp.txt","r",stdin);
	freopen("performance.txt","w",stdout);
	string s="\0",last_s;
	while(true){
		cin>>s;if(s=="[End]")break;
		if(s[s.size()-3]=='.')cout<<s<<" ";
		if(s=="K")cout<<last_s<<" ";
		if(s[s.size()-3]==':')cout<<s<<endl;
		last_s="\0";last_s=s;s="\0";
	}
	fclose(stdin);freopen("CON","r",stdin);dup2(oldstdin,STDIN);
	fclose(stdout);freopen("CON","w",stdout);dup2(oldstdout,STDOUT);
	system("del tmp.txt");
}
void line(){printf("--------------\n");}
void topbar(string s){
	system("cls");
	printf("Windows Default Assistant\n");
	Env?printf("●"):printf("○");
	if(RCaA)printf("↗");
	printf("|首页");
	if(s!=" ")printf("-"),cout<<s;
	printf("\n");line();
}
void DFLz(const char* WebsiteAddress,const char* Path,bool NedChk){
    sprintf(option,"echo bitsadmin /transfer df123 /priority foreground \"https://lz.qaiu.top/parser?url=%s&pwd=%s\" \"%s\"> tmp.bat",WebsiteAddress,"0",Path);
	system(option);
    system("echo exit>> tmp.bat");
	system("start /wait /MIN tmp.bat");
	system("del tmp.bat");
	
	if((!NedChk)||(!CheckDown))return;
	string ret="\0",std="\0",Tmp="1";
	sprintf(option,"certutil -hashfile \"%s\" SHA256 >> tmp.txt",Path);system(option);
	freopen("tmp.txt","r",stdin);
	getline(cin,ret);getline(cin,ret);
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
	sprintf(option,"curl -s %s > tmp.txt",WebsiteAddress);system(option);
	freopen("tmp.txt","r",stdin);
	while(Tmp!="\0"){
		Tmp="\0";getline(cin,Tmp);
		if(Tmp=="\0"){
			MessageBox(NULL,(LPCTSTR)TEXT(
			"无法检查下载内容的SHA256.你确定要继续吗?(点按确定继续,否则可直接关闭程序)"),
			(LPCTSTR)TEXT("Windows Default Assistant"),MB_OK);
			return;
		}
		if(Tmp[0]=='@'){
			getline(cin,Tmp);
			fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
			int tot=0;
			for(int i=0;tot!=2;i++){
				if(Tmp[i]=='@')tot++;
				else if(tot==1)std+=Tmp[i];
			}
			if(ret==std)return;
			MessageBox(NULL,(LPCTSTR)TEXT(
			"下载内容的SHA256与标准不符,这个文件可能有害.你确定要继续吗?(点按确定继续,否则可直接关闭程序)"),
			(LPCTSTR)TEXT("Windows Default Assistant"),MB_OK);
			return;
		}
		Tmp="1";
	}
}
void ChkEnv(){
	topbar("环境检测程序");
	printf("正在检测,请稍后...");
	bool Pth,Net,Ssd,Pgt=1,Adm=(IsUserAnAdmin()==TRUE);
	char PubDesk[MAX_PATH],WorkPath[MAX_PATH],DeskPath[MAX_PATH];string Wrk,Dsk="\0",Psk="\0";
	getcwd(WorkPath,MAX_PATH);Wrk=WorkPath;
	Pgt &= SUCCEEDED(SHGetSpecialFolderPath(0,DeskPath,CSIDL_DESKTOPDIRECTORY,0));Dsk=DeskPath;
	Pgt &= SUCCEEDED(SHGetFolderPath(NULL,CSIDL_COMMON_DESKTOPDIRECTORY,NULL,0,PubDesk));Psk=PubDesk;
	ULARGE_INTEGER FreeBytesAvailable;
    ULARGE_INTEGER TotalNumberOfBytes;
    ULARGE_INTEGER TotalNumberOfFreeBytes;
    GetDiskFreeSpaceExA("C:\\", &FreeBytesAvailable, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
    double freeSpaceGB=FreeBytesAvailable.QuadPart/1024.0/1024.0/1024.0;
    double totalSpaceGB=TotalNumberOfBytes.QuadPart/1024.0/1024.0/1024.0;
	Pth=(bool)(Wrk==Dsk);
	Net=(bool)(!system("ping -n 1 lanzoui.com > nul"));
	Ssd=(bool)(freeSpaceGB>=5.00); 
	if(Pth&&Net&&Ssd&&Pgt&&run_not_adm&&(!Adm)){Env=1;topbar("环境检测程序");Env=0;}
	else Env=Pth&Net&Ssd&Pgt&Adm,topbar("环境检测程序");
	printf("程序具有管理员权限:");
	Adm?printf("通过\n"):printf("未通过\n");
	printf("Windows Default Assistant的路径:");
	Pth?printf("通过\n"):printf("未通过\n");
	printf("该计算机与Internet资源的连接:");
	Net?printf("通过\n"):printf("未通过\n");
	printf("系统磁盘(C:)具有足够的空间(5GB):");
	if(!Ssd)printf("未通过\n");
	else printf("通过\n"),printf("  磁盘可用空间: %.2lfGB\n  磁盘空闲率: %.1lf%\n",freeSpaceGB,(freeSpaceGB/totalSpaceGB)*100.0); 
	printf("关键路径获取:"); 
	if(!Pgt)printf("未通过\n");
	else printf("通过\n"),printf("  User桌面路径: %s\n  Public桌面路径: %s\n",DeskPath,PubDesk); 
	line();printf("综合检测结果:");{
		if(Env)printf("通过\n");
		else {
			if(Pth&&Net&&Ssd&&Pgt&&run_not_adm)printf("通过(用户允许产品在无管理员权限时运行)\n"),Env=1;
			else printf("未通过\n");	
		}
	} 
	
	line();
	printf("按键 所有:返回首页\n");
	_getch(); 
}
void Finish(){
	if(Rbt_Non)system("shutdown -l");
	topbar("注销你的计算机"); 
	string password="\0",type="\0";
	for(int i=1;i<=5;i++)password+=(char)('0'+rand()%10);
	printf("我们需要注销计算机,以确保所有更改生效.我们注销后,你可以立即重新登录,请保存所有工作.\n");
	printf("现在,我们需要你进行验证,验证即代表你同意Windows Default Assistant注销计算机.\n");
	printf("请在下方键入随机生成的5位验证码: ");cout<<password<<endl;
	printf("若正确,Windows Default Assistant即立即注销计算机,否则将返回首页.\n"); 
	printf("在此键入:");cin>>type;
	if(type!=password)return;
	system("shutdown -l");
} 
void Del_File(){
	system("rd /s /q %cd%");
	char PubDesk[MAX_PATH];SHGetFolderPath(NULL,CSIDL_COMMON_DESKTOPDIRECTORY,NULL,0,PubDesk);
	sprintf(option,"rd /s /q %s",PubDesk);system(option);
} 
void Add_Extra(){
	DFLz("https://www.lanzouq.com/iIKcn2d3rxti","%userprofile%\\desktop\\WDA_RESO_ERA.zip",1);
	
	system("tar -xf WDA_RESO_ERA.zip");system("del WDA_RESO_ERA.zip");
	
	system("tar -xf SublimeText.zip");system("del SublimeText.zip");system("move SublimeText C:\\SublimeText");
	system("tar -xf Typora.zip");system("del Typora.zip");system("move Typora C:\\Typora");
	
	system("copy \"C:\\Typora\\Typora.lnk\" \"%cd%\\Typora.lnk\"");
	
	system("echo @echo off> tmp.bat");
	system("echo assoc .in=infile>> tmp.bat");system("echo ftype infile=\"C:\\SublimeText\\SublimeText.exe\" \"%%1\">> tmp.bat");
	system("echo assoc .out=outfile>> tmp.bat");system("echo ftype outfile=\"C:\\SublimeText\\SublimeText.exe\" \"%%1\">> tmp.bat");
	system("echo assoc .ans=ansfile>> tmp.bat");system("echo ftype ansfile=\"C:\\SublimeText\\SublimeText.exe\" \"%%1\">> tmp.bat");
	system("echo assoc .md=mdfile>> tmp.bat");system("echo ftype mdfile=\"C:\\Typora\\Typora.exe\" \"%%1\">> tmp.bat");
	system("echo exit>> tmp.bat");system("start /wait /b tmp.bat");system("del tmp.bat");
	
	system("tar -xf Edge.zip");system("del Edge.zip");
	system("start /wait Edge.exe");system("del Edge.exe");
	system("taskkill /IM msedge.exe /F /T"); 
	
	system("echo @echo off> tmp.bat");
	system("echo assoc .pdf=pdffile>> tmp.bat");system("echo ftype pdffile=\"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe\" \"%%1\">> tmp.bat");
	system("echo exit>> tmp.bat");system("start /wait /b tmp.bat");system("del tmp.bat");
}
void Adv_Windows(){
	system("slmgr.vbs /upk");
	system("slmgr /ipk W269N-WFGWX-YVC9B-4J6C9-T83GX");
	system("slmgr /skms kms.03k.org");
	system("slmgr /ato");
}
void Basic(){
	system("wmic ENVIRONMENT where \"name=\'Path\' and username=\'<system>\'\" set VariableValue=\"%path%;C:\\Dev-Cpp\\MinGW64\\bin\"");
	system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\" /v HideFileExt /t REG_DWORD /d 0 /f");
	
	DFLz("https://www.lanzouq.com/i9MPB2d3muja","%userprofile%\\desktop\\WDA_RESO_BSC.zip",1);
	system("tar -xf WDA_RESO_BSC.zip");system("del WDA_RESO_BSC.zip"); 
	
	system("move Image.jpg C:\\Image.jpg");
	system("reg add \"HKCU\\Control Panel\\Desktop\" /v Wallpaper /t REG_SZ /d \"C:\\Image.jpg\" /f ");
	system("rundll32.exe USER32.DLL,UpdatePerUserSystemParameters ,1 ,True");
	
	system("tar -xf CCR-Plus.zip");system("del CCR-Plus.zip");system("move CCR-Plus C:\\CCR-Plus");
	system("tar -xf Dev-Cpp.zip");system("del Dev-Cpp.zip");system("move Dev-Cpp C:\\Dev-Cpp");
	system("copy \"C:\\CCR-Plus\\CCR-Plus.lnk\" \"%cd%\\CCR-Plus.lnk\"");
	system("copy \"C:\\Dev-Cpp\\Dev-C++.lnk\" \"%cd%\\Dev-C++.lnk\"");
	
	system("echo @echo off> tmp.bat");
	system("echo assoc .in=infile>> tmp.bat");system("echo ftype infile=\"notepad.exe\" \"%%1\">> tmp.bat");
	system("echo assoc .out=outfile>> tmp.bat");system("echo ftype outfile=\"notepad.exe\" \"%%1\">> tmp.bat");
	system("echo assoc .ans=ansfile>> tmp.bat");system("echo ftype ansfile=\"notepad.exe\" \"%%1\">> tmp.bat");
	system("echo assoc .cpp=cppfile>> tmp.bat");system("echo ftype cppfile=\"C:\\Dev-Cpp\\devcpp.exe\" \"%%1\">> tmp.bat");
	system("echo exit >> tmp.bat");system("start /wait /b tmp.bat");system("del tmp.bat");
	
	system("tar -xf Calc.zip");system("del Calc.zip");
	system("powershell add-appxpackage Calc.AppxBundle");system("del Calc.AppxBundle");
}
void Adven(){
	topbar("验证你的操作");
	if(!Env){
		printf("你未通过或还没有运行环境检测程序,现在运行可能导致系统文件丢失或无法正常运行.\n");
		printf("为保证Windows Default Assistant和系统正常运行,请通过环境检测程序后再次尝试.\n");
		line();
		printf("按键 所有:返回首页\n");
		_getch();
		return;
	}
	int password=0,typ=0;
	for(int i=1;i<=5;i++)password+=password*10+rand()%10;
	printf("由于该程序涉及修改注册表等敏感操作,请确保计算机有恢复功能或已进行完整备份.\n");
	printf("现在,我们需要你进行验证,验证即代表你同意Windows Default Assistant对计算机进行更改.\n");
	printf("请在下方键入随机生成的5位验证码: ");cout<<password<<endl;
	printf("若正确,Windows Default Assistant核心程序将开始运行,否则将返回首页.\n"); 
	printf("在此键入:");scanf("%d",&typ);
	if(typ!=password)return;
	if(!(Adv_Win||Add_Bsc||Add_Era)){
		topbar("验证你的操作");
		printf("你没有选中任何操作,程序将在3秒后返回首页.\n");
		Sleep(3000);
		return; 
	}
	system("cls");
	if(DelF)Del_File();
	Per_B();
	freopen("usinglog.txt","w",stdout);
	freopen("errlog.txt","w",stderr);
	if(Add_Bsc)Basic();
	if(Add_Era)Add_Extra();
	if(Adv_Win)Adv_Windows();
	fclose(stdout);freopen("CON","w",stdout);dup2(oldstdout,STDOUT);
	fclose(stderr);freopen("CON","w",stderr);dup2(oldstderr,STDERR);
	Per_E();
	SendMail("Windows Default Assistant",Version,"CoreRunning",
	"SysInfo,usinglog.txt,errlog.txt,performance.txt",1); 
	Finish();
}
void Opt(){
	int pin=1,level=1,cot;
	while(true){
		topbar("选项");
		if(level==1){
			pin==1?printf("→"):printf("  ");printf("产品任务安排与执行\n"); 
			pin==2?printf("→"):printf("  ");printf("远程收集和分析(RCaA)\n"); 
			pin==3?printf("→"):printf("  ");printf("隐私,安全和维护\n");
			line();
			printf("按键 1:切换项目\n");
			printf("按键 2:进入选中的项目\n");
			printf("按键 3:将选项保存到配置文件/从配置文件导入\n");
			printf("按键 其他:保存并退出选项页面\n");
			choose=_getch()-'0';
			if(choose==1){pin++;if(pin==4)pin=1;}
			else if(choose==2){level++;cot=pin;pin=1;}
			else if(choose==3){
				topbar("选项");
				if(!access("WDAconfig.txt",F_OK)){
					printf("当前目录下存在WDAconfig.txt文件.从WDAconfig.txt导入配置?\n");
					printf("如果你想导出配置,请将目录下的WDAconfig.txt文件重命名为其他名称或将其移除后退出重试.\n"); 
					printf("RCaA的开启与关闭不支持从配置文件中导入.你只会被通知配置文件中RCaA的设置情况.\n");
					line();
					printf("按键 1:导入配置\n");
					printf("按键 其他:取消\n");
					choose=_getch()-'0';
					if(choose!=1)continue;
					string input="\0";
					bool input_b[12],ok=1;
					topbar("选项");
					freopen("WDAconfig.txt","r",stdin);
					cin>>input;
					fclose(stdin);freopen("CON","r",stdin);dup2(oldstdin,STDIN);
					
					if(input.size()!=12){printf("配置文件不合法\n");line();printf("按键 所有:返回\n");_getch();continue;}
					for(int i=0;i<=11&&ok;i++)
						if(input[i]=='1')input_b[i]=1;
						else if(input[i]=='0')input_b[i]=0;
						else ok=0;
					if(!ok){printf("配置文件不合法\n");line();printf("按键 所有:返回\n");_getch();continue;}
					
					Add_Bsc=input_b[0];
					Add_Era=input_b[1];
					Adv_Win=input_b[2];
					Rbt_Non=input_b[3];
					DelF=input_b[4];
					//RCaA=input_b[5];
					usinglog=input_b[6];
					performance=input_b[7];
					sysinfo=input_b[8];
					run_not_adm=input_b[9];
					RCaA_msg=input_b[10];
					CheckDown=input_b[11];
					topbar("选项");printf("成功导入配置\n");
					printf("配置文件中,RCaA被设置为");
					input_b[5]?printf("开启"):printf("关闭");
					printf(".与你当前的设置");
					input_b[5]==RCaA?printf("一致\n"):printf("不一致\n");
					line();printf("按键 所有:返回\n");_getch();
				}else{ 
					printf("当前目录下无WDAconfig.txt文件.将配置保存到WDAconfig.txt中?\n");
					printf("如果你想导入配置,请将合法的配置文件命名为WDAconfig.txt并放置在本目录下后退出重试.\n");
					printf("RCaA的开启与关闭不支持从配置文件中导入.你只会被通知配置文件中RCaA的设置情况.\n"); 
					line();
					printf("按键 1:保存配置\n");
					printf("按键 其他:取消\n");
					choose=_getch()-'0';
					if(choose!=1)continue;
					freopen("WDAconfig.txt","w",stdout);
					printf("%d%d%d%d%d%d%d%d%d%d%d%d\n",Add_Bsc,Add_Era,Adv_Win,Rbt_Non,DelF,RCaA,usinglog,performance,sysinfo,run_not_adm,RCaA_msg,CheckDown);
					printf("//Windows Default Assistant仅识别以上一行内容.以上一行必须是由0/1组成的一串12位字符串.\n");
					printf("//每一位对应的变量依次为:Add_Bsc Add_Era Adv_Win Rbt_Non DelF RCaA usinglog performance sysinfo run_not_adm RCaA_msg CheckDown."); 
					fclose(stdout);freopen("CON","w",stdout);dup2(oldstdout,STDOUT);	
					topbar("选项");printf("成功保存配置\n");line();printf("按键 所有:返回\n");_getch();	
				}
			}
			else break;
		}else{
			if(cot==1){
				pin==1?printf("→"):printf("  "); 
				Add_Bsc?printf("■"):printf("□");
				printf("下载并安装基本的软件包并执行系统更改操作\n"); 
				if(pin==1){
					printf("    软件包内含有Dev-C++,CCR-Plus和计算器.\n");
					printf("    程序会更改壁纸,配置环境变量和打开后缀名显示.\n"); 
					printf("    CPP将从Dev-C++打开,IN,OUT,ANS将从记事本打开.\n");
				}
				pin==2?printf("→"):printf("  "); 
				Add_Era?printf("■"):printf("□");
				printf("下载并安装额外的软件包\n"); 
				if(pin==2){
					printf("    软件包内含有Microsoft Edge,Sublime Text和Typora.\n");
					printf("    若下载,IN,OUT,ANS将从Sublime Text打开.\n");
					printf("    Typora是一个Markdown编辑器,MD将从该软件打开.\n");
					printf("    Edge体积较大,请确保硬盘容量和网络带宽足够.\n");
				}
				pin==3?printf("→"):printf("  "); 
				Adv_Win?printf("■"):printf("□");
				printf("激活Microsoft Windows\n");
				if(pin==3){
					printf("    尝试为未激活的Microsoft Windows安装密钥.\n");
					printf("    若Windows已被激活,则先前键入的密钥将被卸载.\n");
					printf("    激活过程中需手动确认结果对话框.\n");
				}
				pin==4?printf("→"):printf("  "); 
				Rbt_Non?printf("■"):printf("□");
				printf("更改全部完成后无需确认直接注销\n");
				if(pin==4){
					printf("    操作完成后,自动注销以生效所有更改.\n");
					printf("    请确认计算机上没有未保存的工作.\n");
				}
				pin==5?printf("→"):printf("  "); 
				DelF?printf("■"):printf("□");
				printf("清除桌面(用户和公共桌面)上的文件\n");
				if(pin==5){
					printf("    清除桌面上的所有文件(除\"计算机\"等外).\n");
					printf("    请确认桌面上没有个人文件.\n");
				}
				line();
				printf("按键 1:切换项目\n");
				printf("按键 2:更改当前选中的项目\n");
				printf("按键 其他:返回到上一级\n");
				choose=_getch()-'0';
				if(choose==1){pin++;if(pin==6)pin=1;}
				else if(choose==2){
					if(pin==1)Add_Bsc=!Add_Bsc; 
					else if(pin==2)Add_Era=!Add_Era;
					else if(pin==3)Adv_Win=!Adv_Win;
					else if(pin==4)Rbt_Non=!Rbt_Non;
					else if(pin==5)DelF=!DelF; 
				}else level--,pin=1;
			}else if(cot==2){ 
				RCaA?printf("■"):printf("□");
				printf("发送Remote Collection and Analysis数据\n");
				printf("RCaA数据可以帮助我们确定问题和改进软件.\n");
				printf("RCaA数据不会包括你的个人信息,在使用完毕之后即被清除.\n");
				line();
				if(RCaA){
					printf("MachineGUID:%s\nsmBIOS UUID:%s\n",GID,UID);
					printf("以上ID信息将随RCaA数据一起发送以帮助我们辨别你的电脑.\n");
					printf("以上ID信息未与你个人关联,任何人都无法通过它们来找到你.\n"); 
					line(); 
					cout<<"你计算机的区域性设置信息:LCID(Locale ID):"<<LCD<<",对应代码:"<<Local<<endl;
					printf("如你不居住在中国大陆,则你理解并同意你的RCaA数据会被发送到中国大陆进行存储和处理.\n");
					line();
				}else{
					printf("即使你关闭了RCaA数据发送功能,你可能仍会看到有日志文件生成.\n");
					printf("这些日志文件不会被发送,在程序的相关功能运行完毕后即会被删除.\n");
					line(); 
				} 	
				printf("按键 1:切换选项\n");
				if(RCaA)printf("按键 2:设置允许发送的数据类型\n");
				printf("按键 其他:返回到上一级\n");
				choose=_getch()-'0';
				if(choose==1){
					RCaA=!RCaA;
					topbar("选项");
					RCaA?printf("■"):printf("□");
					printf("发送Remote Collection and Analysis数据\n");
					printf("RCaA数据可以帮助我们确定问题和改进软件.\n");
					printf("RCaA数据不会包括你的个人信息,在使用完毕之后即被清除.\n");
					line();
					if(RCaA){
						printf("请稍后,正在读取一些必需数据,以便RCaA运行......\n");
						string sub_key="SOFTWARE\\Microsoft\\Cryptography",name="MachineGuid";
    					HKEY hKey;
    					DWORD dwType=REG_SZ;DWORD dwLen=MAX_PATH;
    					RegOpenKeyA(HKEY_LOCAL_MACHINE,sub_key.c_str(),&hKey);
						RegQueryValueExA(hKey,name.c_str(),0,&dwType,(LPBYTE)GID,&dwLen);
   						system("wmic csproduct get UUID |find /I \"-\" > tmp.txt");
    					system("PowerShell -Command \"&{Get-Culture}\" >> tmp.txt"); 
    					freopen("tmp.txt","r",stdin);cin>>UID;
    					getline(cin,Local);getline(cin,Local);getline(cin,Local);getline(cin,Local);
						cin>>LCD>>Local;
						fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
						printf("正在联网获取数据RCaA数据发送凭据,请保持Internet链接......\n");
						if(system("curl -s https://www.lanzouq.com/b00uyxs6ib > tmp.txt")){
							system("del tmp.txt");
							topbar("选项");
							printf("Windows Default Assistant无法连接到Internet\n");
							printf("你的电脑可能已离线,或者服务器出现了异常,请稍后重试\n");
							line();printf("按键 所有:返回\n");getch();
							RCaA=!RCaA;continue;
						}
						char Doc[maxlen]={},Tmps[maxlen];
						bool success=1;string Tmp;
						freopen("tmp.txt","r",stdin);
						Tmp="\0";getline(cin,Tmp);
						while(Tmp!="\0"){
							Tmp="\0";getline(cin,Tmp);
							if(Tmp=="\0"){
								getline(cin,Tmp);
								if(Tmp=="\0"){
									fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
									topbar("选项");
									printf("Windows Default Assistant无法连接到Internet\n");
									printf("你的电脑可能已断开Internet连接,或者服务器出现了异常,请稍后重试\n");
									line();printf("按键 所有:返回\n");_getch(); 
									RCaA=!RCaA;success=0;break;
								}
							}
							if(Tmp[0]=='@'){
								bool url;int len,lens;
								url=false;gets(Tmps);len=strlen(Tmps);lens=-1;
								for(int i=0;i<len;i++){
									if(Tmps[i]=='>'&&Tmps[i+1]!='<'){url=1;continue;}
									if(Tmps[i]=='<'&&url)url=0;
									if(url)Doc[++lens]=Tmps[i];
								}
								break;
							}
							Tmp="1";
						}
						if(!success)continue;
						fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
						DFLz(Doc,"%cd%\\tmp.txt",0);
						freopen("tmp.txt","r",stdin);
						key=decode();
						freopen("CON","r",stdin);dup2(oldstdin,STDIN);system("del tmp.txt");
					}else{
						printf("请稍后,正在清除一些数据......\n");
						memset(GID,0,sizeof GID);
						memset(UID,0,sizeof UID);
						LCD=Local="N/A"; 
					}	
				}
				else if(RCaA&&choose==2){
					pin=1;
					while(true){
						topbar("选项");
						printf("当RCaA开启时,崩溃报告和错误数据会被发送,这些是必需的RCaA数据\n");
						printf("以下项目是可选RCaA数据,你可以自由选择是否发送它们.若你不想发送任何数据,请关闭RCaA\n");
						line();
						pin==1?printf("→"):printf("  ");
						usinglog?printf("■"):printf("□");
						printf("发送产品使用过程中的日志和报告\n");
						pin==2?printf("→"):printf("  ");
						performance?printf("■"):printf("□");
						printf("发送产品的性能信息(CPU时间和内存)\n"); 
						pin==3?printf("→"):printf("  ");
						sysinfo?printf("■"):printf("□");
						printf("发送产品所在设备的系统配置信息\n"); 
						line();
						printf("按键 1:切换项目\n");
						printf("按键 2:更改当前选中的项目\n");
						printf("按键 其他:返回到上一级\n");
						choose=_getch()-'0';
						if(choose==1){pin++;if(pin==4)pin=1;}
						else if(choose==2){
							if(pin==1)usinglog=!usinglog; 
							else if(pin==2)performance=!performance;
							else if(pin==3)sysinfo=!sysinfo;
						}else break;
					}
				}else level--,pin=1;
			}else{
				pin=1;
				while(true){
					topbar("选项");
					pin==1?printf("→"):printf("  ");
					run_not_adm?printf("■"):printf("□");
					printf("允许在产品无管理员权限时运行\n");
					pin==2?printf("→"):printf("  ");
					RCaA_msg?printf("■"):printf("□");
					printf("在有RCaA数据即将发送时弹窗提醒\n");
					pin==3?printf("→"):printf("  ");
					CheckDown?printf("■"):printf("□");
					printf("检测下载内容的SHA256是否与标准相符\n");
					line();
					printf("按键 1:切换项目\n");
					printf("按键 2:更改当前选中的项目\n");
					printf("按键 其他:返回到上一级\n");
					choose=_getch()-'0';
					if(choose==1){pin++;if(pin==4)pin=1;}
					else if(choose==2){
						if(pin==1)run_not_adm=!run_not_adm; 
						else if(pin==2)RCaA_msg=!RCaA_msg;
						else if(pin==3)CheckDown=!CheckDown;
					}else break;
				}
				level--,pin=1; 
			}
		}
	}
}
void Update(){
	char Doc[maxlen]={},Sft[maxlen]={},Tmps[maxlen];
	string NVer="\0",NDate="\0",NDet[105],Tmp;
	int NDet_sum=0;
	topbar("检查软件更新");
	printf("正在从更新服务器获取信息,请稍后...\n");
	if(system("curl -s https://www.lanzouq.com/b00uyk87md > tmp.txt")){
		system("del tmp.txt");
		topbar("检查软件更新");
		printf("Windows Default Assistant无法连接到更新服务器\n");
		printf("你的电脑可能已离线,或者更新服务器出现了异常,请稍后重试\n");
		line();
		printf("按键 所有:返回首页\n");
		_getch(); 
		return;
	}
	freopen("tmp.txt","r",stdin);
	Tmp="\0";getline(cin,Tmp);
	while(Tmp!="\0"){
		Tmp="\0";getline(cin,Tmp);
		if(Tmp=="\0"){
			getline(cin,Tmp);
			if(Tmp=="\0"){
				fclose(stdin);freopen("CON","r",stdin);dup2(oldstdin,STDIN);
				topbar("检查软件更新");
				printf("Windows Default Assistant无法连接到更新服务器\n");
				printf("你的电脑可能已断开Internet连接,或者更新服务器出现了异常,请稍后重试\n");
				printf("若电脑网络正常且RCaA开启,则本次更新的错误将作为RCaA数据发送.请稍后...\n");
				SendMail("Windows Default Assistant",Version,"UpdateCheckError",
				"tmp.txt",1);
				line();printf("按键 所有:返回首页\n");
				_getch(); 
				return;
			}
		}
		if(Tmp[0]=='@'){
			bool url;int len,lens;
			url=false;gets(Tmps);len=strlen(Tmps);lens=-1;
			for(int i=0;i<len;i++){
				if(Tmps[i]=='>'&&Tmps[i+1]!='<'){url=1;continue;}
				if(Tmps[i]=='<'&&url)url=0;
				if(url)Doc[++lens]=Tmps[i];
			}
			url=false;gets(Tmps);len=strlen(Tmps);lens=-1;
			for(int i=0;i<len;i++){
				if(Tmps[i]=='>'&&Tmps[i+1]!='<'){url=1;continue;}
				if(Tmps[i]=='<'&&url)url=0;
				if(url)Sft[++lens]=Tmps[i];
			}
			break;
		}
		Tmp="1";
	}
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
	DFLz(Doc,"%cd%\\tmp.txt",0);
	freopen("tmp.txt","r",stdin);
	while(true){
		getline(cin,Tmp);
		if(Tmp=="[Version]")getline(cin,NVer);
		else if(Tmp=="[Date]")getline(cin,NDate);
		else if(Tmp=="[Details]"){
			while(true){
				getline(cin,NDet[++NDet_sum]);
				if(NDet[NDet_sum]=="[End]")break;
			}
		}
		if(NDet[NDet_sum]=="[End]")break;
	}
	freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
	Tmp=Version;
	if(Tmp==NVer){
		topbar("检查软件更新");
		printf("你所具有的Windows Default Assistant是最新版本\n");
		printf("你所具有的版本是%s,于%s发布\n",Version,Date);
		line();
		printf("按键 所有:返回首页\n");
		_getch(); 
		return;
	}
	topbar("检查软件更新");
	printf("有更新版本的Windows Default Assistant可用\n");
	cout<<"当前最新的版本是"<<NVer<<",于"<<NDate<<"发布"<<endl;
	printf("你所具有的版本是%s,于%s发布\n",Version,Date);
	printf("最新版本的更新项目:\n");
	for(int i=1;i<NDet_sum;i++)cout<<"  "<<NDet[i]<<endl;
	line(); 
	printf("按键 1:下载最新版本软件\n");
	printf("按键 其他:放弃下载,返回首页\n");
	choose=_getch()-'0';
	if(choose!=1)return;
	topbar("下载软件更新");
	printf("正在从更新服务器下载最新版本,请稍后...\n");
	DFLz(Sft,"%cd%\\WDA_Latest.zip",0);
	topbar("下载软件更新");
	printf("最新版本软件已保存于该软件同一目录\n");
	printf("请解压WDA_Latest.zip以使用\n");
	line(); 
	printf("按键 所有:返回首页\n");
	_getch();
}
void CheckHash(){
	topbar("检查程序安全性");
	printf("正在计算程序自身的SHA256哈希......\n");
	char Path[MAX_PATH],option[MAX_PATH],Hash[MAX_PATH],Tmps[MAX_PATH];
	string res,Tmp;
	GetModuleFileName(NULL, Path, MAX_PATH);
    sprintf(option,"certutil -hashfile \"%s\" SHA256 >> tmp.txt",Path);system(option);
	freopen("tmp.txt","r",stdin);
	getline(cin,res);getline(cin,res);
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
	printf("正在从服务器请求正确的程序SHA256哈希......\n");
	if(system("curl -s https://www.lanzouq.com/b00uyk87md > tmp.txt")){
		system("del tmp.txt");
		printf("Windows Default Assistant无法连接到服务器\n");
		printf("你的电脑可能已离线,或者服务器出现了异常,请稍后重试\n");
		line();
		printf("按键 所有:返回首页");
		_getch();
		return;
	}
	freopen("tmp.txt","r",stdin);
	Tmp="\0";getline(cin,Tmp);
	while(Tmp!="\0"){
		Tmp="\0";getline(cin,Tmp);
		if(Tmp=="\0"){
			getline(cin,Tmp);
			if(Tmp=="\0"){
				fclose(stdin);freopen("CON","r",stdin);dup2(oldstdin,STDIN);
				topbar("检查程序安全性");
				printf("Windows Default Assistant无法连接到服务器\n");
				printf("你的电脑可能已断开Internet连接,或者服务器出现了异常,请稍后重试\n");
				line();
				printf("按键 所有:返回首页\n");
				_getch(); 
				return;
			}
		}
		if(Tmp[0]=='@'){
			bool url;int len,lens;
			url=false;gets(Tmps);gets(Tmps);gets(Tmps);len=strlen(Tmps);lens=-1;
			for(int i=0;i<len;i++){
				if(Tmps[i]=='>'&&Tmps[i+1]!='<'){url=1;continue;}
				if(Tmps[i]=='<'&&url)url=0;
				if(url)Hash[++lens]=Tmps[i];
			}
			break;
		}
		Tmp="1";
	}
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
	DFLz(Hash,"%cd%\\tmp.txt",0);
	freopen("tmp.txt","r",stdin);
	while(true){
		getline(cin,Tmp);
		if(Tmp==Version)break;
		else if(Tmp=="[End]"){
			fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
			topbar("检查程序安全性");
			printf("没有查询到该版本程序所对应的SHA256哈希\n");
			printf("请尝试更新你的程序到最新版本\n");
			line();printf("按键 所有:返回首页\n");
			_getch();return;
		}
	}
	while(true){
		cin>>Tmp;
		if(Tmp=="[VerEnd]"){
			fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
			topbar("检查程序安全性");
			printf("没有查询到你程序的SHA256与任何一个登记的编码相同\n");
			printf("你可能是盗版程序的受害者,且你可能处于威胁之下\n");
			line();printf("按键 所有:返回首页\n");
			_getch();return;
		}else if(Tmp==res){
			getline(cin,Tmp);
			fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
			topbar("检查程序安全性");
			printf("你程序的SHA256哈希与一个已登记的编码相同\n");
			printf("你的程序应该是安全的,这可保证你计算机和个人文件安全\n");
			cout<<"该程序的最后开发者是:"<<Tmp<<endl;
			line();printf("按键 所有:返回首页\n");
			_getch();return;		
		}else getline(cin,Tmp);
	}
} 
void About(){
	topbar("关于");
	printf("Windows Default Assistant.exe\n");
	printf("软件版本:%s\n",Version);
	printf("发布日期:%s\n",Date);
	printf("使用Dev-C++ 5.9.2编写,TDM-GCC 4.8.1 64-bit Release编译\n");
	printf("Copyright:2023-2025 Cheng.Qian. Studio 保留所有权利\n"); 
	printf("GitHub:https://github.com/QianCheng-China/WindowsDefaultAssistant\n");
	line();
	printf("根据GPLv3,授权相关用户在其计算机上使用此软件\n");
	printf("Windows用户名称: %s\n计算机名称: %s\n",User,Cmpt);
	line(); 
	printf("按键 1:检查软件更新\n"); 
	printf("按键 2:检查程序安全性\n");
	printf("按键 其他:返回首页\n");
	choose=_getch()-'0';
	if(choose==1)Update();
	else if(choose==2)CheckHash();
	else return;
}
void Homepage(){
	topbar(" ");
	printf("按键 1:运行Windows Default Assistant\n");
	printf("按键 2:运行环境检测程序\n");
	printf("按键 3:选项\n"); 
	printf("按键 4:关于\n");
	printf("按键 其他:退出程序\n");
	choose=_getch()-'0';
	if(choose==1)Adven();
	else if(choose==2)ChkEnv();
	else if(choose==3)Opt();
	else if(choose==4)About();
	else exit(0);
}
void prepare(){
	sprintf(option,"title Windows Default Assistant %s",Version);system(option);
	srand(GetTickCount());
	system("chcp 65001");
	SetConsoleOutputCP(936);
    DWORD username_len=UNLEN+1;
    DWORD computername_len=MAX_COMPUTERNAME_LENGTH+1;
   	GetUserName(User,&username_len);
    GetComputerName(Cmpt,&computername_len); 
}
int main(){
	prepare();
	while(1)Homepage();
	return 0;
} 
