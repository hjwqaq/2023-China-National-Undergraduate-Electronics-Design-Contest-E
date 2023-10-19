import sensor, image, time
import json
import pyb
from pyb import UART
from pid import PID

uart = UART(3, 19200)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_auto_whitebal(False)
sensor.set_brightness(3000)
sensor.skip_frames(time = 20)
clock = time.clock()
count=0
la_xa=0
lla_xa=0
llla_xa=0
kp=3.9
kpy=4.9
time.sleep_ms(1000)

while(True):
    clock.tick()
    img = sensor.snapshot()
    for r in img.find_rects(threshold = 10000):
        if r.w() > 10 and r.h() > 10 and r.w() < 100 and r.h() < 100:
            img.draw_rectangle(r.rect(), color = (255, 0, 0), scale = 4)
            xa=r.corners()[2][0]
            ya=r.corners()[2][1]
            xb=r.corners()[1][0]
            yb=r.corners()[1][1]
            xc=r.corners()[0][0]
            yc=r.corners()[0][1]
            xd=r.corners()[3][0]
            yd=r.corners()[3][1]
            print(xa,ya,xb,yb,xc,yc,xd,yd)
            if la_xa==xa and lla_xa==la_xa and llla_xa==lla_xa and r.w()<57 and r.h()<57:
                print(r.corners())
                xa=1100-(r.corners()[2][0]-100)*kp
                xb=1100-(r.corners()[1][0]-100)*kp
                xc=1100-(r.corners()[0][0]-100)*kp
                xd=1100-(r.corners()[3][0]-100)*kp
                if ya<25:
                    ya=1291+(r.corners()[2][1]-52)*kpy
                    yd=1291+(r.corners()[3][1]-52)*kpy
                    yb=1291+(r.corners()[1][1]-52)*kpy
                    yc=1291+(r.corners()[0][1]-52)*kpy
                else:
                    ya=1291+(r.corners()[2][1]-55)*kpy
                    yd=1291+(r.corners()[3][1]-55)*kpy
                    yb=1291+(r.corners()[1][1]-55)*kpy
                    yc=1291+(r.corners()[0][1]-55)*kpy

                xa_str = json.dumps(xa)
                ya_str = json.dumps(ya)
                xb_str = json.dumps(xb)
                yb_str = json.dumps(yb)
                xc_str = json.dumps(xc)
                yc_str = json.dumps(yc)
                xd_str = json.dumps(xd)
                yd_str = json.dumps(yd)
                count=count+1
                uart.write('xa' + xa_str + '\n')
                time.sleep_ms(50)
                uart.write('ya' + ya_str + '\n')
                time.sleep_ms(50)
                uart.write('xb' + xb_str + '\n')
                time.sleep_ms(50)
                uart.write('yb' + yb_str + '\n')
                time.sleep_ms(50)
                uart.write('xc' + xc_str + '\n')
                time.sleep_ms(50)
                uart.write('yc' + yc_str + '\n')
                time.sleep_ms(50)
                uart.write('xd' + xd_str + '\n')
                time.sleep_ms(50)
                uart.write('yd' + yd_str + '\n')
                time.sleep_ms(50)
            else:
                llla_xa=lla_xa
                lla_xa=la_xa
                la_xa=xa