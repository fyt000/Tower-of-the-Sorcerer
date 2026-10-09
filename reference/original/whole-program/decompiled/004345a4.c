/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004345a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TAboutBox_copyrightonclick(int *param_1)

{
  HWND hwnd;
  LPCSTR lpOperation;
  char *lpFile;
  LPCSTR lpParameters;
  LPCSTR lpDirectory;
  INT nShowCmd;
  
  nShowCmd = 5;
  lpDirectory = "";
  lpParameters = "";
  lpFile = "http://plaza.across.or.jp/~furano/index.html";
  lpOperation = "open";
  hwnd = (HWND)FUN_00416cbc(param_1);
  ShellExecuteA(hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd);
  return;
}

