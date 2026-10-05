/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0047d2d8. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_0047d2d8(int *param_1)

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
  lpFile = ".\\tsw.hlp";
  lpOperation = "open";
  hwnd = (HWND)FUN_00416cbc(param_1);
  ShellExecuteA(hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd);
  return;
}
