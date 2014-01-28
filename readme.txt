「RTC::CameraImage <-> cv::Mat」，「cv::Mat <-> mwArray」を「>>」および「<<」演算子で相互変換するライブラリ  
  
動作環境  
・Windows 7 64bit  
・Visual Studio 2010 Professional  
・OpenCV 2.4.5  
・OpenRTM 1.1 64bit  
・MATLAB Compiler Runtime R2012b (8.0)  
  
中身  
・ヘッダファイル  
--convert_template.h  
・ソースファイル  
--convert_template.cpp  
・Release用  
--libconvert100.dll  
--libconvert100.exp  
--libconvert100.lib  
・Debug用  
--libconvert100d.dll  
--libconvert100.exp  
--libconvert100.lib  
  
使い方  
1. convert_template.hへのインクルードパスを設定する  
2. libconvert100d.libまたはlibconvert100.libへのライブラリパスを設定する  
3. 使用したいソースコードファイル内でconvert_template.hをインクルードする  
  
*Debugの場合  
4. libconvert100d.libとリンクする  
5. 実行ファイルと同じフォルダにlibconvert100d.dll，libconvert100d.expをコピーする  
  
*Releaseの場合  
4. libconvert100.libとリンクする  
5. 実行ファイルと同じフォルダにlibconvert100.dll，libconvert100.expをコピーする  
