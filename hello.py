from flask import Flask, render_template,request, url_for, redirect            # 플라스크 모듈 호출
from picamera import PiCamera
from time import sleep

import serial
arduino = serial.Serial('/dev/ttyACM0', 9600)

name =0
img_name="image/IMG_0234.JPG"

app = Flask(__name__)               # 플라스크 앱 생성        

@app.route('/')                     # 기본('/') 웹주소로 요청이 오면                     
def home():                        #hello 함수 실행
    global img_name
    return render_template('index.html',imgname=img_name)

@app.route('/capture')                               
def capture():                                    
    global name
    global img_name
    camera = PiCamera()             #카메라 객체 생성
    img_name = 'image/picture'+str(name)+'.JPG'
    camera.capture('/home/pi/midHW/static/'+img_name)     #사진을 찍어서 static/image/picture.jpg로 저장
    sleep(1) 
    #// 2초간 대기
    arduino.write(b'1')
    arduino.write(b'thanks')
    camera.close()
    name= name+1
    return redirect(url_for('home',imgname=img_name ))                           


@app.route('/lcd', methods=["GET", "POST"])                               
def lcd( ):                                    
    global img_name
    state =request.form['lcd']
    print(state)
    arduino.write(b'2')
    arduino.write(state.encode())

    return redirect(url_for('home',imgname=img_name ))                           

@app.route('/segment', methods=["GET", "POST"] )                               
def segment():                                    
    global img_name
    state =request.form['segment']
    print(state)
    arduino.write(b'3')
    arduino.write(state.encode())


    return redirect(url_for('home',imgname=img_name ))                           


if __name__ == '__main__':          # 현재 파일 실행시 개발용 웹서버 구동
    app.run(debug=True, port=8080, host='0.0.0.0')
