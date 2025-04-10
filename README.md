<div align="center">
    <img src="https://github.com/user-attachments/assets/099b80dd-a6a5-4a14-940f-06401dadf024" width="200" alt="GARDENs logo" />
   <h1>MIS MCU Source code(CCS C)</h1>
</div>

## 概要  
本リポジトリは、GARDENsのMIS MCU(PIC)に実装するソースコードの基盤を提供するものである。
これを基に各ミッションへ派生させることによる以下の実現を目的とする。

- **開発効率の向上**  
- **担当領域の明確化**  
- **統一された挙動による試験・運用の円滑化**  

---

## ファイル構成
```
./
├─ README.md
│
├─ main.c
│
├─ main.ccspjt
│
├─ docs
│  ├─ development.md
│  ├─ design.md
│  ├─ library_communication_mis_mcu.md
│  ├─ library_communication.md
│  ├─ library_mission_tools.md
│  └─ library_mission.md
│
└─ lib
   ├─ src
   │  ├─ communication_mis_mcu.c
   │  ├─ communication.c
   │  ├─ data_copy.c
   │  ├─ mission_tools.c
   │  └─ mission.c
   │
   ├─ 18F67J94.h
   ├─ communication_mis_mcu.h
   ├─ communication.h
   ├─ config.h
   ├─ data_copy.h
   ├─ define.h
   ├─ mission_tools.h
   ├─ mission.h
   ├─ typedef.h
   └─ value.h
```
- ミッション開発時は`development.md`を読むこと
- ソフトウェアの設計は`design.md`に示している
   - ライブラリの設計は各`library_XXX.md`に示している