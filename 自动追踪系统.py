import sensor, image, time
import json
from pid import PID
from pyb import Servo
import time
from pyb import UART
uart = UART(3, 9600)
red_threshold  = (79, 30, 15, 59, -53, 25)  # (61, 30, 12, 59, -53, 25)
pan_pid = PID(p=4, i=0,d=0.5)
tilt_pid = PID(p=1.5, i=0,d=0.3)
l_max_blob_x=0
ll_max_blob_x=0
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_auto_whitebal(False)     # 设置自动白平衡
sensor.set_brightness(3000)         # 设置亮度为3000
sensor.skip_frames(20)
sensor.set_auto_gain(False)
sensor.skip_frames(20)
sensor.set_auto_exposure(False, exposure_us=40000)
clock = time.clock()
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob
count=0
max_flag=0
while(True):
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs([red_threshold])
    if blobs:
        max_blob = find_max(blobs)
        print(max_blob.cx())
        print(max_blob.cy())
        max_blob_x=max_blob.cx()
        if ll_max_blob_x==l_max_blob_x and l_max_blob_x==max_blob_x:
            max_flag=1
        else:
            ll_max_blob_x=l_max_blob_x
            l_max_blob_x=max_blob_x
            max_flag=0
        if max_blob.cx()<150 and max_blob.cx()>5 and max_blob.cy()<150 and max_blob.cy()>5 and max_flag==1:
            pan_error = -max_blob.cx()+img.width()/2-13
            tilt_error = max_blob.cy()-img.height()/2+4
            img.draw_rectangle(max_blob.rect())
            img.draw_cross(max_blob.cx(), max_blob.cy())
            pan_output=pan_pid.get_pid(pan_error,1)/2
            tilt_output=tilt_pid.get_pid(tilt_error,1)
            pan_output=int(pan_output)
            tilt_output=int(tilt_output)
            if pan_output>100:
                pan_output=100
            if pan_output<-100:
                pan_output=-100
            if tilt_output>150:
                tilt_output=150
            if tilt_output<-150:
                tilt_output=-150
            pan_str = json.dumps(pan_output)
            tilt_str = json.dumps(tilt_output)
            count=count+1
            if  (pan_error<15 and pan_error>-15) or (tilt_error <15 and  tilt_error>-15):
                #print(pan_error)
                #print(tilt_error)
                uart.write('kaihhh')
                time.sleep_ms(70)
            else:
                uart.write('offhhh')
                time.sleep_ms(70)
            if count%2==0:
                print("pan_output",pan_output)
                uart.write('pan'+pan_str+'\n')
                #time.sleep_ms(20)
            else:
                print("tilt_output",tilt_output)
                uart.write('tit'+tilt_str+'\n')
                #time.sleep_ms(20)
