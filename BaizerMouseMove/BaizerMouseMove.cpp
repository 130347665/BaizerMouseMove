#include <iostream>
#include<Windows.h>
void sendinput_move(int x, int y)
{
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	Input.mi.dx = x;
	Input.mi.dy = y;
	::SendInput(1, &Input, sizeof(INPUT));
}
POINT twoOrderBezier(double t, POINT p1, POINT cp1, POINT p2) {
	//参数分别是t,起始点,控制点和终点
	POINT mouse_xy;
	GetCursorPos(&mouse_xy);
	std::cout << "mouse_x " << mouse_xy.x << "mouse_y " << mouse_xy.y << std::endl;
	POINT ans;
	ans.x = (1 - t) * (1 - t) * p1.x + 2 * t * (1 - t) * cp1.x + t * t * p2.x,
		ans.y = (1 - t) * (1 - t) * p2.y + 2 * t * (1 - t) * cp1.y + t * t * p2.y;
	std::cout << "x " << ans.x << "y " << ans.y << std::endl;

	return ans;
}

int main()
{
	Sleep(1000);
	POINT p1;
	GetCursorPos(&p1);

	POINT p2;
	p2.x = p1.x + 100;
	p2.y = p1.y;
	POINT cp;
	cp.x = p1.x + 50 + 10; cp.y = p1.y - 100;

	for (double x = 0; x <= 1; x += 0.001)
	{
		POINT ans = twoOrderBezier(x, p1, cp, p2);
		POINT p3;
		GetCursorPos(&p3);
		sendinput_move(ans.x - p3.x, ans.y - p3.y);
	}
}