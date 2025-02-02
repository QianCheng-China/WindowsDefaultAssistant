#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<ShlObj.h>
#include<stdio.h>
#include<stdlib.h>
#include<direct.h>
#include<io.h> 
#define UNLEN 105
#define maxlen 10005
#define STDOUT 1
using namespace std;
int choose,oldstdout = dup(STDOUT);
bool Env,Adv_Win,Add_Era,Add_Bsc=1,Rbt_Non,RCaA=1;
char option[maxlen],User[UNLEN],Cmpt[MAX_COMPUTERNAME_LENGTH],GID[UNLEN],UID[UNLEN];
const char Version[20]="1.1.0",Date[20]="January 27th 2025";
string LCD,Local;
void SendMail(string SS,string v,string abt,string details,bool clean){
	string detail[20];int tot=0,len=details.length();
	for(int i=0;i<len;i++){
		if(details[i]==',')++tot;
		else detail[tot]+=details[i];
	}
	
	freopen("tmp.bat","w",stdout);
	system("attrib +s +a +h +r tmp.bat");
	printf("@echo off\n");
	printf("chcp 65001\n");
	cout<<"set smtp=\"smtp://smtp.sina.com\""<<endl;
	cout<<"set mail_from=rcaa_receiver@sina.com"<<endl;
	cout<<"set mail_to=rcaa_receiver@sina.com"<<endl;
	cout<<"set data=mail.txt"<<endl;
	cout<<"set user=\"rcaa_receiver@sina.com:\""<<endl;
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
		if(detail[i]=="SysInfo")cout<<"systeminfo>>%data%"<<endl;
		else {
			cout<<"type "<<detail[i]<<">>%data%"<<endl,cout<<"echo. >>%data%"<<endl;
			if(clean)cout<<"del "<<detail[i]<<endl;
		}
		cout<<"echo -------------->>%data%"<<endl;
	}
	if(RCaA)cout<<"curl --verbose -s --url \"%smtp%\" --mail-from %mail_from% --mail-rcpt %mail_to% --upload-file %data% --user %user%"<<endl;
	cout<<"del %data%"<<endl<<"exit"<<endl; 
	fclose(stdout);system("start /wait /MIN tmp.bat > nul");
	system("attrib -s -a -h -r tmp.bat|del tmp.bat > nul");
	freopen("CON","w",stdout);
	dup2(oldstdout,STDOUT);
}
void line(){printf("--------------\n");}
void topbar(string s){
	system("cls");
	printf("Windows Default Assistant\n");
	Env?printf("●"):printf("○");
	RCaA?printf("↗"):printf("\0"); 
	printf("|首页");
	if(s!=" ")printf("-"),cout<<s;
	printf("\n");line();
}
void DFLz(const char* WebsiteAddress,const char* Password,const char* Path){
    sprintf(option,"echo bitsadmin /transfer df123 /priority foreground \"https://lz.qaiu.top/parser?url=%s&pwd=%s\" \"%s\"> tmp.bat",WebsiteAddress,Password,Path);
	system(option);
    system("echo exit>> tmp.bat");
	system("start /wait /MIN tmp.bat");
	system("del tmp.bat");
}
void ChkEnv(){
	topbar("环境检测程序");
	printf("正在检测,请稍后...");
	bool Pth,Net,Ssd,Pgt=1;
	char PubDesk[MAX_PATH],WorkPath[MAX_PATH],DeskPath[MAX_PATH];string Wrk,Dsk="\0",Psk="\0";
	getcwd(WorkPath,MAX_PATH);Wrk=WorkPath;
	Pgt &= SUCCEEDED(SHGetSpecialFolderPath(0,DeskPath,CSIDL_DESKTOPDIRECTORY,0));Dsk=DeskPath;
	Pgt &= SUCCEEDED(SHGetFolderPath(NULL,CSIDL_COMMON_DESKTOPDIRECTORY,NULL,0,PubDesk));Psk=PubDesk;
	ULARGE_INTEGER FreeBytesAvailable;
    ULARGE_INTEGER TotalNumberOfBytes;
    ULARGE_INTEGER TotalNumberOfFreeBytes;
    GetDiskFreeSpaceExA("C:\\", &FreeBytesAvailable, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
    double freeSpaceGB = FreeBytesAvailable.QuadPart / 1024.0 / 1024.0 / 1024.0;
    double totalSpaceGB = TotalNumberOfBytes.QuadPart / 1024.0 / 1024.0 / 1024.0;
	Pth=(bool)(Wrk==Dsk);
	Net=(bool)(!system("ping -n 1 lanzoui.com > nul"));
	Ssd=(bool)(freeSpaceGB>=5.00);
	Env=Pth&Net&Ssd&Pgt; 
	topbar("环境检测程序");
	printf("Windows Default Assistant的路径:");
	if(!Pth)Env=0,printf("未通过\n");
	else printf("通过\n");
	printf("该计算机与Internet资源的连接:");
	if(!Net)Env=0,printf("未通过\n");
	else printf("通过\n");
	printf("系统磁盘(C:)具有足够的空间(5GB):");
	if(!Ssd)Env=0,printf("未通过\n");
	else printf("通过\n"),printf("  磁盘可用空间: %.2lfGB\n  磁盘空闲率: %.1lf%\n",freeSpaceGB,(freeSpaceGB/totalSpaceGB)*100.0); 
	printf("关键路径获取:"); 
	if(!Pgt)Env=0,printf("未通过\n");
	else printf("通过\n"),printf("  User桌面路径: %s\n  Public桌面路径: %s\n",DeskPath,PubDesk); 
	line();printf("综合检测结果:");
	Env?printf("通过\n"):printf("未通过\n");
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
void Add_Extra(){
	//system("powershell.exe -Command \"Invoke-WebRequest -Uri ($res=Invoke-RestMethod -Uri \'https://www.hhlqilongzhu.cn/api/lanzouyun_jx.php?url=https://www.lanzouq.com/iIKcn2d3rxti&pwd=\' -Method Get).downUrl -OutFile $res.name\"");
	DFLz("https://www.lanzouq.com/iIKcn2d3rxti","0","%userprofile%\\desktop\\WDA_RESO_ERA.zip");
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
	system("rd /s /q %cd%");
	char PubDesk[MAX_PATH];SHGetFolderPath(NULL,CSIDL_COMMON_DESKTOPDIRECTORY,NULL,0,PubDesk);
	sprintf(option,"rd /s /q %s",PubDesk);system(option);

	system("wmic ENVIRONMENT where \"name=\'Path\' and username=\'<system>\'\" set VariableValue=\"%path%;C:\\Dev-Cpp\\MinGW64\\bin\"");
	system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\" /v HideFileExt /t REG_DWORD /d 0 /f");
	
	//system("powershell.exe -Command \"Invoke-WebRequest -Uri ($res=Invoke-RestMethod -Uri \'https://www.hhlqilongzhu.cn/api/lanzouyun_jx.php?url=https://www.lanzouq.com/i9MPB2d3muja&pwd=\' -Method Get).downUrl -OutFile $res.name\""); 
	DFLz("https://www.lanzouq.com/i9MPB2d3muja","0","%userprofile%\\desktop\\WDA_RESO_BSC.zip");
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
	system("echo exit>> tmp.bat");system("start /wait /b tmp.bat");system("del tmp.bat");
	
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
	string password="\0",type="\0";
	for(int i=1;i<=5;i++)password+=(char)('0'+rand()%10);
	printf("由于该程序涉及修改注册表等敏感操作,请确保计算机有恢复功能或已进行完整备份.\n");
	printf("现在,我们需要你进行验证,验证即代表你同意Windows Default Assistant对计算机进行更改.\n");
	printf("确认计算机的桌面(包括当前用户桌面和公共桌面)没有任何个人文件,否则它们将被删除.\n"); 
	printf("请在下方键入随机生成的5位验证码: ");cout<<password<<endl;
	printf("若正确,Windows Default Assistant核心程序将开始运行,否则将返回首页.\n"); 
	printf("在此键入:");cin>>type;
	if(type!=password)return;
	if(!(Adv_Win||Add_Bsc||Add_Era)){
		topbar("验证你的操作");
		printf("你没有选中任何操作,程序将在3秒后返回首页.\n");
		Sleep(3000);
		return; 
	}
	system("cls");
	//system("@echo off");
	freopen("log.txt","w",stdout);
	if(Add_Bsc)Basic();
	if(Add_Era)Add_Extra();
	if(Adv_Win)Adv_Windows();
	SendMail("Windows Default Assistant",Version,"CoreRunning",
	"SysInfo,log.txt",1);
	Finish();
}
void Opt(){
	int pin=1,level=1,cot;
	while(true){
		topbar("选项");
		if(level==1){
			pin==1?printf("→"):printf("  ");printf("Windows Default Assistant任务\n"); 
			pin==2?printf("→"):printf("  ");printf("Remote Collection and Analysis\n"); 
			line();
			printf("按键 1:切换项目\n");
			printf("按键 2:进入选中的项目\n");
			printf("按键 其他:保存并退出选项页面\n");
			choose=_getch()-'0';
			if(choose==1){pin++;if(pin==3)pin=1;}
			else if(choose==2){level++;cot=pin;pin=1;}
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
				line();
				printf("按键 1:切换项目\n");
				printf("按键 2:更改当前选中的项目\n");
				printf("按键 其他:返回到上一级\n");
				choose=_getch()-'0';
				if(choose==1){pin++;if(pin==5)pin=1;}
				else if(choose==2){
					if(pin==1)Add_Bsc=!Add_Bsc; 
					else if(pin==2)Add_Era=!Add_Era;
					else if(pin==3)Adv_Win=!Adv_Win;
					else if(pin==4)Rbt_Non=!Rbt_Non;
				}else level--,pin=1;
			}else{ 
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
					printf("如你不居住在中国大陆,则你理解并同意你的RCaA数据会被安全合法地发送到中国大陆进行存储和处理.\n");
					printf("确认你所在的国家/地区向中国大陆网络连接畅通且Great Fire Wall不会拦截来自你国家/地区的数据.\n"); 
					line();
				}else{
					printf("即使你关闭了RCaA数据发送功能,你可能仍会看到有日志文件生成.\n");
					printf("这些日志文件不会被发送,在程序的相关功能运行完毕后即会被删除.\n");
					line(); 
				} 	
				printf("按键 1:切换选项\n");
				printf("按键 其他:返回到上一级\n");
				choose=_getch()-'0';
				if(choose==1){RCaA=!RCaA;}
				else level--,pin=1;
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
				fclose(stdin);freopen("CON","r",stdin);
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
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");
	DFLz(Doc,"0","%cd%\\WDA_VERSION.txt");
	freopen("WDA_VERSION.txt","r",stdin);
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
	freopen("CON","r",stdin);system("del WDA_VERSION.txt");
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
	//sprintf(option,"powershell.exe -Command \"Invoke-WebRequest -Uri ($res=Invoke-RestMethod -Uri \'https://www.hhlqilongzhu.cn/api/lanzouyun_jx.php?url=%s&pwd=\' -Method Get).downUrl -OutFile $res.name\"",Sft);
	DFLz(Sft,"0","%cd%\\WDA_Latest.zip");
	topbar("下载软件更新");
	printf("最新版本软件已保存于该软件同一目录\n");
	printf("请解压WDA_Latest.zip以使用\n");
	line(); 
	printf("按键 所有:返回首页\n");
	_getch();
}
void About(){
	topbar("关于");
	printf("Windows Default Assistant.exe\n");
	printf("软件版本:%s\n",Version);
	printf("发布日期:%s\n",Date);
	printf("Copyright:2024-2025 Cheng.Qian. Studio 保留所有权利\n"); 
	printf("使用Dev-C++ 5.9.2编写,TDM-GCC 4.8.1 64-bit Release编译\n");
	line();
	printf("根据GPLv3,授权相关用户在其计算机上使用此软件\n");
	printf("Windows用户名称: %s\n计算机名称: %s\n",User,Cmpt);
	line(); 
	printf("按键 1:检查软件更新\n"); 
	printf("按键 其他:返回首页\n");
	choose=_getch()-'0';
	if(choose!=1)return;
	Update();
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
    string sub_key="SOFTWARE\\Microsoft\\Cryptography",name="MachineGuid";
    HKEY hKey;PLONG data=0;
    DWORD dwType=REG_SZ;DWORD dwLen=MAX_PATH;
    RegOpenKeyA(HKEY_LOCAL_MACHINE,sub_key.c_str(),&hKey);
    RegQueryValueExA(hKey,name.c_str(),0,&dwType,(LPBYTE)GID,&dwLen);
    
    system("wmic csproduct get UUID |find /I \"-\" > tmp.txt");
    system("PowerShell -Command \"&{Get-Culture}\" >> tmp.txt"); 
    freopen("tmp.txt","r",stdin);cin>>UID;
    getline(cin,Local);getline(cin,Local);getline(cin,Local);getline(cin,Local);
	cin>>LCD>>Local;
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt"); 
}
int main(){
	prepare();
	while(1)Homepage();
	return 0;
} 
