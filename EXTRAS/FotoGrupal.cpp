#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <windows.h>  
#include <iostream>


static HWND  hConWnd;
void color(int X)
{
SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X);
}
HWND BCX_Bitmap(char*,HWND=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0);
HWND GetConsoleWndHandle(void);

/*void BitImage(string file,int x,int y,int z)
{
	char *writable = new char[file.size()+1];
}*/

int main()
{
	color(63);
  hConWnd = GetConsoleWndHandle();
  if (hConWnd)
  {
     //nombre de la imagen, handle, ID, ubicacion x, ubicacio Y, ancho, altura,0 ajuste auyomatico
	 for(int x=0;x<100;x+=10) 
	 {
	 	fflush(stdin);
	  BCX_Bitmap("FotoGrupal.bmp",hConWnd,123,100,0,0,0);
	  Sleep(1000);
	  }
      getchar();
  }
  return 0;
}


//draw the bitmap
HWND BCX_Bitmap(char* Text,HWND hWnd,int id,int X,int Y,int W,int H,int Res,int Style,int Exstyle)
{
  	HWND A;
  	HBITMAP hBitmap;

  	if (!Style) Style = WS_CLIPSIBLINGS|WS_CHILD|WS_VISIBLE|SS_BITMAP|WS_TABSTOP;

  	A = CreateWindowEx(Exstyle,"static",NULL,Style,X,Y,0,0,hWnd,(HMENU)id,GetModuleHandle(0),NULL);

  	hBitmap=(HBITMAP)LoadImage(0,Text,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);

  	if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap,IMAGE_BITMAP,W,H,LR_COPYRETURNORG);
  	
	SendMessage(A,(UINT)STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hBitmap);
  
  	if (W || H) SetWindowPos(A,HWND_TOP,X,Y,W,H,SWP_DRAWFRAME);
  
  	return A;
}


HWND GetConsoleWndHandle(void)
{
  HWND hConWnd;
  OSVERSIONINFO os;
  char szTempTitle[64], szClassName[128], szOriginalTitle[1024];

  os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
  GetVersionEx( &os );
  
  if ( os.dwPlatformId == VER_PLATFORM_WIN32s ) return 0;

  GetConsoleTitle( szOriginalTitle, sizeof ( szOriginalTitle ) );
  sprintf( szTempTitle,"%u - %u", GetTickCount(), GetCurrentProcessId() );
  SetConsoleTitle( szTempTitle );
  Sleep( 60 );
  
  hConWnd = FindWindow( NULL, szTempTitle );
  SetConsoleTitle( szOriginalTitle );

  
  if ( os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
  {
    hConWnd = GetWindow( hConWnd, GW_CHILD );
    if ( hConWnd == NULL ) return 0;
    GetClassName( hConWnd, szClassName, sizeof ( szClassName ) );
    // while ( _stricmp( szClassName, "ttyGrab" ) != 0 )
    while ( stricmp( szClassName, "ttyGrab" ) != 0 )
    {
      hConWnd = GetNextWindow( hConWnd, GW_HWNDNEXT );
      if ( hConWnd == NULL ) return 0;
      GetClassName( hConWnd, szClassName, sizeof( szClassName ) );
    }
  }
  return hConWnd;
}
