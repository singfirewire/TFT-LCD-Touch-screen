ระบบขายสินค้าอัตโนมัติที่ใช้จอ TFT LCD แบบ Touch screen

โค้ดนี้เป็นตัวอย่างระบบขายสินค้าอัตโนมัติที่มีคุณสมบัติดังนี้:

1. หน้าจอแสดงผล:
- แสดงรายการสินค้า 3 รายการ (ปากกาดำ, แดง, น้ำเงิน)
- แสดงราคาและจำนวนสินค้าคงเหลือ
- มีส่วนแสดงจำนวนเงินที่ใส่

2. การทำงาน:
- ใช้จอ TFT LCD แบบสัมผัส
- ใช้ Servo motor ในการจ่ายสินค้า
- มีระบบตรวจสอบเงินและสินค้าคงเหลือ
- แสดงข้อความแจ้งเตือนเมื่อเงินไม่พอหรือสินค้าหมด

3. สิ่งที่ต้องเพิ่มเติม:
- ระบบทอนเงิน
- ระบบบันทึกการขาย
- ระบบแจ้งเตือนเมื่อสินค้าใกล้หมด
- ระบบรับธนบัตร/เหรียญจริง

อุปกรณ์ที่ต้องใช้:
1. Arduino MEGA (แนะนำเพราะมีหน่วยความจำมากพอ)
2. จอ TFT LCD แบบ Touch Screen
3. Servo motor สำหรับกลไกจ่ายสินค้า
4. สายไฟและอุปกรณ์ประกอบ

Library ที่ต้องติดตั้ง:
1. MCUFRIEND_kbv
2. Adafruit_GFX
3. TouchScreen
