import smbus
import time

# 設定樹莓派I2C的總線
bus = smbus.SMBus(1)

# 設定Arduino 的I2C位置
address = 0x04

# 傳送訊息
def writeNumber(value):
    bus.write_byte(address, value)
    return -1

# 讀取訊息
def readNumber():
    number = bus.read_byte(address)
    return number

while True:
    # 指定var接受使用者輸入的指令
    var = int(input('Enter 1 – 9: '))
    
    #寫入使用的輸入的指令Var
    writeNumber(var)
    print ('RPI: Hi Arduino, I sent you ', var)
    
    # 等待1秒
    time.sleep(1)
    
    #接收Arduino回傳的訊息
    number = readNumber()
    print ('Arduino: Hey RPI, I received a digit ', number)