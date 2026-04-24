# H-Bridge Driver Truth Table

這是一份關於馬達驅動器（如 TB6612）輸入與輸出動作的實測記錄表。

| AIN1 | AIN2 | STBY | PWM | 馬達動作 (Motor Action) | 物理現象描述 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| H | L | H | 255 | 正轉 (Forward) | |
| L | H | H | 255 | 反轉 (Reverse) | |
| H | H | H | 0 | 急煞 (Short Brake) | |
| L | L | H | 0 | 空轉 (Coast) | |
| X | X | L | X | 待機 (Standby) | |

## 實驗筆記

1. **(H, H) 短路煞車原理**：當兩個輸入端皆為高電位時，馬達內部的反向電動勢會產生一個阻礙運動的力。
2. **空轉 vs 煞車**：在實驗中觀察到的停止滑動距離差異...
