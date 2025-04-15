
# ミッションの開発方法


## 手順
1. 初期設定
  - `config.h`
    - **`#pin_select`** → それぞれ適切なものに変更する
    - **`#use`** → それぞれ適切なものに変更する
  
  - `define.h` **24行目** → `#SELF_DEVICE_ID` を、14 ~ 25行目の定数の中から適切なものに選択する。

2. ミッションの実装
  - `missoin.h` **20行目以降** → 実装するミッションの関数名を記入する。返り値は`void`、引数は`(unsigned int8 parameter[])`である。
  - `mission.c` **40行目** → 先程の関数をswitch-caseの中に追記する。
  - `mission.c` **97行目** → 先程の関数の実装をする。

## シミュレーター
- 本ソフトは以下のソフトと併用することで実際のBOSS PICとの通信からミッション実行、終了までの動作をシミュレーションできる
- 本ソフトは擬似的にすでに3つのミッションが実装されているため実際に実行して動作理解を深めてから実装に入るとよい

[BOSS PIC simulater](https://github.com/CIT-GARDENs-Organization/BOSS_PIC_simulator)

| CMD ID     | 使用パラメーター         | 説明                                         |
|:-----------|:------------            |:------------                                |
| 00         | なし | 5秒待機し、SMFへコピーするデータを生成する                                 |
| 01         | なし | 5秒待機する                   |
| 02         | なし | 最初にSMFへアクセスし、10秒秒待機する  |


---

## 制約 & その他  

### **⚠️必ず守らなければならないこと**
- ミッション実行中において、最低5秒に1回は`void check_and_respond_to_boss()`という**関数を呼ぶこと**
  - ミッション実行中、BOSS PICからstatus checkフレームが来たかどうかの判定とそれに対する返信をこの関数で行う。
  - できれば1秒、2秒以内が好ましい

### **⭕️許可されていること**
- 新規ファイル作成
- 新規関数作成

## **mission.c内で使用可能な関数一覧**
### 一覧
- `void check_and_respond_to_boss()`
- `void enqueue_smf_data(SmfDataStruct *data)`
- `int1 req_use_smf()`
- `void finished_use_smf()`
- `void executed_mission_pop()`
- `void continue_mis_mcu(int16 duration_second)`
- その他`flash.h`に定義されている関数

### 説明
- BOSS PICとの通信
  - `void check_and_respond_to_boss()`を実行する
  - この関数は、BOSS PICからのコマンドの有無の判定と、受信していた場合の返信を行う
  - **最低でもミッション実行中に5秒以内毎に実行されなければならない**

- SMFへのデータコピー
  - `void enqueue_smf_data(SmfDataStruct *data)`を実行する
  - 例
  ```c
  SmfDataStruct data;
  data.dest = 0x00000000; // コピー先のSMFのアドレス
  data.src = 0x00000000; // コピー元のMIS_FMのアドレス
  data.size = 0x00000000; // コピーするデータのサイズ
  enqueue_smf_data(&data); // SMFへのデータコピーを実行する
  ```
- SMFの利用(読み取りのみなど)
  - `int1 req_use_smf()`を実行すること
    - この関数は、次回BOSS PICからstatus checkが来た時にSMFの使用要求を送り、使用の可否を返り値として返す。
    - 使用可能な場合、`TRUE`が返ってくる 
    - 使用不可の場合、`FALSE`が返ってくる
    - 現在は例外処理として10分間この関数が実行されると`FALSE`を返すようにしている。
    - 何度実行しても構わない
  - **SMFの使用終了後は必ず`void finished_use_smf()`を実行すること。**


- ミッション連続実行系
  - `void executed_mission_pop()`
    - MIS MCUは、地上局からの連続アップリンクで誤動作しないようにするため同じミッションをその機器の起動中に実行しないようにしている
    - そのため、同じミッションを連続で実行したい場合はこの関数を実行する必要がある
  - `void continue_mis_mcu(int16 duration_second)`
    - ミッション終了後、SMFのキューの中身がなくてもMIS MCUを起動させておくための関数
    - 引数に指定した秒数だけMIS MCUを起動させることができる

---


## 今後の更新予定 (作業担当者: GARDENs)
1. SMFへのコピー機能の実装
   - 現在はprint出力でSMFへのコピーを模しているが、今後実際に機能を開発し統一されたSMFへのコピー機能を搭載する。