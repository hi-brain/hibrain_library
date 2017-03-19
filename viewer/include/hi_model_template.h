/* 
 * File:   hi_model_template.h
 * 
 * Method List
 *	void create()
 *		: オブジェクト生成時に呼び出されます．初期化は release() 実行後に呼び出されます．
 *		  モジュール名とパラメータ構造体へのポインタを引数とします．
 *		  パラメータ構造体を別途定義する必要があります．
 * 	void release()
 *		: 停止(OnDeactivated)時に呼び出されます．メモリの開放処理を行う関数
 *  void process()
 *		: 実行(OnExecute)中、input更新後に呼び出されます．outputの更新処理を行う関数
 *  void first_process()
 *		: 実行(OnExecute)中、最初のinputが入力された時にのみ、process実行前に呼び出されます
 *  void show()
 *		: 実行(OnExecute)中、process実行後に呼び出されます．outputの表示などの出力処理を行う関数
 * 
 * Created on 2014/03/14, 18:41
 */

#ifndef HI_MODEL_TEMPLATE_H
#define	HI_MODEL_TEMPLATE_H

namespace hi{
	class VModelBase{
	public:
		VModelBase(){ this->st = true; };
	  	virtual ~VModelBase(){ this->release();}
		virtual void create()=0;
		virtual void first_execute()=0;
		virtual void execute()=0;
		virtual void release(){};
		virtual bool status(){ return this->st; }
	protected:
		bool st;
	};
}

#endif	/* HI_MODEL_TEMPLATE_H */

