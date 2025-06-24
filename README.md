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
├─ config.h
│
├─ mission.c
├─ mission.h
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
   │  ├─ communication.c
   │  ├─ communication_driver.c
   │  ├─ data_copy.c
   │  ├─ flash.c
   │  ├─ mission_tools.c
   │  ├─ smf_queue.c
   │  ├─ timer.c
   │  └─ uart.c
   │
   ├─ 18F67J94.h
   ├─ communication.h
   ├─ communication_driver.h
   ├─ data_copy.h
   ├─ flash.h
   ├─ mission_tools.h
   ├─ timer.h
   ├─ typedef_content.h
   ├─ uart.h
   └─ value_status.h
```
- ミッション開発時は[`mission_development.md`](https://github.com/CIT-GARDENs-Organization/MIS_MCU_CCSC/blob/main/docs/mission_development.md)を読むこと
- ソフトウェアの設計は[`design.md`](https://github.com/CIT-GARDENs-Organization/MIS_MCU_CCSC/blob/main/docs/design.md)に示している
   - ライブラリの設計は各`library_XXX.md`に示している
