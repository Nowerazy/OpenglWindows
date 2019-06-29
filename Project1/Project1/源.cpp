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
		//处理应用程序未处理的窗口信息,函数确保每个消息都被处理
		return DefWindowProc(hWnd, msgId, wParam, lParam);//默认窗口过程
		break;
	}
	return 0;
}
int CALLBACK WinMain(
	HINSTANCE hinstance,//当前窗口类实例句柄
	HINSTANCE hpreInstance,//调用当前实例的实例
	LPSTR lpCmdLine,//应用的命令行,包含该程序的名称 
	int nshowCmd//显示隐藏
) {
	UNREFERENCED_PARAMETER(hpreInstance); //告诉编译器不能使用某些参数,方便编译器进行一些额外的优化
	UNREFERENCED_PARAMETER(lpCmdLine);
	//1 注册窗口类
	WNDCLASSEX wnd;
	memset(&wnd, 0, sizeof(wnd));
	wnd.cbSize = sizeof(wnd);
	wnd.lpfnWndProc = wndProc;//指向窗口过程的指针
	wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hinstance, IDC_ARROW);
	//-------
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	//-------
	//wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //窗口类图标的句柄
	//wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //窗口类图标的句柄

	wnd.hInstance = hinstance;
	wnd.lpszClassName = _T("myOPENGLWinClass");
	wnd.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//双击/水平横向滚动/拥有独立dc(用来绘制的设备上下文)
	RegisterClassEx(&wnd);
	//创建窗口
	HWND hWnd = CreateWindowEx(
		0,//窗口风格
		_T("myOPENGLWinClass"),//和注册窗口类保持一致
		_T("LessonOPENGL01"),//窗口的标题
		WS_OVERLAPPEDWINDOW,//窗口风格
		100,
		100,
		480,
		320,
		0,//系统菜单
		0,//子/父窗口
		hinstance,//实例
		0//用户自定义菜单
	);
	//3 更新显示
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
	//4 消息循环
	long int frame = 0;
	clock_t star = clock();
	clock_t end ;
	AllocConsole();
	freopen("conout$", "w", stdout);
	while (WM_QUIT != msg.message) {
		//GetMessage(&msg, 0, 0, 0)有阻塞,会停止,直到新消息到.
		//而PeekMessage(&msg, 0, 0, 0,PM_REMOVE)不会阻塞.
		//(PM_REMOVE:获取消息后,把当前消息移除出队列)

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(10);
			//openGL绘制
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
	//注销窗口类,释放该类占用的内存
	return (int)msg.wParam;
	//从应用程序消息队列中返回一个成功推出代码或最后一个消息代码

	//return 0;
}