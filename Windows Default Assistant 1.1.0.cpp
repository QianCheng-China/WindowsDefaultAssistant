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
	Env?printf("��"):printf("��");
	RCaA?printf("�J"):printf("\0"); 
	printf("|��ҳ");
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
	topbar("����������");
	printf("���ڼ��,���Ժ�...");
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
	topbar("����������");
	printf("Windows Default Assistant��·��:");
	if(!Pth)Env=0,printf("δͨ��\n");
	else printf("ͨ��\n");
	printf("�ü������Internet��Դ������:");
	if(!Net)Env=0,printf("δͨ��\n");
	else printf("ͨ��\n");
	printf("ϵͳ����(C:)�����㹻�Ŀռ�(5GB):");
	if(!Ssd)Env=0,printf("δͨ��\n");
	else printf("ͨ��\n"),printf("  ���̿��ÿռ�: %.2lfGB\n  ���̿�����: %.1lf%\n",freeSpaceGB,(freeSpaceGB/totalSpaceGB)*100.0); 
	printf("�ؼ�·����ȡ:"); 
	if(!Pgt)Env=0,printf("δͨ��\n");
	else printf("ͨ��\n"),printf("  User����·��: %s\n  Public����·��: %s\n",DeskPath,PubDesk); 
	line();printf("�ۺϼ����:");
	Env?printf("ͨ��\n"):printf("δͨ��\n");
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
	topbar("��֤��Ĳ���");
	if(!Env){
		printf("��δͨ����û�����л���������,�������п��ܵ���ϵͳ�ļ���ʧ���޷���������.\n");
		printf("Ϊ��֤Windows Default Assistant��ϵͳ��������,��ͨ��������������ٴγ���.\n");
		line();
		printf("���� ����:������ҳ\n");
		_getch();
		return;
	}
	string password="\0",type="\0";
	for(int i=1;i<=5;i++)password+=(char)('0'+rand()%10);
	printf("���ڸó����漰�޸�ע�������в���,��ȷ��������лָ����ܻ��ѽ�����������.\n");
	printf("����,������Ҫ�������֤,��֤��������ͬ��Windows Default Assistant�Լ�������и���.\n");
	printf("ȷ�ϼ����������(������ǰ�û�����͹�������)û���κθ����ļ�,�������ǽ���ɾ��.\n"); 
	printf("�����·�����������ɵ�5λ��֤��: ");cout<<password<<endl;
	printf("����ȷ,Windows Default Assistant���ĳ��򽫿�ʼ����,���򽫷�����ҳ.\n"); 
	printf("�ڴ˼���:");cin>>type;
	if(type!=password)return;
	if(!(Adv_Win||Add_Bsc||Add_Era)){
		topbar("��֤��Ĳ���");
		printf("��û��ѡ���κβ���,������3��󷵻���ҳ.\n");
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
		topbar("ѡ��");
		if(level==1){
			pin==1?printf("��"):printf("  ");printf("Windows Default Assistant����\n"); 
			pin==2?printf("��"):printf("  ");printf("Remote Collection and Analysis\n"); 
			line();
			printf("���� 1:�л���Ŀ\n");
			printf("���� 2:����ѡ�е���Ŀ\n");
			printf("���� ����:���沢�˳�ѡ��ҳ��\n");
			choose=_getch()-'0';
			if(choose==1){pin++;if(pin==3)pin=1;}
			else if(choose==2){level++;cot=pin;pin=1;}
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
				line();
				printf("���� 1:�л���Ŀ\n");
				printf("���� 2:���ĵ�ǰѡ�е���Ŀ\n");
				printf("���� ����:���ص���һ��\n");
				choose=_getch()-'0';
				if(choose==1){pin++;if(pin==5)pin=1;}
				else if(choose==2){
					if(pin==1)Add_Bsc=!Add_Bsc; 
					else if(pin==2)Add_Era=!Add_Era;
					else if(pin==3)Adv_Win=!Adv_Win;
					else if(pin==4)Rbt_Non=!Rbt_Non;
				}else level--,pin=1;
			}else{ 
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
					printf("���㲻��ס���й���½,������Ⲣͬ�����RCaA���ݻᱻ��ȫ�Ϸ��ط��͵��й���½���д洢�ʹ���.\n");
					printf("ȷ�������ڵĹ���/�������й���½�������ӳ�ͨ��Great Fire Wall�����������������/����������.\n"); 
					line();
				}else{
					printf("��ʹ��ر���RCaA���ݷ��͹���,������Իῴ������־�ļ�����.\n");
					printf("��Щ��־�ļ����ᱻ����,�ڳ������ع���������Ϻ󼴻ᱻɾ��.\n");
					line(); 
				} 	
				printf("���� 1:�л�ѡ��\n");
				printf("���� ����:���ص���һ��\n");
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
				fclose(stdin);freopen("CON","r",stdin);
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
	//sprintf(option,"powershell.exe -Command \"Invoke-WebRequest -Uri ($res=Invoke-RestMethod -Uri \'https://www.hhlqilongzhu.cn/api/lanzouyun_jx.php?url=%s&pwd=\' -Method Get).downUrl -OutFile $res.name\"",Sft);
	DFLz(Sft,"0","%cd%\\WDA_Latest.zip");
	topbar("�����������");
	printf("���°汾����ѱ����ڸ����ͬһĿ¼\n");
	printf("���ѹWDA_Latest.zip��ʹ��\n");
	line(); 
	printf("���� ����:������ҳ\n");
	_getch();
}
void About(){
	topbar("����");
	printf("Windows Default Assistant.exe\n");
	printf("����汾:%s\n",Version);
	printf("��������:%s\n",Date);
	printf("Copyright:2024-2025 Cheng.Qian. Studio ��������Ȩ��\n"); 
	printf("ʹ��Dev-C++ 5.9.2��д,TDM-GCC 4.8.1 64-bit Release����\n");
	line();
	printf("����GPLv3,��Ȩ����û�����������ʹ�ô����\n");
	printf("Windows�û�����: %s\n���������: %s\n",User,Cmpt);
	line(); 
	printf("���� 1:����������\n"); 
	printf("���� ����:������ҳ\n");
	choose=_getch()-'0';
	if(choose!=1)return;
	Update();
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
