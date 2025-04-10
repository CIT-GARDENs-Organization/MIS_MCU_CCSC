# ライブラリ仕様書 `mission_tools`

## 1. 概要
このライブラリは、MIS MCUにおけるmissionライブラリが使用可能な機能を提供する

## 2. 関数一覧
「<span style="color:red;">+</span>」: 外部ファイルからアクセス可能な関数<br>
「<span style="color:blue;">-</span>」: 内部専用関数

1. <span style="color:red;">+</span>void check_and_respond_to_boss()
2. <span style="color:red;">+</span>void executed_mission_pop();
3. <span style="color:red;">+</span>int1 req_use_smf()
4. <span style="color:red;">+</span>void finished_use_smf();
5. <span style="color:red;">+</span>void enqueue_smf_data(unsigned int32 dest, unsigned int32 src, unsigned int32 size)
6. <span style="color:red;">+</span>void continue_mis_mcu(int16 duration_second)


## 3. 関数詳細
### 1. check_and_respond_to_boss

**概要**  
BOSS PICからのコマンドの有無の判定と、受信していた場合の返信を行う
**最低でもミッション実行中に5秒以内毎に実行されなければならない**

**引数**
無し

**戻り値**  
`void`

**副作用**  
- BOSS PICとの通信

---

### 2. executed_mission_pop

**概要**  
一度のMIS MCUの起動中に同じミッションを複数回実行したい場合、この関数をそのミッション内で一度使用する。

**引数**
無し

**戻り値**  
`int1`

**副作用**  
無し

---

### 3. req_use_smf

**概要**  
SMFの使用要求をBOSS PICに送信する

**引数**
無し


**戻り値**  
`int1`

**副作用**  
- BOSS PICとの通信
- 変数`status`の操作

---

### 4. finished_use_smf

**概要**  
SMFの使用を終了したときに使用する

**引数**
無し

**戻り値**  
`void`

**副作用**  
- 変数`status`の操作

---

### 5. enqueue_smf_data

**概要**  
各MIS MCUの持つフラッシュメモリーのデータをSMFにコピーするために、その情報をキューに格納する

**引数**
| 引数名 | 型 | 説明 |
| - | - | - |
| `dest` | `unsigned int32` | SMFの保存先のアドレス<br>0x00000000 ~ 0x0EE6B280(2Gbit)を網羅する |
| `src` | `int32` | 各MIS MCUが持つFMの保存元のアドレス<br>0x00000000 ~ 0x01000000(128Mbit)を網羅する |
| `size` | `int32` | コピーするデータバイト数<br>0x00000000 ~ 0x01000000(128Mbit)を満足する |

**戻り値**  
`void`

**副作用**  
- `smf_data`の操作

---

### 6. continue_mis_mcu

**概要**  
MIS MCUがミッション終了後、引数の秒数の起動を保証する

**引数**

| 引数名 | 型       | 説明                       |
| ------ | -------- | -------------------------- |
| `duration_second` | `int16`    | ミッション終了後に起動を保証する秒数　|

**戻り値**  
`void`

**副作用** 
- `duration_sec`の操作