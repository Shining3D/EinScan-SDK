#include "sdk_demo_fix.h"
#include <QtWidgets/QApplication>

#include <windows.h>
#include <qmessagebox.h>
bool checkOnly()
{
 
	HANDLE m_hMutex = CreateMutex(NULL, FALSE, L"sn3d_sdk_demo");
 	if (GetLastError() == ERROR_ALREADY_EXISTS)  {
		 
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	 
		return  false;
	}

	return true;
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	if (!checkOnly())
	{
		QMessageBox::information(NULL, "information", "Software is unable to repeat opening while running.", "OK");
		return 0;
	}
	sdk_demo_fix w;
	w.show();
	return a.exec();
}
