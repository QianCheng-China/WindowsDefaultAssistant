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
		ret=MessageBox(NULL,(LPCTSTR)TEXT("һ��RCaA�����Ѿ�����.��ȷ��Ҫ������?"),(LPCTSTR)TEXT("Windows Default Assistant"),MB_OKCANCEL);
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
	Env?printf("��"):printf("��");
	if(RCaA)printf("�J");
	printf("|��ҳ");
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
			"�޷�����������ݵ�SHA256.��ȷ��Ҫ������?(�㰴ȷ������,�����ֱ�ӹرճ���)"),
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
			"�������ݵ�SHA256���׼����,����ļ������к�.��ȷ��Ҫ������?(�㰴ȷ������,�����ֱ�ӹرճ���)"),
			(LPCTSTR)TEXT("Windows Default Assistant"),MB_OK);
			return;
		}
		Tmp="1";
	}
}
void ChkEnv(){
	topbar("����������");
	printf("���ڼ��,���Ժ�...");
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
	if(Pth&&Net&&Ssd&&Pgt&&run_not_adm&&(!Adm)){Env=1;topbar("����������");Env=0;}
	else Env=Pth&Net&Ssd&Pgt&Adm,topbar("����������");
	printf("������й���ԱȨ��:");
	Adm?printf("ͨ��\n"):printf("δͨ��\n");
	printf("Windows Default Assistant��·��:");
	Pth?printf("ͨ��\n"):printf("δͨ��\n");
	printf("�ü������Internet��Դ������:");
	Net?printf("ͨ��\n"):printf("δͨ��\n");
	printf("ϵͳ����(C:)�����㹻�Ŀռ�(5GB):");
	if(!Ssd)printf("δͨ��\n");
	else printf("ͨ��\n"),printf("  ���̿��ÿռ�: %.2lfGB\n  ���̿�����: %.1lf%\n",freeSpaceGB,(freeSpaceGB/totalSpaceGB)*100.0); 
	printf("�ؼ�·����ȡ:"); 
	if(!Pgt)printf("δͨ��\n");
	else printf("ͨ��\n"),printf("  User����·��: %s\n  Public����·��: %s\n",DeskPath,PubDesk); 
	line();printf("�ۺϼ����:");{
		if(Env)printf("ͨ��\n");
		else {
			if(Pth&&Net&&Ssd&&Pgt&&run_not_adm)printf("ͨ��(�û������Ʒ���޹���ԱȨ��ʱ����)\n"),Env=1;
			else printf("δͨ��\n");	
		}
	} 
	
	line();
	printf("���� ����:������ҳ\n");
	_getch(); 
}
void Finish(){
	if(Rbt_Non)system("shutdown -l");
	topbar("ע����ļ����"); 
	string password="\0",type="\0";
	for(int i=1;i<=5;i++)password+=(char)('0'+rand()%10);
	printf("������Ҫע�������,��ȷ�����и�����Ч.����ע����,������������µ�¼,�뱣�����й���.\n");
	printf("����,������Ҫ�������֤,��֤��������ͬ��Windows Default Assistantע�������.\n");
	printf("�����·�����������ɵ�5λ��֤��: ");cout<<password<<endl;
	printf("����ȷ,Windows Default Assistant������ע�������,���򽫷�����ҳ.\n"); 
	printf("�ڴ˼���:");cin>>type;
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
	topbar("��֤��Ĳ���");
	if(!Env){
		printf("��δͨ����û�����л���������,�������п��ܵ���ϵͳ�ļ���ʧ���޷���������.\n");
		printf("Ϊ��֤Windows Default Assistant��ϵͳ��������,��ͨ��������������ٴγ���.\n");
		line();
		printf("���� ����:������ҳ\n");
		_getch();
		return;
	}
	int password=0,typ=0;
	for(int i=1;i<=5;i++)password+=password*10+rand()%10;
	printf("���ڸó����漰�޸�ע�������в���,��ȷ��������лָ����ܻ��ѽ�����������.\n");
	printf("����,������Ҫ�������֤,��֤��������ͬ��Windows Default Assistant�Լ�������и���.\n");
	printf("�����·�����������ɵ�5λ��֤��: ");cout<<password<<endl;
	printf("����ȷ,Windows Default Assistant���ĳ��򽫿�ʼ����,���򽫷�����ҳ.\n"); 
	printf("�ڴ˼���:");scanf("%d",&typ);
	if(typ!=password)return;
	if(!(Adv_Win||Add_Bsc||Add_Era)){
		topbar("��֤��Ĳ���");
		printf("��û��ѡ���κβ���,������3��󷵻���ҳ.\n");
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
		topbar("ѡ��");
		if(level==1){
			pin==1?printf("��"):printf("  ");printf("��Ʒ��������ִ��\n"); 
			pin==2?printf("��"):printf("  ");printf("Զ���ռ��ͷ���(RCaA)\n"); 
			pin==3?printf("��"):printf("  ");printf("��˽,��ȫ��ά��\n");
			line();
			printf("���� 1:�л���Ŀ\n");
			printf("���� 2:����ѡ�е���Ŀ\n");
			printf("���� 3:��ѡ��浽�����ļ�/�������ļ�����\n");
			printf("���� ����:���沢�˳�ѡ��ҳ��\n");
			choose=_getch()-'0';
			if(choose==1){pin++;if(pin==4)pin=1;}
			else if(choose==2){level++;cot=pin;pin=1;}
			else if(choose==3){
				topbar("ѡ��");
				if(!access("WDAconfig.txt",F_OK)){
					printf("��ǰĿ¼�´���WDAconfig.txt�ļ�.��WDAconfig.txt��������?\n");
					printf("������뵼������,�뽫Ŀ¼�µ�WDAconfig.txt�ļ�������Ϊ�������ƻ����Ƴ����˳�����.\n"); 
					printf("RCaA�Ŀ�����رղ�֧�ִ������ļ��е���.��ֻ�ᱻ֪ͨ�����ļ���RCaA���������.\n");
					line();
					printf("���� 1:��������\n");
					printf("���� ����:ȡ��\n");
					choose=_getch()-'0';
					if(choose!=1)continue;
					string input="\0";
					bool input_b[12],ok=1;
					topbar("ѡ��");
					freopen("WDAconfig.txt","r",stdin);
					cin>>input;
					fclose(stdin);freopen("CON","r",stdin);dup2(oldstdin,STDIN);
					
					if(input.size()!=12){printf("�����ļ����Ϸ�\n");line();printf("���� ����:����\n");_getch();continue;}
					for(int i=0;i<=11&&ok;i++)
						if(input[i]=='1')input_b[i]=1;
						else if(input[i]=='0')input_b[i]=0;
						else ok=0;
					if(!ok){printf("�����ļ����Ϸ�\n");line();printf("���� ����:����\n");_getch();continue;}
					
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
					topbar("ѡ��");printf("�ɹ���������\n");
					printf("�����ļ���,RCaA������Ϊ");
					input_b[5]?printf("����"):printf("�ر�");
					printf(".���㵱ǰ������");
					input_b[5]==RCaA?printf("һ��\n"):printf("��һ��\n");
					line();printf("���� ����:����\n");_getch();
				}else{ 
					printf("��ǰĿ¼����WDAconfig.txt�ļ�.�����ñ��浽WDAconfig.txt��?\n");
					printf("������뵼������,�뽫�Ϸ��������ļ�����ΪWDAconfig.txt�������ڱ�Ŀ¼�º��˳�����.\n");
					printf("RCaA�Ŀ�����رղ�֧�ִ������ļ��е���.��ֻ�ᱻ֪ͨ�����ļ���RCaA���������.\n"); 
					line();
					printf("���� 1:��������\n");
					printf("���� ����:ȡ��\n");
					choose=_getch()-'0';
					if(choose!=1)continue;
					freopen("WDAconfig.txt","w",stdout);
					printf("%d%d%d%d%d%d%d%d%d%d%d%d\n",Add_Bsc,Add_Era,Adv_Win,Rbt_Non,DelF,RCaA,usinglog,performance,sysinfo,run_not_adm,RCaA_msg,CheckDown);
					printf("//Windows Default Assistant��ʶ������һ������.����һ�б�������0/1��ɵ�һ��12λ�ַ���.\n");
					printf("//ÿһλ��Ӧ�ı�������Ϊ:Add_Bsc Add_Era Adv_Win Rbt_Non DelF RCaA usinglog performance sysinfo run_not_adm RCaA_msg CheckDown."); 
					fclose(stdout);freopen("CON","w",stdout);dup2(oldstdout,STDOUT);	
					topbar("ѡ��");printf("�ɹ���������\n");line();printf("���� ����:����\n");_getch();	
				}
			}
			else break;
		}else{
			if(cot==1){
				pin==1?printf("��"):printf("  "); 
				Add_Bsc?printf("��"):printf("��");
				printf("���ز���װ�������������ִ��ϵͳ���Ĳ���\n"); 
				if(pin==1){
					printf("    ������ں���Dev-C++,CCR-Plus�ͼ�����.\n");
					printf("    �������ı�ֽ,���û��������ʹ򿪺�׺����ʾ.\n"); 
					printf("    CPP����Dev-C++��,IN,OUT,ANS���Ӽ��±���.\n");
				}
				pin==2?printf("��"):printf("  "); 
				Add_Era?printf("��"):printf("��");
				printf("���ز���װ����������\n"); 
				if(pin==2){
					printf("    ������ں���Microsoft Edge,Sublime Text��Typora.\n");
					printf("    ������,IN,OUT,ANS����Sublime Text��.\n");
					printf("    Typora��һ��Markdown�༭��,MD���Ӹ������.\n");
					printf("    Edge����ϴ�,��ȷ��Ӳ����������������㹻.\n");
				}
				pin==3?printf("��"):printf("  "); 
				Adv_Win?printf("��"):printf("��");
				printf("����Microsoft Windows\n");
				if(pin==3){
					printf("    ����Ϊδ�����Microsoft Windows��װ��Կ.\n");
					printf("    ��Windows�ѱ�����,����ǰ�������Կ����ж��.\n");
					printf("    ������������ֶ�ȷ�Ͻ���Ի���.\n");
				}
				pin==4?printf("��"):printf("  "); 
				Rbt_Non?printf("��"):printf("��");
				printf("����ȫ����ɺ�����ȷ��ֱ��ע��\n");
				if(pin==4){
					printf("    ������ɺ�,�Զ�ע������Ч���и���.\n");
					printf("    ��ȷ�ϼ������û��δ����Ĺ���.\n");
				}
				pin==5?printf("��"):printf("  "); 
				DelF?printf("��"):printf("��");
				printf("�������(�û��͹�������)�ϵ��ļ�\n");
				if(pin==5){
					printf("    ��������ϵ������ļ�(��\"�����\"����).\n");
					printf("    ��ȷ��������û�и����ļ�.\n");
				}
				line();
				printf("���� 1:�л���Ŀ\n");
				printf("���� 2:���ĵ�ǰѡ�е���Ŀ\n");
				printf("���� ����:���ص���һ��\n");
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
				RCaA?printf("��"):printf("��");
				printf("����Remote Collection and Analysis����\n");
				printf("RCaA���ݿ��԰�������ȷ������͸Ľ����.\n");
				printf("RCaA���ݲ��������ĸ�����Ϣ,��ʹ�����֮�󼴱����.\n");
				line();
				if(RCaA){
					printf("MachineGUID:%s\nsmBIOS UUID:%s\n",GID,UID);
					printf("����ID��Ϣ����RCaA����һ�����԰������Ǳ����ĵ���.\n");
					printf("����ID��Ϣδ������˹���,�κ��˶��޷�ͨ���������ҵ���.\n"); 
					line(); 
					cout<<"��������������������Ϣ:LCID(Locale ID):"<<LCD<<",��Ӧ����:"<<Local<<endl;
					printf("���㲻��ס���й���½,������Ⲣͬ�����RCaA���ݻᱻ���͵��й���½���д洢�ʹ���.\n");
					line();
				}else{
					printf("��ʹ��ر���RCaA���ݷ��͹���,������Իῴ������־�ļ�����.\n");
					printf("��Щ��־�ļ����ᱻ����,�ڳ������ع���������Ϻ󼴻ᱻɾ��.\n");
					line(); 
				} 	
				printf("���� 1:�л�ѡ��\n");
				if(RCaA)printf("���� 2:���������͵���������\n");
				printf("���� ����:���ص���һ��\n");
				choose=_getch()-'0';
				if(choose==1){
					RCaA=!RCaA;
					topbar("ѡ��");
					RCaA?printf("��"):printf("��");
					printf("����Remote Collection and Analysis����\n");
					printf("RCaA���ݿ��԰�������ȷ������͸Ľ����.\n");
					printf("RCaA���ݲ��������ĸ�����Ϣ,��ʹ�����֮�󼴱����.\n");
					line();
					if(RCaA){
						printf("���Ժ�,���ڶ�ȡһЩ��������,�Ա�RCaA����......\n");
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
						printf("����������ȡ����RCaA���ݷ���ƾ��,�뱣��Internet����......\n");
						if(system("curl -s https://www.lanzouq.com/b00uyxs6ib > tmp.txt")){
							system("del tmp.txt");
							topbar("ѡ��");
							printf("Windows Default Assistant�޷����ӵ�Internet\n");
							printf("��ĵ��Կ���������,���߷������������쳣,���Ժ�����\n");
							line();printf("���� ����:����\n");getch();
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
									topbar("ѡ��");
									printf("Windows Default Assistant�޷����ӵ�Internet\n");
									printf("��ĵ��Կ����ѶϿ�Internet����,���߷������������쳣,���Ժ�����\n");
									line();printf("���� ����:����\n");_getch(); 
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
						printf("���Ժ�,�������һЩ����......\n");
						memset(GID,0,sizeof GID);
						memset(UID,0,sizeof UID);
						LCD=Local="N/A"; 
					}	
				}
				else if(RCaA&&choose==2){
					pin=1;
					while(true){
						topbar("ѡ��");
						printf("��RCaA����ʱ,��������ʹ������ݻᱻ����,��Щ�Ǳ����RCaA����\n");
						printf("������Ŀ�ǿ�ѡRCaA����,���������ѡ���Ƿ�������.���㲻�뷢���κ�����,��ر�RCaA\n");
						line();
						pin==1?printf("��"):printf("  ");
						usinglog?printf("��"):printf("��");
						printf("���Ͳ�Ʒʹ�ù����е���־�ͱ���\n");
						pin==2?printf("��"):printf("  ");
						performance?printf("��"):printf("��");
						printf("���Ͳ�Ʒ��������Ϣ(CPUʱ����ڴ�)\n"); 
						pin==3?printf("��"):printf("  ");
						sysinfo?printf("��"):printf("��");
						printf("���Ͳ�Ʒ�����豸��ϵͳ������Ϣ\n"); 
						line();
						printf("���� 1:�л���Ŀ\n");
						printf("���� 2:���ĵ�ǰѡ�е���Ŀ\n");
						printf("���� ����:���ص���һ��\n");
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
					topbar("ѡ��");
					pin==1?printf("��"):printf("  ");
					run_not_adm?printf("��"):printf("��");
					printf("�����ڲ�Ʒ�޹���ԱȨ��ʱ����\n");
					pin==2?printf("��"):printf("  ");
					RCaA_msg?printf("��"):printf("��");
					printf("����RCaA���ݼ�������ʱ��������\n");
					pin==3?printf("��"):printf("  ");
					CheckDown?printf("��"):printf("��");
					printf("����������ݵ�SHA256�Ƿ����׼���\n");
					line();
					printf("���� 1:�л���Ŀ\n");
					printf("���� 2:���ĵ�ǰѡ�е���Ŀ\n");
					printf("���� ����:���ص���һ��\n");
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
	topbar("����������");
	printf("���ڴӸ��·�������ȡ��Ϣ,���Ժ�...\n");
	if(system("curl -s https://www.lanzouq.com/b00uyk87md > tmp.txt")){
		system("del tmp.txt");
		topbar("����������");
		printf("Windows Default Assistant�޷����ӵ����·�����\n");
		printf("��ĵ��Կ���������,���߸��·������������쳣,���Ժ�����\n");
		line();
		printf("���� ����:������ҳ\n");
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
				topbar("����������");
				printf("Windows Default Assistant�޷����ӵ����·�����\n");
				printf("��ĵ��Կ����ѶϿ�Internet����,���߸��·������������쳣,���Ժ�����\n");
				printf("����������������RCaA����,�򱾴θ��µĴ�����ΪRCaA���ݷ���.���Ժ�...\n");
				SendMail("Windows Default Assistant",Version,"UpdateCheckError",
				"tmp.txt",1);
				line();printf("���� ����:������ҳ\n");
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
		topbar("����������");
		printf("�������е�Windows Default Assistant�����°汾\n");
		printf("�������еİ汾��%s,��%s����\n",Version,Date);
		line();
		printf("���� ����:������ҳ\n");
		_getch(); 
		return;
	}
	topbar("����������");
	printf("�и��°汾��Windows Default Assistant����\n");
	cout<<"��ǰ���µİ汾��"<<NVer<<",��"<<NDate<<"����"<<endl;
	printf("�������еİ汾��%s,��%s����\n",Version,Date);
	printf("���°汾�ĸ�����Ŀ:\n");
	for(int i=1;i<NDet_sum;i++)cout<<"  "<<NDet[i]<<endl;
	line(); 
	printf("���� 1:�������°汾���\n");
	printf("���� ����:��������,������ҳ\n");
	choose=_getch()-'0';
	if(choose!=1)return;
	topbar("�����������");
	printf("���ڴӸ��·������������°汾,���Ժ�...\n");
	DFLz(Sft,"%cd%\\WDA_Latest.zip",0);
	topbar("�����������");
	printf("���°汾����ѱ����ڸ����ͬһĿ¼\n");
	printf("���ѹWDA_Latest.zip��ʹ��\n");
	line(); 
	printf("���� ����:������ҳ\n");
	_getch();
}
void CheckHash(){
	topbar("������ȫ��");
	printf("���ڼ�����������SHA256��ϣ......\n");
	char Path[MAX_PATH],option[MAX_PATH],Hash[MAX_PATH],Tmps[MAX_PATH];
	string res,Tmp;
	GetModuleFileName(NULL, Path, MAX_PATH);
    sprintf(option,"certutil -hashfile \"%s\" SHA256 >> tmp.txt",Path);system(option);
	freopen("tmp.txt","r",stdin);
	getline(cin,res);getline(cin,res);
	fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
	printf("���ڴӷ�����������ȷ�ĳ���SHA256��ϣ......\n");
	if(system("curl -s https://www.lanzouq.com/b00uyk87md > tmp.txt")){
		system("del tmp.txt");
		printf("Windows Default Assistant�޷����ӵ�������\n");
		printf("��ĵ��Կ���������,���߷������������쳣,���Ժ�����\n");
		line();
		printf("���� ����:������ҳ");
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
				topbar("������ȫ��");
				printf("Windows Default Assistant�޷����ӵ�������\n");
				printf("��ĵ��Կ����ѶϿ�Internet����,���߷������������쳣,���Ժ�����\n");
				line();
				printf("���� ����:������ҳ\n");
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
			topbar("������ȫ��");
			printf("û�в�ѯ���ð汾��������Ӧ��SHA256��ϣ\n");
			printf("�볢�Ը�����ĳ������°汾\n");
			line();printf("���� ����:������ҳ\n");
			_getch();return;
		}
	}
	while(true){
		cin>>Tmp;
		if(Tmp=="[VerEnd]"){
			fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
			topbar("������ȫ��");
			printf("û�в�ѯ��������SHA256���κ�һ���Ǽǵı�����ͬ\n");
			printf("������ǵ��������ܺ���,������ܴ�����в֮��\n");
			line();printf("���� ����:������ҳ\n");
			_getch();return;
		}else if(Tmp==res){
			getline(cin,Tmp);
			fclose(stdin);freopen("CON","r",stdin);system("del tmp.txt");dup2(oldstdin,STDIN);
			topbar("������ȫ��");
			printf("������SHA256��ϣ��һ���ѵǼǵı�����ͬ\n");
			printf("��ĳ���Ӧ���ǰ�ȫ��,��ɱ�֤�������͸����ļ���ȫ\n");
			cout<<"�ó������󿪷�����:"<<Tmp<<endl;
			line();printf("���� ����:������ҳ\n");
			_getch();return;		
		}else getline(cin,Tmp);
	}
} 
void About(){
	topbar("����");
	printf("Windows Default Assistant.exe\n");
	printf("����汾:%s\n",Version);
	printf("��������:%s\n",Date);
	printf("ʹ��Dev-C++ 5.9.2��д,TDM-GCC 4.8.1 64-bit Release����\n");
	printf("Copyright:2023-2025 Cheng.Qian. Studio ��������Ȩ��\n"); 
	printf("GitHub:https://github.com/QianCheng-China/WindowsDefaultAssistant\n");
	line();
	printf("����GPLv3,��Ȩ����û�����������ʹ�ô����\n");
	printf("Windows�û�����: %s\n���������: %s\n",User,Cmpt);
	line(); 
	printf("���� 1:����������\n"); 
	printf("���� 2:������ȫ��\n");
	printf("���� ����:������ҳ\n");
	choose=_getch()-'0';
	if(choose==1)Update();
	else if(choose==2)CheckHash();
	else return;
}
void Homepage(){
	topbar(" ");
	printf("���� 1:����Windows Default Assistant\n");
	printf("���� 2:���л���������\n");
	printf("���� 3:ѡ��\n"); 
	printf("���� 4:����\n");
	printf("���� ����:�˳�����\n");
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
