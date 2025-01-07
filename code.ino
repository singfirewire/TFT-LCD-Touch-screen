#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Servo.h>

// Pin definitions for the Touch Screen
#define YP A2  // must be an analog pin
#define XM A3  // must be an analog pin
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

// Touch Screen calibration
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Motor pins for dispensing
#define MOTOR1_PIN 2  // ปากกาดำ
#define MOTOR2_PIN 3  // ปากกาแดง
#define MOTOR3_PIN 4  // ปากกาน้ำเงิน

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

// Colors
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GRAY    0x8410

// Product structure
struct Product {
    String name;
    int price;
    int stock;
    int motorPin;
    int x;
    int y;
    int width;
    int height;
};

// Initialize objects
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Servo motors[3];

// Products array
Product products[] = {
    {"Black Pen", 15, 10, MOTOR1_PIN, 30, 100, 260, 80},
    {"Red Pen", 15, 10, MOTOR2_PIN, 30, 200, 260, 80},
    {"Blue Pen", 15, 10, MOTOR3_PIN, 30, 300, 260, 80}
};

int currentMoney = 0;
int selectedProduct = -1;

void setup() {
    Serial.begin(9600);
    
    // Initialize screen
    tft.reset();
    uint16_t identifier = tft.readID();
    tft.begin(identifier);
    tft.setRotation(0);
    
    // Initialize motors
    for(int i = 0; i < 3; i++) {
        motors[i].attach(products[i].motorPin);
        motors[i].write(90);  // Initial position
    }
    
    drawMainScreen();
}

void loop() {
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // Restore pins that are used for touch sensing
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // Map touch coordinates
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, SCREEN_WIDTH);
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, SCREEN_HEIGHT);
        
        // Check for button presses
        checkProductSelection(p.x, p.y);
        checkMoneyButtons(p.x, p.y);
    }
}

void drawMainScreen() {
    tft.fillScreen(BLACK);
    tft.setTextSize(2);
    
    // Draw title
    tft.setTextColor(WHITE);
    tft.setCursor(50, 20);
    tft.print("Vending Machine");
    
    // Draw product buttons
    for(int i = 0; i < 3; i++) {
        drawProduct(products[i]);
    }
    
    // Draw money section
    drawMoneySection();
}

void drawProduct(Product product) {
    tft.drawRect(product.x, product.y, product.width, product.height, WHITE);
    tft.setCursor(product.x + 10, product.y + 20);
    tft.setTextColor(WHITE);
    tft.print(product.name);
    tft.setCursor(product.x + 10, product.y + 45);
    tft.print(String(product.price) + " THB");
    tft.setCursor(product.x + 180, product.y + 45);
    tft.print("x" + String(product.stock));
}

void drawMoneySection() {
    tft.fillRect(30, 400, 260, 60, GRAY);
    tft.setCursor(50, 420);
    tft.setTextColor(BLACK);
    tft.print("Money: ");
    tft.print(currentMoney);
    tft.print(" THB");
}

void checkProductSelection(int x, int y) {
    for(int i = 0; i < 3; i++) {
        if (x > products[i].x && x < (products[i].x + products[i].width) &&
            y > products[i].y && y < (products[i].y + products[i].height)) {
            if (products[i].stock > 0 && currentMoney >= products[i].price) {
                dispenseProduct(i);
                currentMoney -= products[i].price;
                products[i].stock--;
                drawMainScreen();
            } else {
                // Show error message
                tft.fillRect(30, 350, 260, 30, RED);
                tft.setCursor(40, 360);
                tft.setTextColor(WHITE);
                if (products[i].stock <= 0) {
                    tft.print("Out of stock!");
                } else {
                    tft.print("Insufficient funds!");
                }
                delay(2000);
                tft.fillRect(30, 350, 260, 30, BLACK);
            }
        }
    }
}

void dispenseProduct(int productIndex) {
    // Rotate servo to dispense product
    motors[productIndex].write(180);  // Rotate to dispense
    delay(1000);
    motors[productIndex].write(90);   // Return to original position
}

void checkMoneyButtons(int x, int y) {
    // Add money buttons (simplified for demo)
    if (y > 400 && y < 460) {
        if (x > 30 && x < 150) {
            currentMoney += 5;  // Add 5 baht
        } else if (x > 160 && x < 280) {
            currentMoney += 10; // Add 10 baht
        }
        drawMoneySection();
    }
}
