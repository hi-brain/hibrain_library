# libhi_convert

[Hi-brain](http://hi-brain.org)環境下でのモデル実装用ライブラリ群

## 内容
* データフォーマット，データ型の相互変換
 - RTC::CameraImage <-> cv::Mat
 - cv::Mat <-> mwArray
 - Vision::Matrix <-> cv::Mat
* 共有メモリ
* [vmc_builder](https://github.com/ttsasano/HibrainLibrary)

## フォルダ構成
* libhiconvert/
 + include/
   - hi_convert.h
	 - hi_matview.h
	 - hi_matviewer3d.h
	 - hi_model_template.h
	 - hi_viewer_template.h
	 - hi-brain.hh
	 - hi-brain.idl
	 - SharedMemory.h
	 - Timed_cvMat.hh
	 - Timed_cvMat.idl
	 - Timed_cvMatStub.h
 + src
   - hi_convert.cpp
	 - hi_convert_vision.cpp
	 - hi_matviewer.cpp
	 - hi_matviewer3d.cpp
	 - hi_brainDynSK.cc
	 - hi-brainSK.cc
	 - SharedMemory.cpp
	 - Timed_cvMatStub.cpp
 + vmc_builder
 + CMakeLists.txt
 + readme.md

## 動作環境
* OpenCV
* OpenRTM 1.1 64bit  
* (MATLAB Compiler Runtime)

## インストール(例：Ubuntu)
1. ダウンロード
	```
	git clone https://github.com/hi-brain/libhi_convert.git
	cd libhi_convert
  ```
2. ライブラリのインストール
	* MATLAB Compiler Runtime(mwArray)を使用する場合

		事前に環境変数MATLAB_RUNTIME_PATHを追加する必要がある．
		```
		echo -e "MATLAB_RUNTIME_PATH=/usr/local/MATLAB/MATLAB_Runtime/<MATLAB_Runtimeのバージョン>/extern/lib/glnxa64" | tee -a /etc/environment
		cmake .
		make
		sudo make install
  	```
	* MATLAB Compiler Runtime(mwArray)を使用しない場合
		```
		cmake -D USE_MATLAB_RUNTIME=OFF .
		make
		sudo make install
		```

3. vmc_builder(Pythonスクリプト)のインストール
	```
	sudo cp -r vmc_builder /usr/local/
	sudo ln -s /usr/local/vmc_builder/vmc_builder /usr/local/bin/vmc_builder
	```

## 使い方

### ライブラリ

1. CMakeLists.txtのあるディレクトリに移動
		cmake .
		sudo make install

    /usr/local/hi-brain下にヘッダとライブラリが作成される
2. コンポーネントのsrc/CMakeLists.txtを編集する[(参照)](https://github.com/hi-brain/model_format/blob/master/src/CMakeLists.txt)



### VMC-builder
４つのサンプルを同梱.

* usbcamera: usbカメラ(or 内蔵カメラ)からのキャプチャを表示、出力するサンプル
* cv_retina: OpenCVのcv::Retina使用サンプル
* filter3d: 3次元フィルタ処理を行うサンプル
* kernel: filter3dで用いるカーネルサンプル(Sobel, Gabor)


#### サンプルのコピーからコンポーネントの生成と実行まで

	cp -r /usr/local/vmc_builder/samples/usbcamera ./
	cd usbcamera
	vmc_builder -d test usbcamera.yaml
	cd test
	cmake .
	make

実行ファイルは src/vm_usbcameraComp に作成される．
ネームサーバを実行している状態で、作成したコンポーネントを実行すれば、
OpenRTMのシステムエディタでコンポーネント一覧に表示される．
コンポーネントの詳しい使い方については
[Hi-brain](http://hi-brain.org)や[OpenRTM-aist](http://www.openrtm.org/openrtm/ja/)を参照．

### 独自のビューアの作成手順
以下のファイルを参考

* /usr/local/vmc_builder/conf/V_*.yaml
* /usr/local/hi-brain/include/hi_viewer_template.h
* /usr/local/hi-brain/include/hi_matviewer*.h
