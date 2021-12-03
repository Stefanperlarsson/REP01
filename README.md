# REP01

所属：京都コンピュータ学院情報処理科

作成者：ラーション・ステファン、学生番号：E20C4033

Git：https://github.com/Stefanperlarsson/REP01

---
## 概要

* [ 外部仕様 ](#specifications)
* [ 内部設計・プログラムの詳細 ](#design)
* [ 流れ ](#flowchart)
* [ 特徴 ](#notes)
* [ 関数の説明 ](#functions)
* [ テスト方法 ](#testing)
* [ まとめ ](#summary)

---
## 外部仕様
<a name="specifications"></a>
C言語でプログラミングしたアドレス帳を作っていました。

端末を使用して、アドレスを追加したり、挿入したり、色々な機能が含めています。

機能として、これはできます：
* 一覧　ー　追加したアドレスを全部出力
* 詳細　ー　あるアドレスをemailで探して細かい情報を出力
* 新規登録　ー　新しいアドレスを追加
* 削除　ー　アドレスを探して消す
* 挿入　ー　アドレスをemailで探して挿入
* 移動　ー　アドレスをemailで探して先頭に移動
* 編集　ー　アドレスをemailで探して編集
* 保存　ー　終了する時に、アドレスを全部XMLファイルで保存されて、起動する時に読み込む

---
## 内部設計・プログラムの詳細
<a name="design"></a>

### 流れ <a name="flowchart"></a>
<img src="REP01.png" width="720">

### 特徴 <a name="notes"></a> - 必修なところ以外では、自分で頑張ってテップアップしました。
* ファイルで保存・読み込み
* 入力確認

### 関数の説明 <a name="functions"></a>

| ファイル名     | 関数名       | 引数              | 戻り値       | 説明                         |
| ------------ | ------------ | ---------------- | ----------- | --------------------------- |
| REP01.c      |              |                  |             |                             |
|              | main         | （なし）          | int         | メイン                        |
| address.c    |              |                  |             |                             |
|              | printAll     | List *pHead      | （なし）     | 全部のアドレスを出力            |
|              | print        | List *pHead      | （なし）     | アドレスを細かくて出力          |
|              | add          | List *pHead      | （なし）     | アドレスを追加                 |
|              | insert       | List *pHead      | （なし）     | アドレスを挿入                 |
|              | move         | List *pHead      | （なし）     | アドレスを削除                 |
|              | edit         | List *pHead      | （なし）     | アドレスを編集                 |
|              | destroyAll   | List *pHead      | （なし）     | 全部のアドレスを削除            |
|              | destroy      | List *pHead      | （なし）     | アドレスを削除                 |
|              | find         | List *pHead      | List *      | emailでアドレスを検索          |
|              | new          | List *node       | （なし）     | アドレス入力                   |
| input.c      |              |                  |             |                              |
|              | string_input | char *c, int s   | char *      | 文字型入力                    |
|              | int_input    | （なし）          | int         | メニュー入力                   |
|              | clear        | （なし）          | （なし）     | インプットバッファを消す         |
| io.c         |              |                  |             |                             |
|              | write        | List *pHead      | （なし）     | アドレスをXMLファイルで保存      |
|              | read         | List *pHead      | int         | アドレスをXMLファイルから読み込む |
| validation.c |              |                  |             |                              |
|              | is_email     | char *           | int         | emailをregexpで確認            |
|              | is_empty     | char *           | int         | 空のstring確認                 |

---
## テスト方法 <a name="testing"></a>
### 必要なパケージ
* libxml2-dev (debian)

#### コンパイル
```bash
gcc `xml2-config --cflags` REP01.c address.c input.c io.c validation.c -o REP01 `xml2-config --libs`;
```

#### 実行
```bash
./REP01;
```

#### 使い方（例）
メニュー
```bash
Ｃ言語実習２　アドレス帳　E20C4033　ラーション・ステファン
7のアドレスを読み込んだ

1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：(これからメニュー入力)
```

新規登録と入力確認
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：3
名前：Stefan Larsson
住所：My address 123, kyoto
電話番号：098-1234-1234 
eメールアドレス：test
eメール書き直してください。例：xxx@xxx.com

eメールアドレス：myemail@gmail.com
```

一覧
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：1

一覧
* hello5@email.com
* myemail@gmail.com
```

詳細
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：2
検索(email):myemail@gmail.com

eメールアドレス：myemail@gmail.com
名前：Stefan Larsson
住所：My address 123, kyoto
電話番号：098-1234-1234
```

削除と入力確認
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：4
検索(email):hello5
hello5：存在してない

1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：4
検索(email):hello5@email.com
```

挿入
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：5
検索(email):myemail@gmail.com
名前：Stefan Per Larsson
住所：Shin-osaka, osaka
電話番号：123-4567-0293
eメールアドレス：mynewemailagain@gmail.com
```

移動
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：6
検索(email):mynewemailagain@gmail.com
```

編集
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：7
検索(email):myemail@gmail.com
名前：Stefan Larsson new
住所：New address
電話番号：080-1236-1203  
eメールアドレス：anotheremail@gmail.com
```

終了
```bash
1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 7)編集 0)終了
：0
```

---
## まとめ <a name="summary"></a>
### 印象
結構すごくいい経験だと思っていました。

「Ｃ言語実習２」を始まる前に、あまりC言語の経験がありませんでした。

得にアドレスのことやポインターの知識が将来でも役に立てるはずだと思っています。

来年の４月、ある会社に入社予定ですが、C言語使ってないけれど、Golang使用していますので、この知識は使えます！

### 改良の余地
* 変数名はもうちょっとまとめたほうが良い
* next/previousを繋がう時のコードはちょっと読み辛い
