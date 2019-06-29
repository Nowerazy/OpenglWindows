//#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include "GlContext.h"
#include "GlControl.h"
#include <time.h>
//void main() {
//	printf("first app");
//}
LRESULT CALLBACK  wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam) {
	switch (msgId)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		//����Ӧ�ó���δ����Ĵ�����Ϣ,����ȷ��ÿ����Ϣ��������
		return DefWindowProc(hWnd, msgId, wParam, lParam);//Ĭ�ϴ��ڹ���
		break;
	}
	return 0;
}
int CALLBACK WinMain(
	HINSTANCE hinstance,//��ǰ������ʵ�����
	HINSTANCE hpreInstance,//���õ�ǰʵ����ʵ��
	LPSTR lpCmdLine,//Ӧ�õ�������,�����ó�������� 
	int nshowCmd//��ʾ����
) {
	UNREFERENCED_PARAMETER(hpreInstance); //���߱���������ʹ��ĳЩ����,�������������һЩ������Ż�
	UNREFERENCED_PARAMETER(lpCmdLine);
	//1 ע�ᴰ����
	WNDCLASSEX wnd;
	memset(&wnd, 0, sizeof(wnd));
	wnd.cbSize = sizeof(wnd);
	wnd.lpfnWndProc = wndProc;//ָ�򴰿ڹ��̵�ָ��
	wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hinstance, IDC_ARROW);
	//-------
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	//-------
	//wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������ͼ��ľ��
	//wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //������ͼ��ľ��

	wnd.hInstance = hinstance;
	wnd.lpszClassName = _T("myOPENGLWinClass");
	wnd.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//˫��/ˮƽ�������/ӵ�ж���dc(�������Ƶ��豸������)
	RegisterClassEx(&wnd);
	//��������
	HWND hWnd = CreateWindowEx(
		0,//���ڷ��
		_T("myOPENGLWinClass"),//��ע�ᴰ���ౣ��һ��
		_T("LessonOPENGL01"),//���ڵı���
		WS_OVERLAPPEDWINDOW,//���ڷ��
		100,
		100,
		480,
		320,
		0,//ϵͳ�˵�
		0,//��/������
		hinstance,//ʵ��
		0//�û��Զ���˵�
	);
	//3 ������ʾ
	if (hWnd) {
		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}
	else
	{
		return -1;
	}
	GlContext cxt;
	GlControl gcl;
	if (!cxt.setup(hWnd, GetDC(hWnd))) {
		return 0;
	};
	MSG msg = { 0 };
	//4 ��Ϣѭ��
	long int frame = 0;
	clock_t star = clock();
	clock_t end ;
	AllocConsole();
	freopen("conout$", "w", stdout);
	while (WM_QUIT != msg.message) {
		//GetMessage(&msg, 0, 0, 0)������,��ֹͣ,ֱ������Ϣ��.
		//��PeekMessage(&msg, 0, 0, 0,PM_REMOVE)��������.
		//(PM_REMOVE:��ȡ��Ϣ��,�ѵ�ǰ��Ϣ�Ƴ�������)

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(10);
			//openGL����
			frame++;
			gcl.ctrolInit(&cxt);
			gcl.render();
			if (frame > 79)
			{
				end = clock();
				printf("time:%ldms     ",end - star);
				printf("Frame:%.2ff/s\n", (float)frame/(end - star)*1000.0);
				frame = 0;
				star = end;
			}
		}

	}
	cxt.shutdown();
	DestroyWindow(hWnd);
	UnregisterClass(wnd.lpszClassName, hinstance);
	//ע��������,�ͷŸ���ռ�õ��ڴ�
	return (int)msg.wParam;
	//��Ӧ�ó�����Ϣ�����з���һ���ɹ��Ƴ���������һ����Ϣ����

	//return 0;
}