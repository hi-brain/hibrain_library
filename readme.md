# HibrainLibrary

[Hi-brain](http://hi-brain.org)環境下でシミュレート可能なコンポーネント作成支援ツール．

テンプレートクラスを元に各メソッドを実装したモデルソース(C++)と、YAML形式の設定ファイルを作成し、
vmc_builder(Python script)を実行することで即Make可能なコンポーネントソース群を生成する．


## インストール(例：Ubuntu)
### ダウンロード

	git clone https://github.com/ttsasano/HibrainLibrary
	cd HibrainLibrary

### C++ライブラリのインストール

	cmake .
	make
	sudo make install

### vmc_builder(Pythonスクリプト)のインストール

	sudo cp -r vmc_builder /usr/local/
	sudo ln -s /usr/local/vmc_builder/vmc_builder /usr/local/bin/vmc_builder
	
## 使い方
４つのサンプルを同梱している．

* usbcamera: usbカメラ(or 内蔵カメラ)からのキャプチャを表示、出力するサンプル
* cv_retina: OpenCVのcv::Retina使用サンプル
* filter3d: 3次元フィルタ処理を行うサンプル
* kernel: filter3dで用いるカーネルサンプル(Sobel, Gabor)

### サンプルのコピーからコンポーネントの生成と実行まで

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

### 独自のコンポーネント作成手順
未作成．サンプルを参考にして下さい．

### vmc_builderの設定ファイル(YAMLファイル)の仕様
未作成．サンプルを参考にして下さい．

### 独自のビューアの作成手順
未作成．以下のファイルを参考にして下さい．

* /usr/local/vmc_builder/conf/V_*.yaml
* /usr/local/hi-brain/include/hi_viewer_template.h
* /usr/local/hi-brain/include/hi_matviewer*.h
