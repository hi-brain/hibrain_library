「RTC::CameraImage <-> cv::Mat」，「cv::Mat <-> mwArray」を「>>」および「<<」演算子で相互変換するライブラリ  
  
動作環境    
・OpenCV 2.4.5  
・OpenRTM 1.1 64bit  
・MATLAB Compiler Runtime R2013a 
  
中身  
・ヘッダファイル  
--hi_convert.h  
・ソースファイル  
--hi_convert.cpp  
・ライブラリ  
--libhi_convert.so
--libhi_convert.so.1
--libhi_convert.so.1.0.0
  
使い方(Linux)
1. CMakeLists.txtのあるディレクトリに移動
1.1 cmake .
1.2 sudo make install
/usr/local/hi-brain下にヘッダとライブラリが作成される
2. コンポーネントのsrc/CMakeLists.txtを編集する
以下を参照
https://github.com/hi-brain/model_format/blob/master/src/CMakeLists.txt
  
