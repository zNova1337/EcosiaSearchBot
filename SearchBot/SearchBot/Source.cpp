//
//#include <string>
//#include <vector>
//
//
//
//
//int main(void) {
//	Handles* pHandle = new Handles();
//	auto m = new Mouse();
//	HWND out = 0;
//	auto pid = ApplicationMgr::GetPID(0, "Chrome_WidgetWin_1", out);
//	if (!pid && !out)
//		print("Pid was null 0x%X out %X", pid, out);
//	else
//		print("Pid @ 0x%X HWND %X", pid, out);
//
//	pHandle->enum_windows(out);
//	auto res = pHandle->get_results();
//	for (auto i : res) {
//		std::cout << (i.caption.c_str()) << std::endl;
//	}
//	m->CurrentMouse();
//
//	std::cin.get();
//	return 0;
//}